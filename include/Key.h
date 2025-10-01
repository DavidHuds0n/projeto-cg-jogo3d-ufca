#ifndef KEY_H
#define KEY_H

#include "InteractableObject.h"
#include "PrimitiveObject.h" // Para a parte visual

class Key : public InteractableObject {
public:
    Key(const Vector3f& position);

    // Métodos herdados que precisamos implementar
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void onClick() override;
    virtual float getCollisionRadius() const override;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    bool _isCollected; // Novo estado para saber se a chave já foi coletada
};

#endif // KEY_H
