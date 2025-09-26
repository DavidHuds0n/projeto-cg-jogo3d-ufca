#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Player.h" // Inclui para ter acesso à struct Vector3f

class LightManager {
public:
    LightManager();

    void init();

    // ASSINATURA CORRIGIDA: Aceita structs em vez de 6 floats.
    void updateFlashlight(const Vector3f& pos, const Vector3f& dir);

    void enableTorch(int torchID);
};

#endif
