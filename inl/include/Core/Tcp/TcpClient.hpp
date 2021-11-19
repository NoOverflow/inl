/*
** EPITECH PROJECT, 2021
** inl
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <optional>
#include <string>
#include <vector>

#include "Core/Socket.hpp"
#include "cross_platform.hpp"

namespace inl {
namespace core {

    class TcpClient {
    public:
        TcpClient();
        TcpClient(const TcpClient&) = delete;
        TcpClient(TcpClient&&);
        TcpClient(
            SOCKET socket, std::optional<SOCKADDR_IN> m_to = std::nullopt);
        ~TcpClient();

        void connect(const std::string& ip, unsigned short port);
        void send(const std::vector<char>& data);
        std::vector<char> recv(size_t len);

        void close();
        TcpClient& operator=(TcpClient&&);
        Socket& get_internal_socket();

        std::optional<SOCKADDR_IN> to() const;

    protected:
    private:
        Socket m_internal_socket;
        std::optional<SOCKADDR_IN> m_to = std::nullopt;
    };

}
}

#endif /* !TCPCLIENT_HPP_ */
