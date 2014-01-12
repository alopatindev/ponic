#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/GridManager.h>
#include <glm/glm.hpp>
#include <vector>

class Player_Class : public Drawable3DImage
{
    const Drawable3DGrid_Class* m_grid;
    glm::vec2 m_gridSize;
    TileType m_collision;
    bool m_groundCollision;
    float m_gravityAcceleration;
    float m_jumpAcceleration;
    std::vector<GameObject*> m_gameObjectsCollided;

public:
    Player_Class();
    virtual ~Player_Class();

    void setGrid(const Drawable3DGrid& grid);

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render() const;

    const std::vector<GameObject*>& getGameObjects();
    bool collidesSurface() const;
    bool isFalling() const;

    bool collidesGameObjects() const;
    void collisionGameObjectsUpdate();

    //bool collidesEnemy() const; // TODO
    void anticollisionUpdate();
    void gravityUpdate();
    void jumpUpdate();
};

typedef Singleton<Player_Class> Player;
