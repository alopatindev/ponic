#include "Utils.h"
#include "System.h"
#include <string>
#include <fstream>

namespace Utils
{
    std::string fileToString(const char* filename)
    {
        std::ifstream file((SYSTEM.getResourcesPath() + filename).c_str());
        std::string str((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();
        return str;
    }
}
