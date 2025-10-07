#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "LightManager.h"
#include "SceneManager.h"
#include "GameStateManager.h"

/**
 * @file Game.h
 * @brief Define a classe principal Game, que orquestra todo o jogo.
 */

// Enum para os estados principais do jogo.
enum GameState {
    PLAYING,
    GAME_OVER,
    WIN
};

class Game {
public:
    /**
     * @brief Construtor da classe Game.
     */
    Game();

    /**
     * @brief Inicializa o jogo, configurando o OpenGL e todos os sistemas.
     */
    void init();

    /**
     * @brief Atualiza a lógica do jogo a cada frame.
     * @param deltaTime O tempo (em ms) desde o último frame.
     */
    void update(float deltaTime);

    /**
     * @brief Renderiza a cena do jogo.
     */
    void render();

    // --- Processamento de Entrada ---
    void processKeyDown(unsigned char key, int x, int y);
    void processKeyUp(unsigned char key, int x, int y);
    void processMouseMotion(int x, int y);

private:
    void processInteraction();

    // --- Membros do Jogo ---
    Player       _player;
    LightManager _lightManager;
    SceneManager _sceneManager;
    GameStateManager _gameStateManager;
    GameState    _currentState;
    GameStateManager _gsm;
};

#endif // GAME_H
