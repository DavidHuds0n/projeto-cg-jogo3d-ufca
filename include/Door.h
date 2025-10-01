#ifndef DOOR_H
#define DOOR_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "Vector.h" // Adicionado para Vector3f

class Door : public InteractableObject {
public:
    // Construtor atualizado para receber a posi��o de spawn
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition);

    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void onClick() override;
    virtual float getCollisionRadius() const override;

    int getTargetRoomIndex() const;
    const Vector3f& getSpawnPosition() const; // Novo m�todo

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    int _targetRoomIndex;
    Vector3f _spawnPosition; // Nova vari�vel para a posi��o de spawn
};

#endif // DOOR_H
