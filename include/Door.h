// Substitua todo o conteúdo de Door.h
#ifndef DOOR_H
#define DOOR_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "Vector.h"
#include "GameData.h"
#include <string>
#include <vector>

class GameStateManager; // Forward declaration

class Door : public InteractableObject {
public:
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition);
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem);
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::vector<ItemType>& requiredItems);
    Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::string& requiredPuzzleId);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;
    virtual BoundingBox getBoundingBox() const override;

    int getTargetRoomIndex() const;
    const Vector3f& getSpawnPosition() const;

    // --- GETTERS RE-ADICIONADOS ---
    const std::vector<ItemType>& getRequiredItems() const;
    const std::string& getRequiredPuzzle() const;

    bool canBeOpenedBy(const GameStateManager& gameStateManager) const;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    int _targetRoomIndex;
    Vector3f _spawnPosition;
    std::vector<ItemType> _requiredItems;
    std::string _requiredPuzzleId;
};

#endif // DOOR_H
