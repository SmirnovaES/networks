//
// Created by elena on 14.11.2019.
//

#include "Station.h"

#include <iostream>
#include <cmath>
#include <thread>

namespace
{
    void yield() {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start + Network::getTact();
        do {
            std::this_thread::yield();
        } while (std::chrono::high_resolution_clock::now() < end);
    }

    void log_time(char station, double seconds) {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Station " << station << " started sending frame in " << seconds * 1000000.0 << " mcs\n";;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start = std::chrono::high_resolution_clock::now();
}

void Station::startCollisionResolution() {
    ++m_attempt;
    int L = rand() % (int)(pow(2, m_attempt) - 1);
    for (int i = 0; i < L; ++i)
    {
        yield();
    }
}

//I'm not sure that all stations will detect collision if only one byte will be sent
void Station::sendJam()
{
    for (size_t i = 0; i < m_frame.size(); ++i)
    {
        Network::get().sendByte(FRAME_BROKEN);
        yield();
    }
}

void Station::sendMessage() {
    for (int i = 0; i < FRAMES_IN_MESSAGE; ++i)
    {
        bool isFrameSent = true;

        while(Network::get().isBusy())
        {
            yield();
        }

        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - m_start;
        log_time( m_seqNum, diff.count() );
        for (size_t j = 0; j < m_frame.size(); ++j)
        {
            Network::get().sendByte(m_frame[j]);
            yield();

            char newCh = Network::get().getCurrentByte();
            if (newCh != m_frame[j])
            {
                sendJam();
                startCollisionResolution();
                isFrameSent = false;
                break;
            }
        }
        if (isFrameSent)
        {
            m_attempt = 0; // new frame - new attempts
            yield(); //so one station won't seize network
        }
        else
        {
            --i; //try to send frame again
        }
    }
}
