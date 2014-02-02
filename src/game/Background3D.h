#include <engine/drawables/Drawable3D.h>
#include <engine/drawables/Drawable3DImage.h>

class Background3D : public Drawable3D
{
    static const int IMAGES_NUMBER = 3;
    Drawable3DImage m_layer0[IMAGES_NUMBER];
    Drawable3DImage m_layer1[IMAGES_NUMBER];
    Drawable3DImage m_sky;

public:
    Background3D();
    virtual ~Background3D();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt) {};
};
