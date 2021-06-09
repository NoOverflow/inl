#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
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

    enum SocketType { TCP, UDP };

    class Socket {
    public:
        Socket(SocketType type);
        Socket(const Socket&) = delete;
        Socket(Socket&&);
        Socket(SOCKET raw_socket);
        ~Socket();

        SOCKET get_internal_socket() const;

        Socket& operator=(Socket&&);

    protected:
    private:
        SOCKET m_internal_socket;
        bool m_moved = false;
#ifdef WIN32
        // This is only used for windows Socket library initialization
        void init_wsa();
        void destroy_wsa();
#endif
    };

}
}

#endif /* !SOCKET_HPP_ */
