#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"
#include <map>

// Não precisamos mais da forward declaration 'class Level;'

class Player {
public:
    Player();

    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    // Voltamos para a assinatura simples do update, sem o Level
    void update(float deltaTime);

    void setPosition(const Vector3f& pos);
    FPSCamera& getCamera();

private:
    Vector3f _position;
    FPSCamera _camera;
    float _movementSpeed;
    float _collisionRadius;

    std::map<unsigned char, bool> _keyState;
};

#endif
