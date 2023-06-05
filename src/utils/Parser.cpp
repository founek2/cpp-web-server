//
// Created by Martin Skalický on 2019-05-02.
//

#include "Parser.h"
#include <algorithm>
#include <cstring>

using namespace std;

int Parser::split(const string & delim, const string &txt, string &leftPart, string &rightPart) {
    size_t pos = txt.find(delim);

    if (pos != string::npos) {
        leftPart = txt.substr(0, pos);
        rightPart = txt.substr(pos + 1);
        return 2;
    }

    leftPart = txt;
    return 1;
}

int Parser::splitWithTrim(const string & delim, const string &txt, string &leftPart, string &rightPart) {
    int res = split(delim, txt, leftPart, rightPart);
    ltrim(leftPart);
    ltrim(rightPart);
    return res;
}


unsigned Parser::find(const char letter, const char * str) {
    unsigned i = 0;
    while (str[i] != letter ||  str[i] == '\0')
        ++i;

    return i;
}

string Parser::getExtension(char *str, size_t len) {
    size_t i = len;
    while (i != 0) {
        --i;

        if (str[i] == '.')
            return string(str + i, len - i);
    }

    return "";
}

string Parser::escapeNewLines(const string &str) {
    string out("");
    for(const auto & letter: str) {
        if (letter == '\n')
            out += "\\n";
       else if (letter == '\r')
            out += "\\r";
        else    out += letter;
    }
    return out;
}

void Parser::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}