#pragma once

#include "misc/Singleton.h"
#include <string>
#include <unordered_map>

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
    //std::string groupName;  // deprecated member
    float left;
    float top;
    float right;
    float bottom;
};

class ImageManager_Class
{
    std::unordered_map<std::string, Group> m_groups;
    std::unordered_map<std::string,
                       std::unordered_map<std::string, Image>> m_groupsImages;

    GLuint m_bindedTextureId;

public:
    ImageManager_Class();
    virtual ~ImageManager_Class();

    void parseAtlasXML(const std::string& filename);
    
    void loadGroup(const std::string& group);
    void freeGroup(const std::string& group);
    void freeAllGroups();

    const Image& bindImage(const std::string& group, const std::string& name);
};

typedef Singleton<ImageManager_Class> ImageManager;
