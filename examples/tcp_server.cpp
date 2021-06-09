#include <iostream>
#include <string>
#include <thread>
#include <vector>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#include "inl.hpp"

using inl::core::TcpClient;
using inl::core::TcpListener;

static char* get_ip_str(const struct sockaddr* sa, char* s, size_t maxlen)
{
    switch (sa->sa_family) {
    case AF_INET:
        inet_ntop(AF_INET, &(((struct sockaddr_in*)sa)->sin_addr), s, maxlen);
        break;
    case AF_INET6:
        inet_ntop(
            AF_INET6, &(((struct sockaddr_in6*)sa)->sin6_addr), s, maxlen);
        break;
    default:
        strncpy(s, "Unknown AF", maxlen);
        return NULL;
    }
    return s;
}

// This is used to pass the value to the managing thread
// You're free to use any other technique since this is not the best
TcpClient pass_client;

static void client_logic()
{
    TcpClient client = std::move(pass_client);

    try {
        while (true) {
            auto data = client.recv(2048);

            client.send(data);
        }
    } catch (const std::exception& e) {
        std::cerr << "A Client disconnected." << '\n';
    }
}

int main()
{
    TcpListener server(8080);
    std::string line;
    std::vector<std::thread> thread_pool;

    std::cout << "[TCP Server] This is a multiclient TCP echo server listening "
                 "on 8080."
              << std::endl;
    server.listen();
    while (true) {
        pass_client = server.accept();
        thread_pool.emplace_back(std::thread([&]() {
            std::cout << "Accepted client." << std::endl;
            client_logic();
        }));
    }
    for (auto& thread : thread_pool) {
        thread.join();
    }
    return 0;
}
