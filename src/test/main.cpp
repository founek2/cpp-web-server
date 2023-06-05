//
// Created by Martin Skalický on 2019-05-22.
//

#include "request.h"
#include "response.h"
#include "configparser.h"
#include "file.h"
#include <iostream>

int main() {
    std::cout << "Running requestTest::testParsing()" << std::endl;
    requestTest::testParsing();

    std::cout << "Running responseTest::testParsing()" << std::endl;
    responseTest::testParsing();

    std::cout << "Running file::testRead()" << std::endl;
    file::testRead();

    std::cout << "Running file::testPermissions()" << std::endl;
    file::testPermissions();

    std::cout << "Running configparser::testParsing()" << std::endl;
    configparser::testParsing();

    std::cout << "All tests passed! DONE" << std::endl;
}