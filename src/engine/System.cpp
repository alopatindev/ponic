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
    this->m_dt = dt;
}
