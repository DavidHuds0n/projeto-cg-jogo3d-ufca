#ifndef FPSCAMERA_H
#define FPSCAMERA_H

class FPSCamera {
public:
    FPSCamera();

    // Este método aplicará a transformação da câmera usando gluLookAt
    void updateView();

    // Métodos para a Pessoa 2 implementar a lógica de input
    void processMouseMotion(int x, int y);
    // ... outros métodos para rotação, etc.
};

#endif
