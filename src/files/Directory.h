//
// Created by Martin Skalický on 2019-05-07.
//

#ifndef HTTP_SERVER_DIRECTORY_H
#define HTTP_SERVER_DIRECTORY_H

#include "BaseFile.h"
#include <string>
#include <map>
#include <memory>

class CannotOpenDir : public std::exception {
public:
    explicit CannotOpenDir(std::string path) : m_path(path) {};

   const std::string & info() const throw() { return m_path; }

private:
    std::string m_path;
};

using namespace std;

class Directory : public BaseFile {
public:
    /**
     * Index all files in provided Dir path
     * @param path - Absolute path of dir
     * @param prefix - Url path to resource, exmple: '/html/docs'
     */
    explicit Directory(const string &path, const string &prefix = "/");

    string dumpContent(ostream &out) override;

    /**
     * Getter
     * @param name - name of file
     * @return - file with provided name
     */
    BaseFile *getFile(const string &name) override;

private:
    string m_prefix;
    map<string, unique_ptr<BaseFile> > m_files;
};


#endif //HTTP_SERVER_DIRECTORY_H
