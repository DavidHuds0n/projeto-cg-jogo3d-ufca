#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "InteractableObject.h"

class ControlPanel : public InteractableObject {
public:
    ControlPanel(const Vector3f& position);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;

    virtual BoundingBox getBoundingBox() const override;
};

#endif // CONTROLPANEL_H
