#ifndef TESTBUTTON_H
#define TESTBUTTON_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "Vector.h" // Adicionado para BoundingBox

class TestButton : public InteractableObject {
public:
    TestButton(const Vector3f& position);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;

    // --- ADICIONE ESTA LINHA ---
    virtual BoundingBox getBoundingBox() const override;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
};

#endif // TESTBUTTON_H
