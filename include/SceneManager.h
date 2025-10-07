#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include "Vector.h"

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
