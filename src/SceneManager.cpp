/**
 * @file SceneManager.cpp
 * @brief Implementação da classe SceneManager, responsável por gerenciar as diferentes salas do jogo.
 */

// Includes para todos os objetos
#include "../include/SceneManager.h"
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/PrimitiveObject.h"
#include "../include/Key.h"
#include "../include/Door.h"
#include "../include/PuzzleDoor.h"
#include "../include/Sign.h"
#include "../include/CubePuzzle.h"
#include "../include/RotatingCube.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/InteractableObject.h"
#include <cstddef>
#include <iostream>

/**
 * @brief Construtor da classe SceneManager.
 *
 * Inicializa o índice da sala atual para um valor inválido (-1).
 */
SceneManager::SceneManager() {
    _currentRoomIndex = -1;
}

/**
 * @brief Destrutor da classe SceneManager.
 *
 * Itera sobre o vetor de salas e deleta cada instância de `Room`, liberando a memória alocada.
 */
SceneManager::~SceneManager() {
    for (Room* room : _rooms) {
        delete room;
    }
    _rooms.clear();
}

/**
 * @brief Inicializa as salas do jogo e a posição inicial do jogador.
 *
 * Este método cria todas as salas do jogo, adiciona objetos a cada uma
 * e define a sala de início e a posição inicial do jogador.
 *
 * @param player A instância do jogador.
 */
