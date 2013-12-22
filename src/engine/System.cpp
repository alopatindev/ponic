#include "System.h"

System_Class::System_Class()
    : m_dt(0)
{
}

System_Class::~System_Class()
{
}

int System_Class::getDt()
{
    return m_dt;
}

void System_Class::setDt(int dt)
{
    m_dt = dt;
}

const std::string& System_Class::getResourcesPath()
{
    return m_resourcesPath;
}

void System_Class::setResourcesPath(const std::string& resourcesPath)
{
    m_resourcesPath = resourcesPath + "/";
}
