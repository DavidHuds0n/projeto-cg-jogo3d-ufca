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

    // Converte o deltaTime (geralmente em milissegundos) para segundos para consist�ncia nos c�lculos.
    float dtSeconds = deltaTime / 1000.0f;
    // Calcula a dist�ncia que o jogador se mover� neste frame.
    float velocity = _movementSpeed * dtSeconds;

    // Pega os vetores de dire��o da c�mera. Eles nos dizem para onde � "frente" e "direita".
    Vector3f front = _camera.getFrontVector();
    Vector3f right = _camera.getRightVector();

    // --- Preven��o de Voo ---
    // Para o movimento de "andar", n�s queremos ignorar a componente Y do vetor 'front'.
    // Se n�o fiz�ssemos isso, o jogador se moveria para cima (voaria) ao olhar para cima.
    Vector3f moveFront = {front.x, 0.0f, front.z};

    // Normalizamos o vetor de movimento 'moveFront' para manter a velocidade constante.
    // Sem isso, o jogador andaria mais devagar ao olhar para cima ou para baixo.
    float length = sqrt(moveFront.x * moveFront.x + moveFront.z * moveFront.z);
    if (length > 0) {
        moveFront = {moveFront.x / length, 0.0f, moveFront.z / length};
    }

    // Atualiza a posi��o do jogador com base em quais teclas est�o pressionadas.
    if (_keyState['w']) { // Mover para frente
        _position.x += moveFront.x * velocity;
        _position.z += moveFront.z * velocity;
    }
    if (_keyState['s']) { // Mover para tr�s
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

    // Sincroniza a posi��o da c�mera com a nova posi��o do jogador.
    // Isso garante que a "vis�o" acompanhe o "corpo" do jogador.
    _camera.setPosition(_position);
}

FPSCamera& Player::getCamera() {
    return _camera;
}
