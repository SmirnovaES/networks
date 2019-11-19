//
// Created by elena on 14.11.2019.
//

#ifndef NETWORKS_STATION_H
#define NETWORKS_STATION_H

#include "Network.h"

#include <array>
#include <chrono>
#include <iostream>
#include <sstream>

class Station {
  public:
    explicit Station( char seqNum ):
    m_seqNum( seqNum ), m_attempt(0) {
        m_frame.fill( seqNum );
    }

    void sendMessage();

    void startCollisionResolution();
    void sendJam();

  private:
    char m_seqNum; //station number
    std::array<char, FRAME_SIZE> m_frame; //frame to send

    int m_attempt; //collision resolution attempt
};

#endif //NETWORKS_STATION_H
