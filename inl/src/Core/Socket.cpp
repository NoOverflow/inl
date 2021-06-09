#include "Core/Socket.hpp"
#include "Core/exceptions/InlCoreException.hpp"

namespace inl {
namespace core {

    Socket::Socket(SocketType type)
    {
#ifdef WIN32
        init_wsa();
#endif
        if ((this->m_internal_socket
             = socket(AF_INET, (type == TCP ? SOCK_STREAM : SOCK_DGRAM), 0))
            == INVALID_SOCKET) {
            throw InlCoreException("Couldn't create raw socket");
        }
    }

    Socket::Socket(Socket&& other)
    {
#ifdef WIN32
        init_wsa();
#endif
        this->m_internal_socket = other.m_internal_socket;
        other.m_moved = true;
    }

    Socket::Socket(SOCKET raw_socket)
    {
#ifdef WIN32
        init_wsa();
#endif
        this->m_internal_socket = raw_socket;
    }

    Socket::~Socket()
    {
#ifdef WIN32
        destroy_wsa();
#endif
        if (!m_moved)
            closesocket(this->m_internal_socket);
    }

    Socket& Socket::operator=(Socket&& other)
    {
        this->m_internal_socket = other.m_internal_socket;
        other.m_moved = true;
        return *this;
    }

    SOCKET Socket::get_internal_socket() const
    {
        return m_internal_socket;
    }

#ifdef WIN32
    void Socket::init_wsa()
    {
        WSAData wsData;
        int err_code = 0;

        if ((err_code = WSAStartup(MAKEWORD(2, 2), &wsData)) != 0) {
            throw InlCoreException(
                "Couldn't initialize WSA error code: "
                + std::to_string(err_code));
        }
    }

    void Socket::destroy_wsa()
    {
        WSACleanup();
    }
#endif

}
}
