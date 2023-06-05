//
// Created by Martin Skalický on 2019-05-08.
//

#ifndef HTTP_SERVER_VIRTUALHOST_H
#define HTTP_SERVER_VIRTUALHOST_H

#include <string>
#include "files/Directory.h"

class VirtualHost {
public:
    /**
     * Inicialize host and index files in provided directory
     * @param path - Absolute path to webRoot (directory)
     */
    explicit VirtualHost(const std::string & path);

    /**
     * Getter
     * @param relativePath
     * @return - resource on provided relative path
     */
    BaseFile * getResource(const std::string & relativePath) const;
private:
    unique_ptr<Directory> m_root;
};


#endif //HTTP_SERVER_VIRTUALHOST_H
