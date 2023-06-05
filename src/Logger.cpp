//
// Created by Martin Skalický on 2019-05-14.
//

#include <iostream>
#include <iomanip>
#include "Logger.h"
#include "utils/Parser.h"

Logger::Logger(int level) : m_level(level) {}

void Logger::setLogFile(string &path) {
    m_path = path;
    m_logFile.open(m_path,  ios::out | ios::app );
    if (!m_logFile.is_open())
        throw CannotOpenLogFile();
}

void Logger::setLogLevel(int level) {
    if (level == Level::DEBUG || level == Level::INFO || level == Level::ERROR)
        m_level = level;
    else
        cout << "ERROR  INVALID LogLevel" << endl;
}

void Logger::debug(const string &msg) {
    if (m_level >= Level::DEBUG) {
        cout << getFormatedDateTime() << "  DEBUG --- " << Parser::escapeNewLines(msg) << endl;
        if (m_logFile.is_open())
            m_logFile << getFormatedDateTime() << "  DEBUG --- " << Parser::escapeNewLines(msg) << endl;
    }


}

void Logger::error(const string &msg) {
    if (m_level >= Level::ERROR) {
        cerr << getFormatedDateTime() << "  ERROR --- " << Parser::escapeNewLines(msg) << endl;
        if (m_logFile.is_open())
            m_logFile << getFormatedDateTime() << "  ERROR --- " << Parser::escapeNewLines(msg) << endl;
    }
}

void Logger::info(const string &msg) {
    if (m_level >= Level::INFO) {
        cout << getFormatedDateTime() << "  " << setw(5) << left << "INFO" << setw(0) << " --- "
             << Parser::escapeNewLines(msg) << endl;
        if (m_logFile.is_open())
            m_logFile << getFormatedDateTime() << "  " << setw(5) << left << "INFO" << setw(0) << " --- "
                      << Parser::escapeNewLines(msg) << endl;
    }
}

string Logger::getFormatedDateTime() {
    time_t t = time(0);   // get time now
    tm *now = localtime(&t);

    string sec = to_string(now->tm_sec);
    return to_string(now->tm_year + 1900) + "-" +
           to_string(now->tm_mon + 1) + "-" +
           to_string(now->tm_mday) + " " +
           to_string(now->tm_hour) + ":" +
           to_string(now->tm_min) + ":" + (sec.size() == 1 ? "0" + sec : sec);
}

Logger::~Logger() {
    if (m_logFile.is_open())
        m_logFile.close();
}