/**
 * @file GameStateManager.cpp
 * @brief Implementa��o da classe GameStateManager, respons�vel por gerenciar o estado do jogo.
 */

#include "../include/GameStateManager.h"
#include <algorithm> // Necess�rio para std::find e std::remove
#include <iostream>  // Para mensagens de depura��o no console
#include "../include/SceneManager.h"

/**
 * @brief Construtor padr�o da classe GameStateManager.
 *
 * Inicializa os estados dos puzzles, o �ndice da cor da lanterna e o estado do teclado num�rico.
 */
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

/**
 * @brief Define o estado de um puzzle espec�fico.
 * @param puzzleId O identificador do puzzle.
 * @param isSolved O novo estado do puzzle (true para resolvido, false para n�o resolvido).
 */
void GameStateManager::setPuzzleState(const std::string& puzzleId, bool isSolved) {
    _puzzleStates[puzzleId] = isSolved;
    std::cout << "Estado do puzzle '" << puzzleId << "' definido como: " << (isSolved ? "RESOLVIDO" : "NAO RESOLVIDO") << std::endl;
}

/**
 * @brief Verifica se um puzzle foi resolvido.
 * @param puzzleId O identificador do puzzle a ser verificado.
 * @return Retorna 'true' se o puzzle estiver resolvido, 'false' caso contr�rio ou se o ID n�o existir.
 */
bool GameStateManager::isPuzzleSolved(const std::string& puzzleId) const {
    // Retorna 'false' se o ID do puzzle n�o for encontrado no mapa
    if (_puzzleStates.find(puzzleId) == _puzzleStates.end()) {
        return false;
    }
    return _puzzleStates.at(puzzleId); // Usar .at() � mais seguro para const maps
}

// --- M�TODOS DE INVENT�RIO ---

/**
 * @brief Adiciona um item ao invent�rio do jogador.
 *
 * O item � adicionado apenas se ele ainda n�o estiver no invent�rio.
 * @param item O tipo de item a ser adicionado.
 */
void GameStateManager::addItemToInventory(ItemType item) {
    // Esta verifica��o interna n�o precisa de const pois o m�todo em si n�o � const
    if (std::find(_inventory.begin(), _inventory.end(), item) == _inventory.end()) {
        _inventory.push_back(item);
        std::cout << "Item adicionado ao inventario!" << std::endl;
    }
}

/**
 * @brief Verifica se o jogador possui um item espec�fico.
 * @param item O tipo de item a ser verificado.
 * @return Retorna 'true' se o item estiver no invent�rio, 'false' caso contr�rio.
 */
bool GameStateManager::playerHasItem(ItemType item) const {
    // Procura o item no vetor de invent�rio
    return std::find(_inventory.begin(), _inventory.end(), item) != _inventory.end();
}

/**
 * @brief Remove um item do invent�rio do jogador.
 * @param item O tipo de item a ser removido.
 */
void GameStateManager::removeItemFromInventory(ItemType item) {
    // Usa o padr�o erase-remove para remover todos os elementos correspondentes do vetor
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
    std::cout << "Item removido do inventario!" << std::endl;
}

// --- M�TODOS ESPEC�FICOS PARA A SALA 1 ---

/**
 * @brief Cicla a cor da lanterna do jogador.
 *
 * A cor muda para a pr�xima na sequ�ncia: branco, vermelho, verde, azul e volta para branco.
 */
void GameStateManager::cycleFlashlightColor() {
    // Cicla o �ndice entre 0, 1, 2, e 3 (4 cores no total)
    _currentFlashlightColorIndex = (_currentFlashlightColorIndex + 1) % 4;
}

/**
 * @brief Obt�m o vetor de cor atual da lanterna.
 * @return Um objeto Vector3f que representa a cor RGB da lanterna.
 */
Vector3f GameStateManager::getCurrentFlashlightColor() {
    switch (_currentFlashlightColorIndex) {
        case 1: return {1.0f, 0.2f, 0.2f}; // Vermelho
        case 2: return {0.2f, 1.0f, 0.2f}; // Verde
        case 3: return {0.2f, 0.2f, 1.0f}; // Azul
        default: return {1.0f, 1.0f, 0.8f}; // Branco (padr�o)
    }
}

/**
 * @brief Adiciona um d�gito � entrada do teclado num�rico.
 * @param digit O caractere do d�gito a ser adicionado.
 */
void GameStateManager::appendToKeypadInput(char digit) {
    if (_keypadInput.length() < 3) { // Limita a 3 d�gitos
        _keypadInput += digit;
        std::cout << "Codigo atual no keypad: " << _keypadInput << std::endl;
    }
}

/**
 * @brief Verifica se a entrada atual do teclado num�rico corresponde a um c�digo correto.
 * @param correctCode A string com o c�digo correto.
 * @return Retorna 'true' se os c�digos forem iguais, 'false' caso contr�rio.
 */
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

/**
 * @brief Obt�m a string de entrada atual do teclado num�rico.
 * @return A string de entrada.
 */
std::string GameStateManager::getKeypadInput() {
    return _keypadInput;
}

/**
 * @brief Define se o teclado num�rico est� ativo.
 *
 * Se o teclado for desativado, a entrada atual � limpa.
 * @param isActive O estado de atividade do teclado.
 */
void GameStateManager::setActiveKeypad(bool isActive) {
    _isKeypadActive = isActive;
    if (!isActive) { // Limpa o input se o keypad for desativado
        _keypadInput = "";
    }
}

/**
 * @brief Verifica se o teclado num�rico est� ativo.
 * @return Retorna 'true' se estiver ativo, 'false' caso contr�rio.
 */
bool GameStateManager::isKeypadActive() const {
    return _isKeypadActive;
}
