#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"

// Usado para rastrear o estado das teclas de movimento
#include <map>

class Player {
public:
    Player();

    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    // Atualiza a posição do jogador com base no input
    void update(float deltaTime);

    FPSCamera& getCamera();

private:
    Vector3f _position;
    FPSCamera _camera;
    float _movementSpeed;

    // Mapa para guardar o estado das teclas (true = pressionada, false = solta)
    std::map<unsigned char, bool> _keyState;
};

#endif
