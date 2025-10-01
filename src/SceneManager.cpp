/**
 * @file SceneManager.cpp
 * @brief Implementação da classe SceneManager.
 */
#include "../include/SceneManager.h"

// Includes para todos os objetos que vamos criar nas salas
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/PrimitiveObject.h"
#include "../include/TestButton.h"
#include "../include/Key.h"
#include "../include/Door.h"

#include <cstddef>
#include <iostream>

SceneManager::SceneManager() {
    _currentRoomIndex = -1;
}

SceneManager::~SceneManager() {
    for (Room* room : _rooms) {
        delete room;
    }
    _rooms.clear();
}

void SceneManager::init() {
    // --- CRIAÇÃO DA SALA 1: O Cubo de Cores ---
    Room* room1 = new Room();
    {
        // Estrutura da Sala 1
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
        const float wallHeight = 4.0f;
        const float wallThickness = 0.5f;
        const float roomSize = 10.0f;
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, wallThickness})); // Fundo
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));  // Frente
        room1->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f})); // Esquerda
        room1->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));  // Direita

        // Porta para a Sala 2 (índice 1)
        room1->addObject(new Door({0.0f, 1.0f, -9.5f}, 1, {0.0f, 1.0f, 6.5f}));

        // --- NOVOS OBJETOS (SALA 1) ---
        // Chave no canto esquerdo-fundo
        room1->addObject(new Key({-8.0f, 1.0f, -8.0f}));

        // Botão de teste ao lado da porta
        room1->addObject(new TestButton({-2.5f, 1.0f, -9.0f}));

        // Objetos primitivos decorativos
        room1->addObject(new PrimitiveObject(PrimitiveShape::CONE, {8.0f, 1.0f, -8.0f}, {0.1f, 0.8f, 0.1f})); // Canto direito-fundo
        room1->addObject(new PrimitiveObject(PrimitiveShape::TORUS, {8.0f, 1.0f, 8.0f}, {0.1f, 0.1f, 0.8f})); // Canto direito-frente
    }
    _rooms.push_back(room1);

    // --- CRIAÇÃO DA SALA 2: O Jogo das Formas ---
    Room* room2 = new Room();
    {
        // Estrutura da Sala 2
        room2->addObject(new Floor({0.0f, 0.0f, 0.0f}, {15.0f, 15.0f}));
        const float wallHeight = 4.0f;
        const float wallThickness = 0.5f;
        const float roomSize = 7.5f;
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
        room2->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));
        room2->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));

        // Portas de conexão
        room2->addObject(new Door({0.0f, 1.0f, 7.0f}, 0, {0.0f, 1.0f, -8.5f}));  // Porta de volta para a Sala 1
        room2->addObject(new Door({0.0f, 1.0f, -7.0f}, 2, {0.0f, 1.0f, 4.0f})); // Porta de avanço para a Sala 3

        // --- NOVOS OBJETOS (SALA 2) ---
        // Chave no canto esquerdo-frente
        room2->addObject(new Key({-6.0f, 1.0f, 6.0f}));

        // Botão de teste na parede direita
        room2->addObject(new TestButton({7.0f, 1.0f, 0.0f}));

        // Objetos primitivos decorativos
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {-6.0f, 1.0f, -6.0f}, {0.8f, 0.8f, 0.1f})); // Canto esquerdo-fundo
        room2->addObject(new PrimitiveObject(PrimitiveShape::SPHERE, {6.0f, 1.0f, 6.0f}, {0.8f, 0.1f, 0.8f})); // Canto direito-frente
    }
    _rooms.push_back(room2);

    // --- CRIAÇÃO DA SALA 3: O Mecanismo Sonoro ---
    Room* room3 = new Room();
    {
        // Estrutura da Sala 3
        room3->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 4.0f;
        const float wallThickness = 0.5f;
        const float roomSize = 5.0f;
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
        room3->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));
        room3->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));

        // Porta de volta para a Sala 2
        room3->addObject(new Door({0.0f, 1.0f, 4.5f}, 1, {0.0f, 1.0f, -6.0f}));

        // --- NOVOS OBJETOS (SALA 3) ---
        // Chave ao lado da porta
        room3->addObject(new Key({-2.0f, 1.0f, 4.0f}));

        // Botão de teste na parede do fundo, onde o puzzle "Simon Says" vai ficar
        room3->addObject(new TestButton({0.0f, 1.5f, -4.5f}));

        // Objetos primitivos decorativos
        room3->addObject(new PrimitiveObject(PrimitiveShape::TORUS, {-4.0f, 1.0f, 0.0f}, {0.2f, 0.9f, 0.9f})); // Parede esquerda
        room3->addObject(new PrimitiveObject(PrimitiveShape::CONE, {4.0f, 1.0f, 0.0f}, {0.9f, 0.2f, 0.2f})); // Parede direita
    }
    _rooms.push_back(room3);

    // O jogo começa na Sala 1 (índice 0)
    if (!_rooms.empty()) {
        _currentRoomIndex = 0;
    }
}

void SceneManager::switchToRoom(int roomIndex) {
    if (roomIndex >= 0 && (unsigned int)roomIndex < _rooms.size()) {
        _currentRoomIndex = roomIndex;
        std::cout << "MUDOU PARA A SALA " << roomIndex << std::endl;
    }
}

void SceneManager::update(float deltaTime) {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->update(deltaTime);
    }
}

void SceneManager::render() {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->render();
    }
}

std::vector<InteractableObject*>& SceneManager::getInteractableObjects() {
    return _rooms[_currentRoomIndex]->getInteractableObjects();
}
