#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

class LightManager {
public:
    LightManager();

    // Métodos para a Pessoa 4 implementar
    void init(); // Habilita GL_LIGHTING e configura luz ambiente global

    // Atualiza a posição/direção da lanterna (spotlight)
    void updateFlashlight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ);

    void enableTorch(int torchID); // Acende uma das tochas (point lights)
};

#endif
