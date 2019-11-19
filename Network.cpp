//
// Created by elena on 14.11.2019.
//

#include "Network.h"

char Network::getCurrentByte() {
    return m_buf;
}

void Network::sendByte(char byte) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_lastSent = std::chrono::high_resolution_clock::now();

    m_buf = byte;
}

bool Network::isBusy() {
    return std::chrono::high_resolution_clock::now() - m_lastSent <= getTact();
}
