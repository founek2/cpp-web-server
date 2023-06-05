//
// Created by Martin Skalický on 2019-05-07.
//

#ifndef HTTP_SERVER_FILEBASE_H
#define HTTP_SERVER_FILEBASE_H

#include <string>
#include <sys/stat.h>

class BaseFile {
public:
    /**
     * Constructor
     * @param path - Absolute path to file
     */
    BaseFile(const std::string &path);

    virtual ~BaseFile() = default;

    /**
     * Dump whole content to stream
     * @param os - input stream
     * @return - Conten-Type for ex. "text/plain"
     */
    virtual std::string dumpContent(std::ostream &os) = 0;

    /**
     * Getter
     * @return - Absolute path
     */
    std::string &getPath();

    /**
     * Getter
     * @return - size of file in Bytes ('xxx Bytes' or for folder '---')
     */
    std::string getSize();

    /**
    * Getter
    * @return - Permissions of file as string formatted as unix-like for ex. "drwxr-xr-x"
    */
    std::string getStrPermissions();

    /*
     * @param name - name of file
     * Return file when it is directory and contains file with that name - def. impl. is nullptr
     */
    virtual BaseFile *getFile(const std::string &name);

    /*
     * Check for exec permission bit
     */
    bool isExecutable();

private:
    std::string m_path;
    struct stat m_stat;
};


#endif //HTTP_SERVER_FILEBASE_H
