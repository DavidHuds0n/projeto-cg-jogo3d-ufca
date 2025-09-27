/**
 * @file Game.h
 * @brief Define a classe principal Game, que orquestra todo o loop e a l�gica do jogo.
 */
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Level.h"
#include "LightManager.h"
#include "Creature.h"

/**
 * @enum GameState
 * @brief Define os poss�veis estados globais do jogo.
 */
enum GameState {
    PLAYING,    ///< O jogo est� em andamento normal.
    GAME_OVER,  ///< O jogador perdeu.
    WIN         ///< O jogador venceu.
};

/**
 * @class Game
 * @brief A classe central que gerencia todos os subsistemas do jogo.
 *
 * Esta classe � respons�vel pelo loop principal (update/render), gerenciamento de estado
 * (PLAYING, GAME_OVER), e pela inicializa��o e comunica��o entre todos os outros
 * objetos do jogo (Player, Level, Creature, etc).
 */
class Game {
public:
    /**
     * @brief Construtor da classe Game.
     */
    Game();

    /**
     * @brief Inicializa todos os componentes do jogo (jogador, n�vel, luzes, etc).
     */
    void init();

    /**
     * @brief Renderiza um �nico quadro (frame) do jogo.
     */
    void render();

    /**
     * @brief Atualiza a l�gica do jogo com base no tempo decorrido.
     * @param [in] deltaTime O tempo (em segundos) desde o �ltimo quadro.
     */
    void update(float deltaTime);

    /**
     * @brief Processa o evento de uma tecla ser pressionada.
     * @param [in] key A tecla pressionada.
     * @param [in] x A coordenada X do mouse no momento do evento.
     * @param [in] y A coordenada Y do mouse no momento do evento.
     */
    void processKeyDown(unsigned char key, int x, int y);

    /**
     * @brief Processa o evento de uma tecla ser solta.
     * @param [in] key A tecla solta.
     * @param [in] x A coordenada X do mouse no momento do evento.
     * @param [in] y A coordenada Y do mouse no momento do evento.
     */
    void processKeyUp(unsigned char key, int x, int y);

    /**
     * @brief Processa o movimento do mouse.
     * @param [in] x A nova coordenada X do mouse.
     * @param [in] y A nova coordenada Y do mouse.
     */
    void processMouseMotion(int x, int y);

private:
    // --- Fun��es de gerenciamento de estado (Tarefa da Pessoa 4) ---

    /**
     * @brief Reinicia o jogo para o seu estado inicial.
     */
    void resetGame();

    /**
     * @brief Verifica e processa colis�es entre entidades (jogador, criatura, paredes).
     */
    void checkCollisions();

    /**
     * @brief Desenha a Interface do Usu�rio (HUD), como vida, muni��o, etc.
     */
    void drawHUD();

    GameState currentState;   ///< O estado atual do jogo (PLAYING, GAME_OVER, etc).
    Player player;            ///< Inst�ncia do jogador.
    Level level;              ///< Inst�ncia do n�vel/labirinto.
    LightManager lightManager;///< Inst�ncia do gerenciador de luz.
    Creature creature;        ///< Inst�ncia da criatura inimiga.
};

#endif // GAME_H
