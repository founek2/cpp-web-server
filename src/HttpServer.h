//
// Created by Martin Skalický on 2019-05-01.
//

#ifndef HTTP_SERVER_HTTPSERVER_H
#define HTTP_SERVER_HTTPSERVER_H


#include "ConfigParser.h"
#include "network/Socket.h"
#include "files/Directory.h"
#include "VirtualHost.h"
#include "Logger.h"
#include <string>
#include <memory>

/**
 * exit(1) is forcing program to quit and dont call desctructors of dynamic object, just static
 * handling in main – return 1;
 */
class ForceExit : public std::exception {
};

class ShutDown : public std::exception {
};

class RequestTooLarge : public std::exception {
};

class HttpServer : Socket {
public:
    HttpServer();

    /**
     * Load config file and prepare server
     * @param configPath - Absolute path to config file
     */
    explicit HttpServer(const char *configPath);

    /**
     * Bind to port and handle connections
     */
    void create();

private:
    ConfigParser m_config;
    std::map<std::string, VirtualHost> m_virtuals;
    unique_ptr<VirtualHost> m_root;
    Logger LOG;
    std::string m_shutDownPath;
};


#endif //HTTP_SERVER_HTTPSERVER_H
