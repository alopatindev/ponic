#include "ImageManager.h"
#include "thirdparty/pugixml-1.2/pugixml.hpp"
#include "Log.h"
#include "System.h"

ImageManager_Class::ImageManager_Class()
    : m_bindedTextureId(0)
{
}

ImageManager_Class::~ImageManager_Class()
{
    freeAllGroups();
}

void ImageManager_Class::parseAtlasXML(const std::string& filename)
{
    std::string fn(SYSTEM.getResourcesPath() + filename);
    LOGI("parsing '%s'", fn.c_str());
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fn.c_str());
    if (!result)
        LOGE("xml_parse_result: status=%d description='%s'",
             (int)result.status,
             result.description()
        );

    pugi::xml_node atlases = doc.child("Root");
    for (pugi::xml_node atlas = atlases.first_child();
         atlas;
         atlas = atlas.next_sibling())
    {
        std::string groupName = atlas.attribute("name").value();
        LOGI(" group '%s'", groupName.c_str());
        GLenum mode = atlas.attribute("mode").value() == std::string("RGBA")
                      ? GL_RGBA
                      : GL_RGB;

        m_groups[groupName].textureId = 0;
        m_groups[groupName].mode = mode;
        m_groups[groupName].loaded = false;
        m_groups[groupName].width = atlas.attribute("width").as_float();
        m_groups[groupName].height = atlas.attribute("height").as_float();

        for(pugi::xml_node i = atlas.first_child(); i; i = i.next_sibling())
        {
            std::string imageName = i.attribute("name").value();
            Image image;
            //image.groupName = groupName;
            LOGI("  image '%s'", imageName.c_str());
            image.left = i.attribute("left").as_float();
            image.top = i.attribute("top").as_float();
            image.right = i.attribute("right").as_float();
            image.bottom = i.attribute("bottom").as_float();
            m_groupsImages[groupName][imageName] = image;
        }
    }
}
