#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"

class Player {
public:
    Player();

    // Métodos para a Pessoa 2 implementar
    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    void update(float deltaTime); // Atualiza posição baseado no input e colisão
    void render();                // Desenha o jogador (se necessário)

    FPSCamera& getCamera();       // Método para a classe Game acessar a câmera

private:
    FPSCamera camera;
    // Posição, velocidade, AABB para colisão, etc.
};

#endif
