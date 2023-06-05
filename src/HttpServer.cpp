//
// Created by Martin Skalický on 2019-05-01.
//

#include "HttpServer.h"

#include <unistd.h>
#include "network/Request.h"
#include "network/Response.h"
#include <iostream>
#include <sstream>
#include "files/File.h"
#include <unistd.h>
#include <limits.h>
#include <typeinfo>

HttpServer::HttpServer() : m_root(nullptr), m_shutDownPath("/shutDown") {
    LOG.info("Indexing default directory");
    char buffer[PATH_MAX];

    if (getcwd(buffer, PATH_MAX) != nullptr)
        m_root = make_unique<VirtualHost>(buffer);
    else
        throw ForceExit();
}

HttpServer::HttpServer(const char *configPath) : m_config(configPath), m_root(nullptr), m_shutDownPath("/shutDown") {
    try {
        m_config.parse();
    } catch (ParseException &e) {
        LOG.error(string(typeid(e).name()) + " " + e.info());
       throw ForceExit();
    } catch (CannotOpenFile &e) {
        LOG.error("Cannot open configFile: " + e.info());
        throw ForceExit();
    }
    std::string param;

    param = m_config.get("LogLevel");
    if (!param.empty())
        LOG.setLogLevel(stoi(param));

    param = m_config.get("LogFile");
    if (!param.empty())
        try {
            LOG.setLogFile(param);
        }catch (CannotOpenLogFile &e){
            LOG.error("CannotOpenLogFile " + param);
        }

    LOG.info("Preparing server");

    param = m_config.get("Port");
    if (!param.empty()) {
        LOG.debug("Setting port to: " + param);
        setPort(stoi(param));
    }

    param = m_config.get("IpAdress");
    if (!param.empty()) {
        LOG.debug("Setting ip to: " + param);
        setAddress(param.c_str());
    }

    param = m_config.get("IpAdress");
    if (!param.empty()) {
        LOG.debug("Setting ip to: " + param);
        setAddress(param.c_str());
    }

    param = m_config.get("ShutDownUrl");
    if (!param.empty()) {
        LOG.debug("Setting shutDown url to: " + param);
        m_shutDownPath = param;
    }

    LOG.info("Indexing default directory");
    try {
        m_root = make_unique<VirtualHost>(m_config.get("DocumentRoot"));
        for (auto &it: m_config.virtuals) {
            LOG.info("Indexing directory for virtual: " + it.first);
            m_virtuals.insert(make_pair(it.first, VirtualHost(it.second.at("DocumentRoot"))));
        }
    } catch (CannotOpenDir &e) {
        LOG.error("While indexing happend: CannotOpenDir " + e.info());
        throw ForceExit();
    } catch (std::exception &e) {
        LOG.error("While indexing happend: " + string(typeid(e).name()));
        throw ForceExit();
    }
}

void HttpServer::create() {
    LOG.info("Starting to listen for connections on port: " + to_string(Socket::getPort()));
    listen();

    bool live = true;
    const int bufferLen = 3000;
    while (live) {
        int new_socket = Accept();

        char buffer[bufferLen] = {0};
        int valread = read(new_socket, buffer, bufferLen);

        Response res;

        try {
            if (valread == bufferLen)
                throw RequestTooLarge();

            auto req = Request(buffer, valread);

            LOG.info(req.getStatus());
            LOG.debug("Full request: " + req.getStatus());

            if (m_shutDownPath == req.m_host.path)
                throw ShutDown();

            auto virt = m_virtuals.find(req.m_host.name);
            VirtualHost *myVirt = nullptr;
            if (virt == m_virtuals.end())
                myVirt = &*m_root;
            else myVirt = &virt->second;

            auto resource = myVirt->getResource(req.m_host.path);

            if (resource) {
                try {
                    string contentType = resource->dumpContent(
                            res.body);
                    res.setContentType(contentType);
                } catch (CannotOpenFile &e) {
                    res.setStatusCode(403);
                    LOG.error("CannotOpenFile " + e.info());
                } catch (std::exception &e) {
                    res.setStatusCode(403);
                    LOG.error(typeid(e).name());
                }
            } else {
                res.setStatusCode(404);
            }
        } catch (UnsupportedMethod &e) {
            res.setStatusCode(501);
        } catch (InvalidHeader &e) {
            res.setStatusCode(400);
        } catch (RequestTooLarge &e) {
            res.setStatusCode(413);
        } catch (ShutDown &e) {
            res.body << "<html><head></head><body><h1>Shutting down...</h1></body></html>";
            res.setContentType("text/html");
            live = false;
        } catch (std::exception &e) {
            res.setStatusCode(500);
            LOG.error(typeid(e).name());
        }


        std::string resStr = res.str();
        write(new_socket, resStr.c_str(), resStr.size());

        LOG.info(res.getStatus());
        LOG.debug("Full response: " + resStr);

        close(new_socket);
    }

    LOG.info("Shutting server down");
}