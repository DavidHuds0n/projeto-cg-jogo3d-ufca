#include "../include/Door.h"
#include <iostream>

Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredItem(requiredItem)
{
    _collisionRadius = 1.5f;
}

void Door::update(float deltaTime, GameStateManager& gameStateManager) {
    // A porta é estática por enquanto, não reage a estados do jogo no update.
}

void Door::render() {
    _visual.render();
}

void Door::onClick(GameStateManager& gameStateManager) {
    std::cout << "Porta interagida!" << std::endl;
    // A lógica de verificar a chave e mudar de sala fica no Game.cpp
}

float Door::getCollisionRadius() const {
    return _collisionRadius;
}

int Door::getTargetRoomIndex() const {
    return _targetRoomIndex;
}

const Vector3f& Door::getSpawnPosition() const {
    return _spawnPosition;
}

ItemType Door::getRequiredItem() const {
    return _requiredItem;
}

BoundingBox Door::getBoundingBox() const {
    // Portas não bloqueiam fisicamente o jogador, apenas a interação.
    return {{0,0,0}, {0,0,0}};
}
