#include "../include/SceneManager.h"

// Includes para todos os objetos que vamos criar nas salas
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/Key.h"
#include "../include/Door.h"
#include "../include/ControlPanel.h"
#include "../include/TestButton.h"
#include "../include/PrimitiveObject.h"
#include "../include/MagicCube.h"
#include "../include/MagicCubeManager.h"
#include <random>

#include <cstddef>
#include <iostream>

SceneManager::SceneManager() {
    _currentRoomIndex = -1;
        _cubeManager = nullptr;
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
        _cubeManager = new MagicCubeManager(3, 3, {0.0f, 1.0f, 0.0f}, 2.0f, 1.0f);

        // Após criar o _cubeManager em SceneManager::init():
        for (int i = 0; i < _cubeManager->getRows(); ++i)
            for (int j = 0; j < _cubeManager->getCols(); ++j)
                room1->addObject(_cubeManager->getCube(i, j));

        // Estrutura
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 10.0f;
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room1->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Porta para a Sala 2 (requer a CHAVE_SALA_1)
        room1->addObject(new Door({0.0f, 1.0f, -9.5f}, 1, {0.0f, 1.6f, 6.5f}, ItemType::CHAVE_SALA_1));

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
        // Atualiza cubos do MagicCubeManager manualmente na sala 1
        if (_currentRoomIndex == 0 && _cubeManager) {
            for (int i = 0; i < _cubeManager->getRows(); ++i)
                for (int j = 0; j < _cubeManager->getCols(); ++j)
                    _cubeManager->getCube(i, j)->update(deltaTime, gameStateManager);
        }
    }
}
void SceneManager::render() {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->render();
        // Renderiza cubos do MagicCubeManager manualmente na sala 1
        if (_currentRoomIndex == 0 && _cubeManager) {
            for (int i = 0; i < _cubeManager->getRows(); ++i)
                for (int j = 0; j < _cubeManager->getCols(); ++j)
                    _cubeManager->getCube(i, j)->render();
        }
    }
}
std::vector<InteractableObject*>& SceneManager::getInteractableObjects() {
    return _rooms[_currentRoomIndex]->getInteractableObjects();
}
const std::vector<GameObject*>& SceneManager::getCurrentRoomObjects() const {
    return _rooms[_currentRoomIndex]->getObjects();
}
