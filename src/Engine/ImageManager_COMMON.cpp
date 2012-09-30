#include "ImageManager.h"
#include "thirdparty/pugixml-1.2/pugixml.hpp"
#include "Log.h"

void ImageManager_Class::parseAtlasXML(const char* filename)
{
    LOGI("parsing '%s'", filename);
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
        LOGI(" group '%s'", groupName.c_str());
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
            LOGI("  image '%s'", imageName.c_str());
            image.x = i.attribute("x").as_float();
            image.y = i.attribute("y").as_float();
            image.width = i.attribute("width").as_float();
            image.height = i.attribute("height").as_float();
            groupsImages[groupName][imageName] = image;
        }
    }
}
