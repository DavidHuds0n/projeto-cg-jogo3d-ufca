#include "../include/FPSCamera.h"
#include <GL/freeglut.h>

FPSCamera::FPSCamera() {
    // Construtor inicializa valores da c�mera (posi��o, �ngulos, etc.)
}

void FPSCamera::updateView() {
    // A Pessoa 2 implementar� a chamada para gluLookAt(...) aqui.
    // Exemplo:
    // gluLookAt(posX, posY, posZ,   // Posi��o da C�mera
    //           targetX, targetY, targetZ, // Para onde olha
    //           upX, upY, upZ);      // Vetor 'up'
}

void FPSCamera::processMouseMotion(int x, int y) {
    // A Pessoa 2 implementar� a l�gica de rota��o da c�mera aqui.
}
