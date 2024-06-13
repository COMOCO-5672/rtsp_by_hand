#pragma once

#include <cstdint>
#include <string>
#include "Socket.h"

namespace TCP {
    class TcpSocket
    {
    public:
        TcpSocket(SOCKET sockfd = 0);
        virtual ~TcpSocket();

        SOCKET Create();
        bool Bind(std::string ip, uint16_t port);
        bool Listen(int backlog);
        SOCKET Accept();
        bool Connect(std::string ip, uint16_t port, int time_out = 0);
        void Close();
        void ShutDownWrite();
        SOCKET GetSocket() const { return m_sockfd_; }

    private:
        SOCKET m_sockfd_ = -1;
    };
}