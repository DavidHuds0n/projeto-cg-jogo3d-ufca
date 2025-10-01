/**
 * @file Player.cpp
 * @brief Implementa��o da classe Player.
 */
#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"

Player::Player() {
    // Define a posi��o inicial do jogador e seus atributos de jogabilidade.
    _position = {0.0f, 1.0f, 5.0f}; // Posi��o inicial (x, y, z)
    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    // Inicializa o estado de todas as teclas de movimento como 'false' (n�o pressionadas).
    // Isso evita que o jogador se mova sem ter pressionado nada.
    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;
    _keyState['e'] = false;

    // A c�mera come�a na mesma posi��o que o jogador.
    _camera.setPosition(_position);
}

void Player::handleKeyDown(unsigned char key) {
    // Quando uma tecla � pressionada, marca seu estado como 'true' no mapa.
    // A fun��o update() usar� essa informa��o para mover o jogador.
    _keyState[key] = true;
}

void Player::handleKeyUp(unsigned char key) {
    // Quando uma tecla � solta, reverte o estado para 'false'.
    _keyState[key] = false;
}

void Player::handleMouseMotion(int x, int y) {
    // A classe Player n�o lida com a rota��o diretamente, ela apenas
    // repassa a informa��o de movimento do mouse para a c�mera.
    _camera.processMouseMotion(x, y);
}

void Player::update(float deltaTime) {
    // --- L�gica de Movimento ---
    float dtSeconds = deltaTime / 1000.0f;
    float velocity = _movementSpeed * dtSeconds;

    Vector3f front = _camera.getFrontVector();
    Vector3f right = _camera.getRightVector();

    // Preven��o de Voo (mant�m o movimento no plano XZ)
    Vector3f moveFront = {front.x, 0.0f, front.z};

    // Normaliza o vetor 'moveFront' para manter a velocidade constante ao olhar para cima/baixo.
    float frontLength = sqrt(moveFront.x * moveFront.x + moveFront.z * moveFront.z);
    if (frontLength > 0) {
        moveFront.x /= frontLength;
        moveFront.z /= frontLength;
    }

    // --- CORRE��O AQUI: Combina os inputs antes de mover ---

    // 1. Cria um vetor de dire��o zerado.
    Vector3f moveDirection = {0.0f, 0.0f, 0.0f};

    // 2. Soma as dire��es com base nas teclas pressionadas.
    if (_keyState['w']) {
        moveDirection.x += moveFront.x;
        moveDirection.z += moveFront.z;
    }
    if (_keyState['s']) {
        moveDirection.x -= moveFront.x;
        moveDirection.z -= moveFront.z;
    }
    if (_keyState['a']) {
        moveDirection.x -= right.x;
        moveDirection.z -= right.z;
    }
    if (_keyState['d']) {
        moveDirection.x += right.x;
        moveDirection.z += right.z;
    }

    // 3. Normaliza o vetor de dire��o final (se ele n�o for zero).
    float dirLength = sqrt(moveDirection.x * moveDirection.x + moveDirection.z * moveDirection.z);
    if (dirLength > 0) {
        // Normaliza o vetor para que seu comprimento seja 1.
        moveDirection.x /= dirLength;
        moveDirection.z /= dirLength;

        // 4. Aplica o movimento usando o vetor normalizado.
        _position.x += moveDirection.x * velocity;
        _position.z += moveDirection.z * velocity;
    }

    // Sincroniza a posi��o da c�mera com a nova posi��o do jogador.
    _camera.setPosition(_position);
}

FPSCamera& Player::getCamera() {
    return _camera;
}
