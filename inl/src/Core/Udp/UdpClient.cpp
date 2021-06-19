/*
** EPITECH PROJECT, 2021
** inl
** File description:
** UdpClient
*/

#include <vector>

#include "Core/Udp/UdpClient.hpp"
#include "Core/exceptions/InlCoreException.hpp"
#include "cross_platform.hpp"

namespace inl {
namespace core {

    UdpClient::UdpClient()
        : m_socket(SocketType::UDP)
    {
    }

    UdpClient::~UdpClient()
    {
    }

    void UdpClient::close()
    {
        m_socket.close();
    }

    void UdpClient::set_destination(const std::string& ip, unsigned short port)
    {
        hostent* hostinfo = gethostbyname(ip.c_str());

        if (!hostinfo) {
            throw InlCoreException("Couldn't resolve given IP");
        }
        m_destination = SOCKADDR_IN {};
        m_destination->sin_addr = *(IN_ADDR*)hostinfo->h_addr;
        m_destination->sin_port = htons(port);
        m_destination->sin_family = AF_INET;
    }

    void UdpClient::send(const std::vector<char>& data)
    {
        if (!m_destination)
            throw InlCoreException("No destination given (You must call "
                                   "::set_destination() at least once");
        if ((sendto(
                m_socket.get_internal_socket(), data.data(), data.size(), 0,
                (SOCKADDR*)&(m_destination.value()),
                (int)sizeof(m_destination.value())))
            <= 0) {
            throw InlCoreException("Error while sending data");
        }
    }

    std::vector<char> UdpClient::recv(size_t len)
    {
        std::vector<char> buffer(len);
        socklen_t slen;

        if (!m_destination)
            throw InlCoreException("No destination given (You must call "
                                   "::set_destination() at least once");
        slen = sizeof(m_destination.value());
        if ((recvfrom(
                m_socket.get_internal_socket(), buffer.data(), len, 0,
                (struct sockaddr*)&m_destination.value(), &slen))
            == -1) {
            throw InlCoreException("Error while receiving data");
        }
        return buffer;
    }
}
}
