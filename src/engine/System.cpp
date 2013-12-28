#include "System.h"

System_Class::System_Class()
{
}

System_Class::~System_Class()
{
}

const std::string& System_Class::getResourcesPath()
{
    return m_resourcesPath;
}

void System_Class::setResourcesPath(const std::string& resourcesPath)
{
    m_resourcesPath = resourcesPath + "/";
}
