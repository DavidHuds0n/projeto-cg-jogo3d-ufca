#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "GameData.h"
#include "Vector.h"
#include "SceneManager.h"
class SceneManager;
class Player;

class GameStateManager {
public:
    GameStateManager();
    void setPuzzleState(const std::string& puzzleId, bool isSolved);
    bool isPuzzleSolved(const std::string& puzzleId) const;
    void addItemToInventory(ItemType item);
    bool playerHasItem(ItemType item) const;
    void removeItemFromInventory(ItemType item);
    void cycleFlashlightColor();
    Vector3f getCurrentFlashlightColor();
    void appendToKeypadInput(char digit);
    bool checkKeypadCode(const std::string& correctCode);
    std::string getKeypadInput();
    void setActiveKeypad(bool isActive);
    bool isKeypadActive() const;

private:
    std::map<std::string, bool> _puzzleStates;
    std::vector<ItemType> _inventory;
    int _currentFlashlightColorIndex;
    std::string _keypadInput;
    bool _isKeypadActive;
};

#endif // GAMESTATEMANAGER_H
