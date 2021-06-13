/*
** EPITECH PROJECT, 2021
** inl
** File description:
** TcpListener
*/

#include "Core/Tcp/TcpListener.hpp"
#include "Core/Tcp/TcpClient.hpp"
#include "Core/exceptions/InlCoreException.hpp"
#include "cross_platform.hpp"

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

    TcpListener::TcpListener(TcpListener&& other)
        : m_internal_socket(std::move(other.m_internal_socket))
    {
        this->m_listening = other.m_listening;
    }

    TcpListener& TcpListener::operator=(TcpListener&& other)
    {
        this->m_internal_socket = std::move(other.m_internal_socket);
        this->m_listening = other.m_listening;
        return *this;
    }

    TcpListener::~TcpListener()
    {
    }

    void TcpListener::close()
    {
        this->m_internal_socket.close();
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
        socklen_t slen = sizeof(SOCKADDR_IN);

        s = ::accept(
            m_internal_socket.get_internal_socket(), (sockaddr*)&sin, &slen);
        if (s == INVALID_SOCKET) {
            throw InlCoreException("Failed while accepting new client");
        }
        return TcpClient(s, sin);
    }
}
}
