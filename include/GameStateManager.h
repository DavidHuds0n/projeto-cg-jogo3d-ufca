#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "GameData.h"
#include "Vector.h" // Inclu�do para o retorno de cor da lanterna

class GameStateManager {
public:
    /**
     * @brief Construtor da classe GameStateManager.
     * Inicializa o estado padr�o de todos os puzzles.
     */
    GameStateManager();

    // --- M�todos de Gerenciamento de Puzzles ---

    /**
     * @brief Define o estado de um puzzle como resolvido ou n�o resolvido.
     * @param puzzleId O identificador �nico do puzzle (de PuzzleID).
     * @param isSolved O novo estado (true para resolvido, false para n�o resolvido).
     */
    void setPuzzleState(const std::string& puzzleId, bool isSolved);

    /**
     * @brief Verifica se um puzzle espec�fico j� foi resolvido.
     * @param puzzleId O identificador �nico do puzzle.
     * @return true se o puzzle foi resolvido, false caso contr�rio.
     */
    bool isPuzzleSolved(const std::string& puzzleId);

    // --- M�todos de Gerenciamento do Invent�rio ---

    /**
     * @brief Adiciona um item ao invent�rio do jogador.
     * @param item O tipo de item a ser adicionado (de ItemType).
     */
    void addItemToInventory(ItemType item);

    /**
     * @brief Verifica se o jogador possui um item espec�fico no invent�rio.
     * @param item O tipo de item a ser verificado.
     * @return true se o jogador possui o item, false caso contr�rio.
     */
    bool playerHasItem(ItemType item);

    /**
     * @brief Remove um item do invent�rio do jogador.
     * @param item O tipo de item a ser removido.
     */
    void removeItemFromInventory(ItemType item);

    // --- M�todos Espec�ficos para a Sala 1: Luz Reveladora ---

    /**
     * @brief Avan�a para a pr�xima cor da lanterna (Branco -> Vrm -> Vrd -> Azl).
     */
    void cycleFlashlightColor();

    /**
     * @brief Obt�m o valor RGB da cor atual da lanterna.
     * @return Um Vector3f representando a cor (R, G, B).
     */
    Vector3f getCurrentFlashlightColor();

    /**
     * @brief Adiciona um d�gito ao input do teclado num�rico.
     * @param digit O caractere do d�gito a ser adicionado.
     */
    void appendToKeypadInput(char digit);

    /**
     * @brief Verifica se o c�digo inserido no teclado num�rico est� correto.
     * @param correctCode O c�digo correto a ser comparado.
     * @return true se o c�digo estiver correto, false caso contr�rio.
     */
    bool checkKeypadCode(const std::string& correctCode);

    /**
     * @brief Obt�m o input atual do teclado num�rico.
     * @return Uma string com os d�gitos inseridos.
     */
    std::string getKeypadInput();

    // NOVOS M�TODOS
    void setActiveKeypad(bool isActive);
    bool isKeypadActive() const;

private:
    // Armazena o estado (resolvido/n�o resolvido) de cada puzzle.
    std::map<std::string, bool> _puzzleStates;
    // Armazena os itens que o jogador coletou.
    std::vector<ItemType> _inventory;

    // Estado espec�fico para os puzzles da Sala 1
    int _currentFlashlightColorIndex; // 0=Branco, 1=Vermelho, 2=Verde, 3=Azul
    std::string _keypadInput;         // Armazena os d�gitos inseridos pelo jogador
    bool _isKeypadActive; // <-- NOVA VARI�VEL
};

#endif // GAMESTATEMANAGER_H
