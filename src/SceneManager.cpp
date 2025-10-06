#include "../include/SceneManager.h"

// Includes para todos os objetos que vamos criar nas salas
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/Key.h"
#include "../include/Door.h"
#include "../include/ControlPanel.h"
#include "../include/TestButton.h"
#include "../include/PrimitiveObject.h"
#include "../include/CubePuzzle.h"
#include "../include/RotatingCube.h"
#include <random>

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
    // --- CRIA��O DA SALA 1 ---

    Room* room1 = new Room();
    {
        // Cria o puzzle dos cubos rotativos (2x2)
        CubePuzzle* puzzle = new CubePuzzle(2, 2, {0.0f, 0.5f, 0.0f}, 2.0f, 1.0f, PuzzleID::Sala_Cubos);
        room1->addObject(puzzle); // Para update/render
        // Adiciona todos os RotatingCubes para raycast/interação
        const auto& cubes = puzzle->getCubes();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                room1->addObject(cubes[i][j]);

        // Estrutura
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 10.0f;
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room1->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Porta para a Sala 2 (requer o puzzle dos cubos resolvido)
        room1->addObject(new Door({0.0f, 1.0f, -9.5f}, 1, {0.0f, 1.6f, 6.5f}, PuzzleID::Sala_Cubos));

        // --- OBJETOS DA SALA 1 ---
    }
    _rooms.push_back(room1);

    // --- CRIA��O DA SALA 2 ---
    Room* room2 = new Room();
    {
        // Estrutura
        room2->addObject(new Floor({0.0f, 0.0f, 0.0f}, {15.0f, 15.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 7.5f;
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room2->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Portas
        room2->addObject(new Door({0.0f, 1.0f, 7.0f}, 0, {0.0f, 1.6f, -8.5f}, ItemType::NENHUM));
        room2->addObject(new Door({0.0f, 1.0f, -7.0f}, 2, {0.0f, 1.6f, 4.0f}, ItemType::CHAVE_SALA_2));

        // --- OBJETOS DA SALA 2 ---
        room2->addObject(new Key({0.0f, 1.0f, 0.0f}, ItemType::CHAVE_SALA_2, ""));
        room2->addObject(new ControlPanel({-2.5f, 1.5f, -6.5f}));
        room2->addObject(new TestButton({6.0f, 1.0f, -6.0f}));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {6.0f, 1.0f, 6.0f}, {0.8f, 0.8f, 0.1f}));
    }
    _rooms.push_back(room2);

    // --- CRIA��O DA SALA 3 ---
    Room* room3 = new Room();
    {
        // Estrutura
        room3->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 5.0f;
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room3->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Porta
        room3->addObject(new Door({0.0f, 1.0f, 4.5f}, 1, {0.0f, 1.6f, -6.0f}, ItemType::NENHUM));

        // --- OBJETOS DA SALA 3 ---
        room3->addObject(new ControlPanel({0.0f, 1.5f, 0.0f}));
        room3->addObject(new TestButton({-4.0f, 1.0f, -4.0f}));
        room3->addObject(new PrimitiveObject(PrimitiveShape::TORUS, {4.0f, 1.0f, -4.0f}, {0.9f, 0.5f, 0.1f}));
    }
    _rooms.push_back(room3);

    // In�cio na Sala 1
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
void SceneManager::update(float deltaTime, GameStateManager& gameStateManager) {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->update(deltaTime, gameStateManager);
        // (Removido: atualização manual de MagicCubeManager)
    }
}
void SceneManager::render() {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->render();
        // (Removido: render manual de MagicCubeManager)
    }
}
std::vector<InteractableObject*>& SceneManager::getInteractableObjects() {
    return _rooms[_currentRoomIndex]->getInteractableObjects();
}
const std::vector<GameObject*>& SceneManager::getCurrentRoomObjects() const {
    return _rooms[_currentRoomIndex]->getObjects();
}
