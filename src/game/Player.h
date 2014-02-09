#pragma once

#include <engine/drawables/Drawable3DAnimation.h>
#include <engine/drawables/Drawable3D.h>
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/GridManager.h>
#include <glm/glm.hpp>
#include <vector>

class Player_Class : public Drawable3D
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
    bool m_leftDirection;

    bool m_frozen;

public:
    enum AnimationStates
    {
        Start_,
        Stand = Start_,
        Run,
        //Freeze,
        //Attack
        End_,
        Jump = End_
    };

private:
    AnimationStates m_animationState;
    AnimationStates m_nextAnimationState;
    Drawable3DAnimation m_animations[AnimationStates::End_ + 1];

public:
    Player_Class();
    virtual ~Player_Class();

    void initPosition(const glm::ivec2& gridPos);

    void setGrid(const Drawable3DGrid& grid);

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render() const;

    void setAnimationState(AnimationStates state)
    {
        m_nextAnimationState = state;
    }

    void setFrozen(bool frozen)
    {
        m_frozen = frozen;
    }

    bool isFrozen() const
    {
        return m_frozen;
    }

    const std::vector<GameObject*>& getGameObjects();
    bool collidesSurface() const;
    bool isFalling() const;

    bool collidesGameObjects() const;
    void collisionGameObjectsUpdate();

    //bool collidesEnemy() const; // TODO
    void anticollisionUpdate(bool& stopMovement);
    void gravityUpdate();
    void jumpUpdate();

    const glm::vec2& getGridSize() const
    {
        return m_gridSize;
    }

    void setLeftDirection(bool leftDirection)
    {
        m_leftDirection = leftDirection;
    }

private:
    Drawable3DAnimation& getCurrentAnimation()
    {
        return m_animations[m_animationState];
    }

    const Drawable3DAnimation& getCurrentAnimation() const
    {
        return m_animations[m_animationState];
    }
};

typedef Singleton<Player_Class> Player;

#define PLAYER (Player::get())
