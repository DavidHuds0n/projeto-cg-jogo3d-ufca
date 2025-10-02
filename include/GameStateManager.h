#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "GameData.h"
#include "Vector.h" // Incluído para o retorno de cor da lanterna

class GameStateManager {
public:
    /**
     * @brief Construtor da classe GameStateManager.
     * Inicializa o estado padrão de todos os puzzles.
     */
    GameStateManager();

    // --- Métodos de Gerenciamento de Puzzles ---

    /**
     * @brief Define o estado de um puzzle como resolvido ou não resolvido.
     * @param puzzleId O identificador único do puzzle (de PuzzleID).
     * @param isSolved O novo estado (true para resolvido, false para não resolvido).
     */
    void setPuzzleState(const std::string& puzzleId, bool isSolved);

    /**
     * @brief Verifica se um puzzle específico já foi resolvido.
     * @param puzzleId O identificador único do puzzle.
     * @return true se o puzzle foi resolvido, false caso contrário.
     */
    bool isPuzzleSolved(const std::string& puzzleId);

    // --- Métodos de Gerenciamento do Inventário ---

    /**
     * @brief Adiciona um item ao inventário do jogador.
     * @param item O tipo de item a ser adicionado (de ItemType).
     */
    void addItemToInventory(ItemType item);

    /**
     * @brief Verifica se o jogador possui um item específico no inventário.
     * @param item O tipo de item a ser verificado.
     * @return true se o jogador possui o item, false caso contrário.
     */
    bool playerHasItem(ItemType item);

    /**
     * @brief Remove um item do inventário do jogador.
     * @param item O tipo de item a ser removido.
     */
    void removeItemFromInventory(ItemType item);

    // --- Métodos Específicos para a Sala 1: Luz Reveladora ---

    /**
     * @brief Avança para a próxima cor da lanterna (Branco -> Vrm -> Vrd -> Azl).
     */
    void cycleFlashlightColor();

    /**
     * @brief Obtém o valor RGB da cor atual da lanterna.
     * @return Um Vector3f representando a cor (R, G, B).
     */
    Vector3f getCurrentFlashlightColor();

    /**
     * @brief Adiciona um dígito ao input do teclado numérico.
     * @param digit O caractere do dígito a ser adicionado.
     */
    void appendToKeypadInput(char digit);

    /**
     * @brief Verifica se o código inserido no teclado numérico está correto.
     * @param correctCode O código correto a ser comparado.
     * @return true se o código estiver correto, false caso contrário.
     */
    bool checkKeypadCode(const std::string& correctCode);

    /**
     * @brief Obtém o input atual do teclado numérico.
     * @return Uma string com os dígitos inseridos.
     */
    std::string getKeypadInput();

    // NOVOS MÉTODOS
    void setActiveKeypad(bool isActive);
    bool isKeypadActive() const;

private:
    // Armazena o estado (resolvido/não resolvido) de cada puzzle.
    std::map<std::string, bool> _puzzleStates;
    // Armazena os itens que o jogador coletou.
    std::vector<ItemType> _inventory;

    // Estado específico para os puzzles da Sala 1
    int _currentFlashlightColorIndex; // 0=Branco, 1=Vermelho, 2=Verde, 3=Azul
    std::string _keypadInput;         // Armazena os dígitos inseridos pelo jogador
    bool _isKeypadActive; // <-- NOVA VARIÁVEL
};

#endif // GAMESTATEMANAGER_H
