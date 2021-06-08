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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#else
#error INL is not supported on this platform
#endif

namespace inl {
namespace core {

    enum SocketType { TCP, UDP };

    class Socket {
    public:
        Socket(SocketType type);
        ~Socket();

        SOCKET get_internal_socket() const;

    protected:
    private:
        SOCKET m_internal_socket;

#ifdef WIN32
        // This is only used for windows Socket library initialization
        void init_wsa();
        void destroy_wsa();
#endif
    };

}
}

#endif /* !SOCKET_HPP_ */
