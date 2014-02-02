#include <engine/drawables/Drawable3D.h>
#include <engine/drawables/Drawable3DImage.h>
#include <glm/glm.hpp>

class Background3D : public Drawable3D
{
    static const int IMAGES_NUMBER = 3;
    Drawable3DImage m_layer0[IMAGES_NUMBER];
    Drawable3DImage m_layer1[IMAGES_NUMBER];
    Drawable3DImage m_sky;
    glm::vec3 m_speed;

public:
    Background3D();
    virtual ~Background3D();

    void updateSpeed(const glm::vec3& speed)
    {
        m_speed = speed;
    }

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt) {};
};
