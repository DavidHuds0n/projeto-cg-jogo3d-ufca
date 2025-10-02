#include "../include/TestButton.h"
#include "../include/PrimitiveObject.h"
#include <iostream>

TestButton::TestButton(const Vector3f& position)
    : InteractableObject(position),
      _visual(PrimitiveShape::SPHERE, position, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f})
{
    _collisionRadius = 0.5f;
}

void TestButton::update(float deltaTime, GameStateManager& gameStateManager) {
    // Botão é estático, não precisa reagir a estados no update.
}

void TestButton::render() {
    _visual.render();
}

void TestButton::onClick(GameStateManager& gameStateManager) {
    std::cout << ">>> BOTAO DE TESTE PRESSIONADO! <<<" << std::endl;
    // Exemplo de como poderia ser usado:
    // gameStateManager.setPuzzleState("algum_puzzle_de_teste", true);
}

float TestButton::getCollisionRadius() const {
    return _collisionRadius;
}

BoundingBox TestButton::getBoundingBox() const {
    return {{_position.x - _collisionRadius, _position.y - _collisionRadius, _position.z - _collisionRadius},
            {_position.x + _collisionRadius, _position.y + _collisionRadius, _position.z + _collisionRadius}};
}
