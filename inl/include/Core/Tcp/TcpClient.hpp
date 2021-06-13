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

#include "Core/Socket.hpp"

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

    protected:
    private:
        Socket m_internal_socket;
        std::optional<SOCKADDR_IN> m_to = std::nullopt;
    };

}
}

#endif /* !TCPCLIENT_HPP_ */
