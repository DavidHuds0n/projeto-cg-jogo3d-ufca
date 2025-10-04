#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"
#include <vector>
#include "../include/GameObject.h"
#include "../include/Wall.h" // Precisa saber o que � uma Wall para testar

// Fun��o auxiliar que verifica se duas caixas de colis�o se sobrep�em
bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.min.x < b.max.x && a.max.x > b.min.x) &&
           (a.min.y < b.max.y && a.max.y > b.min.y) &&
           (a.min.z < b.max.z && a.max.z > b.min.z);
}

// Construtor
Player::Player() {
    // Define a posi��o inicial do jogador e seus atributos de jogabilidade.
    // ATUALIZA��O AQUI: Aumentamos a altura do jogador.
    _position = {0.0f, 1.6f, 5.0f}; // Posi��o inicial (x, y, z) - Y alterado de 1.0 para 1.6

    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    // Inicializa o estado de todas as teclas de movimento como 'false' (n�o pressionadas).
    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;
    _keyState['e'] = false;

    // A c�mera come�a na mesma posi��o que o jogador.
    _camera.setPosition(_position);
}

// M�todos de Input
void Player::handleKeyDown(unsigned char key) { _keyState[key] = true; }
void Player::handleKeyUp(unsigned char key) { _keyState[key] = false; }
void Player::handleMouseMotion(int x, int y) { _camera.processMouseMotion(x, y); }

// M�todo para definir a posi��o
void Player::setPosition(const Vector3f& pos) {
    _position = pos;
    _camera.setPosition(_position);
}

// M�todo para obter a caixa de colis�o do jogador
BoundingBox Player::getBoundingBox() const {
    BoundingBox box;
    box.min = { _position.x - _collisionRadius, _position.y - 1.0f, _position.z - _collisionRadius };
    box.max = { _position.x + _collisionRadius, _position.y + 1.0f, _position.z + _collisionRadius };
    return box;
}

// Getter para a c�mera
FPSCamera& Player::getCamera() {
    return _camera;
}

// M�TODO UPDATE COM L�GICA DE COLIS�O
void Player::update(float deltaTime, const std::vector<GameObject*>& objects, GameStateManager& gameStateManager) {
    float dtSeconds = deltaTime / 1000.0f;
    float velocity = _movementSpeed * dtSeconds;

    Vector3f front = _camera.getFrontVector();
    Vector3f right = _camera.getRightVector();
    Vector3f moveFront = {front.x, 0.0f, front.z};

    float frontLength = sqrt(moveFront.x * moveFront.x + moveFront.z * moveFront.z);
    if (frontLength > 0) {
        moveFront.x /= frontLength;
        moveFront.z /= frontLength;
    }

    Vector3f moveDirection = {0.0f, 0.0f, 0.0f};
    if (_keyState['w']) { moveDirection.x += moveFront.x; moveDirection.z += moveFront.z; }
    if (_keyState['s']) { moveDirection.x -= moveFront.x; moveDirection.z -= moveFront.z; }
    if (_keyState['a']) { moveDirection.x -= right.x; moveDirection.z -= right.z; }
    if (_keyState['d']) { moveDirection.x += right.x; moveDirection.z += right.z; }

    float dirLength = sqrt(moveDirection.x * moveDirection.x + moveDirection.z * moveDirection.z);
    if (dirLength > 0) {
        moveDirection.x /= dirLength;
        moveDirection.z /= dirLength;

        // --- L�GICA DE COLIS�O ---

        // 1. Tenta mover no eixo X
        Vector3f originalPosition = _position;
        _position.x += moveDirection.x * velocity;

        for (const auto* obj : objects) {
            const Wall* wall = dynamic_cast<const Wall*>(obj);
            if (wall) { // S� colidimos com paredes
                if (checkCollision(getBoundingBox(), wall->getBoundingBox())) {
                    _position.x = originalPosition.x; // Colidiu, desfaz o movimento em X
                    break;
                }
            }
        }

        // 2. Tenta mover no eixo Z
        _position.z += moveDirection.z * velocity;

        for (const auto* obj : objects) {
            const Wall* wall = dynamic_cast<const Wall*>(obj);
            if (wall) {
                if (checkCollision(getBoundingBox(), wall->getBoundingBox())) {
                    _position.z = originalPosition.z; // Colidiu, desfaz o movimento em Z
                    break;
                }
            }
        }
    }

    // Sincroniza a c�mera com a posi��o final e segura do jogador
    _camera.setPosition(_position);
}
