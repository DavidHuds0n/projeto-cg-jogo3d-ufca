/**
 * @file Door.cpp
 * @brief Implementação da classe Door.
 */
#include "../include/Door.h"
#include <iostream>

// Construtor atualizado para receber a posição do objeto, o índice da sala de destino
// e a posição de spawn do jogador na nova sala.
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition)
    // Inicializa a classe base com a posição
    : InteractableObject(position),
      // O visual da porta será uma esfera marrom e alta para simular uma porta.
      // Usamos SPHERE como placeholder, mas ajustamos a escala para parecer um portal/porta.
      _visual(PrimitiveShape::SPHERE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition) // Inicializa a nova variável de posição de spawn
{
    _collisionRadius = 1.5f; // Raio de colisão para a interação
}

void Door::update(float deltaTime) {
    // A porta é estática por enquanto. No futuro, poderia ter uma animação de abertura.
}

void Door::render() {
    // Apenas renderiza o objeto visual que representa a porta.
    _visual.render();
}

void Door::onClick() {
    // A porta em si não executa a lógica de transição. Ela apenas sinaliza
    // que foi interagida. A classe Game gerencia a mudança de cena.
    std::cout << "Porta interagida! Tentando mudar para a sala " << _targetRoomIndex << std::endl;
}

float Door::getCollisionRadius() const {
    return _collisionRadius;
}

int Door::getTargetRoomIndex() const {
    return _targetRoomIndex;
}

// Retorna a posição onde o jogador deve aparecer após atravessar a porta.
const Vector3f& Door::getSpawnPosition() const {
    return _spawnPosition;
}
