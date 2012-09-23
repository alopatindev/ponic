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
    float width;
    float height;
    float depth;
};

class ResourceManagerClass
{
    // groups of names
    std::map<std::string,
             std::map<std::string, Texture> textures;

public:
    ResourceManagerClass();
    virtual ~ResourceManagerClass();
    
    void loadGroup(const char* group);
    const Texture* getTexture(const char* group, const char* name) const;

    void freeGroups();
};

typedef Singleton<ResourceManagerClass> ResourceManager;
