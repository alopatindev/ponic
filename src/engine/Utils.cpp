#include "Utils.h"
#include <string>
#include <fstream>

namespace Utils
{
    std::string fileToString(const char* filename)
    {
        std::ifstream file(filename);
        std::string str((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();
        return str;
    }
}
