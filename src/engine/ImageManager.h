#pragma once

#include "misc/Singleton.h"
#include <map>
#include <string>

#ifdef ANDROID
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#else
    #include <GL/glut.h>
#endif

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
    std::map<std::string, Group> m_groups;
    std::map< std::string, std::map<std::string, Image> > m_groupsImages;

    GLuint m_bindedTextureId;

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
