//
// Created by Martin Skalický on 2019-05-01.
//

#ifndef HTTP_SERVER_CONFIGPARSER_H
#define HTTP_SERVER_CONFIGPARSER_H


#include <string>
#include <fstream>
#include <map>

class ParseException : public std::exception {
public:
    ParseException(std::string & txt): m_txt(txt) {
    }

    const std::string & info() const throw() {
        return m_txt;
    }

private:
    std::string m_txt;
};

using namespace std;

class ConfigParser {
public:
    ConfigParser();
    /**
     * Inicialize path
     * @param path - Absolute path to config file
     */
    explicit ConfigParser(const char *path);

    /**
     * Get config value by key
     * @param key - String key in config
     * @return - Value for key
     */

    string get(const string &key) const;

    /**
     * Read config file and parse it
     */
    void parse();

    map<string, map<string, string> > virtuals;

private:
    const char *m_path;
    map<string, string> m_data;

};


#endif //HTTP_SERVER_CONFIGPARSER_H
