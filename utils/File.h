#ifndef FILE_H
#define FILE_H

#include <sstream>
#include <fstream>

#include "Diagnostics.h"

std::string g_ReadStream(std::istream& input)
{
    std::string line;
    std::stringstream resultStream;
    while (std::getline(input, line)) {
        resultStream << line << std::endl;
    }

    return resultStream.str();
}

std::string g_ReadFile(const std::string& fileName)
{
    std::ifstream fileStream{ fileName.c_str() };
    DIAG_ASSERT(fileStream.is_open());

    std::string result = g_ReadStream(fileStream);

    fileStream.close();

    return result;
}


#endif
