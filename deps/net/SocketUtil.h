#include "Socket.h"
#include <string>

namespace Socket_Util {
class SocketUtil {
  public:
    static bool Bind(SOCKET sockfd, std::string ip, uint16_t port);
    static void SetNonBlock(SOCKET fd);
    static void SetBlock(SOCKET fd, int write_timeout = 0);
    static void SetReuseAddr(SOCKET fd);
    static void SetReusePort(SOCKET fd);
    static void SetNoDelay(SOCKET fd);
    static void SetKeepALive(SOCKET fd);
    static void SetNoSigPipe(SOCKET fd);
    static void SetSendBufSize(SOCKET fd, int size);
    static void SetRecvBufSize(SOCKET fd, int size);
    static std::string GetPeerIp(SOCKET fd);
    static std::string GetSocketIp(SOCKET fd);
    static int GetSocketAddr(SOCKET fd, struct sockaddr_in* addr);
    static uint16_t GetPeerPort(SOCKET fd);
    static int GetPeerAddr(SOCKET fd, struct sockaddr_in* addr);
    static void Close(SOCKET fd);
    static bool Connect(SOCKET fd, std::string ip, uint16_t port, int time_out = 0);
};

} // namespace Socket_Util
