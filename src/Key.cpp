#include "../include/Key.h"
#include <iostream>

Key::Key(const Vector3f& position, const std::string& puzzleIdRequired)
    : InteractableObject(position),
      _visual(PrimitiveShape::CONE, position, {0.2f, 0.5f, 1.0f}, {0.4f, 0.4f, 0.4f}),
      _puzzleIdRequired(puzzleIdRequired)
{
    _collisionRadius = 0.5f;
    _isCollected = false;
    _isVisible = false;
    setInteractable(false);
}

void Key::update(float deltaTime, GameStateManager& gameStateManager) {
    if (!_isVisible && gameStateManager.isPuzzleSolved(_puzzleIdRequired)) {
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
    gameStateManager.addItemToInventory(ItemType::CHAVE_SALA_1);
}

float Key::getCollisionRadius() const {
    return _collisionRadius;
}

BoundingBox Key::getBoundingBox() const {
    // A chave não é um obstáculo físico.
    return {{0,0,0}, {0,0,0}};
}
