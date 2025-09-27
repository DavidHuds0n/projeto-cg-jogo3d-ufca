/**
 * @file LightManager.cpp
 * @brief Implementação da classe LightManager.
 */
#include "../include/LightManager.h"
#include "../include/Config.h"
#include <GL/freeglut.h>

LightManager::LightManager() {
    // O construtor está vazio, pois toda a configuração
    // é feita no método init() para garantir que o OpenGL já esteja pronto.
}

void LightManager::init() {
    // --- Configurações Gerais de Iluminação ---

    // Habilita o cálculo de iluminação do OpenGL. Sem esta linha, nada acende.
    glEnable(GL_LIGHTING);

    // Define uma luz ambiente global. É uma luz fraca que existe em todo o cenário,
    // garantindo que mesmo as áreas não iluminadas diretamente não fiquem totalmente pretas.
    GLfloat global_ambient[] = { Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, Config::AMBIENT_LIGHT_INTENSITY, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    // --- Configuração da Lanterna (GL_LIGHT0) ---
    // Vamos usar a fonte de luz número 0 (LIGHT0) do OpenGL para ser a nossa lanterna.

    // Propriedades da luz da lanterna:
    // Luz ambiente da lanterna (geralmente zero, para não iluminar tudo ao redor).
    GLfloat ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    // Cor principal da luz (difusa). Um branco amarelado para parecer uma lanterna.
    GLfloat diffuse_light[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    // Cor do brilho especular que a luz cria nas superfícies.
    GLfloat specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Aplica as propriedades de cor à LIGHT0.
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    // Configura a atenuação da luz - como ela perde força com a distância.
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Config::FLASHLIGHT_ATT_CONSTANT);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Config::FLASHLIGHT_ATT_LINEAR);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Config::FLASHLIGHT_ATT_QUADRATIC);

    // Configura o formato do cone de luz (spotlight).
    // CUTOFF define o ângulo de abertura do cone.
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, Config::FLASHLIGHT_CUTOFF);
    // EXPONENT define a suavidade da borda do cone (valores maiores = borda mais nítida).
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Config::FLASHLIGHT_EXPONENT);

    // Finalmente, habilita a fonte de luz LIGHT0.
    glEnable(GL_LIGHT0);
}

void LightManager::updateFlashlight(const Vector3f& pos, const Vector3f& dir) {
    // Esta função é chamada a cada frame para atualizar a posição e direção da lanterna,
    // sincronizando-a com a câmera do jogador.

    // Define a posição da luz no mundo. O '1.0f' no final indica que é uma luz posicional.
    GLfloat light_position[] = { pos.x, pos.y, pos.z, 1.0f };
    // Define para onde o cone de luz (spotlight) está apontando.
    GLfloat spot_direction[] = { dir.x, dir.y, dir.z };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
}

void LightManager::enableTorch(int torchID) {
    // TODO: Implementar a lógica para ativar outras fontes de luz (GL_LIGHT1, GL_LIGHT2, etc.)
    // que representarão as tochas no cenário.
}
