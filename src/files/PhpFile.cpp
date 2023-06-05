//
// Created by Martin Skalický on 2019-05-14.
//

#include "PhpFile.h"
#include "File.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <array>

PhpFile::PhpFile(const std::string& path) : BaseFile(path) {}

std::string PhpFile::dumpContent(std::ostream &os) {
    if (!isExecutable()) throw PermissionsException();

    //os << std::system(("php -f " + getPath()).c_str());

    std::array<char, 150> buffer;
    std::string result;

    FILE *pipe = popen(("php -f " + getPath()).c_str(), "r");
    if (!pipe) {
        std::cerr << "Couldn't start command." << std::endl;
        throw PipeException();
    }
    while (fgets(buffer.data(), 150, pipe) != NULL) {
        os << buffer.data();
    }
    auto returnCode = pclose(pipe);
    if (returnCode == 0)
        return "text/html";

    throw PhpExecException();
}