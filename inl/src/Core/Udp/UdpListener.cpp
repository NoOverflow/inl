/*
** EPITECH PROJECT, 2021
** inl
** File description:
** UdpListener
*/

#include <cstring>

#include "Core/Udp/UdpListener.hpp"
#include "Core/exceptions/InlCoreException.hpp"

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
typedef int socklen_t;
#elif __linux__
typedef int SOCKET; // Windows uses a typedef called SOCKET as well
#define INVALID_SOCKET -1
#define closesocket(s) close(s)
#include <arpa/inet.h>
#include <netdb.h> /* gethostbyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> /* close */
#else
#error INL is not supported on this platform
#endif

namespace inl {
namespace core {

    UdpListener::UdpListener(unsigned short port)
        : m_internal_socket(SocketType::UDP)
    {
        struct sockaddr_in si_me;

        this->m_port = port;
        memset((char*)&si_me, 0, sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons(port);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(
                this->m_internal_socket.get_internal_socket(),
                (const sockaddr*)&si_me, sizeof(si_me))
            == -1) {
            throw("Couldn't bind UDP server to provided port.");
        }
    }

    UdpListener::~UdpListener()
    {
    }

    void UdpListener::close()
    {
        this->m_internal_socket.close();
    }

    UdpPacket UdpListener::recv(int size)
    {
        UdpPacket ret;
        int n = 0;
        int total_read = 0;
        socklen_t len = sizeof(ret.addr);

        ret.data = std::vector<char>(size);
        if ((n = recvfrom(
                 this->m_internal_socket.get_internal_socket(),
                 ret.data.data() + total_read, size, 0,
                 (struct sockaddr*)&ret.addr, &len))
            == -1) {
            throw("Couldn't receive UDP packet.");
        }
        ret.size = n;
        return ret;
    }

    void UdpListener::send(
        const std::vector<char>& data, IN_ADDR addr, unsigned short port)
    {
        sockaddr_in other;

        memset((char*)&other, 0, sizeof(other));
        other.sin_addr = addr;
        other.sin_port = port;
        other.sin_family = AF_INET;
        if (sendto(
                this->m_internal_socket.get_internal_socket(), data.data(),
                data.size(), 0, (const sockaddr*)&other, sizeof(other))
            == -1) {
            throw("Couldn't send UDP packet.");
        }
    }
}
}
