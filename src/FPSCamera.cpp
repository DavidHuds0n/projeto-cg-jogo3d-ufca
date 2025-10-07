/**
 * @file FPSCamera.cpp
 * @brief Implementa��o da classe FPSCamera, respons�vel por gerenciar a visualiza��o do jogador em primeira pessoa.
 */

#include "../include/FPSCamera.h"
#include <GL/freeglut.h>
#include <cmath> // Para sin, cos
#include "../include/Config.h"

// --- Constantes ---
/**
 * @brief Fator de convers�o de graus para radianos.
 */
const float PI = 3.1415926535f;
const float toRadians = PI / 180.0f;

// --- Implementa��o da Classe ---

/**
 * @brief Construtor padr�o da classe FPSCamera.
 *
 * Inicializa a c�mera com uma posi��o padr�o, define o vetor 'up' do mundo
 * e os �ngulos de rota��o iniciais (yaw e pitch). Em seguida, calcula os
 * vetores de dire��o da c�mera com base nesses �ngulos.
 */
FPSCamera::FPSCamera() {
    // Posi��o inicial padr�o da c�mera.
    _position = {0.0f, 1.0f, 5.0f};
    // O vetor 'para cima' do mundo � fixo (eixo Y positivo).
    _worldUp = {0.0f, 1.0f, 0.0f};
    // Yaw inicial aponta para a frente (ao longo do eixo Z negativo).
    _yaw = -90.0f;
    // Pitch inicial � reto, sem olhar para cima ou para baixo.
    _pitch = 0.0f;
    _mouseSensitivity = Config::CAMERA_SENSITIVITY;

    // Calcula os vetores iniciais (_front, _right, _up) com base nos �ngulos.
    updateCameraVectors();
}

/**
 * @brief Define a posi��o da c�mera.
 * @param pos A nova posi��o da c�mera no espa�o 3D.
 */
void FPSCamera::setPosition(const Vector3f& pos) {
    _position = pos;
}

/**
 * @brief Obt�m a posi��o atual da c�mera.
 * @return Uma refer�ncia constante para o vetor de posi��o.
 */
const Vector3f& FPSCamera::getPosition() const {
    return _position;
}
/**
 * @brief Obt�m o vetor de dire��o frontal da c�mera.
 * @return Uma refer�ncia constante para o vetor frontal.
 */
const Vector3f& FPSCamera::getFrontVector() const {
    return _front;
}
/**
 * @brief Obt�m o vetor de dire��o lateral (direita) da c�mera.
 * @return Uma refer�ncia constante para o vetor lateral.
 */
const Vector3f& FPSCamera::getRightVector() const {
    return _right;
}

/**
 * @brief Aplica as transforma��es de visualiza��o do OpenGL.
 *
 * Este m�todo usa a fun��o `gluLookAt` para posicionar e orientar
 * a "c�mera" da cena com base na posi��o e nos vetores de dire��o.
 */
void FPSCamera::updateView() {
    gluLookAt(
        _position.x, _position.y, _position.z,                                   // Posi��o da c�mera (eye)
        _position.x + _front.x, _position.y + _front.y, _position.z + _front.z,  // Ponto para onde olhamos (center)
        _up.x, _up.y, _up.z                                                      // Vetor 'up' da c�mera
    );
}

/**
 * @brief Processa o movimento do mouse para rotacionar a c�mera.
 *
 * Calcula o deslocamento do mouse e atualiza os �ngulos de yaw (rota��o horizontal)
 * e pitch (rota��o vertical). O �ngulo de pitch � limitado para evitar
 * rota��es problem�ticas.
 *
 * @param x A coordenada X do cursor.
 * @param y A coordenada Y do cursor.
 */
void FPSCamera::processMouseMotion(int x, int y) {
    // Calcula o quanto o mouse se moveu desde o �ltimo frame.
    // O ponto de refer�ncia � sempre o centro da tela.
    float xoffset = (float)(x - Config::SCREEN_WIDTH / 2);
    // A coordenada Y � invertida (em janelas, Y cresce para baixo).
    float yoffset = (float)(Config::SCREEN_HEIGHT / 2 - y);

    // Aplica a sensibilidade para controlar a velocidade da rota��o.
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    // Atualiza os �ngulos de rota��o horizontal (yaw) e vertical (pitch).
    _yaw += xoffset;
    _pitch += yoffset;

    // Limita o �ngulo vertical (pitch) para evitar que a c�mera "vire de cabe�a para baixo".
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    // Com os �ngulos atualizados, recalcula todos os vetores de dire��o.
    updateCameraVectors();
}

/**
 * @brief Recalcula os vetores de dire��o da c�mera.
 *
 * Este m�todo converte os �ngulos de yaw e pitch em vetores 3D normalizados
 * para frente (`_front`), para a direita (`_right`) e para cima (`_up`).
 * Isso � feito usando fun��es trigonom�tricas e o produto vetorial (cross product).
 */
void FPSCamera::updateCameraVectors() {
    // Converte os �ngulos de Euler (yaw e pitch) em um vetor de dire��o 3D.
    Vector3f front;
    front.x = cos(_yaw * toRadians) * cos(_pitch * toRadians);
    front.y = sin(_pitch * toRadians);
    front.z = sin(_yaw * toRadians) * cos(_pitch * toRadians);

    // Normaliza o vetor 'front' para garantir que seu comprimento seja 1.
    float length = sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
    _front = {front.x / length, front.y / length, front.z / length};

    // Recalcula o vetor 'right' usando o Produto Vetorial (Cross Product).
    _right.x = _front.y * _worldUp.z - _front.z * _worldUp.y;
    _right.y = _front.z * _worldUp.x - _front.x * _worldUp.z;
    _right.z = _front.x * _worldUp.y - _front.y * _worldUp.x;
    length = sqrt(_right.x * _right.x + _right.y * _right.y + _right.z * _right.z);
    _right = {_right.x / length, _right.y / length, _right.z / length};

    // Recalcula o vetor 'up' da c�mera usando o produto vetorial entre 'right' e 'front'.
    _up.x = _right.y * _front.z - _right.z * _front.y;
    _up.y = _right.z * _front.x - _right.x * _front.z;
    _up.z = _right.x * _front.y - _right.y * _front.x;
}
