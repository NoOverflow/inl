/*
** EPITECH PROJECT, 2021
** inl
** File description:
** TcpListener
*/

#ifndef TCPLISTENER_HPP_
#define TCPLISTENER_HPP_

#include "Core/Socket.hpp"
#include "Core/Tcp/TcpClient.hpp"

namespace inl {
namespace core {

    class TcpListener {
    public:
        TcpListener(unsigned short port);
        TcpListener(const TcpListener &) = delete;
        TcpListener(TcpListener&&);
        ~TcpListener();

        void listen();
        TcpClient accept();
        void close();

        TcpListener& operator=(TcpListener&&);

    protected:
    private:
        Socket m_internal_socket;
        bool m_listening = false;
    };

}
}

#endif /* !TCPLISTENER_HPP_ */
