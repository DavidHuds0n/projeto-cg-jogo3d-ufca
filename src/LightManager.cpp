#include "../include/LightManager.h"
#include <GL/freeglut.h>

LightManager::LightManager() {}

void LightManager::init() {
    // A Pessoa 4 implementar� glEnable(GL_LIGHTING) e a configura��o
    // da luz ambiente (glLightModelfv) aqui.
}

void LightManager::updateFlashlight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ) {
    // A Pessoa 4 implementar� a atualiza��o de GL_LIGHT0 (a lanterna) aqui,
    // usando glLightfv para posi��o e dire��o.
}

void LightManager::enableTorch(int torchID) {
    // A Pessoa 4 implementar� a l�gica para ligar GL_LIGHT1, GL_LIGHT2, etc.
}
