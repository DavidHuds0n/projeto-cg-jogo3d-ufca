#include "../include/SceneManager.h"

// Includes para todos os objetos que vamos criar nas salas
#include "../include/Floor.h"
#include "../include/Wall.h"
#include "../include/PrimitiveObject.h"
#include "../include/TestButton.h"
#include "../include/Key.h"
#include "../include/Door.h"
#include "../include/PuzzleDoor.h"
#include "../include/Sign.h"
#include "../include/ControlPanel.h"
#include "../include/Keypad.h"
#include "../include/Room.h"
#include "../include/InteractableObject.h"

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

void SceneManager::init(Player& player) {
    // --- CRIAÇÃO DA SALA 1 ---
     _player = &player;

    Room* room1 = new Room();
    {
        room1->addObject(new Floor({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f}));
        const float wallHeight = 4.0f;
        const float roomSize   = 5.0f;
        const int indexPuzzle5 = 1;
        room1->addObject(new Wall({0.0f, wallHeight/2.0f, -roomSize}, {roomSize*2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({0.0f, wallHeight/2.0f,  roomSize}, {roomSize*2.0f, wallHeight, 0.5f}));
        room1->addObject(new Wall({-roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f}));
        room1->addObject(new Wall({ roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f}));

        // Portas no fundo (z = -4.6f aprox). Cores:
        // Azul (correta), Vermelha (errada), Amarela (errada)
        Vector3f RED   = {0.85f, 0.10f, 0.10f};
        Vector3f CYAN  = {0.1f, 0.5f, 1.0f};  // brilho “oceano/céu”
        Vector3f AMBER = {1.00f, 0.72f, 0.12f};  // brilho “sol”
        Vector3f LIME  = {0.45f, 0.95f, 0.35f};  // brilho “montanha/terra”

        // Esquerda: errada (SOL)
        room1->addObject(new PuzzleDoor(
            {-3.0f, 1.0f, -4.6f},
            //PuzzleDoor::Mode::Deadly,
            RED,-1,
            PuzzleDoor::Icon::Sun, AMBER
        ));
        // Centro: CORRETA (ONDA = oceano)
        room1->addObject(new PuzzleDoor(
            { 0.0f, 1.0f, -4.6f},
            //PuzzleDoor::Mode::Winning,
            RED,indexPuzzle5,
            PuzzleDoor::Icon::Wave, CYAN
        ));
        // Direita: errada (MONTANHA)
        room1->addObject(new PuzzleDoor(
            { 3.0f, 1.0f, -4.6f},
            //PuzzleDoor::Mode::Deadly,
            RED,-1,
            PuzzleDoor::Icon::Mountain, LIME
        ));

        // Placa (mesma charada do oceano)
        room1->addObject(new Sign({0.0f, 2.75f, -4.25f},
          "Mostro fogo ao entardecer, visto gelo em alguns lugares e guardo picos que quase ninguem ve. Quem sou eu?"));
    }
    _rooms.push_back(room1);

      Room* room2 = new Room();
    {
        // Estrutura
        room2->addObject(new Floor({0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}));
        const float wallHeight = 4.0f;
        const float roomSize   = 6.0f;
        room2->addObject(new Wall({0.0f, wallHeight/2.0f, -roomSize}, {roomSize*2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({0.0f, wallHeight/2.0f,  roomSize}, {roomSize*2.0f, wallHeight, 0.5f}));
        room2->addObject(new Wall({-roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f}));
        room2->addObject(new Wall({ roomSize,wallHeight/2.0f, 0.0f},   {0.5f, wallHeight, roomSize*2.0f}));

        // Porta de Volta para Sala 4 (entrada)
       // room2->addObject(new Door({0.0f, 1.0f, 5.5f}, 3, {0.0f, 1.0f, -3.5f}, ItemType::NENHUM));

        // Porta de Saída para Sala 6 (requer CHAVE_SALA_5)
        room2->addObject(new Door({0.0f, 1.0f, -5.5f}, 2, {0.0f, 1.0f, 4.5f}, ItemType::CHAVE_SALA_1));

        // --- OBJETOS DA SALA 5: O Puzzle de Anomalia (Teapots) ---
        Vector3f TEAPOT_COLOR_NORMAL = {0.7f, 0.7f, 0.7f}; // Cinza-Claro Normal
        Vector3f TEAPOT_COLOR_ANOMALY = {0.7f, 0.3f, 0.3f}; // Vermelho Sutil

        // Crio 8 Teapots normais em círculo/quadrado
        float teapot_y = 1.0f;
        float radius = 3.5f;

        // Posições em 4 cantos
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {-radius, teapot_y, -radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, { radius, teapot_y, -radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {-radius, teapot_y,  radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        // O Teapot de Canto Anormal (Cor diferente)
        //room5->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, { radius, teapot_y,  radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_ANOMALY));

        // Posições no meio das paredes
        //room5->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, { 0.0f, teapot_y, -radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, { 0.0f, teapot_y,  radius}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, {-radius, teapot_y,  0.0f}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));
        room2->addObject(new PrimitiveObject(PrimitiveShape::TEAPOT, { radius, teapot_y,  0.0f}, {0.5f, 0.5f, 0.5f}, TEAPOT_COLOR_NORMAL));

        // A Placa com a Dica
        room2->addObject(new Sign({0.0f, 2.75f, -5.0f},
          "Olhe atentamente para o que parece igual. A chave para o proximo passo esconde-se naquele que tem uma COR ou FORMA ligeiramente diferente."));

        // O objeto que o jogador deve interagir para obter a chave
        // Use um Keypad simples como "botão" do puzzle.
        // Ele vai aparecer na localização do teapot de canto anormal
        //room5->addObject(new Keypad({radius, 1.0f, radius}));

        // A CHAVE_SALA_5 que o jogador obtém (escondida num item interativo)
        // O KEYPAD (ou outro objeto interativo no local) deverá fornecer a chave
        // quando a condição do puzzle for satisfeita (no seu código de lógica).
        // Aqui apenas coloco um Keypad no local do teapot diferente.
        // Se a chave for dropada, o jogador a pega.
        room2->addObject(new Key({ radius, teapot_y,  radius}, ItemType::CHAVE_SALA_1, "",true)); // Posicionada em outro lugar para ser pega após a interacao
    }
    _rooms.push_back(room2);

    // --- CRIAÇÃO DA SALA 6 (Saída) ---
    Room* room3 = new Room();
    {
        // ... (Estrutura da Sala 6 - Sala Final ou próxima fase) ...
        room3->addObject(new Floor({0.0f, 0.0f, 0.0f}, {12.0f, 12.0f}));
        const float wallHeight = 5.0f;
        const float roomSize = 6.0f;
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, -roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({0.0f, wallHeight / 2.0f, roomSize}, {roomSize * 2.0f, wallHeight, 0.5f}));
        room3->addObject(new Wall({-roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));
        room3->addObject(new Wall({roomSize, wallHeight / 2.0f, 0.0f}, {0.5f, wallHeight, roomSize * 2.0f}));

        //room3->addObject(new Door({0.0f, 1.0f, 2.0f}, 4, {0.0f, 1.0f, -4.5f}, ItemType::NENHUM)); // Volta para Sala 5

        room3->addObject(new Sign({0.0f, 0.75f, -8.0f}, "PARABENS! Voce escapou! (Fim da Demo)"));
    }
    _rooms.push_back(room3);



    // Início na Sala 1
    if (!_rooms.empty()) {
        _currentRoomIndex = 0;
    }
}

void SceneManager::setActiveRoom(int index){
    if(index>=0 && index<(int)_rooms.size()){
        _activeRoom = index;
    }
}

void SceneManager::switchToRoom(int roomIndex, Player& player) {
    if (roomIndex >= 0 && (unsigned int)roomIndex < _rooms.size()) {
        _currentRoomIndex = roomIndex;
        // Define a posição inicial do jogador na nova sala
        player.setPosition(_rooms[_currentRoomIndex]->getSpawnPoint());
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
