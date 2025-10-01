#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include "GameObject.h"
#include "Vector.h"

// Enum para especificar qual forma queremos desenhar
enum class PrimitiveShape {
    SPHERE,
    CONE,
    TORUS,
    TEAPOT
};

class PrimitiveObject : public GameObject {
public:
    /**
     * @param shape O tipo de primitiva a ser desenhada (esfera, cone, etc.).
     * @param position A posição do centro do objeto no mundo.
     * @param color A cor difusa do material do objeto.
     * @param scale A escala do objeto (padrão é 1.0 em todos os eixos).
     */
    PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale = {1.0f, 1.0f, 1.0f});

    virtual void update(float deltaTime) override;
    virtual void render() override;

private:
    PrimitiveShape _shape;
    Vector3f _position;
    Vector3f _color;
    Vector3f _scale;
};

#endif // PRIMITIVEOBJECT_H
