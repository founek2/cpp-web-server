//
// Created by Martin Skalický on 2019-05-21.
//

#ifndef HTTP_SERVER_FILE_H
#define HTTP_SERVER_FILE_H


#include <string>
#include "BaseFile.h"
#include <iostream>

class CannotOpenFile : public std::exception {
public:
    explicit CannotOpenFile(std::string path) : m_path(std::move(path)) {};

    const std::string & info() const throw() { return m_path; }

private:
    std::string m_path;
};

class File : public BaseFile {
public:
    explicit File(const std::string &path, const std::string contentType = "text/plain",const std::string encoding = "");

    std::string dumpContent(std::ostream &os) override;

private:
    std::string m_contentType;
    std::string m_encoding;
};


#endif //HTTP_SERVER_FILE_H
