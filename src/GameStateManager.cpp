#include "../include/GameStateManager.h"
#include <algorithm> // Necess�rio para std::find e std::remove
#include <iostream>  // Para mensagens de depura��o no console

GameStateManager::GameStateManager() {
    // Inicializa o estado de todos os puzzles como "n�o resolvidos"
    _puzzleStates[PuzzleID::Sala1_CodigoCaixa] = false;
    _puzzleStates[PuzzleID::Sala2_FormasEncaixadas] = false;
    _puzzleStates[PuzzleID::Sala3_SequenciaBotoes] = false;

    // Inicializa o estado dos puzzles espec�ficos da Sala 1
    _currentFlashlightColorIndex = 0; // Come�a com a luz branca padr�o
    _keypadInput = "";

     _isKeypadActive = false; // Come�a inativo
}

// --- M�TODOS DE PUZZLE ---

void GameStateManager::setPuzzleState(const std::string& puzzleId, bool isSolved) {
    _puzzleStates[puzzleId] = isSolved;
    std::cout << "Estado do puzzle '" << puzzleId << "' definido como: " << (isSolved ? "RESOLVIDO" : "NAO RESOLVIDO") << std::endl;
}

bool GameStateManager::isPuzzleSolved(const std::string& puzzleId) {
    // Retorna 'false' se o ID do puzzle n�o for encontrado no mapa
    if (_puzzleStates.find(puzzleId) == _puzzleStates.end()) {
        return false;
    }
    return _puzzleStates[puzzleId];
}

// --- M�TODOS DE INVENT�RIO ---

void GameStateManager::addItemToInventory(ItemType item) {
    if (!playerHasItem(item)) { // Evita adicionar itens duplicados
        _inventory.push_back(item);
        std::cout << "Item adicionado ao inventario!" << std::endl;
    }
}

bool GameStateManager::playerHasItem(ItemType item) {
    // Procura o item no vetor de invent�rio
    return std::find(_inventory.begin(), _inventory.end(), item) != _inventory.end();
}

void GameStateManager::removeItemFromInventory(ItemType item) {
    // Usa o padr�o erase-remove para remover todos os elementos correspondentes do vetor
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
    std::cout << "Item removido do inventario!" << std::endl;
}

// --- M�TODOS ESPEC�FICOS PARA A SALA 1 ---

void GameStateManager::cycleFlashlightColor() {
    // Cicla o �ndice entre 0, 1, 2, e 3 (4 cores no total)
    _currentFlashlightColorIndex = (_currentFlashlightColorIndex + 1) % 4;
}

Vector3f GameStateManager::getCurrentFlashlightColor() {
    switch (_currentFlashlightColorIndex) {
        case 1: return {1.0f, 0.2f, 0.2f}; // Vermelho
        case 2: return {0.2f, 1.0f, 0.2f}; // Verde
        case 3: return {0.2f, 0.2f, 1.0f}; // Azul
        default: return {1.0f, 1.0f, 0.8f}; // Branco (padr�o)
    }
}

void GameStateManager::appendToKeypadInput(char digit) {
    if (_keypadInput.length() < 3) { // Limita a 3 d�gitos
        _keypadInput += digit;
        std::cout << "Codigo atual no keypad: " << _keypadInput << std::endl;
    }
}

bool GameStateManager::checkKeypadCode(const std::string& correctCode) {
    if (_keypadInput == correctCode) {
        _keypadInput = ""; // Limpa o input ap�s o sucesso
        std::cout << "Codigo CORRETO!" << std::endl;
        return true;
    }
    _keypadInput = ""; // Limpa o input ap�s o erro
    std::cout << "Codigo INCORRETO! Input resetado." << std::endl;
    return false;
}

std::string GameStateManager::getKeypadInput() {
    return _keypadInput;
}

// Adicione estes m�todos no final:
void GameStateManager::setActiveKeypad(bool isActive) {
    _isKeypadActive = isActive;
    if (!isActive) { // Limpa o input se o keypad for desativado
        _keypadInput = "";
    }
}

bool GameStateManager::isKeypadActive() const {
    return _isKeypadActive;
}