void SceneManager::init(Player& player) {
    _player = &player;
    const int penaltyRoomIndex = 5; // Índice da sala de "Game Over"
    const float spawnHeight = 1.6f; // Altura padrão consistente para o spawn do jogador

    // --- SALA 1 (ÍNDICE 0): PUZZLE DAS PORTAS COM ÍCONES ---
    Room* room1 = new Room();
    {
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 4.0f;
        const float roomSize   = 5.0f;
        room1->addObject(new Wall({0.0f, wallHeight/2.0f, -roomSize}, {roomSize*2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room1->addObject(new Wall({0.0f, wallHeight/2.0f,  roomSize}, {roomSize*2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room1->addObject(new Wall({-roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/628.jpg"));
        room1->addObject(new Wall({ roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/628.jpg"));

        Vector3f RED   = {0.85f, 0.10f, 0.10f};
        Vector3f CYAN  = {0.1f, 0.5f, 1.0f};
        Vector3f AMBER = {1.00f, 0.72f, 0.12f};
        Vector3f LIME  = {0.45f, 0.95f, 0.35f};

        // Portas erradas levam à sala de penalidade. A correta leva para a próxima sala (índice 1).
        room1->addObject(new PuzzleDoor({-3.0f, 1.0f, -4.6f}, penaltyRoomIndex, {0.0f, spawnHeight, 4.0f}, RED, PuzzleDoor::Icon::Sun, AMBER));
        room1->addObject(new PuzzleDoor({ 0.0f, 1.0f, -4.6f}, penaltyRoomIndex, {0.0f, spawnHeight, 4.0f}, RED, PuzzleDoor::Icon::Wave, CYAN));
        room1->addObject(new PuzzleDoor({ 3.0f, 1.0f, -4.6f}, 1, {0.0f, spawnHeight, 4.5f}, RED, PuzzleDoor::Icon::Mountain, LIME)); // CORRETA

        room1->addObject(new Sign({0.0f, 2.75f, -4.25f}, "Mostro fogo ao entardecer, visto gelo em alguns lugares e guardo picos que quase ninguem ve. Quem sou eu?"));
    }
    _rooms.push_back(room1);

    // --- SALA 2 (ÍNDICE 1): PUZZLE DAS PORTAS COLORIDAS ---
    Room* room2 = new Room();
    {
        room2->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 4.0f;
        const float roomSize   = 5.0f;
        room2->addObject(new Wall({0.0f, wallHeight/2.0f, -roomSize}, {roomSize*2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room2->addObject(new Wall({0.0f, wallHeight/2.0f,  roomSize}, {roomSize*2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room2->addObject(new Wall({-roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/628.jpg"));
        room2->addObject(new Wall({ roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/628.jpg"));

        Vector3f RED   = {0.85f, 0.10f, 0.10f};
        Vector3f CYAN  = {0.1f, 0.5f, 1.0f};
        Vector3f AMBER = {1.00f, 0.72f, 0.12f};
        Vector3f LIME  = {0.45f, 0.95f, 0.35f};

        room2->addObject(new PuzzleDoor({-3.0f, 1.0f, -4.6f}, penaltyRoomIndex, {0.0f, spawnHeight, 4.0f}, RED, PuzzleDoor::Icon::None, AMBER));
        room2->addObject(new PuzzleDoor({ 0.0f, 1.0f, -4.6f}, penaltyRoomIndex, {0.0f, spawnHeight, 4.0f}, CYAN, PuzzleDoor::Icon::None, CYAN));
        room2->addObject(new PuzzleDoor({ 3.0f, 1.0f, -4.6f}, 2, {0.0f, spawnHeight, 4.5f}, LIME, PuzzleDoor::Icon::None, LIME)); // CORRETA

        room2->addObject(new Sign({0.0f, 2.75f, -4.25f}, "Tres caminhos aguardam.O fogo tenta seduzir com brilho,o mar chama com profundezas, mas quem busca calma e crescimento segue onde a vida floresce."));
    }
    _rooms.push_back(room2);

    // --- SALA 3 (ÍNDICE 2): COLETA DE CHAVES ---
    Room* room3 = new Room();
    {
        room3->addObject(new Floor({0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}));
        const float wallHeight = 4.0f;
        const float roomSize   = 6.0f;
        room3->addObject(new Wall({0.0f, wallHeight/2.0f, -roomSize}, {roomSize*2.0f, wallHeight, 0.5f},"Textures/1124.jpg"));
        room3->addObject(new Wall({0.0f, wallHeight/2.0f,  roomSize}, {roomSize*2.0f, wallHeight, 0.5f},"Textures/1124.jpg"));
        room3->addObject(new Wall({-roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/1124.jpg"));
        room3->addObject(new Wall({ roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f},"Textures/1124.jpg"));

        // A porta requer as chaves vermelha (SALA_2) e azul (SALA_3)
        room3->addObject(new Door({0.0f, 1.0f, -5.5f}, 3, {0.0f, spawnHeight, 8.5f}, {ItemType::CHAVE_SALA_2, ItemType::CHAVE_SALA_3}));

        float radius = 4.5f;

        // Plataformas visuais para as chaves
        room3->addObject(new PrimitiveObject(PrimitiveShape::CUBE, { 0.0f, 0.5f, radius }, {0.3f, 0.3f, 0.3f}, {1.0f, 1.0f, 1.0f}));
        room3->addObject(new PrimitiveObject(PrimitiveShape::CUBE, { -radius, 0.75f, 0.0f }, {0.3f, 0.3f, 0.3f}, {1.0f, 1.5f, 1.0f}));
        room3->addObject(new PrimitiveObject(PrimitiveShape::CUBE, { radius, 0.25f, 0.0f }, {0.3f, 0.3f, 0.3f}, {1.0f, 0.5f, 1.0f}));

        // Chaves posicionadas em cima das plataformas
        room3->addObject(new Key({ 0.0f, 1.5f, radius }, ItemType::CHAVE_SALA_4, "", false, {0.0f, 1.0f, 0.5f}));  // Chave Verde
        room3->addObject(new Key({ -radius, 2.25f, 0.0f }, ItemType::CHAVE_SALA_3, "", false, {0.0f, 0.0f, 1.0f})); // Chave Azul
        room3->addObject(new Key({ radius, 1.25f, 0.0f }, ItemType::CHAVE_SALA_2, "", false, {1.0f, 0.0f, 0.0f}));   // Chave Vermelha

        room3->addObject(new Sign({0.0f, 2.75f, -5.0f}, "A porta pede o fruto da uniao do fogo e do ceu. Colete as cores certas para provar seu valor."));
    }
    _rooms.push_back(room3);

    // --- SALA 4 (ÍNDICE 3): PUZZLE FINAL DOS CUBOS ---
    Room* room4 = new Room();
    {
        room4->addObject(new Floor({0.0f, 0.0f, 0.0f}, {20.0f, 20.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 10.0f;
        room4->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room4->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}, "Textures/628.jpg"));
        room4->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}, "Textures/628.jpg"));
        room4->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}, "Textures/628.jpg"));

        // Pedestal visual para dar destaque ao puzzle
        room4->addObject(new PrimitiveObject(PrimitiveShape::CUBE, {0.0f, 0.1f, 0.0f}, {0.1f, 0.1f, 0.1f}, {5.0f, 0.2f, 5.0f}));

        // Puzzle dos cubos centralizado e em cima do pedestal
        CubePuzzle* puzzle = new CubePuzzle(2, 2, {-1.0f, 0.7f, -1.0f}, 2.0f, 1.0f, PuzzleID::Sala_Cubos);
        room4->addObject(puzzle);
        const auto& cubes = puzzle->getCubes();
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                room4->addObject(cubes[i][j]);

        // Porta da vitória que leva para a sala de índice 4
        room4->addObject(new Door({0.0f, 1.0f, -9.5f}, 4, {0.0f, spawnHeight, 4.5f}, PuzzleID::Sala_Cubos));
        room4->addObject(new Sign({0.0f, 2.75f, -9.4f}, "O desafio final. A ordem precede a vitoria. Encontre a harmonia."));
    }
    _rooms.push_back(room4);

    // --- SALA 5 (ÍNDICE 4): VITÓRIA ---
    Room* room5 = new Room();
    {
        room5->addObject(new Floor({0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}));
        const float wallHeight = 4.0f;
        const float roomSize = 6.0f;
        room5->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f},"../Textures/festa.jpg"));
        room5->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f},"../Textures/festa.jpg"));
        room5->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f},"../Textures/festa.jpg"));
        room5->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f},"../Textures/festa.jpg"));

        room5->addObject(new Sign({0.0f, 1.5f, 0.0f}, "PARABENS! Voce escapou!"));
    }
    _rooms.push_back(room5);

    // --- SALA 6 (ÍNDICE 5): PENALIDADE / GAME OVER ---
    Room* room6 = new Room();
    {
        room6->addObject(new Floor({0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}));
        const float wallHeight = 4.0f;
        const float roomSize = 6.0f;
        room6->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f},"../Textures/game_over.jpg"));
        room6->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f},"../Textures/game_over.jpg"));
        room6->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f},"../Textures/game_over.jpg"));
        room6->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f},"../Textures/game_over.jpg"));

        // Porta para voltar ao início do jogo (sala de índice 0)
        room6->addObject(new Door({0.0f, 1.0f, 5.5f}, 0, {0.0f, spawnHeight, 4.0f}));
        room6->addObject(new Sign({0.0f, 1.5f, -5.0f}, "Uma escolha errada te trouxe aqui. Tente novamente."));
    }
    _rooms.push_back(room6);

    // Início do jogo na Sala 1
    if (!_rooms.empty()) {
        _currentRoomIndex = 0;
        player.setPosition({0.0f, spawnHeight, 4.0f}); // Posição inicial do jogador no jogo
    }
}

