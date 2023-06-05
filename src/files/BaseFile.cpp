//
// Created by Martin Skalický on 2019-05-07.
//

#include "BaseFile.h"
#include <sys/stat.h>

BaseFile::BaseFile(const std::string &path) : m_path(path) {
    stat(path.c_str(), &m_stat);
}

std::string &BaseFile::getPath() { return m_path; }

BaseFile *BaseFile::getFile(const std::string &name) {
    return nullptr;
}

std::string BaseFile::getStrPermissions() {
    std::string str = S_ISDIR(m_stat.st_mode) ? "d" : "-";
    str += (m_stat.st_mode & S_IRUSR) ? "r" : "-";
    str += (m_stat.st_mode & S_IWUSR) ? "w" : "-";
    str += (m_stat.st_mode & S_IXUSR) ? "x" : "-";
    str += (m_stat.st_mode & S_IRGRP) ? "r" : "-";
    str += (m_stat.st_mode & S_IWGRP) ? "w" : "-";
    str += (m_stat.st_mode & S_IXGRP) ? "x" : "-";
    str += (m_stat.st_mode & S_IROTH) ? "r" : "-";
    str += (m_stat.st_mode & S_IWOTH) ? "w" : "-";
    str += isExecutable() ? "x" : "-";

    return str;
}

std::string BaseFile::getSize(){
    return S_ISDIR(m_stat.st_mode) ? "---": std::to_string(m_stat.st_size) + " Bytes";
}

bool BaseFile::isExecutable() {
    return (m_stat.st_mode & S_IXOTH);
}