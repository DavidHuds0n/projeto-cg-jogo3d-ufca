#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"

class Player {
public:
    Player();

    // M�todos para a Pessoa 2 implementar
    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    void update(float deltaTime); // Atualiza posi��o baseado no input e colis�o
    void render();                // Desenha o jogador (se necess�rio)

    FPSCamera& getCamera();       // M�todo para a classe Game acessar a c�mera

private:
    FPSCamera camera;
    // Posi��o, velocidade, AABB para colis�o, etc.
};

#endif
