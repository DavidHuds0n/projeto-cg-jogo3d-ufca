#include "../include/Key.h"
#include <iostream>

Key::Key(const Vector3f& position, ItemType keyType, const std::string& puzzleIdRequired, bool form)
    : InteractableObject(position),
      _visual(form ? PrimitiveShape::TEAPOT : PrimitiveShape::CONE, position, {0.9f, 0.9f, 0.1f}, {0.4f, 0.4f, 0.4f}), // Cor dourada
      _puzzleIdRequired(puzzleIdRequired),
      _keyType(keyType)
{
    _collisionRadius = 0.5f;
    _isCollected = false;
    // Se não depende de puzzle, já começa visível
    _isVisible = puzzleIdRequired.empty();
    setInteractable(puzzleIdRequired.empty());
}

void Key::update(float deltaTime, GameStateManager& gameStateManager) {
    if (!_isVisible && !_puzzleIdRequired.empty() && gameStateManager.isPuzzleSolved(_puzzleIdRequired)) {
        std::cout << "O puzzle foi resolvido! A chave apareceu!" << std::endl;
        _isVisible = true;
        setInteractable(true);
    }
}

void Key::render() {
    if (_isVisible && !_isCollected) {
        _visual.render();
    }
}

void Key::onClick(GameStateManager& gameStateManager) {
    if (!_isVisible || _isCollected) return;

    std::cout << "*** Chave Coletada! ***" << std::endl;
    _isCollected = true;
    setInteractable(false);
    // Adiciona o TIPO CORRETO de chave ao inventário
    gameStateManager.addItemToInventory(_keyType);
}

float Key::getCollisionRadius() const {
    return _collisionRadius;
}

BoundingBox Key::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
