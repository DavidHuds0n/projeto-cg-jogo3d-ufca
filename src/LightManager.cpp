#include "../include/LightManager.h"
#include <GL/freeglut.h>

LightManager::LightManager() {}

void LightManager::init() {
    // A Pessoa 4 implementará glEnable(GL_LIGHTING) e a configuração
    // da luz ambiente (glLightModelfv) aqui.
}

void LightManager::updateFlashlight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ) {
    // A Pessoa 4 implementará a atualização de GL_LIGHT0 (a lanterna) aqui,
    // usando glLightfv para posição e direção.
}

void LightManager::enableTorch(int torchID) {
    // A Pessoa 4 implementará a lógica para ligar GL_LIGHT1, GL_LIGHT2, etc.
}
