/**
 * @file FPSCamera.cpp
 * @brief Implementação da classe FPSCamera, responsável por gerenciar a visualização do jogador em primeira pessoa.
 */

#include "../include/FPSCamera.h"
#include <GL/freeglut.h>
#include <cmath> // Para sin, cos
#include "../include/Config.h"

// --- Constantes ---
/**
 * @brief Fator de conversão de graus para radianos.
 */
const float PI = 3.1415926535f;
const float toRadians = PI / 180.0f;

// --- Implementação da Classe ---

/**
 * @brief Construtor padrão da classe FPSCamera.
 *
 * Inicializa a câmera com uma posição padrão, define o vetor 'up' do mundo
 * e os ângulos de rotação iniciais (yaw e pitch). Em seguida, calcula os
 * vetores de direção da câmera com base nesses ângulos.
 */
FPSCamera::FPSCamera() {
    // Posição inicial padrão da câmera.
    _position = {0.0f, 1.0f, 5.0f};
    // O vetor 'para cima' do mundo é fixo (eixo Y positivo).
    _worldUp = {0.0f, 1.0f, 0.0f};
    // Yaw inicial aponta para a frente (ao longo do eixo Z negativo).
    _yaw = -90.0f;
    // Pitch inicial é reto, sem olhar para cima ou para baixo.
    _pitch = 0.0f;
    _mouseSensitivity = Config::CAMERA_SENSITIVITY;

    // Calcula os vetores iniciais (_front, _right, _up) com base nos ângulos.
    updateCameraVectors();
}

/**
 * @brief Define a posição da câmera.
 * @param pos A nova posição da câmera no espaço 3D.
 */
void FPSCamera::setPosition(const Vector3f& pos) {
    _position = pos;
}

/**
 * @brief Obtém a posição atual da câmera.
 * @return Uma referência constante para o vetor de posição.
 */
const Vector3f& FPSCamera::getPosition() const {
    return _position;
}
/**
 * @brief Obtém o vetor de direção frontal da câmera.
 * @return Uma referência constante para o vetor frontal.
 */
const Vector3f& FPSCamera::getFrontVector() const {
    return _front;
}
/**
 * @brief Obtém o vetor de direção lateral (direita) da câmera.
 * @return Uma referência constante para o vetor lateral.
 */
const Vector3f& FPSCamera::getRightVector() const {
    return _right;
}

/**
 * @brief Aplica as transformações de visualização do OpenGL.
 *
 * Este método usa a função `gluLookAt` para posicionar e orientar
 * a "câmera" da cena com base na posição e nos vetores de direção.
 */
void FPSCamera::updateView() {
    gluLookAt(
        _position.x, _position.y, _position.z,                                   // Posição da câmera (eye)
        _position.x + _front.x, _position.y + _front.y, _position.z + _front.z,  // Ponto para onde olhamos (center)
        _up.x, _up.y, _up.z                                                      // Vetor 'up' da câmera
    );
}

/**
 * @brief Processa o movimento do mouse para rotacionar a câmera.
 *
 * Calcula o deslocamento do mouse e atualiza os ângulos de yaw (rotação horizontal)
 * e pitch (rotação vertical). O ângulo de pitch é limitado para evitar
 * rotações problemáticas.
 *
 * @param x A coordenada X do cursor.
 * @param y A coordenada Y do cursor.
 */
void FPSCamera::processMouseMotion(int x, int y) {
    // Calcula o quanto o mouse se moveu desde o último frame.
    // O ponto de referência é sempre o centro da tela.
    float xoffset = (float)(x - Config::SCREEN_WIDTH / 2);
    // A coordenada Y é invertida (em janelas, Y cresce para baixo).
    float yoffset = (float)(Config::SCREEN_HEIGHT / 2 - y);

    // Aplica a sensibilidade para controlar a velocidade da rotação.
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    // Atualiza os ângulos de rotação horizontal (yaw) e vertical (pitch).
    _yaw += xoffset;
    _pitch += yoffset;

    // Limita o ângulo vertical (pitch) para evitar que a câmera "vire de cabeça para baixo".
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    // Com os ângulos atualizados, recalcula todos os vetores de direção.
    updateCameraVectors();
}

/**
 * @brief Recalcula os vetores de direção da câmera.
 *
 * Este método converte os ângulos de yaw e pitch em vetores 3D normalizados
 * para frente (`_front`), para a direita (`_right`) e para cima (`_up`).
 * Isso é feito usando funções trigonométricas e o produto vetorial (cross product).
 */
void FPSCamera::updateCameraVectors() {
    // Converte os ângulos de Euler (yaw e pitch) em um vetor de direção 3D.
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

    // Recalcula o vetor 'up' da câmera usando o produto vetorial entre 'right' e 'front'.
    _up.x = _right.y * _front.z - _right.z * _front.y;
    _up.y = _right.z * _front.x - _right.x * _front.z;
    _up.z = _right.x * _front.y - _right.y * _front.x;
}
