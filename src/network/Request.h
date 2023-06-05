//
// Created by Martin Skalický on 2019-05-01.
//

#ifndef HTTP_SERVER_REQUEST_H
#define HTTP_SERVER_REQUEST_H

#include <map>
#include <string>

class InvalidHeader : public std::exception {
};

class UnsupportedMethod : public InvalidHeader {
};

class UnsupportedProtocol : public InvalidHeader {
};

class UnsupportedHttpVersion : public InvalidHeader {
};

using namespace std;

class Request {
public:
    /**
     * Parse whole request
     * @param req - whole request
     * @param len - Lenght of provided req
     */
    Request(const char *req, unsigned len);

    /*
     * Getter
     * @return - first line of request for ex. "GET / HTTP/1.1"
     */
    string getStatus();

    /**
     * Getter
     * @return - whole request
     */
    string getRequest();

    struct Host {
        unsigned port;
        string name;
        string path;
    };
    Host m_host;

private:
    static unsigned parseHeader(const char *lines, const char delimiter, map<string, string> &myMap);

    int parseFirstLine(const char *req);

    map<string, string> m_headers;
    string m_body;

    const char *m_req;
    unsigned m_reqHeaderLen;
};


#endif //HTTP_SERVER_REQUEST_H
