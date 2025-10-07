// Substitua todo o conteúdo de GameStateManager.h
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
    bool isPuzzleSolved(const std::string& puzzleId) const; // <-- const ADICIONADO
    void addItemToInventory(ItemType item);
    bool playerHasItem(ItemType item) const; // <-- const ADICIONADO
    void removeItemFromInventory(ItemType item);
    void cycleFlashlightColor();
    Vector3f getCurrentFlashlightColor();
    void appendToKeypadInput(char digit);
    bool checkKeypadCode(const std::string& correctCode);
    std::string getKeypadInput();
    void setActiveKeypad(bool isActive);
    bool isKeypadActive() const;
    // --- APAGUE AS 3 LINHAS ABAIXO ---
    // void queueRoomChange(int roomIndex) { _pendinRoom = roomIndex; }
    // void processPending(SceneManager& sm, Player& player);
    // ------------------------------------

private:
    std::map<std::string, bool> _puzzleStates;
    std::vector<ItemType> _inventory;
    int _currentFlashlightColorIndex;
    std::string _keypadInput;
    bool _isKeypadActive;
    // --- APAGUE AS 2 LINHAS ABAIXO ---
    // int _pendinRoom = -1;
    // float _player; // Esta variável parece ser um erro de digitação de qualquer forma
    // ------------------------------------
};

#endif // GAMESTATEMANAGER_H
