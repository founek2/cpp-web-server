//
// Created by Martin Skalický on 2019-05-14.
//

#ifndef HTTP_SERVER_PHPFILE_H
#define HTTP_SERVER_PHPFILE_H

#include <string>
#include "BaseFile.h"

class PipeException : std::exception {
};

class PhpExecException : std::exception {
};

class PermissionsException : public std::exception {
};

class PhpFile: public BaseFile  {
public:
    PhpFile(const std::string & path);

    /**
     * Execute php script and dump output to stream
     * @param os - output stream
     * @return - Content-Type
     */
    std::string dumpContent(std::ostream &os) override;
};


#endif //HTTP_SERVER_PHPFILE_H
