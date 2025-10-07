/**
 * @file Player.cpp
 * @brief Implementa��o da classe Player, que representa o jogador e sua intera��o com o ambiente.
 */

#include "../include/Player.h"
#include <cmath>
#include "../include/Config.h"
#include <vector>
#include "../include/GameObject.h"
#include "../include/Wall.h"

/**
 * @brief Verifica a colis�o entre duas caixas delimitadoras (Bounding Boxes).
 * @param a A primeira BoundingBox.
 * @param b A segunda BoundingBox.
 * @return Retorna 'true' se as caixas se sobrep�em, 'false' caso contr�rio.
 */
bool checkCollision(const BoundingBox& a, const BoundingBox& b) {
    return (a.min.x < b.max.x && a.max.x > b.min.x) &&
           (a.min.y < b.max.y && a.max.y > b.min.y) &&
           (a.min.z < b.max.z && a.max.z > b.min.z);
}

/**
 * @brief Construtor padr�o da classe Player.
 *
 * Inicializa a posi��o do jogador, sua velocidade de movimento, raio de colis�o e
 * o estado de suas teclas de movimento. A c�mera � sincronizada com a posi��o inicial.
 */
Player::Player() {
    // Voltamos a definir a altura da vis�o diretamente em _position.y
    _position = {0.0f, 1.6f, 3.0f};

    _movementSpeed = Config::PLAYER_SPEED;
    _collisionRadius = Config::PLAYER_COLLISION_RADIUS;

    _keyState['w'] = false;
    _keyState['a'] = false;
    _keyState['s'] = false;
    _keyState['d'] = false;
    _keyState['e'] = false;

    // A c�mera come�a na mesma posi��o que o jogador.
    _camera.setPosition(_position);
}

// M�todos de Input
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
 * @brief Lida com o movimento do mouse para controlar a c�mera.
 * @param x A coordenada x do mouse.
 * @param y A coordenada y do mouse.
 */
void Player::handleMouseMotion(int x, int y) { _camera.processMouseMotion(x, y); }

/**
 * @brief Define a posi��o do jogador e sincroniza a c�mera.
 * @param pos A nova posi��o do jogador.
 */
void Player::setPosition(const Vector3f& pos) {
    _position = pos;
    _camera.setPosition(_position);
}

/**
 * @brief Obt�m a Bounding Box (caixa delimitadora) do jogador.
 *
 * A caixa de colis�o � uma caixa que representa a �rea do jogador, usada para
 * detec��o de colis�o.
 *
 * @return Um objeto BoundingBox que representa a �rea de colis�o do jogador.
 */
BoundingBox Player::getBoundingBox() const {
    BoundingBox box;
    // Caixa de colis�o centrada na altura do jogador
    box.min = { _position.x - _collisionRadius, _position.y - 1.0f, _position.z - _collisionRadius };
    box.max = { _position.x + _collisionRadius, _position.y + 1.0f, _position.z + _collisionRadius };
    return box;
}

/**
 * @brief Obt�m a inst�ncia da c�mera do jogador.
 * @return Uma refer�ncia para o objeto FPSCamera.
 */
FPSCamera& Player::getCamera() {
    return _camera;
}

/**
 * @brief Atualiza a posi��o do jogador e lida com as colis�es.
 *
 * O m�todo calcula a dire��o do movimento com base nas teclas pressionadas.
 * Em seguida, ele move o jogador e, para cada objeto na cena, verifica se houve
 * uma colis�o. Se uma colis�o com uma parede for detectada, o movimento
 * correspondente � revertido.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
 * @param objects Uma lista de objetos do jogo para verificar a colis�o.
 * @param gameStateManager O gerenciador de estado do jogo (n�o usado nesta implementa��o).
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

    // Sincroniza a c�mera com a posi��o final e segura do jogador
    _camera.setPosition(_position);
}
