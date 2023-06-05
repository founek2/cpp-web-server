//
// Created by Martin Skalický on 2019-05-01.
//

#include "Request.h"
#include "../utils/Parser.h"
#include <cstring>

Request::Request(const char *req, unsigned len) : m_headers(), m_req(req) {
    int pos;

    if (len <= 14) {
        throw InvalidHeader();
    }

    pos = parseFirstLine(req);
    m_reqHeaderLen = pos - 2; // - '\r\n'

    try {
        unsigned end = parseHeader(req + pos, ':', m_headers) + pos;
        m_body = string(req + end, req + len);
    } catch (InvalidLine &e) {
        throw InvalidHeader();
    }

    try {
        string host = m_headers.at("Host");
        auto posPort = host.find(':');
        auto posPath = host.find('/');

        if (posPort == string::npos)
            m_host.port = 80;
        else {
            m_host.port = stoi(host.substr(posPort + 1, posPath));
        }

        if (posPort == string::npos)
            m_host.name = host.substr(0, posPath);
        else {
            m_host.name = host.substr(0, posPort);
        }

    }
    catch (out_of_range &e) {
        throw InvalidHeader();
    }
}

string Request::getStatus() {
    return string(m_req, m_reqHeaderLen);
}


string Request::getRequest() {
    return string(m_req);
}

int Request::parseFirstLine(const char *req) {
    int pos = Parser::find(' ', req);
    string method = string(req, req + pos);
    if (method != "GET") throw UnsupportedMethod();

    m_headers.insert(make_pair("method", method));

    ++pos; // skip space

    int pos2 = Parser::find(' ', req + pos);
    if (pos2 > 0) {   // minimal is "/"
        m_host.path = string(req + pos, pos2);
    } else throw InvalidHeader();
    pos += pos2 + 1;  // skip space

    if (strncmp(req + pos, "HTTP/", 5) != 0)
        throw UnsupportedProtocol();
    pos += 5;

    if (strncmp(req + pos, "1.1\r\n", 5) != 0)
        throw UnsupportedHttpVersion();
    pos += 5;
    return pos;
}

unsigned Request::parseHeader(const char *lines, const char delim, map<string, string> &myMap) {

    unsigned i = 0;
    unsigned delimPos;
    unsigned linePos;

    bool emptyLine = false;
    while (lines[i] != '\0') {
        //catch empty lines
        if (lines[i] == '\r' && lines[i + 1] == '\n') {
            emptyLine = true;
            break;
        }

        delimPos = 0;
        linePos = i;

        while (++i) {
            if (lines[i] == '\0')
                throw InvalidLine();
            if (lines[i] == delim) {
                delimPos = i;
                break;
            }
        }

        while (++i) {
            if ((lines[i] == '\r' && lines[i + 1] == '\n') || lines[i] == '\0') {
                auto key = string(lines + linePos, lines + delimPos);
                auto value = string(lines + delimPos + 2, lines + i); // after delim is space
                myMap.insert(make_pair(key, value));
                break;
            }
        }
        i += 2;
    }
    if (!emptyLine) // after header must be empty line
        throw InvalidHeader();

    return i;
}