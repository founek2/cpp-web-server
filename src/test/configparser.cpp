//
// Created by Martin Skalický on 2019-05-22.
//

#include "configparser.h"
#include "../ConfigParser.h"
#include <unistd.h>
#include <limits.h>
#include <string>
#include "../files/Directory.h"

std::string getConfigPath() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX) == nullptr)
        throw CannotOpenDir("looking for exec directory");

    return std::string(buffer) + "/src/test/resources/config";
}

namespace configparser {
    void testParsing() {
        ConfigParser c(getConfigPath().c_str());

        c.parse();

        assert(c.get("IpAdress") == "127.0.0.1");

        assert(c.get("Port") == "8081");

        assert(c.virtuals.at("skalicky.cz").at("DocumentRoot") == "/magic/path");

        assert(c.virtuals.at("localhost").at("DocumentRoot") == "/root/ponny");
    }
}