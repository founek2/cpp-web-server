//
// Created by Martin Skalický on 2019-05-08.
//


#include "VirtualHost.h"
#include <iostream>
#include <memory>

VirtualHost::VirtualHost(const std::string &path) : m_root(nullptr) {
    m_root = make_unique<Directory>(path);
}

BaseFile *VirtualHost::getResource(const std::string &relativePath) const {
    if (relativePath == "/")
        return &*m_root;

    auto pos = relativePath.find('/', 1); // first is always '/'
    auto pathSubstr = relativePath.substr(1, pos - 1); // -1 -> without ending '/'

    auto it = m_root->getFile(pathSubstr);
    auto gPos = pos;
    while (pos != std::string::npos) {
        auto newPath = relativePath.substr(gPos + 1, std::string::npos);
        // const auto newPos = relativePath.find("/", pos); find with start position is causing problem!
        pos = newPath.find('/');
        pathSubstr = newPath.substr(0, pos);

        it = it->getFile(pathSubstr);
        if (!it) return nullptr;
        gPos += pos + 1;   // skip '/'
    }

    return it;
}