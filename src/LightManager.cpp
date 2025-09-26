#include "../include/LightManager.h"
#include "../include/Config.h"
#include <GL/freeglut.h>

LightManager::LightManager() {}

void LightManager::init() {
    glEnable(GL_LIGHTING);

    GLfloat global_ambient[] = { Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse_light[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    GLfloat specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Config::FLASHLIGHT_ATT_CONSTANT);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Config::FLASHLIGHT_ATT_LINEAR);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Config::FLASHLIGHT_ATT_QUADRATIC);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, Config::FLASHLIGHT_CUTOFF);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Config::FLASHLIGHT_EXPONENT);

    glEnable(GL_LIGHT0);
}

// DEFINIÇÃO CORRIGIDA: Usa as structs para corresponder ao .h
void LightManager::updateFlashlight(const Vector3f& pos, const Vector3f& dir) {
    GLfloat light_position[] = { pos.x, pos.y, pos.z, 1.0f };
    GLfloat spot_direction[] = { dir.x, dir.y, dir.z };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
}

void LightManager::enableTorch(int torchID) {
    // Será implementado no futuro
}
