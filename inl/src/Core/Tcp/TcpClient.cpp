/*
** EPITECH PROJECT, 2021
** inl
** File description:
** TcpClient
*/

#include <string>

#include "Core/Tcp/TcpClient.hpp"
#include "Core/exceptions/InlCoreException.hpp"
#include "cross_platform.hpp"

namespace inl {
namespace core {

    TcpClient::TcpClient()
        : m_internal_socket(TCP)
    {
    }

    TcpClient::TcpClient(SOCKET socket, std::optional<SOCKADDR_IN> remote)
        : m_internal_socket(socket)
        , m_to(remote)
    {
    }

    TcpClient::TcpClient(TcpClient&& other)
        : m_internal_socket(std::move(other.m_internal_socket))
    {
        this->m_to = other.m_to;
    }

    TcpClient::~TcpClient()
    {
    }

    void TcpClient::close()
    {
        this->m_internal_socket.close();
    }

    TcpClient& TcpClient::operator=(TcpClient&& other)
    {
        this->m_internal_socket = std::move(other.m_internal_socket);
        this->m_to = other.m_to;
        return *this;
    }

    void TcpClient::connect(const std::string& ip, unsigned short port)
    {
        struct hostent* hostinfo = NULL;
        SOCKADDR_IN sin = { 0 };

        if (m_to) {
            throw InlCoreException("Already connected.");
        }
        hostinfo = gethostbyname(ip.c_str());
        if (!hostinfo) {
            throw InlCoreException("Couldn't resolve given hostname");
        }
        m_to = SOCKADDR_IN {};
        m_to->sin_addr = *(IN_ADDR*)hostinfo->h_addr;
        m_to->sin_port = htons(port);
        m_to->sin_family = AF_INET;
        if (::connect(
                m_internal_socket.get_internal_socket(),
                (SOCKADDR*)&(m_to.value()), sizeof(SOCKADDR))
            == SOCKET_ERROR) {
            m_to = std::nullopt;
            throw InlCoreException("Couldn't connect to given hostname");
        }
    }

    void TcpClient::send(const std::vector<char>& data)
    {
        size_t total_wrote = 0;
        int n = 0;

        while (total_wrote != data.size()) {
            n = ::send(
                this->m_internal_socket.get_internal_socket(),
                data.data() + total_wrote, data.size() - total_wrote,
#ifdef __linux__
                MSG_NOSIGNAL
#else
                0
#endif
            );
            if (n <= 0) {
                throw InlCoreException("Couldn't send data");
            }
            total_wrote += n;
        }
    }

    std::vector<char> TcpClient::recv(size_t len)
    {
        std::vector<char> ret(len);
        size_t total_read = 0;
        int n = 0;

        while (total_read != len) {
            n = ::recv(
                this->m_internal_socket.get_internal_socket(),
                ret.data() + total_read, len - total_read, 0);
            if (n <= 0) {
                throw InlCoreException("Couldn't receive data");
            }
            total_read += n;
        }
        return ret;
    }
}
}
