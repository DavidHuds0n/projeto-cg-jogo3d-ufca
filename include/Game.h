// include/Game.h
#ifndef GAME_H
#define GAME_H

// Nossos novos includes
#include "Player.h"
#include "Level.h"
#include "LightManager.h"

enum GameState {
    PLAYING,
    GAME_OVER,
    WIN
};

class Game {
public:
    Game();
    void init();
    void render();
    void update(float deltaTime);
    void processKeyDown(unsigned char key, int x, int y);
    void processKeyUp(unsigned char key, int x, int y);
    void processMouseMotion(int x, int y);

private:
    GameState currentState;

    // --- ARQUITETURA COMPLETA ---
    // Agora temos instâncias de todas as nossas classes principais.
    Player player;
    Level level;
    LightManager lightManager;
};

#endif // GAME_H
