#include "ImageManager.h"
#include "Log.h"
#include "System.h"
#include <cstdlib>
#include <GL/glu.h>

void ImageManager_Class::loadGroup(const std::string& group)
{
    LOGI("loading group '%s'", group.c_str());

    GLuint textureId;
    glGenTextures(1, &textureId);

    std::string fn(SYSTEM.getResourcesPath() + "atlases/" + group + ".tga");
    tga_data_t* tga = tga_data_load(fn.c_str());

    float width = m_groups[group].width;
    float height = m_groups[group].height;
    GLenum mode = m_groups[group].mode;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    m_bindedTextureId = textureId;

    // uploading to video memory
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode,
                 GL_UNSIGNED_BYTE, tga->data);

    std::free(tga->data);
    std::free(tga);

    m_groups[group].textureId = textureId;
    m_groups[group].loaded = true;
}

void ImageManager_Class::freeGroup(const std::string& group)
{
    LOGI("freeing group '%s'", group.c_str());

    Group* g = &m_groups[group];
    g->loaded = false;
    g->textureId = 0;
    glDeleteTextures(1, &g->textureId);
}

void ImageManager_Class::freeAllGroups()
{
    LOGI("freeing all groups");
    for (auto it = m_groups.begin(); it != m_groups.end(); ++it)
    {
        it->second.loaded = false;
        it->second.textureId = 0;
        glDeleteTextures(1, &it->second.textureId);
    }
}

const Image&
ImageManager_Class::bindImage(const std::string& group, const std::string& name)
{
#ifdef _DEBUG
    if (!m_groups[group].loaded)
        LOGE("trying to get image '%s' from unloaded group '%s'",
             name.c_str(),
             group.c_str());
    if (m_groupsImages[group].find(name) == m_groupsImages[group].end())
        LOGE("trying to get unknown image '%s' from group '%s'",
             name.c_str(),
             group.c_str());
#endif

    GLuint id = m_groups[group].textureId;
    if (id != m_bindedTextureId)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        m_bindedTextureId = id;
    }

    return m_groupsImages[group][name];
}
