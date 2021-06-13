#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "cross_platform.hpp"
#include <string>

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
        void close();

        Socket& operator=(Socket&&);

    protected:
    private:
        SOCKET m_internal_socket;
        bool m_moved = false;
        bool m_closed = false;
#ifdef WIN32
        // This is only used for windows Socket library initialization
        void init_wsa();
        void destroy_wsa();
#endif
    };

}
}

#endif /* !SOCKET_HPP_ */
