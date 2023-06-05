//
// Created by Martin Skalický on 2019-05-14.
//

#ifndef HTTP_SERVER_LOGGER_H
#define HTTP_SERVER_LOGGER_H

#include <string>
#include <fstream>

class CannotOpenLogFile: public std::exception {
};

struct Level {
    const static int DEBUG = 3;
    const static int INFO = 2;
    const static int ERROR = 1;
};

using namespace std;

class Logger {
public:
    /**
     * Set config level
     * @param level
     */
    Logger(int level = 2);

    /**
     * Logging on levels: DEBUG
     */
    void debug(const string &);

    /**
     * Logging on levels: INFO || DEBUG
     */
    void info(const string &);

    /**
     * Logging on levels: ERROR
     */
    void error(const string &);

    /**
     * Setter for level
     * @param level
     */
    void setLogLevel(int level);


    /**
     * Setter for log file
     * @param path - absolute path to logFile
     */
    void setLogFile(string & path);

    /**
     * Close logFile if opened
     */
    ~Logger();
private:
    int m_level;
    string m_path;
    ofstream m_logFile;

    string getFormatedDateTime();
};


#endif //HTTP_SERVER_LOGGER_H
