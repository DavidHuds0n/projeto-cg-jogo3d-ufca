#ifndef FPSCAMERA_H
#define FPSCAMERA_H

struct Vector3f {
    float x, y, z;
};

class FPSCamera {
public:
    FPSCamera();

    void setPosition(const Vector3f& pos);
    const Vector3f& getPosition() const;
    const Vector3f& getFrontVector() const;
    const Vector3f& getRightVector() const;

    // Aplica a transformação da câmera usando gluLookAt
    void updateView();

    // Processa a entrada do mouse para rotacionar a câmera
    void processMouseMotion(int x, int y);

private:
    // Atualiza os vetores de direção da câmera com base nos ângulos
    void updateCameraVectors();

    Vector3f _position;
    Vector3f _front;
    Vector3f _up;
    Vector3f _right;
    Vector3f _worldUp;

    float _yaw;   // Rotação horizontal
    float _pitch; // Rotação vertical

    float _mouseSensitivity;
};

#endif
