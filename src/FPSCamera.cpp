#include "../include/FPSCamera.h"
#include <GL/freeglut.h>
#include <cmath> // Para sin, cos
#include "../include/Config.h"

// Constantes para conversão de graus para radianos
const float PI = 3.1415926535f;
const float toRadians = PI / 180.0f;

FPSCamera::FPSCamera() {
    _position = {0.0f, 1.0f, 5.0f};
    _worldUp = {0.0f, 1.0f, 0.0f};
    _yaw = -90.0f;
    _pitch = 0.0f;
    _mouseSensitivity = Config::CAMERA_SENSITIVITY;
    updateCameraVectors();
}

void FPSCamera::setPosition(const Vector3f& pos) {
    _position = pos;
}

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
    // A função chave que aplica a transformação de visão
    gluLookAt(
        _position.x, _position.y, _position.z, // Posição da câmera (eye)
        _position.x + _front.x, _position.y + _front.y, _position.z + _front.z, // Ponto para onde olhamos (center)
        _up.x, _up.y, _up.z // Vetor 'up' da câmera
    );
}

void FPSCamera::processMouseMotion(int x, int y) {
    // Calcula o deslocamento do mouse a partir do centro da tela
    float xoffset = (float)(x - Config::SCREEN_WIDTH / 2);
    float yoffset = (float)(Config::SCREEN_HEIGHT / 2 - y);

    // Aplica a sensibilidade
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    // Atualiza os ângulos yaw e pitch
    _yaw += xoffset;
    _pitch += yoffset;

    // Limita o pitch
    if (_pitch > 89.0f) _pitch = 89.0f;
    if (_pitch < -89.0f) _pitch = -89.0f;

    // Recalcula os vetores da câmera
    updateCameraVectors();
}

void FPSCamera::updateCameraVectors() {
    // Calcula o novo vetor 'front' usando trigonometria
    Vector3f front;
    front.x = cos(_yaw * toRadians) * cos(_pitch * toRadians);
    front.y = sin(_pitch * toRadians);
    front.z = sin(_yaw * toRadians) * cos(_pitch * toRadians);

    // Normaliza o vetor (garante que seu comprimento seja 1)
    float length = sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
    _front = {front.x / length, front.y / length, front.z / length};

    // Recalcula o vetor 'right' usando o produto vetorial
    _right.x = _front.y * _worldUp.z - _front.z * _worldUp.y;
    _right.y = _front.z * _worldUp.x - _front.x * _worldUp.z;
    _right.z = _front.x * _worldUp.y - _front.y * _worldUp.x;
    length = sqrt(_right.x * _right.x + _right.y * _right.y + _right.z * _right.z);
    _right = {_right.x / length, _right.y / length, _right.z / length};

    // Recalcula o vetor 'up' da câmera
    _up.x = _right.y * _front.z - _right.z * _front.y;
    _up.y = _right.z * _front.x - _right.x * _front.z;
    _up.z = _right.x * _front.y - _right.y * _front.x;
}
