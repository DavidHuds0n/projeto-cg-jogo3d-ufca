#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include "GameObject.h"
#include "Vector.h"

// Mantivemos a adi��o do CUBE, escolhendo a vers�o com melhor formata��o.
enum class PrimitiveShape { SPHERE, CONE, TORUS, TEAPOT, CUBE };

class PrimitiveObject : public GameObject {
public:
    PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale = {1.0f, 1.0f, 1.0f});

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual BoundingBox getBoundingBox() const override;

    // Mantivemos o novo m�todo 'setColor', que n�o estava em conflito.
    void setColor(const Vector3f& c) {_color = c;}

private:
    PrimitiveShape _shape;
    Vector3f _position;
    Vector3f _color;
    Vector3f _scale;
};

#endif // PRIMITIVEOBJECT_H
