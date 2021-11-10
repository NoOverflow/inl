#include <iostream>
#include <string>

#include "inl.hpp"

using inl::core::UdpClient;

int main()
{
    UdpClient client = std::move(UdpClient{});
    std::string line;

    std::cout << "[UDP Client] I will send what you type here to the server."
              << std::endl;
    client.set_destination("127.0.0.1", 8080);
    while (!std::cin.eof()) {
        std::vector<char> v;

        std::getline(std::cin, line);
        if (std::cin.eof())
            break;
        std::copy(line.begin(), line.end(), std::back_inserter(v));
        client.send(v);
    }
    return 0;
}
