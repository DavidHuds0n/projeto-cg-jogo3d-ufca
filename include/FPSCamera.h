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

    // Aplica a transforma��o da c�mera usando gluLookAt
    void updateView();

    // Processa a entrada do mouse para rotacionar a c�mera
    void processMouseMotion(int x, int y);

private:
    // Atualiza os vetores de dire��o da c�mera com base nos �ngulos
    void updateCameraVectors();

    Vector3f _position;
    Vector3f _front;
    Vector3f _up;
    Vector3f _right;
    Vector3f _worldUp;

    float _yaw;   // Rota��o horizontal
    float _pitch; // Rota��o vertical

    float _mouseSensitivity;
};

#endif
