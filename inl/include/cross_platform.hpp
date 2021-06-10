/*
** EPITECH PROJECT, 2021
** inl
** File description:
** cross_platform
*/

#ifndef CROSS_PLATFORM_HPP_
#define CROSS_PLATFORM_HPP_

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
typedef int socklen_t;
#elif __linux__
typedef int SOCKET; // Windows uses a typedef called SOCKET as well
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#include <arpa/inet.h>
#include <netdb.h> /* gethostbyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> /* close */
#else
#error INL is not supported on this platform
#endif

#endif /* !CROSS_PLATFORM_HPP_ */
