/**
 * @file FPSCamera.cpp
 * @brief Implementa��o da classe FPSCamera.
 */
#include "../include/FPSCamera.h"
#include <GL/freeglut.h>
#include <cmath> // Para sin, cos
#include "../include/Config.h"

// --- Constantes ---
/**
 * @brief Fator de convers�o de graus para radianos.
 * As fun��es de trigonometria em C++ (sin, cos) esperam �ngulos em radianos.
 */
const float PI = 3.1415926535f;
const float toRadians = PI / 180.0f;

// --- Implementa��o da Classe ---

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

void FPSCamera::setPosition(const Vector3f& pos) {
    _position = pos;
}

// Fun��es 'getter' s�o simples e geralmente n�o precisam de coment�rios de implementa��o.
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
    // Esta � a fun��o chave que posiciona a "c�mera" do OpenGL.
    // Ela usa a posi��o da c�mera (_position), um ponto para onde ela olha
    // (posi��o + vetor frontal) e o vetor 'up' para orientar a cena.
    gluLookAt(
        _position.x, _position.y, _position.z,                                     // Posi��o da c�mera (eye)
        _position.x + _front.x, _position.y + _front.y, _position.z + _front.z,  // Ponto para onde olhamos (center)
        _up.x, _up.y, _up.z                                                        // Vetor 'up' da c�mera
    );
}

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
    // Um valor de 90 graus faria a c�mera olhar diretamente para cima, o que pode causar problemas matem�ticos.
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    // Com os �ngulos atualizados, recalcula todos os vetores de dire��o.
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors() {
    // --- M�gica da Trigonometria ---
    // Converte os �ngulos de Euler (yaw e pitch) em um vetor de dire��o 3D (cartesiano).
    Vector3f front;
    front.x = cos(_yaw * toRadians) * cos(_pitch * toRadians);
    front.y = sin(_pitch * toRadians);
    front.z = sin(_yaw * toRadians) * cos(_pitch * toRadians);

    // Normaliza o vetor 'front'. Isso garante que seu comprimento seja 1.
    // Manter o comprimento 1 � crucial para c�lculos de movimento consistentes.
    float length = sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
    _front = {front.x / length, front.y / length, front.z / length};

    // Recalcula o vetor 'right' usando o Produto Vetorial (Cross Product) entre
    // o vetor 'front' e o vetor 'up' do mundo. O resultado � um vetor perpendicular a ambos.
    _right.x = _front.y * _worldUp.z - _front.z * _worldUp.y;
    _right.y = _front.z * _worldUp.x - _front.x * _worldUp.z;
    _right.z = _front.x * _worldUp.y - _front.y * _worldUp.x;
    length = sqrt(_right.x * _right.x + _right.y * _right.y + _right.z * _right.z);
    _right = {_right.x / length, _right.y / length, _right.z / length}; // Normaliza tamb�m.

    // Recalcula o vetor 'up' da c�mera. � o produto vetorial entre 'right' e 'front'.
    // Isso garante que os tr�s vetores (_front, _right, _up) sejam sempre perpendiculares entre si.
    _up.x = _right.y * _front.z - _right.z * _front.y;
    _up.y = _right.z * _front.x - _right.x * _front.z;
    _up.z = _right.x * _front.y - _right.y * _front.x;
}
