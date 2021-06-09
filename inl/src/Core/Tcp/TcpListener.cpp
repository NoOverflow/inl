/*
** EPITECH PROJECT, 2021
** inl
** File description:
** TcpListener
*/

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#elif __linux__
typedef int SOCKET; // Windows uses a typedef called SOCKET as well
#define INVALID_SOCKET -1
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#include <arpa/inet.h>
#include <netdb.h> /* gethostbyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> /* close */
#else
#error INL is not supported on this platform
#endif

#include "Core/Tcp/TcpClient.hpp"
#include "Core/Tcp/TcpListener.hpp"
#include "Core/exceptions/InlCoreException.hpp"

namespace inl {
namespace core {

    TcpListener::TcpListener(unsigned short port)
        : m_internal_socket(TCP)
    {
        SOCKADDR_IN sin = { 0 };

        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(port);
        sin.sin_family = AF_INET;
        if (bind(
                m_internal_socket.get_internal_socket(), (const SOCKADDR*)&sin,
                sizeof(sin))
            == SOCKET_ERROR) {
            throw InlCoreException("Couldn't bind to given port");
        }
    }

    TcpListener::~TcpListener()
    {
    }

    void TcpListener::listen()
    {
        if (::listen(m_internal_socket.get_internal_socket(), 10)
            == SOCKET_ERROR) {
            throw InlCoreException("Couldn't start listening");
        }
        m_listening = true;
    }

    TcpClient TcpListener::accept()
    {
        SOCKADDR_IN sin = { 0 };
        SOCKET s = 0;
        int slen = sizeof(SOCKADDR_IN);

        s = ::accept(
            m_internal_socket.get_internal_socket(), (sockaddr*)&sin, &slen);
        if (s == INVALID_SOCKET) {
            throw InlCoreException("Failed while accepting new client");
        }
        return TcpClient(s, sin);
    }

}
}
