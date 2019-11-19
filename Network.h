//
// Created by elena on 14.11.2019.
//

#ifndef NETWORKS_NETWORK_H
#define NETWORKS_NETWORK_H

#include <vector>
#include <set>
#include <chrono>
#include <mutex>

#define FRAME_BROKEN 'b'
#define FRAME_SIZE 8
#define FRAMES_IN_MESSAGE 5

class Network {
  public:
    char getCurrentByte();
    void sendByte( char byte );
    bool isBusy();

    static Network & get()
    {
        static Network instance;
        return instance;
    }

    static std::chrono::nanoseconds getTact()
    {
        static std::chrono::nanoseconds tact(51200);
        return tact;
    }

  private:
    Network(): m_buf(FRAME_BROKEN), m_lastSent(std::chrono::high_resolution_clock::now()) {}

  private:
    char m_buf;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastSent;
    std::mutex m_mutex;
};

#endif //NETWORKS_NETWORK_H
