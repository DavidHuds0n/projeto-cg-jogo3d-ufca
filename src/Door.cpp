/**
 * @file Door.cpp
 * @brief Implementa��o da classe Door.
 */
#include "../include/Door.h"
#include <iostream>

// Construtor atualizado para receber a posi��o do objeto, o �ndice da sala de destino
// e a posi��o de spawn do jogador na nova sala.
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition)
    // Inicializa a classe base com a posi��o
    : InteractableObject(position),
      // O visual da porta ser� uma esfera marrom e alta para simular uma porta.
      // Usamos SPHERE como placeholder, mas ajustamos a escala para parecer um portal/porta.
      _visual(PrimitiveShape::SPHERE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition) // Inicializa a nova vari�vel de posi��o de spawn
{
    _collisionRadius = 1.5f; // Raio de colis�o para a intera��o
}

void Door::update(float deltaTime) {
    // A porta � est�tica por enquanto. No futuro, poderia ter uma anima��o de abertura.
}

void Door::render() {
    // Apenas renderiza o objeto visual que representa a porta.
    _visual.render();
}

void Door::onClick() {
    // A porta em si n�o executa a l�gica de transi��o. Ela apenas sinaliza
    // que foi interagida. A classe Game gerencia a mudan�a de cena.
    std::cout << "Porta interagida! Tentando mudar para a sala " << _targetRoomIndex << std::endl;
}

float Door::getCollisionRadius() const {
    return _collisionRadius;
}

int Door::getTargetRoomIndex() const {
    return _targetRoomIndex;
}

// Retorna a posi��o onde o jogador deve aparecer ap�s atravessar a porta.
const Vector3f& Door::getSpawnPosition() const {
    return _spawnPosition;
}
