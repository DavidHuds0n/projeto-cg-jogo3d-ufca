#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include <map>
#include <vector>

bool checkCollision(const BoundingBox& a, const BoundingBox& b);

class Player {
public:
    Player();

    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    void update(float deltaTime, const std::vector<GameObject*>& objects, GameStateManager& gameStateManager);

    void setPosition(const Vector3f& pos);
    FPSCamera& getCamera();
    BoundingBox getBoundingBox() const;

private:
    Vector3f _position; // A única variável de posição para o corpo E a câmera
    FPSCamera _camera;
    float _movementSpeed;
    float _collisionRadius;
    std::map<unsigned char, bool> _keyState;
};

#endif // PLAYER_H
