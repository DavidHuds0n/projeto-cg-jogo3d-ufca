#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include "Vector.h" // <-- ADICIONE ESTA LINHA

// Forward declarations
class GameObject;
class InteractableObject;
class Room;
class Player;
class GameStateManager;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void init(Player& player);
    void update(float deltaTime, GameStateManager& gameStateManager);
    void render();

    // Garante que a assinatura está correta, usando Vector3f
    void switchToRoom(int roomIndex, Player& player, const Vector3f& spawnPosition);

    void setActiveRoom(int index);
    std::vector<InteractableObject*>& getInteractableObjects();
    const std::vector<GameObject*>& getCurrentRoomObjects() const;

private:
    std::vector<Room*> _rooms;
    int _currentRoomIndex;
    Player* _player;
};

#endif // SCENEMANAGER_H
