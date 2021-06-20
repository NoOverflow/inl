/*
** EPITECH PROJECT, 2021
** inl
** File description:
** IpUtils
*/

#include <iostream>
#include <string>

#include "Core/exceptions/InlCoreException.hpp"
#include "Utils/IpUtils.hpp"
#include "cross_platform.hpp"
#include "inl.hpp"

namespace inl {

IpUtils::IpUtils()
{
#ifdef WIN32
    init_wsa();
#endif
}

IpUtils::~IpUtils()
{
#ifdef WIN32
    destroy_wsa();
#endif
}

std::string IpUtils::get_local_ip()
{
    std::string google_dns_server = "8.8.8.8";
    unsigned short dns_port = 53;
    inl::core::TcpClient client;
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    char buffer[80];
    const char* p;

    client.connect(google_dns_server, dns_port);
    getsockname(
        client.get_internal_socket().get_internal_socket(),
        (struct sockaddr*)&name, &namelen);
    p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
    return p != NULL ? buffer : "";
}

#ifdef WIN32
void IpUtils::init_wsa()
{
    WSAData wsData;
    int err_code = 0;

    if ((err_code = WSAStartup(MAKEWORD(2, 2), &wsData)) != 0) {
        throw core::InlCoreException(
            "Couldn't initialize WSA error code: " + std::to_string(err_code));
    }
}

void IpUtils::destroy_wsa()
{
    WSACleanup();
}
}

#endif
