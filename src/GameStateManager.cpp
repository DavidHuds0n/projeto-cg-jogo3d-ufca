/**
 * @file GameStateManager.cpp
 * @brief Implementação da classe GameStateManager, responsável por gerenciar o estado do jogo.
 */

#include "../include/GameStateManager.h"
#include <algorithm> // Necessário para std::find e std::remove
#include <iostream>  // Para mensagens de depuração no console
#include "../include/SceneManager.h"

/**
 * @brief Construtor padrão da classe GameStateManager.
 *
 * Inicializa os estados dos puzzles, o índice da cor da lanterna e o estado do teclado numérico.
 */
GameStateManager::GameStateManager() {
    // Inicializa o estado de todos os puzzles como "não resolvidos"
    _puzzleStates[PuzzleID::Sala1_CodigoCaixa] = false;
    _puzzleStates[PuzzleID::Sala2_FormasEncaixadas] = false;
    _puzzleStates[PuzzleID::Sala3_SequenciaBotoes] = false;

    // Inicializa o estado dos puzzles específicos da Sala 1
    _currentFlashlightColorIndex = 0; // Começa com a luz branca padrão
    _keypadInput = "";

    _isKeypadActive = false; // Começa inativo
}

// --- MÉTODOS DE PUZZLE ---

/**
 * @brief Define o estado de um puzzle específico.
 * @param puzzleId O identificador do puzzle.
 * @param isSolved O novo estado do puzzle (true para resolvido, false para não resolvido).
 */
void GameStateManager::setPuzzleState(const std::string& puzzleId, bool isSolved) {
    _puzzleStates[puzzleId] = isSolved;
    std::cout << "Estado do puzzle '" << puzzleId << "' definido como: " << (isSolved ? "RESOLVIDO" : "NAO RESOLVIDO") << std::endl;
}

/**
 * @brief Verifica se um puzzle foi resolvido.
 * @param puzzleId O identificador do puzzle a ser verificado.
 * @return Retorna 'true' se o puzzle estiver resolvido, 'false' caso contrário ou se o ID não existir.
 */
bool GameStateManager::isPuzzleSolved(const std::string& puzzleId) const {
    // Retorna 'false' se o ID do puzzle não for encontrado no mapa
    if (_puzzleStates.find(puzzleId) == _puzzleStates.end()) {
        return false;
    }
    return _puzzleStates.at(puzzleId); // Usar .at() é mais seguro para const maps
}

// --- MÉTODOS DE INVENTÁRIO ---

/**
 * @brief Adiciona um item ao inventário do jogador.
 *
 * O item é adicionado apenas se ele ainda não estiver no inventário.
 * @param item O tipo de item a ser adicionado.
 */
void GameStateManager::addItemToInventory(ItemType item) {
    // Esta verificação interna não precisa de const pois o método em si não é const
    if (std::find(_inventory.begin(), _inventory.end(), item) == _inventory.end()) {
        _inventory.push_back(item);
        std::cout << "Item adicionado ao inventario!" << std::endl;
    }
}

/**
 * @brief Verifica se o jogador possui um item específico.
 * @param item O tipo de item a ser verificado.
 * @return Retorna 'true' se o item estiver no inventário, 'false' caso contrário.
 */
bool GameStateManager::playerHasItem(ItemType item) const {
    // Procura o item no vetor de inventário
    return std::find(_inventory.begin(), _inventory.end(), item) != _inventory.end();
}

/**
 * @brief Remove um item do inventário do jogador.
 * @param item O tipo de item a ser removido.
 */
void GameStateManager::removeItemFromInventory(ItemType item) {
    // Usa o padrão erase-remove para remover todos os elementos correspondentes do vetor
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
    std::cout << "Item removido do inventario!" << std::endl;
}

// --- MÉTODOS ESPECÍFICOS PARA A SALA 1 ---

/**
 * @brief Cicla a cor da lanterna do jogador.
 *
 * A cor muda para a próxima na sequência: branco, vermelho, verde, azul e volta para branco.
 */
void GameStateManager::cycleFlashlightColor() {
    // Cicla o índice entre 0, 1, 2, e 3 (4 cores no total)
    _currentFlashlightColorIndex = (_currentFlashlightColorIndex + 1) % 4;
}

/**
 * @brief Obtém o vetor de cor atual da lanterna.
 * @return Um objeto Vector3f que representa a cor RGB da lanterna.
 */
Vector3f GameStateManager::getCurrentFlashlightColor() {
    switch (_currentFlashlightColorIndex) {
        case 1: return {1.0f, 0.2f, 0.2f}; // Vermelho
        case 2: return {0.2f, 1.0f, 0.2f}; // Verde
        case 3: return {0.2f, 0.2f, 1.0f}; // Azul
        default: return {1.0f, 1.0f, 0.8f}; // Branco (padrão)
    }
}

/**
 * @brief Adiciona um dígito à entrada do teclado numérico.
 * @param digit O caractere do dígito a ser adicionado.
 */
void GameStateManager::appendToKeypadInput(char digit) {
    if (_keypadInput.length() < 3) { // Limita a 3 dígitos
        _keypadInput += digit;
        std::cout << "Codigo atual no keypad: " << _keypadInput << std::endl;
    }
}

/**
 * @brief Verifica se a entrada atual do teclado numérico corresponde a um código correto.
 * @param correctCode A string com o código correto.
 * @return Retorna 'true' se os códigos forem iguais, 'false' caso contrário.
 */
bool GameStateManager::checkKeypadCode(const std::string& correctCode) {
    if (_keypadInput == correctCode) {
        _keypadInput = ""; // Limpa o input após o sucesso
        std::cout << "Codigo CORRETO!" << std::endl;
        return true;
    }
    _keypadInput = ""; // Limpa o input após o erro
    std::cout << "Codigo INCORRETO! Input resetado." << std::endl;
    return false;
}

/**
 * @brief Obtém a string de entrada atual do teclado numérico.
 * @return A string de entrada.
 */
std::string GameStateManager::getKeypadInput() {
    return _keypadInput;
}

/**
 * @brief Define se o teclado numérico está ativo.
 *
 * Se o teclado for desativado, a entrada atual é limpa.
 * @param isActive O estado de atividade do teclado.
 */
void GameStateManager::setActiveKeypad(bool isActive) {
    _isKeypadActive = isActive;
    if (!isActive) { // Limpa o input se o keypad for desativado
        _keypadInput = "";
    }
}

/**
 * @brief Verifica se o teclado numérico está ativo.
 * @return Retorna 'true' se estiver ativo, 'false' caso contrário.
 */
bool GameStateManager::isKeypadActive() const {
    return _isKeypadActive;
}
