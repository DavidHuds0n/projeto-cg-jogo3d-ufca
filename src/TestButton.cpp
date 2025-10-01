#include "../include/TestButton.h"
#include <iostream>

TestButton::TestButton(const Vector3f& position)
    // Inicializa a classe base com a posição
    : InteractableObject(position),
      // Inicializa o visual como uma esfera vermelha
      _visual(PrimitiveShape::SPHERE, position, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f})
{
    _collisionRadius = 0.5f; // Raio da esfera para o teste de colisão
}

void TestButton::update(float deltaTime) {
    // O botão é estático, não faz nada no update.
}

void TestButton::render() {
    // Apenas renderiza o objeto visual.
    _visual.render();
}

void TestButton::onClick() {
    // A mágica acontece aqui!
    std::cout << "------------------------------------" << std::endl;
    std::cout << ">>> BOTAO DE TESTE PRESSIONADO! <<<" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // No futuro, aqui você mudaria o estado do jogo.
    // Ex: _gameStateManager->setPuzzleState("Room1_Button", true);
}

float TestButton::getCollisionRadius() const {
    return _collisionRadius; // <-- ADICIONE ESTE MÉTODO
}
