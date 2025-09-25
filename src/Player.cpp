#include "../include/Player.h"

Player::Player() {
    // Construtor inicializa a posição do jogador, etc.
}

void Player::handleKeyDown(unsigned char key) { /* Implementação da Pessoa 2 */ }
void Player::handleKeyUp(unsigned char key) { /* Implementação da Pessoa 2 */ }
void Player::handleMouseMotion(int x, int y) {
    camera.processMouseMotion(x, y);
}

void Player::update(float deltaTime) { /* Implementação da Pessoa 2 */ }
void Player::render() { /* Implementação da Pessoa 2 */ }

FPSCamera& Player::getCamera() {
    return camera;
}
