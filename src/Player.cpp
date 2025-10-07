/**
 * @file Player.cpp
 * @brief Implementação da classe Player, que representa o jogador e sua interação com o ambiente.
 */

#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"
#include <vector>
#include "../include/GameObject.h"
#include "../include/Wall.h"

/**
 * @brief Verifica a colisão entre duas caixas delimitadoras (Bounding Boxes).
 * @param a A primeira BoundingBox.
 * @param b A segunda BoundingBox.
 * @return Retorna 'true' se as caixas se sobrepõem, 'false' caso contrário.
 */
bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.min.x < b.max.x && a.max.x > b.min.x) &&
           (a.min.y < b.max.y && a.max.y > b.min.y) &&
           (a.min.z < b.max.z && a.max.z > b.min.z);
}

/**
 * @brief Construtor padrão da classe Player.
 *
 * Inicializa a posição do jogador, sua velocidade de movimento, raio de colisão e
 * o estado de suas teclas de movimento. A câmera é sincronizada com a posição inicial.
 */
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

// Métodos de Input
/**
 * @brief Lida com o evento de uma tecla ser pressionada.
 * @param key O caractere da tecla pressionada.
 */
void Player::handleKeyDown(unsigned char key) { _keyState[key] = true; }
/**
 * @brief Lida com o evento de uma tecla ser liberada.
 * @param key O caractere da tecla liberada.
 */
void Player::handleKeyUp(unsigned char key) { _keyState[key] = false; }
/**
 * @brief Lida com o movimento do mouse para controlar a câmera.
 * @param x A coordenada x do mouse.
 * @param y A coordenada y do mouse.
 */
void Player::handleMouseMotion(int x, int y) { _camera.processMouseMotion(x, y); }

/**
 * @brief Define a posição do jogador e sincroniza a câmera.
 * @param pos A nova posição do jogador.
 */
void Player::setPosition(const Vector3f& pos) {
    _position = pos;
    _camera.setPosition(_position);
}

/**
 * @brief Obtém a Bounding Box (caixa delimitadora) do jogador.
 *
 * A caixa de colisão é uma caixa que representa a área do jogador, usada para
 * detecção de colisão.
 *
 * @return Um objeto BoundingBox que representa a área de colisão do jogador.
 */
BoundingBox Player::getBoundingBox() const {
    BoundingBox box;
    // Caixa de colisão centrada na altura do jogador
    box.min = { _position.x - _collisionRadius, _position.y - 1.0f, _position.z - _collisionRadius };
    box.max = { _position.x + _collisionRadius, _position.y + 1.0f, _position.z + _collisionRadius };
    return box;
}

/**
 * @brief Obtém a instância da câmera do jogador.
 * @return Uma referência para o objeto FPSCamera.
 */
FPSCamera& Player::getCamera() {
    return _camera;
}

/**
 * @brief Atualiza a posição do jogador e lida com as colisões.
 *
 * O método calcula a direção do movimento com base nas teclas pressionadas.
 * Em seguida, ele move o jogador e, para cada objeto na cena, verifica se houve
 * uma colisão. Se uma colisão com uma parede for detectada, o movimento
 * correspondente é revertido.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param objects Uma lista de objetos do jogo para verificar a colisão.
 * @param gameStateManager O gerenciador de estado do jogo (não usado nesta implementação).
 */
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
