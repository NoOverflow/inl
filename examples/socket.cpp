#include <iostream>

#include "inl.hpp"

using inl::core::Socket;
using inl::core::SocketType;

int main()
{
    try {
        // This example is a bit useless cause you should not need to create a
        // raw socket at any point
        Socket sock(SocketType::TCP);

        std::cout << "Socket created successfully !" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
