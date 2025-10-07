#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"
#include <vector>
#include "../include/GameObject.h"
#include "../include/Wall.h"

bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.min.x < b.max.x && a.max.x > b.min.x) &&
           (a.min.y < b.max.y && a.max.y > b.min.y) &&
           (a.min.z < b.max.z && a.max.z > b.min.z);
}

// Construtor Revertido
Player::Player() {
    // Voltamos a definir a altura da visão diretamente em _position.y
    _position = {0.0f, 1.6f, 3.0f};

    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;
    _keyState['e'] = false;

    // A câmera começa na mesma posição que o jogador.
    _camera.setPosition(_position);
}

// Métodos de Input (sem alterações)
void Player::handleKeyDown(unsigned char key) { _keyState[key] = true; }
void Player::handleKeyUp(unsigned char key) { _keyState[key] = false; }
void Player::handleMouseMotion(int x, int y) { _camera.processMouseMotion(x, y); }

// setPosition Revertido
void Player::setPosition(const Vector3f& pos) {
    _position = pos;
    _camera.setPosition(_position);
}

// getBoundingBox Revertido para uma lógica mais simples
BoundingBox Player::getBoundingBox() const {
    BoundingBox box;
    // Caixa de colisão centrada na altura do jogador
    box.min = { _position.x - _collisionRadius, _position.y - 1.0f, _position.z - _collisionRadius };
    box.max = { _position.x + _collisionRadius, _position.y + 1.0f, _position.z + _collisionRadius };
    return box;
}

// Getter para a câmera (sem alterações)
FPSCamera& Player::getCamera() {
    return _camera;
}

// MÉTODO UPDATE Revertido
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

        Vector3f originalPosition = _position;
        _position.x += moveDirection.x * velocity;

        for (const auto* obj : objects) {
            const Wall* wall = dynamic_cast<const Wall*>(obj);
            if (wall && checkCollision(getBoundingBox(), wall->getBoundingBox())) {
                _position.x = originalPosition.x;
                break;
            }
        }

        _position.z += moveDirection.z * velocity;

        for (const auto* obj : objects) {
            const Wall* wall = dynamic_cast<const Wall*>(obj);
            if (wall && checkCollision(getBoundingBox(), wall->getBoundingBox())) {
                _position.z = originalPosition.z;
                break;
            }
        }
    }

    // Sincroniza a câmera com a posição final e segura do jogador
    _camera.setPosition(_position);
}
