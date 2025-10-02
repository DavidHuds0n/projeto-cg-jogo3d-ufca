#ifndef DOOR_H
#define DOOR_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "Vector.h"
#include "GameData.h" // Inclui o ItemType

class Door : public InteractableObject {
public:
    // Construtor que pode aceitar um item necessário para abrir
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem = ItemType::CHAVE_SALA_1); // Usando um placeholder

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;

    int getTargetRoomIndex() const;
    const Vector3f& getSpawnPosition() const;
    ItemType getRequiredItem() const;

    // --- ADICIONE ESTA LINHA ---
    virtual BoundingBox getBoundingBox() const override;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    int _targetRoomIndex;
    Vector3f _spawnPosition;
    ItemType _requiredItem;
};

#endif // DOOR_H
