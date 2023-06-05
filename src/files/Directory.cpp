//
// Created by Martin Skalický on 2019-05-07.
//

#include "Directory.h"
#include "../utils/Parser.h"
#include "File.h"
#include <dirent.h>
#include <iostream>
#include "PhpFile.h"
#include <cstring>
#include <algorithm>

Directory::Directory(const string &path, const string &prefix) : BaseFile(path), m_prefix(prefix) {
    if (path == "." || path == "..")
        return;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir((path).c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            int dirLen = strlen(ent->d_name);
            if (!((strncmp(".", ent->d_name, 1) == 0 && dirLen == 1) ||
                  (strncmp("..", ent->d_name, 2) == 0 && dirLen == 2))) {
                string key(ent->d_name);
                replace(key.begin(), key.end(), ' ', '+'); // in URL can not be spaces -> replacing for +

                if (ent->d_type == DT_DIR) {    // directory
                    string newPrefix = prefix + ent->d_name + "/";
                    m_files.insert(make_pair(key,
                                             make_unique<Directory>(path + "/" + ent->d_name, newPrefix)));
                } else if (ent->d_type == DT_REG) {       // regular file
                    string ext = Parser::getExtension(ent->d_name, strlen(ent->d_name));
                    if (ext == ".php")
                        m_files.insert(
                                make_pair(key, make_unique<PhpFile>(path + "/" + ent->d_name)));
                    else if (ext == ".html")
                        m_files.insert(
                                make_pair(key, make_unique<File>(path + "/" + ent->d_name, "text/html", "charset=UTF-8")));
                    else if (ext == ".css")
                        m_files.insert(
                                make_pair(key, make_unique<File>(path + "/" + ent->d_name, "text/css")));
                    else if (ext == ".js")
                        m_files.insert(
                                make_pair(key, make_unique<File>(path + "/" + ent->d_name, "application/javascript")));
                    else if (ext == ".png" || ext == ".jpeg") {
                        m_files.insert(
                                make_pair(key, make_unique<File>(path + "/" + ent->d_name,
                                                                 "image/" + ext.substr(1, std::string::npos))));
                    } else
                        m_files.insert(make_pair(key, make_unique<File>(path + "/" + ent->d_name, "text/plain", "charset=UTF-8")));
                }
                //printf("%s - %d\n", ent->d_name, ent->d_type);
            }
        }
        closedir(dir);
    } else {
        cout << path << endl;
        throw CannotOpenDir(path);
    }
}

string Directory::dumpContent(ostream &out) {
    out << "<html><head></head><body><table>"
           "<tr>"
           "<th>Name</th>"
           "<th>Permissions</th>"
           "<th>Size</th>";
    if (m_prefix != "/") {
        auto pos = m_prefix.rfind("/", m_prefix.size() - 2);    // ignor ending / - dir example = '/images/'
        out << "<tr><td><a href='" << m_prefix.substr(0, pos == 0 ? 1 : pos) << "'>..</td><td>--</td><td>---</td></tr>";
    }
    for (auto &file: m_files) {
        out << "<tr><td><a href='" << m_prefix + file.first << "'>";
        out << file.first;
        out << "</a></td><td>";
        out << file.second->getStrPermissions();
        out << "</td><td>";
        out << file.second->getSize();
        out << "</td>" << "</tr>";
    }
    out << "</table></body></html>";

    return "text/html; charset=UTF-8";
}

BaseFile *Directory::getFile(const string &name) {
    try {
        return &*(m_files.at(name));
    } catch (out_of_range &e) {
        return nullptr;
    }
}