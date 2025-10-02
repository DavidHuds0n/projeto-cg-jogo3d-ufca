#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Vector.h"

class Wall : public GameObject {
public:
    Wall(const Vector3f& position, const Vector3f& size);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual BoundingBox getBoundingBox() const override;

private:
    Vector3f _position;
    Vector3f _size;
};

#endif // WALL_H
