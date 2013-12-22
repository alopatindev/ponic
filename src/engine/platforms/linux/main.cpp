#include <Application.h>
#include <engine/System.h>
#include <unistd.h>

static const size_t PATH_SIZE = 1024;
static char CURRENT_DIR[PATH_SIZE];

int main(int argc, char* argv[])
{
    getcwd(CURRENT_DIR, PATH_SIZE);
    SYSTEM.setResourcesPath(CURRENT_DIR);
    Application::init();
    Application::run();
    return 0;
}
