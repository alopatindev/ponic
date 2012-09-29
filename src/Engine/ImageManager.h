#pragma once

#include "misc/Singleton.h"
#include <map>
#include <string>
#include <GL/glut.h>

extern "C"
{
    #include "thirdparty/tgaload.h"
};

struct Group
{
    GLuint textureId;
    GLenum mode;
    bool loaded;
    float width;
    float height;
};

struct Image
{
    std::string groupName;
    float x;
    float y;
    float width;
    float height;
};

class ImageManager_Class
{
    std::map<std::string, Group> groups;
    std::map< std::string, std::map<std::string, Image> > groupsImages;

public:
    ImageManager_Class();
    virtual ~ImageManager_Class();

    void parseAtlasXML(const char* filename);
    
    void loadGroup(const char* group);
    void freeGroup(const char* group);
    void freeAllGroups();

    const Texture* getImage(const char* group, const char* name) const;
};

typedef Singleton<ImageManager_Class> ImageManager;
