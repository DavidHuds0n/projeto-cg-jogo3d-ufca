#include "../include/Key.h"
#include <iostream>
#include <algorithm> // Necessário para usar std::max
#include <cmath>     // Necessário para usar std::max em algumas configurações de compilador

Key::Key(const Vector3f& position,
         ItemType keyType,
         const std::string& puzzleIdRequired,
         bool form,
         const Vector3f& color,
         const Vector3f& scale)
    : InteractableObject(position),
      _visual(form ? PrimitiveShape::TEAPOT : PrimitiveShape::CONE,
              position,
              color,
              scale),
      _puzzleIdRequired(puzzleIdRequired),
      _keyType(keyType)
{
    _color = color;
    _visual.setColor(color);
    _isCollected = false;
    _isVisible = puzzleIdRequired.empty();
    setInteractable(puzzleIdRequired.empty());

    // --- LÓGICA DE HITBOX DINÂMICA ---
    // Em vez de um valor fixo, calculamos o raio com base no tamanho visual do objeto.

    // 1. Pega a maior dimensão da escala do objeto (x, y, ou z).
    float maxScale = std::max({scale.x, scale.y, scale.z});

    // 2. Define um raio base para o modelo 3D (cone/bule) em escala 1.0.
    //    Este valor pode ser ajustado se o modelo for muito largo ou fino. 0.8 é um bom começo.
    float baseModelRadius = 0.8f;

    // 3. Calcula o raio final: o raio do modelo * a maior escala * uma pequena folga (10%).
    _collisionRadius = baseModelRadius * maxScale * 1.1f;
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

    gameStateManager.addItemToInventory(_keyType);
}

float Key::getCollisionRadius() const {
    return _collisionRadius;
}

BoundingBox Key::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
