#ifndef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include "GameObject.h"
#include "Vector.h"
#include "GameStateManager.h"

class InteractableObject : public GameObject {
public:
    InteractableObject(const Vector3f& position) : _position(position), _isInteractable(true) {}
    virtual ~InteractableObject() {}

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override = 0;
    virtual void onClick(GameStateManager& gameStateManager) = 0;

    void setInteractable(bool interactable) { _isInteractable = interactable; }
    bool isInteractable() const { return _isInteractable; }

    const Vector3f& getPosition() const { return _position; }
    virtual float getCollisionRadius() const = 0;

protected:
    Vector3f _position;
    bool _isInteractable;
};

#endif // INTERACTABLEOBJECT_H
