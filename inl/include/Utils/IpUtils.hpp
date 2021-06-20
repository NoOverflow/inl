/*
** EPITECH PROJECT, 2021
** inl
** File description:
** IpUtils
*/

#ifndef IPUTILS_HPP_
#define IPUTILS_HPP_

#include <string>

namespace inl {

class IpUtils {
public:
    IpUtils();
    ~IpUtils();
    IpUtils(const IpUtils&) = delete;

    std::string get_local_ip();

protected:
private:
    void init_wsa();
    void destroy_wsa();
};

}

#endif /* !IPUTILS_HPP_ */
