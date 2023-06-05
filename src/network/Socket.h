#ifndef HTTP_SERVER_SOCKET_H
#define HTTP_SERVER_SOCKET_H


#include <netinet/in.h>
#include "string"

class Socket {
public:
    /**
     * Prepare TCP socket
     */
    Socket();

    /**
    * Close TCP socket
    */
    ~Socket();

    /**
     * Bind socket to port
     */
    void listen();

    void setPort(int port);

    void setAddress(const char *ipAddr);

    int getPort();

    /**
     * Accept incoming connection
     * @return - socket to handl incoming connection
     */
    int Accept();

private:
    int m_socketFD;  // socket field descriptor
    struct sockaddr_in m_address;
    socklen_t m_addrLen;
};


#endif //HTTP_SERVER_SOCKET_H
