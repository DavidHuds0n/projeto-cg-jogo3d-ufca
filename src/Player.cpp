#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"

Player::Player() {
    _position = {0.0f, 1.0f, 5.0f};
    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    // Inicializa o estado de todas as teclas como 'false' (não pressionadas)
    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;

    _camera.setPosition(_position);
}

void Player::handleKeyDown(unsigned char key) {
    // Quando uma tecla é pressionada, atualiza seu estado no mapa
    _keyState[key] = true;
}

void Player::handleKeyUp(unsigned char key) {
    // Quando uma tecla é solta, atualiza seu estado
    _keyState[key] = false;
}

void Player::handleMouseMotion(int x, int y) {
    // Repassa o movimento do mouse para a câmera
    _camera.processMouseMotion(x, y);
}

void Player::update(float deltaTime) {
    // Converte o deltaTime de milissegundos para segundos
    float dtSeconds = deltaTime / 1000.0f;
    float velocity = _movementSpeed * dtSeconds;

    // Pega os vetores da câmera para o movimento
    Vector3f front = _camera.getFrontVector();
    Vector3f right = _camera.getRightVector();

    // Para o movimento de "andar", ignoramos a componente Y do vetor 'front'
    // Isso impede que o jogador voe para cima ao olhar para cima
    Vector3f moveFront = {front.x, 0.0f, front.z};
    // Normaliza para manter a velocidade constante
    float length = sqrt(moveFront.x * moveFront.x + moveFront.z * moveFront.z);
    if (length > 0) {
        moveFront = {moveFront.x / length, 0.0f, moveFront.z / length};
    }

    // Atualiza a posição com base nas teclas pressionadas
    if (_keyState['w']) {
        _position.x += moveFront.x * velocity;
        _position.z += moveFront.z * velocity;
    }
    if (_keyState['s']) {
        _position.x -= moveFront.x * velocity;
        _position.z -= moveFront.z * velocity;
    }
    if (_keyState['a']) {
        _position.x -= right.x * velocity;
        _position.z -= right.z * velocity;
    }
    if (_keyState['d']) {
        _position.x += right.x * velocity;
        _position.z += right.z * velocity;
    }

    // Sincroniza a posição da câmera com a nova posição do jogador
    _camera.setPosition(_position);
}

FPSCamera& Player::getCamera() {
    return _camera;
}
