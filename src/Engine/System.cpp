#include "System.h"

System_Class::System_Class()
    : dt(0)
{
}

System_Class::~System_Class()
{
}

int System_Class::getDt()
{
    return dt;
}

void System_Class::setDt(int dt)
{
    this->dt = dt;
}
