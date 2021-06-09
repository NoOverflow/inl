#include "inl.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>

using inl::core::TcpClient;

int main()
{
    TcpClient client;
    std::string line;
    std::vector<char> buffer;

    std::cout << "[TCP Client] I will send what you type here to the server."
              << std::endl;
    client.connect("127.0.0.1", 8080);
    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        buffer.resize(2048);
        for (int i = 0; i < 2048; i++) {
            if (i <= line.size()) {
                buffer[i] = line[i];
            } else {
                buffer[i] = '\0';
            }
        }
        client.send(buffer);

        auto raw_answer = client.recv(2048);
        std::string s(raw_answer.begin(), raw_answer.end());

        std::cout << s.c_str() << std::endl;
    }
    return 0;
}