/**
 * @brief Define a sala ativa pelo seu índice.
 * @param index O índice da sala para se tornar ativa.
 */
void SceneManager::setActiveRoom(int index) {
    if(index >= 0 && index < (int)_rooms.size()) {
        _currentRoomIndex = index;
    }
}

/**
 * @brief Muda a sala atual e teletransporta o jogador para uma nova posição.
 *
 * Atualiza o índice da sala atual e ajusta a posição do jogador para a
 * posição de spawn especificada.
 *
 * @param roomIndex O índice da nova sala.
 * @param player A instância do jogador.
 * @param spawnPosition A nova posição do jogador.
 */
void SceneManager::switchToRoom(int roomIndex, Player& player, const Vector3f& spawnPosition) {
    if (roomIndex >= 0 && (unsigned int)roomIndex < _rooms.size()) {
        _currentRoomIndex = roomIndex;
        player.setPosition(spawnPosition);
        std::cout << "MUDOU PARA A SALA " << roomIndex << std::endl;
    }
}

/**
 * @brief Atualiza a sala ativa.
 *
 * Chama o método `update` da sala atual, delegando a atualização de seus objetos.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void SceneManager::update(float deltaTime, GameStateManager& gameStateManager) {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->update(deltaTime, gameStateManager);
    }
}

/**
 * @brief Renderiza a sala ativa.
 *
 * Chama o método `render` da sala atual, delegando o desenho de seus objetos.
 */
void SceneManager::render() {
    if (_currentRoomIndex != -1) {
        _rooms[_currentRoomIndex]->render();
    }
}

/**
 * @brief Obtém os objetos interativos da sala ativa.
 * @return Uma referência para o vetor de objetos interativos da sala.
 */
std::vector<InteractableObject*>& SceneManager::getInteractableObjects() {
    return _rooms[_currentRoomIndex]->getInteractableObjects();
}

/**
 * @brief Obtém todos os objetos da sala ativa.
 * @return Uma referência constante para o vetor de objetos da sala.
 */
const std::vector<GameObject*>& SceneManager::getCurrentRoomObjects() const {
    return _rooms[_currentRoomIndex]->getObjects();
}
