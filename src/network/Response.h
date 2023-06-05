//
// Created by Martin Skalický on 2019-05-09.
//

#ifndef HTTP_SERVER_RESPONSE_H
#define HTTP_SERVER_RESPONSE_H


#include <string>
#include <sstream>
#include <map>

class InvalidStatusCode: public std::exception {
};

class Response {
public:
    Response();

    /**
     * Setter
     * @param num - Number of HTTP status code
     */
    void setStatusCode(unsigned num);

    /**
     * Setter
     * Set contenty-type to plain/text
     */
    void setContentType(const std::string & contentType);

    std::string getHeader();

    std::string & getBody();

    std::ostringstream body;

    /*
     * Getter
     * @return - first line of response for ex. "HTTP/1.1 200 OK"
     */
    std::string getStatus();

    /**
     * Convert whole response to string
     * @return - whole response
     */
    std::string str();
private:
    unsigned m_statusCode;
    std::string m_contentType;
    std::map<unsigned, std::string> m_txtCodes;
    std::string m_body;
};


#endif //HTTP_SERVER_RESPONSE_H
