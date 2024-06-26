#include "TcpSocket.h"
#include "Socket.h"

namespace TCP {
TcpSocket::TcpSocket(SOCKET sockfd) : m_sockfd_(sockfd) {}

TcpSocket::~TcpSocket() {}

SOCKET TcpSocket::Create()
{
    m_sockfd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    return m_sockfd_;
}

bool TcpSocket::Bind(std::string ip, uint16_t port)
{
    struct sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);

    if (::bind(m_sockfd_, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        return false;
    }

    return true;
}

bool TcpSocket::Listen(int backlog)
{
    if (::Listen(m_sockfd_, backlog) == SOCKET_ERROR) {
        return false;
    }

    return true;
}

SOCKET TcpSocket::Accept()
{
    struct sockaddr_in addr = {0};
    socklen_t addrlen = sizeof(addr);

    SOCKET socket_fd = ::accept(m_sockfd_, (struct sockaddr*)&addr, &addrlen);
    return socket_fd;
}

bool TcpSocket::Connect(std::string ip, uint16_t port, int time_out)
{
    
}
} // namespace TCP
