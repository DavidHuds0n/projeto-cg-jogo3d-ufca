
#ifndef MAGICCUBE_H
#define MAGICCUBE_H

#include "InteractableObject.h"
#include "Vector.h"
#include "GameStateManager.h"

class MagicCube : public InteractableObject {
public:
    MagicCube(const Vector3f& position, float size, float rotation);
    virtual ~MagicCube();

    void update(float deltaTime, GameStateManager& gameStateManager) override;
    void onClick(GameStateManager& gameStateManager) override;
    void render() override;
    BoundingBox getBoundingBox() const override;
    float getCollisionRadius() const override;

private:
    float _size;
    float _rotation; // graus
};

#endif // MAGICCUBE_H
