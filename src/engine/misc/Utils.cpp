#include "Utils.h"
#include "System.h"
#include <string>
#include <fstream>

namespace Utils
{
    std::string fileToString(const std::string& filename)
    {
        std::ifstream file(SYSTEM.getResourcesPath() + filename);
        std::string str((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        return str;
    }
}
