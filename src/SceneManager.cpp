#include "../include/SceneManager.h"

// Includes
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/Key.h"
#include "../include/Door.h"
#include "../include/ControlPanel.h"
#include "../include/PrimitiveObject.h"

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
    // --- CRIAÇÃO DA SALA 1 ---
    Room* room1 = new Room();
    {
        // Estrutura da sala
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
        const float wallHeight = 4.0f;
        const float roomSize = 10.0f;
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room1->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Porta para a Sala 2 (requer a CHAVE_SALA_1)
        room1->addObject(new Door({0.0f, 1.0f, -9.5f}, 1, {0.0f, 1.0f, 6.5f}, ItemType::CHAVE_SALA_1));

        // --- OBJETOS DA SALA 1 ---
        // Chave da Sala 1 (cor padrão) no centro
        room1->addObject(new Key({0.0f, 1.0f, 0.0f}, ItemType::CHAVE_SALA_1, ""));
    }
    _rooms.push_back(room1);

    // --- CRIAÇÃO DA SALA 2 ---
    Room* room2 = new Room();
    {
        // Estrutura da sala
        room2->addObject(new Floor({0.0f, 0.0f, 0.0f}, {15.0f, 15.0f}));
        const float wallHeight = 4.0f;
        const float roomSize = 7.5f;
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room2->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Portas de conexão
        room2->addObject(new Door({0.0f, 1.0f, 7.0f}, 0, {0.0f, 1.0f, -8.5f}, ItemType::NENHUM));
        room2->addObject(new Door({0.0f, 1.0f, -7.0f}, 2, {0.0f, 1.0f, 4.0f}, ItemType::CHAVE_SALA_2));

        // --- OBJETOS DA SALA 2 ---
        // Chave da Sala 2 (cor padrão) no centro
        room2->addObject(new Key({0.0f, 1.0f, 0.0f}, ItemType::CHAVE_SALA_2, ""));
    }
    _rooms.push_back(room2);

    // --- CRIAÇÃO DA SALA 3 ---
    Room* room3 = new Room();
    {
        // Estrutura da sala
        room3->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 4.0f;
        const float roomSize = 5.0f;
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room3->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        // Porta de volta para a Sala 2
        room3->addObject(new Door({0.0f, 1.0f, 4.5f}, 1, {0.0f, 1.0f, -6.0f}, ItemType::NENHUM));

        // --- OBJETOS DA SALA 3 ---
        // Painel de controle no centro
        room3->addObject(new ControlPanel({0.0f, 1.5f, 0.0f}));
    }
    _rooms.push_back(room3);

    // O jogo começa na Sala 1
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
const std::vector<GameObject*>& SceneManager::getCurrentRoomObjects() const {
    return _rooms[_currentRoomIndex]->getObjects();
}
