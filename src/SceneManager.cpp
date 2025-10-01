/**
 * @file SceneManager.cpp
 * @brief Implementação da classe SceneManager.
 */
#include "../include/SceneManager.h"
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/PrimitiveObject.h"
#include "../include/TestButton.h"

SceneManager::SceneManager() {
    // Inicializa o índice da sala atual como -1 para indicar que nenhuma
    // sala foi carregada ainda.
    _currentRoomIndex = -1;
}

SceneManager::~SceneManager() {
    // Libera a memória alocada para cada sala no vetor.
    for (Room* room : _rooms) {
        delete room;
    }
    _rooms.clear();
}

void SceneManager::init() {
    // --- CRIAÇÃO DA SALA 1 ---
    Room* room1 = new Room();

    // Adiciona o chão e as paredes (código anterior)
    room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
    const float wallHeight = 4.0f;
    const float wallThickness = 0.5f;
    const float roomSize = 10.0f;
    room1->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
    room1->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, wallThickness}));
    room1->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));
    room1->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {wallThickness, wallHeight, roomSize * 2.0f}));

    // --- ADICIONANDO OBJETOS DE TESTE ---

    // Adiciona uma esfera amarela no centro da sala
    room1->addObject(new PrimitiveObject(PrimitiveShape::SPHERE, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}));

    // Adiciona um cone vermelho em um canto
    room1->addObject(new PrimitiveObject(PrimitiveShape::CONE, {-5.0f, 1.0f, -5.0f}, {1.0f, 0.0f, 0.0f}));

    // Adiciona um torus (donut) azul em outro canto
    room1->addObject(new PrimitiveObject(PrimitiveShape::TORUS, {5.0f, 1.0f, -5.0f}, {0.0f, 0.5f, 1.0f}));

    // Adiciona o clássico bule de chá (teapot) roxo
    room1->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {5.0f, 1.0f, 5.0f}, {0.6f, 0.2f, 0.8f}));

    // ADICIONE NOSSO BOTAO DE TESTE BEM NA FRENTE DO JOGADOR
    room1->addObject(new TestButton({0.0f, 1.0f, -2.0f}));

    // --- FIM DA ADIÇÃO DE OBJETOS ---

    _rooms.push_back(room1);

    if (!_rooms.empty()) {
        _currentRoomIndex = 0;
    }
}

void SceneManager::update(float deltaTime) {
    // Verifica se há uma sala válida para atualizar.
    if (_currentRoomIndex >= 0 && _currentRoomIndex < _rooms.size()) {
        // Delega a chamada de update para a sala atual.
        _rooms[_currentRoomIndex]->update(deltaTime);
    }
}

void SceneManager::render() {
    // Verifica se há uma sala válida para renderizar.
    if (_currentRoomIndex >= 0 && _currentRoomIndex < _rooms.size()) {
        // Delega a chamada de render para a sala atual.
        _rooms[_currentRoomIndex]->render();
    }
}

// Em SceneManager.cpp, no final do arquivo
std::vector<InteractableObject*>& SceneManager::getInteractableObjects() {
    // Apenas repassa a chamada para a sala atual
    return _rooms[_currentRoomIndex]->getInteractableObjects();
}
