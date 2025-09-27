/**
 * @file Player.cpp
 * @brief Implementação da classe Player.
 */
#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"

Player::Player() {
    // Define a posição inicial do jogador e seus atributos de jogabilidade.
    _position = {0.0f, 1.0f, 5.0f}; // Posição inicial (x, y, z)
    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    // Inicializa o estado de todas as teclas de movimento como 'false' (não pressionadas).
    // Isso evita que o jogador se mova sem ter pressionado nada.
    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;

    // A câmera começa na mesma posição que o jogador.
    _camera.setPosition(_position);
}

void Player::handleKeyDown(unsigned char key) {
    // Quando uma tecla é pressionada, marca seu estado como 'true' no mapa.
    // A função update() usará essa informação para mover o jogador.
    _keyState[key] = true;
}

void Player::handleKeyUp(unsigned char key) {
    // Quando uma tecla é solta, reverte o estado para 'false'.
    _keyState[key] = false;
}

void Player::handleMouseMotion(int x, int y) {
    // A classe Player não lida com a rotação diretamente, ela apenas
    // repassa a informação de movimento do mouse para a câmera.
    _camera.processMouseMotion(x, y);
}

void Player::update(float deltaTime) {
    // --- Lógica de Movimento ---

    // Converte o deltaTime (geralmente em milissegundos) para segundos para consistência nos cálculos.
    float dtSeconds = deltaTime / 1000.0f;
    // Calcula a distância que o jogador se moverá neste frame.
    float velocity = _movementSpeed * dtSeconds;

    // Pega os vetores de direção da câmera. Eles nos dizem para onde é "frente" e "direita".
    Vector3f front = _camera.getFrontVector();
    Vector3f right = _camera.getRightVector();

    // --- Prevenção de Voo ---
    // Para o movimento de "andar", nós queremos ignorar a componente Y do vetor 'front'.
    // Se não fizéssemos isso, o jogador se moveria para cima (voaria) ao olhar para cima.
    Vector3f moveFront = {front.x, 0.0f, front.z};

    // Normalizamos o vetor de movimento 'moveFront' para manter a velocidade constante.
    // Sem isso, o jogador andaria mais devagar ao olhar para cima ou para baixo.
    float length = sqrt(moveFront.x * moveFront.x + moveFront.z * moveFront.z);
    if (length > 0) {
        moveFront = {moveFront.x / length, 0.0f, moveFront.z / length};
    }

    // Atualiza a posição do jogador com base em quais teclas estão pressionadas.
    if (_keyState['w']) { // Mover para frente
        _position.x += moveFront.x * velocity;
        _position.z += moveFront.z * velocity;
    }
    if (_keyState['s']) { // Mover para trás
        _position.x -= moveFront.x * velocity;
        _position.z -= moveFront.z * velocity;
    }
    if (_keyState['a']) { // Mover para a esquerda (strafe)
        _position.x -= right.x * velocity;
        _position.z -= right.z * velocity;
    }
    if (_keyState['d']) { // Mover para a direita (strafe)
        _position.x += right.x * velocity;
        _position.z += right.z * velocity;
    }

    // Sincroniza a posição da câmera com a nova posição do jogador.
    // Isso garante que a "visão" acompanhe o "corpo" do jogador.
    _camera.setPosition(_position);
}

FPSCamera& Player::getCamera() {
    return _camera;
}
