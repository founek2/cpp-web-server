#include <arpa/inet.h>
#include <unistd.h>
#include "Socket.h"
#include <cstring>

Socket::Socket() {
    if ((m_socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    // force reuse address - default is time_wait +- 4min
    int enabled = 1;
    if (setsockopt(m_socketFD, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(8080);

    memset(m_address.sin_zero, '\0', sizeof m_address.sin_zero);

    m_addrLen = sizeof(m_address);
}

Socket::~Socket() {
    close(m_socketFD); // close() function will deallocate the file descriptor indicated by files
}

void Socket::listen() {
    if (bind(m_socketFD, (struct sockaddr *) &m_address, m_addrLen) < 0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (::listen(m_socketFD, 10) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}

void Socket::setPort(int port) {
    m_address.sin_port = htons(port);
}

void Socket::setAddress(const char *ipAddr) {
    m_address.sin_addr.s_addr = inet_addr(ipAddr);

    m_addrLen = sizeof(m_address);
}

int Socket::Accept() {
    int new_socket;
    if ((new_socket = accept(m_socketFD, (struct sockaddr *) &m_address, &m_addrLen)) < 0) {
        perror("In accept");
        exit(EXIT_FAILURE);
    }

    return new_socket;
}

int Socket::getPort() {
    return ntohs(m_address.sin_port);
}