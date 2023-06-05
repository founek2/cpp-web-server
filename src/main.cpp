#include "HttpServer.h"
#include <iostream>
#include <cstring>

/*! Simple HTTP server
 *
 * \section intro_sec Introduction
 * This is simple implementation of HTTP server, that generate index on provided document root
 * (by default current directory or provided in config) with virtual hosts support.
 * Displays files in directory as HTML table and user can navigate through whole dir tree via html links, just by clicking on file names.
 *
 * \section commands_sec Make commands
 *      - make all
 *      - make compile - compile HttpServer as runnable binary
 *      - make run - run compiled binary
 *      - make doc - generate docs by DoxyGen
 *      - make test - compile and run tests
 *      - make clean
 *      - make createBuildDirs - prepare directories for build
 *
 * \section config_sec Config file
 * Changes default behavior by providing specific parameters:
 *      - IpAdress
 *      - Port
 *      - LogFile
 *      - LogLevel
 *      - ShutDownUrl
 *      - DocumentRoot - defines absolute path to folder, that will be used for content indexing
 *      - Virtual - defines virtual host such as docschool.com
 *          - DocumentRoot - folder for virtual host
 *
 * \subsection defaultConfig_sec Default values
 *      - IpAdress: 0.0.0.0
 *      - Port: 8080
 *      - LogFile: - ignoring
 *      - DocumentRoot - directory from it was executed
 *      - ShutDownUrl: /shutDown
 *
 * \section examples_sec Examples
 *
 * \subsection multiVirtualHost Multi virtual host
 * Demo with prepared script for launch http server with custom config. Befor running it needs to edit absolute paths in config to
 * correspond with your files location.
 *
 * \subsection noconf No config
 * Example bash script for launch server.
 */

int main(int argc, char const *argv[])
{
    try
    {
        if (argc >= 2)
        {
            if (strlen(argv[1]) != 8 && strncmp(argv[1], "--config", 8) != 0)
            {
                std::cout << "Invalid argument: " << argv[1] << std::endl;
                std::cout << "Available are: "
                          << "--config *absolutePahtToConfig*" << std::endl;
                return 1;
            }

            if (argc < 3)
            {
                std::cout << "Missing argument: Absolute path to config " << std::endl;
                return 1;
            }

            HttpServer http(argv[2]);
            http.create();
        }
        else
        {
            HttpServer http;
            http.create();
        }
    }
    catch (ForceExit &e)
    {
        return 1;
    }
    return 0;
}
