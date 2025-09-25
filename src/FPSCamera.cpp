#include "../include/FPSCamera.h"
#include <GL/freeglut.h>

FPSCamera::FPSCamera() {
    // Construtor inicializa valores da câmera (posição, ângulos, etc.)
}

void FPSCamera::updateView() {
    // A Pessoa 2 implementará a chamada para gluLookAt(...) aqui.
    // Exemplo:
    // gluLookAt(posX, posY, posZ,   // Posição da Câmera
    //           targetX, targetY, targetZ, // Para onde olha
    //           upX, upY, upZ);      // Vetor 'up'
}

void FPSCamera::processMouseMotion(int x, int y) {
    // A Pessoa 2 implementará a lógica de rotação da câmera aqui.
}
