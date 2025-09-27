/**
 * @file FPSCamera.cpp
 * @brief Implementação da classe FPSCamera.
 */
#include "../include/FPSCamera.h"
#include <GL/freeglut.h>
#include <cmath> // Para sin, cos
#include "../include/Config.h"

// --- Constantes ---
/**
 * @brief Fator de conversão de graus para radianos.
 * As funções de trigonometria em C++ (sin, cos) esperam ângulos em radianos.
 */
const float PI = 3.1415926535f;
const float toRadians = PI / 180.0f;

// --- Implementação da Classe ---

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

void FPSCamera::setPosition(const Vector3f& pos) {
    _position = pos;
}

// Funções 'getter' são simples e geralmente não precisam de comentários de implementação.
const Vector3f& FPSCamera::getPosition() const {
    return _position;
}
const Vector3f& FPSCamera::getFrontVector() const {
    return _front;
}
const Vector3f& FPSCamera::getRightVector() const {
    return _right;
}

void FPSCamera::updateView() {
    // Esta é a função chave que posiciona a "câmera" do OpenGL.
    // Ela usa a posição da câmera (_position), um ponto para onde ela olha
    // (posição + vetor frontal) e o vetor 'up' para orientar a cena.
    gluLookAt(
        _position.x, _position.y, _position.z,                                     // Posição da câmera (eye)
        _position.x + _front.x, _position.y + _front.y, _position.z + _front.z,  // Ponto para onde olhamos (center)
        _up.x, _up.y, _up.z                                                        // Vetor 'up' da câmera
    );
}

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
    // Um valor de 90 graus faria a câmera olhar diretamente para cima, o que pode causar problemas matemáticos.
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    // Com os ângulos atualizados, recalcula todos os vetores de direção.
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors() {
    // --- Mágica da Trigonometria ---
    // Converte os ângulos de Euler (yaw e pitch) em um vetor de direção 3D (cartesiano).
    Vector3f front;
    front.x = cos(_yaw * toRadians) * cos(_pitch * toRadians);
    front.y = sin(_pitch * toRadians);
    front.z = sin(_yaw * toRadians) * cos(_pitch * toRadians);

    // Normaliza o vetor 'front'. Isso garante que seu comprimento seja 1.
    // Manter o comprimento 1 é crucial para cálculos de movimento consistentes.
    float length = sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
    _front = {front.x / length, front.y / length, front.z / length};

    // Recalcula o vetor 'right' usando o Produto Vetorial (Cross Product) entre
    // o vetor 'front' e o vetor 'up' do mundo. O resultado é um vetor perpendicular a ambos.
    _right.x = _front.y * _worldUp.z - _front.z * _worldUp.y;
    _right.y = _front.z * _worldUp.x - _front.x * _worldUp.z;
    _right.z = _front.x * _worldUp.y - _front.y * _worldUp.x;
    length = sqrt(_right.x * _right.x + _right.y * _right.y + _right.z * _right.z);
    _right = {_right.x / length, _right.y / length, _right.z / length}; // Normaliza também.

    // Recalcula o vetor 'up' da câmera. É o produto vetorial entre 'right' e 'front'.
    // Isso garante que os três vetores (_front, _right, _up) sejam sempre perpendiculares entre si.
    _up.x = _right.y * _front.z - _right.z * _front.y;
    _up.y = _right.z * _front.x - _right.x * _front.z;
    _up.z = _right.x * _front.y - _right.y * _front.x;
}
