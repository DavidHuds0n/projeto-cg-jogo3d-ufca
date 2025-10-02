#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"
#include "GameObject.h" // Precisa saber o que é um GameObject para o update
#include "GameStateManager.h" // E o GameStateManager
#include <map>
#include <vector>

// --- ADICIONE A DECLARAÇÃO DA FUNÇÃO AQUI ---
    // Isso torna a função visível para qualquer arquivo que inclua "Player.h"
    bool checkCollision(const BoundingBox& a, const BoundingBox& b);

class Player {
public:
    Player();

    void handleKeyDown(unsigned char key);
    void handleKeyUp(unsigned char key);
    void handleMouseMotion(int x, int y);

    // Assinatura ATUALIZADA para receber a lista de objetos da sala
    void update(float deltaTime, const std::vector<GameObject*>& objects, GameStateManager& gameStateManager);

    void setPosition(const Vector3f& pos);
    FPSCamera& getCamera();
    BoundingBox getBoundingBox() const;

private:
    Vector3f _position;
    FPSCamera _camera;
    float _movementSpeed;
    float _collisionRadius;
    std::map<unsigned char, bool> _keyState;
};

#endif // PLAYER_H
