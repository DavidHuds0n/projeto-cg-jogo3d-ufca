#include "../include/Player.h"

Player::Player() {
    // Construtor inicializa a posi��o do jogador, etc.
}

void Player::handleKeyDown(unsigned char key) { /* Implementa��o da Pessoa 2 */ }
void Player::handleKeyUp(unsigned char key) { /* Implementa��o da Pessoa 2 */ }
void Player::handleMouseMotion(int x, int y) {
    camera.processMouseMotion(x, y);
}

void Player::update(float deltaTime) { /* Implementa��o da Pessoa 2 */ }
void Player::render() { /* Implementa��o da Pessoa 2 */ }

FPSCamera& Player::getCamera() {
    return camera;
}
