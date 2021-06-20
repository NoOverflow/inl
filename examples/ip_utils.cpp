#include "inl.hpp"
#include <array>
#include <iostream>
#include <string>
#include <vector>

using inl::IpUtils;

int main()
{
    IpUtils ipu;

    std::cout << "Local ip is : " << ipu.get_local_ip() << std::endl;
    return 0;
}
