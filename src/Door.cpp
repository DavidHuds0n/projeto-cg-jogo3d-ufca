#include "../include/Door.h"
#include "../include/PrimitiveObject.h"
#include "../include/GameStateManager.h" // Incluído para acessar os métodos de verificação
#include <iostream>

// Construtores (sem alteração)
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredItems({requiredItem}),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::vector<ItemType>& requiredItems)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredItems(requiredItems),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::string& requiredPuzzleId)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredPuzzleId(requiredPuzzleId)
{
    _collisionRadius = 1.5f;
}

// --- IMPLEMENTAÇÃO DO NOVO MÉTODO ---
bool Door::canBeOpenedBy(const GameStateManager& gameStateManager) const {
    // 1. Verifica se a porta precisa de um puzzle resolvido
    if (!_requiredPuzzleId.empty()) {
        return gameStateManager.isPuzzleSolved(_requiredPuzzleId);
    }

    // 2. Verifica se a porta precisa de itens (chaves)
    if (!_requiredItems.empty()) {
        // Itera por TODOS os itens necessários
        for (const ItemType& item : _requiredItems) {
            // Se o jogador NÃO TIVER pelo menos UM dos itens, a porta não abre
            if (!gameStateManager.playerHasItem(item)) {
                return false;
            }
        }
    }

    // 3. Se não caiu em nenhuma das condições acima (ou passou por elas), a porta está aberta
    return true;
}


void Door::update(float deltaTime, GameStateManager& gameStateManager) {}
void Door::render() { _visual.render(); }
void Door::onClick(GameStateManager& gameStateManager) {
    std::cout << "Porta interagida!" << std::endl;
}

float Door::getCollisionRadius() const { return _collisionRadius; }
int Door::getTargetRoomIndex() const { return _targetRoomIndex; }
const Vector3f& Door::getSpawnPosition() const { return _spawnPosition; }

// GETTERS ABAIXO NÃO SÃO MAIS USADOS DIRETAMENTE PELO GAME.CPP, MAS MANTEMOS
const std::vector<ItemType>& Door::getRequiredItems() const { return _requiredItems; }
const std::string& Door::getRequiredPuzzle() const { return _requiredPuzzleId; }

BoundingBox Door::getBoundingBox() const { return {{0,0,0}, {0,0,0}}; }
