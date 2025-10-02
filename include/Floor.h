#ifndef FLOOR_H
#define FLOOR_H

#include "GameObject.h"
#include "Vector.h"

class Floor : public GameObject {
public:
    Floor(const Vector3f& position, const Vector2f& size);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual BoundingBox getBoundingBox() const override;

private:
    Vector3f _position;
    Vector2f _size;
};

#endif // FLOOR_H
