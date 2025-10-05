#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include "GameObject.h"
#include "Vector.h"

enum class PrimitiveShape { SPHERE, CONE, TORUS, TEAPOT,CUBE };

class PrimitiveObject : public GameObject {
public:
    PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale = {1.0f, 1.0f, 1.0f});

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual BoundingBox getBoundingBox() const override;

private:
    PrimitiveShape _shape;
    Vector3f _position;
    Vector3f _color;
    Vector3f _scale;
};

#endif // PRIMITIVEOBJECT_H
