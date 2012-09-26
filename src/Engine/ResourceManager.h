#pragma once

#include "misc/Singleton.h"
#include <map>
#include <string>
#include <GL/glut.h>

extern "C"
{
    #include "thirdparty/tgaload.h"
};

struct Texture
{
    GLuint id;
    float x;
    float y;
    float width;
    float height;
    int depth;
};

class ResourceManager_Class
{
    // groups of names
    std::map<std::string,
             std::map<std::string, Texture> textures;

public:
    ResourceManager_Class();
    virtual ~ResourceManager_Class();
    
    void loadGroup(const char* group);
    void freeGroup(const char* group);

    const Texture* getTexture(const char* group, const char* name) const;

    void freeGroups();
};

typedef Singleton<ResourceManager_Class> ResourceManager;
