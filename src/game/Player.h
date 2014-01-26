#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/GridManager.h>
#include <glm/glm.hpp>
#include <vector>

class Player_Class : public Drawable3DImage
{
    Drawable3DGrid_Class* m_grid;
    glm::vec2 m_gridSize;
    TileType m_collision;
    bool m_groundCollision;
    float m_gravityAcceleration;
    float m_jumpAcceleration;
    std::vector<GameObject*> m_gameObjectsCollided;

    glm::ivec2 m_initialPos;
    bool m_initializePos;

public:
    Player_Class();
    virtual ~Player_Class();

    void initPosition(const glm::ivec2& gridPos);

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

    const glm::vec2& getGridSize() const
    {
        return m_gridSize;
    }
};

typedef Singleton<Player_Class> Player;
