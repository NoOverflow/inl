#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <optional>
#include <vector>

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
