#ifndef DOOR_H
#define DOOR_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "Vector.h"
#include "GameData.h" // Inclui o ItemType


class Door : public InteractableObject {
public:
    // Construtor para porta com item
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem = ItemType::CHAVE_SALA_1);
    // Construtor para porta com puzzle
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::string& requiredPuzzleId);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;

    int getTargetRoomIndex() const;
    const Vector3f& getSpawnPosition() const;
    ItemType getRequiredItem() const;
    const std::string& getRequiredPuzzle() const;
    bool requiresPuzzle() const { return _requiresPuzzle; }
    virtual BoundingBox getBoundingBox() const override;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    int _targetRoomIndex;
    Vector3f _spawnPosition;
    ItemType _requiredItem;
    std::string _requiredPuzzleId;
    bool _requiresPuzzle = false;
};

#endif // DOOR_H
