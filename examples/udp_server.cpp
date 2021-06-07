#include <iostream>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <ws2tcpip.h>
#elif defined(UNIX)
typedef int SOCKET; // Windows uses a typedef called SOCKET as well
#define INVALID_SOCKET -1
#define closesocket(s) close(s)
#else
#error INL is not supported on this platform
#endif

#include "inl.hpp"

#define PACKET_SIZE 2048

using inl::core::UdpListener;
using inl::core::UdpPacket;

static char* get_ip_str(const struct sockaddr* sa, char* s, size_t maxlen)
{
    switch (sa->sa_family) {
    case AF_INET:
        inet_ntop(AF_INET, &(((struct sockaddr_in*)sa)->sin_addr), s, maxlen);
        break;
    case AF_INET6:
        inet_ntop(
            AF_INET6, &(((struct sockaddr_in6*)sa)->sin6_addr), s, maxlen);
        break;
    default:
        strncpy(s, "Unknown AF", maxlen);
        return NULL;
    }

    return s;
}

int main()
{
    UdpListener server(8080);
    UdpPacket packet;
    char str_data[PACKET_SIZE + 1] = { 0 };
    char ip[256] = { 0 };

    std::cout << "Listening for incoming UDP packets. (You can use ncat -vv "
                 "localhost 8080 -u)"
              << std::endl;
    while (true) {
        packet = server.recv(PACKET_SIZE);
        memcpy(str_data, packet.data.data(), packet.size);
        std::cout << "Data received from "
                  << get_ip_str((const sockaddr*)&packet.addr, ip, 256) << " : "
                  << str_data << std::endl;
        memset(str_data, '\0', PACKET_SIZE + 1);
        memset(ip, '\0', 256);
    }
    return 0;
}
