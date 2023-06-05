//
// Created by Martin Skalický on 2019-05-21.
//

#include <fstream>
#include "File.h"

File::File(const std::string &path,const std::string contentType,const std::string encoding) : BaseFile(path),
                                                                                 m_contentType(contentType),
                                                                                 m_encoding(encoding) {}

std::string File::dumpContent(std::ostream &os) {
    std::ifstream myReadFile;
    myReadFile.open(getPath());
    if (myReadFile.is_open()) {
        os << myReadFile.rdbuf();
    } else throw CannotOpenFile(getPath());
    myReadFile.close();
    return m_contentType + (m_encoding.empty() ? "" : "; " + m_encoding);
}