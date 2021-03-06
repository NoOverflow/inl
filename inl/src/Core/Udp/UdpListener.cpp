/*
** EPITECH PROJECT, 2021
** inl
** File description:
** UdpListener
*/

#include <cstring>

#include "Core/Udp/UdpListener.hpp"
#include "Core/exceptions/InlCoreException.hpp"
#include "cross_platform.hpp"

namespace inl {
namespace core {

    UdpListener::UdpListener()
        : m_internal_socket(SocketType::UDP)
    {
    }

    UdpListener::UdpListener(UdpListener&& other)
        : m_internal_socket(std::move(other.m_internal_socket))
    {
        *this = std::move(other);
    }

    UdpListener& UdpListener::operator=(UdpListener&& other)
    {
        this->m_internal_socket = std::move(other.m_internal_socket);
        this->m_port = other.m_port;
        return *this;
    }

    UdpListener::~UdpListener()
    {
    }

    void UdpListener::bind(unsigned short port)
    {
        struct sockaddr_in si_me;

        this->m_port = port;
        memset((char*)&si_me, 0, sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons(port);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);
        if (::bind(
                this->m_internal_socket.get_internal_socket(),
                (const sockaddr*)&si_me, sizeof(si_me))
            == -1) {
            throw InlCoreException(
                "Couldn't bind UDP server to provided port.");
        }
    }

    Socket& UdpListener::socket()
    {
        return this->m_internal_socket;
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
            throw InlCoreException("Couldn't receive UDP packet.");
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
            throw InlCoreException("Couldn't send UDP packet.");
        }
    }
}
}
