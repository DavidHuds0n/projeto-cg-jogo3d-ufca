#ifndef FPSCAMERA_H
#define FPSCAMERA_H

class FPSCamera {
public:
    FPSCamera();

    // Este m�todo aplicar� a transforma��o da c�mera usando gluLookAt
    void updateView();

    // M�todos para a Pessoa 2 implementar a l�gica de input
    void processMouseMotion(int x, int y);
    // ... outros m�todos para rota��o, etc.
};

#endif
