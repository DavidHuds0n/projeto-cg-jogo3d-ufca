#include "../include/Key.h"
#include <iostream>

Key::Key(const Vector3f& position)
    // Inicializa a classe base com a posi��o
    : InteractableObject(position),
      // Para ser diferente, o visual da chave ser� um CONE AZUL
      _visual(PrimitiveShape::CONE, position, {0.2f, 0.5f, 1.0f}, {0.4f, 0.4f, 0.4f})
{
    _collisionRadius = 0.5f;
    _isCollected = false; // A chave come�a no mundo, n�o coletada.
}

void Key::update(float deltaTime) {
    // A chave � est�tica, n�o faz nada no update.
}

void Key::render() {
    // S� renderiza a chave se ela ainda N�O foi coletada.
    if (!_isCollected) {
        _visual.render();
    }
}

void Key::onClick() {
    // A l�gica �nica da CHAVE acontece aqui!
    std::cout << "*************************" << std::endl;
    std::cout << "*** Chave Azul Coletada! ***" << std::endl;
    std::cout << "*************************" << std::endl;

    // Marca a chave como coletada e desativa futuras intera��es.
    _isCollected = true;
    setInteractable(false);
}

float Key::getCollisionRadius() const {
    return _collisionRadius;
}
