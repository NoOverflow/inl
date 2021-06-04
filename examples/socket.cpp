#include <iostream>

#include "inl.hpp"

using inl::core::SocketType;
using inl::core::Socket;

int main()
{
    try
    {
        Socket sock(SocketType::TCP);

        std::cout << "Socket created successfully !" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
