/*
** EPITECH PROJECT, 2021
** inl
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#ifdef WIN32
    #pragma comment(lib, "ws2_32.lib")
    #include <WinSock2.h>
#elif defined (UNIX)
    typedef int SOCKET; // Windows uses a typedef called SOCKET as well
    #define INVALID_SOCKET -1
    #define closesocket(s) close(s)
#else
    #error INL is not supported on this platform
#endif

namespace inl {
namespace core {

enum SocketType {
    TCP,
    UDP
};

class Socket {
    public:
        Socket(SocketType type);
        ~Socket();

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
