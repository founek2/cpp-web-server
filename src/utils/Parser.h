//
// Created by Martin Skalický on 2019-05-02.
//

#ifndef HTTP_SERVER_PARSER_H
#define HTTP_SERVER_PARSER_H

#include <string>
#include <map>

class InvalidLine : public std::exception
{
};

using namespace std;

/**
 * Takes config file and creates Config object from parsed file
 */
class Parser
{
public:
    /**
     * Split string by provided delimiter
     * @param delim - delimiter
     * @param str - string to split
     * @param leftPart - output
     * @param rightPart - output
     * @return - number of parts
     */
    static int split(const string &delim, const string &str, string &leftPart, string &rightPart);

    /**
     * Do split and trim from left both parts
     * @param delim - delimiter
     * @param str - string to split
     * @param leftPart - output
     * @param rightPart - output
     * @return - number of parts
     */
    static int splitWithTrim(const string &delim, const string &str, string &leftPart, string &rightPart);

    /**
     * Find first occurrence of letter in string
     * @param letter
     * @param str - string to search
     * @return - position of finding (start by 0)
     */
    static unsigned find(const char letter, const char *str);

    /**
     * Trim from left all spaces
     * @param s - string to trim
     */
    static inline void ltrim(std::string &s);

    /**
     * Return extension of file name
     * @param fileName - name of file
     * @param len - Lenght of file name
     * @return extension with leading dot (.html)
     */
    static string getExtension(char *fileName, size_t len);

    /**
     * Escape all occurrence of LF or CR
     * @param str - string to escape
     * @return - escaped string
     */
    static string escapeNewLines(const string &str);
};

#endif // HTTP_SERVER_PARSER_H
