#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <optional>
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#else
#error INL is not supported on this platform
#endif

#include "Core/Socket.hpp"

namespace inl {
namespace core {

    class UdpClient {
    public:
        UdpClient();
        ~UdpClient();

        void set_destination(const std::string& ip, unsigned short port);
        void send(const std::vector<char>& data);
        std::vector<char> recv(size_t len);

    protected:
    private:
        Socket m_socket;
        std::optional<SOCKADDR_IN> m_destination = std::nullopt;
    };

}
}

#endif /* !UDPCLIENT_HPP_ */
