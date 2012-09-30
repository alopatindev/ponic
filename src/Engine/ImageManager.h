#pragma once

#include "misc/Singleton.h"
#include <map>
#include <string>
#include <GL/glut.h>

extern "C"
{
    #include "thirdparty/tgaload/tgaload.h"
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
    std::string groupName;  // deprecated member
    float left;
    float top;
    float right;
    float bottom;
};

class ImageManager_Class
{
    std::map<std::string, Group> groups;
    std::map< std::string, std::map<std::string, Image> > groupsImages;

    GLuint bindedTextureId;

public:
    ImageManager_Class();
    virtual ~ImageManager_Class();

    void parseAtlasXML(const char* filename);
    
    void loadGroup(const char* group);
    void freeGroup(const char* group);
    void freeAllGroups();

    Image* bindImage(const char* group, const char* name);
};

typedef Singleton<ImageManager_Class> ImageManager;
