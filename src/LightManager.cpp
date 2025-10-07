/**
 * @file LightManager.cpp
 * @brief Implementa��o da classe LightManager, respons�vel por gerenciar a ilumina��o no ambiente 3D.
 */

#include "../include/LightManager.h"
#include "../include/Config.h"
#include <GL/freeglut.h>

/**
 * @brief Construtor da classe LightManager.
 *
 * O construtor est� vazio, pois toda a configura��o
 * � feita no m�todo init() para garantir que o OpenGL j� esteja pronto.
 */
LightManager::LightManager() {
    // O construtor est� vazio, pois toda a configura��o
    // � feita no m�todo init() para garantir que o OpenGL j� esteja pronto.
}

/**
 * @brief Inicializa as configura��es globais de ilumina��o.
 *
 * Habilita o sistema de ilumina��o do OpenGL, define uma luz ambiente global
 * e configura as propriedades da fonte de luz principal (GL_LIGHT0), que atua
 * como uma lanterna.
 */
void LightManager::init() {
    // --- Configura��es Gerais de Ilumina��o ---

    // Habilita o c�lculo de ilumina��o do OpenGL.
    glEnable(GL_LIGHTING);

    // Define uma luz ambiente global.
    GLfloat global_ambient[] = { Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    // --- Configura��o da Lanterna (GL_LIGHT0) ---
    // Luz ambiente da lanterna.
    GLfloat ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    // Cor principal da luz (difusa).
    GLfloat diffuse_light[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    // Cor do brilho especular.
    GLfloat specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Aplica as propriedades de cor � LIGHT0.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    // Configura a atenua��o da luz.
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Config::FLASHLIGHT_ATT_CONSTANT);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Config::FLASHLIGHT_ATT_LINEAR);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Config::FLASHLIGHT_ATT_QUADRATIC);

    // Configura o formato do cone de luz (spotlight).
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, Config::FLASHLIGHT_CUTOFF);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Config::FLASHLIGHT_EXPONENT);

    // Habilita a fonte de luz LIGHT0.
    glEnable(GL_LIGHT0);
}

/**
 * @brief Atualiza a posi��o e dire��o da lanterna.
 *
 * Sincroniza a posi��o e o vetor de dire��o da luz GL_LIGHT0 com
 * a posi��o e a dire��o de visualiza��o da c�mera.
 *
 * @param pos A posi��o da fonte de luz (c�mera do jogador).
 * @param dir O vetor de dire��o para onde a luz est� apontando.
 */
void LightManager::updateFlashlight(const Vector3f& pos, const Vector3f& dir) {
    // Define a posi��o da luz no mundo.
    GLfloat light_position[] = { pos.x, pos.y, pos.z, 1.0f };
    // Define para onde o cone de luz (spotlight) est� apontando.
    GLfloat spot_direction[] = { dir.x, dir.y, dir.z };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
}

/**
 * @brief Define a cor da luz da lanterna.
 *
 * Altera a cor difusa da fonte de luz GL_LIGHT0.
 *
 * @param color O vetor de cor (RGB) a ser aplicado.
 */
void LightManager::setFlashlightColor(const Vector3f& color) {
    GLfloat diffuse_color[] = { color.x, color.y, color.z, 1.0f };
    // Atualiza a cor difusa da LIGHT0 (nossa lanterna)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
}
