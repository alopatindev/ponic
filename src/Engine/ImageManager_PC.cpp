#include "ImageManager.h"
#include "Log.h"
#include <cstdlib>
#include <GL/glu.h>
#include "thirdparty/pugixml-1.2/pugixml.hpp"

ImageManager_Class::ImageManager_Class()
    : bindedTextureId(0)
{
}

ImageManager_Class::~ImageManager_Class()
{
}

void ImageManager_Class::parseAtlasXML(const char* filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename))
    {
        LOGE("can't load file '%s'", filename);
    }

    pugi::xml_node atlases = doc.child("Root");
    for (pugi::xml_node atlas = atlases.first_child();
         atlas;
         atlas = atlas.next_sibling())
    {
        std::string groupName = atlas.attribute("name").value();
        LOGI("group '%s'", groupName);
        GLenum mode = atlas.attribute("mode").value() == std::string("RGBA")
                      ? GL_RGBA
                      : GL_RGB;

        groups[groupName].textureId = 0;
        groups[groupName].mode = mode;
        groups[groupName].loaded = false;
        groups[groupName].width = atlas.attribute("width").as_float();
        groups[groupName].height = atlas.attribute("height").as_float();

        for(pugi::xml_node i = atlas.first_child();
            i;
            i = i.next_sibling())
        {
            std::string imageName = i.attribute("name").value();
            Image image;
            image.groupName = groupName;
            LOGI(" image '%s'", imageName);
            image.x = i.attribute("x").as_float();
            image.y = i.attribute("y").as_float();
            image.width = i.attribute("width").as_float();
            image.height = i.attribute("height").as_float();
            groupsImages[groupName][imageName] = image;
        }
    }
}

void ImageManager_Class::loadGroup(const char* group)
{
    GLuint textureId;
    glGenTextures(1, &textureId);

    tga_data_t* tga = tga_data_load(
        ("atlases/" + std::string(group) + ".tga").c_str()
    );

    float width = groups[group].width;
    float height = groups[group].height;
    GLenum mode = groups[group].mode;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    bindedTextureId = textureId;

    // uploading to video memory
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode,
                 GL_UNSIGNED_BYTE, tga->data);

    std::free(tga->data);
    std::free(tga);

    groups[group].textureId = textureId;
    groups[group].loaded = true;
}

void ImageManager_Class::freeGroup(const char* group)
{
    Group* g = &groups[group];
    g->loaded = false;
    g->textureId = 0;
    glDeleteTextures(1, &g->textureId);
}

void ImageManager_Class::freeAllGroups()
{
    for (std::map<std::string, Group>::iterator it = groups.begin();
         it != groups.end();
         ++it)
    {
        it->second.loaded = false;
        it->second.textureId = 0;
        glDeleteTextures(1, &it->second.textureId);
    }
}

Image*
ImageManager_Class::bindImage(const char* group, const char* name)
{
#ifdef _DEBUG
    if (!groups[group].loaded)
        LOGE("trying to get image '%s' from unloaded group '%s'", name, group);
#endif

    GLuint id = groups[group].textureId;
    if (id != bindedTextureId)
        glBindTexture(GL_TEXTURE_2D, id);

    return &groupsImages[group][name];
}
