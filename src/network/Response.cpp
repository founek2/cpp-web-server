//
// Created by Martin Skalický on 2019-05-09.
//

#include "Response.h"

Response::Response() : m_statusCode(200), m_contentType("text/plain") {
    m_txtCodes.insert(std::make_pair(200, "OK"));
    m_txtCodes.insert(std::make_pair(404, "Not Found"));
    m_txtCodes.insert(std::make_pair(400, "Bad request"));
    m_txtCodes.insert(std::make_pair(403, "Forbidden"));
    m_txtCodes.insert(std::make_pair(413, "Payload Too Large"));
    m_txtCodes.insert(std::make_pair(500, "Internal Server Error"));
    m_txtCodes.insert(std::make_pair(501, "Not Implemented"));
}

void Response::setStatusCode(unsigned num) {
    if (m_txtCodes.find(num) != m_txtCodes.end())
        m_statusCode = num;
    else
        throw InvalidStatusCode();
}

void Response::setContentType(const std::string & contentType) {
    m_contentType = contentType;
}

std::string Response::getStatus() {
    return "HTTP/1.1 " + std::to_string(m_statusCode) + " " + m_txtCodes.at(m_statusCode);
}

std::string Response::getHeader() {

    std::string header = getStatus() + "\r\n";

    if (m_statusCode >= 400)
        return header;

    header += "Content-Type: " + m_contentType + "\r\n";
    header += "Content-Length: " + std::to_string(getBody().size()) + "\r\n";

    return header;
}

std::string & Response::getBody() {
    if (m_body.empty())
        m_body = body.str();
    return m_body;
}

std::string Response::str() {
    if (m_statusCode >= 400) {
        return getHeader();
    } else {
        return getHeader() + "\r\n" + getBody();
    }
}