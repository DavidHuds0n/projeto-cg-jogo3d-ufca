#ifndef KEYPAD_H
#define KEYPAD_H

#include "InteractableObject.h"

class Keypad : public InteractableObject {
public:
    Keypad(const Vector3f& position);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;

    virtual BoundingBox getBoundingBox() const override;
};

#endif // KEYPAD_H
