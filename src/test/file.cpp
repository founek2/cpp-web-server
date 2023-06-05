//
// Created by Martin Skalický on 2019-05-22.
//

#include "file.h"
#include "../files/File.h"
#include "../files/Directory.h"
#include <unistd.h>
#include <limits.h>
#include <string>

#include <iostream>
#include <sstream>

std::string getFilePath() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX) == nullptr)
        throw CannotOpenDir("looking for exec directory");

    return std::string(buffer) + "/src/test/resources/text.txt";
}

namespace file {
    void testRead() {
        File f(getFilePath());

        std::ostringstream os;
        assert(f.dumpContent(os) == "text/plain");
        assert(os.str() ==
               "Při implementaci Vaší semestrální práce můžete využívat knihovny třetích stran, které jsou uvedené v seznamu níže. Použití těchto knihoven není závazné, ale umožní Vám práci zpracovat zajímavějším způsobem.\n");
    }

    void testPermissions() {
        File f(getFilePath());

        assert(f.getStrPermissions() == "-rw-r--r--");
    }
}