#include "ImageManager.h"
#include "Log.h"
#include <cstdlib>
#include <GL/glu.h>

ImageManager_Class::ImageManager_Class()
    : m_bindedTextureId(0)
{
}

ImageManager_Class::~ImageManager_Class()
{
}

void ImageManager_Class::loadGroup(const char* group)
{
    LOGI("loading group '%s'", group);

    GLuint textureId;
    glGenTextures(1, &textureId);

    tga_data_t* tga = tga_data_load(
        ("atlases/" + std::string(group) + ".tga").c_str()
    );

    float width = m_groups[group].width;
    float height = m_groups[group].height;
    GLenum mode = m_groups[group].mode;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_bindedTextureId = textureId;

    // uploading to video memory
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode,
                 GL_UNSIGNED_BYTE, tga->data);

    std::free(tga->data);
    std::free(tga);

    m_groups[group].textureId = textureId;
    m_groups[group].loaded = true;
}

void ImageManager_Class::freeGroup(const char* group)
{
    LOGI("freeing group '%s'", group);

    Group* g = &m_groups[group];
    g->loaded = false;
    g->textureId = 0;
    glDeleteTextures(1, &g->textureId);
}

void ImageManager_Class::freeAllGroups()
{
    LOGI("freeing all groups");
    for (std::map<std::string, Group>::iterator it = m_groups.begin();
         it != m_groups.end();
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
    if (!m_groups[group].loaded)
        LOGE("trying to get image '%s' from unloaded group '%s'", name, group);
#endif

    GLuint id = m_groups[group].textureId;
    if (id != m_bindedTextureId)
        glBindTexture(GL_TEXTURE_2D, id);

    return &m_groupsImages[group][name];
}
