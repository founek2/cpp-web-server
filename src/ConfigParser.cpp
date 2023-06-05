//
// Created by Martin Skalický on 2019-05-01.
//

#include <iostream>
#include "ConfigParser.h"
#include "utils/Parser.h"
#include "files/File.h"
#include <cstring>

ConfigParser::ConfigParser(): m_path(nullptr) {}

ConfigParser::ConfigParser(const char *path) : m_path(path) {}

void ConfigParser::parse() {
    ifstream file(m_path);

    if (file.is_open()) {
        string line;
        bool virt = false;
        string left, right;
        string host;
        while (getline(file, line)) {
            if (!line.empty()) {

                if (virt){
                    if (line[0] != ' ')
                        virt = false;
                }

                if (strncmp(line.c_str(), "virtual:", 8) == 0) {
                    virt = true;
                    if (Parser::splitWithTrim(":", line, left, right) == 2) {
                        host = right;
                        virtuals.insert(make_pair(right, map<string, string>()));
                    } else throw ParseException(line);
                } else if(virt){
                    if (Parser::splitWithTrim(":", line, left, right) == 2) {
                        virtuals.at(host).insert(make_pair(left, right));
                    } else throw ParseException(line);
                }else {

                    if (Parser::splitWithTrim(":", line, left, right) == 2) {
                        m_data.insert(make_pair(left, right));
                    }
                }
            }
        }
        file.close();
    } else {
        throw CannotOpenFile(m_path);
    }
}

std::string ConfigParser::get(const std::string &key) const {
    try {
        return m_data.at(key);
    } catch (out_of_range & e) {
        return "";
    }
}