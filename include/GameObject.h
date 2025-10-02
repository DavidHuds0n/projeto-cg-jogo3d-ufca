#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"

class GameStateManager;

class GameObject {
public:
    virtual ~GameObject() {}

    virtual void update(float deltaTime, GameStateManager& gameStateManager) = 0;
    virtual void render() = 0;
    virtual BoundingBox getBoundingBox() const = 0;
};

#endif // GAMEOBJECT_H
