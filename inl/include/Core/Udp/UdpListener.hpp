/*
** EPITECH PROJECT, 2021
** inl
** File description:
** UdpListener
*/

#ifndef UDPLISTENER_HPP_
#define UDPLISTENER_HPP_

#include <string>
#include <vector>

#include "Core/Udp/UdpClient.hpp"

namespace inl {
namespace core {

    struct UdpPacket {
        std::vector<char> data;
        struct sockaddr_in addr;
        int size;
    };

    class UdpListener {
    public:
        UdpListener();
        UdpListener(const UdpListener&) = delete;
        UdpListener(UdpListener&&);
        ~UdpListener();

        void bind(unsigned short port);
        void close();

        UdpPacket recv(int size);
        void
        send(const std::vector<char>& data, IN_ADDR addr, unsigned short port);

        Socket &socket();
        UdpListener &operator=(UdpListener &&);
    protected:
    private:
        Socket m_internal_socket;
        unsigned short m_port;
    };

}
}

#endif /* !UDPLISTENER_HPP_ */
