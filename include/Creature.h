/**
 * @file Creature.h
 * @brief Define a classe Creature, que controla o inimigo (IA) do jogo.
 */
#ifndef CREATURE_H
#define CREATURE_H

#include "Player.h" // Para usar Vector3f
#include <vector>

// Forward declaration para evitar dependências circulares com Level.h
class Level;

/**
 * @enum AIState
 * @brief Define os possíveis estados de comportamento da Inteligência Artificial da criatura.
 */
enum AIState {
    PATROLLING, ///< A criatura está patrulhando uma área aleatoriamente.
    CHASING     ///< A criatura detectou o jogador e está o perseguindo.
};

/**
 * @struct PathNode
 * @brief Estrutura simples para representar um nó (uma coordenada) no caminho da criatura.
 */
struct PathNode {
    int x, z;
};

/**
 * @class Creature
 * @brief Gerencia o comportamento, movimento e estado da criatura inimiga.
 *
 * Esta classe contém a lógica de IA, incluindo patrulha, perseguição (usando pathfinding)
 * e interação com o jogador e o nível.
 */
class Creature {
public:
    /**
     * @brief Construtor padrão da Criatura.
     */
    Creature();

    /**
     * @brief Reinicia o estado da criatura para uma posição inicial.
     * @param [in] playerPos A posição atual do jogador, para evitar nascer muito perto.
     * @param [in] level Referência ao objeto Level para encontrar uma posição válida.
     */
    void reset(const Vector3f& playerPos, Level& level);

    /**
     * @brief Atualiza a lógica da criatura a cada frame.
     * @param [in] deltaTime O tempo decorrido desde o último frame.
     * @param [in] playerPos A posição atual do jogador, para a lógica de detecção.
     * @param [in] level Referência ao objeto Level para a lógica de pathfinding.
     */
    void update(float deltaTime, const Vector3f& playerPos, Level& level);

    /**
     * @brief Renderiza a criatura no mundo.
     */
    void render();

    /**
     * @brief Obtém a posição atual da criatura.
     * @return Um Vector3f representando a posição da criatura.
     */
    Vector3f getPosition() const;

private:
    Vector3f _position;         ///< Posição atual da criatura.
    float _speed;               ///< Velocidade de movimento da criatura.
    AIState _currentState;      ///< O estado atual da IA (patrulha ou perseguição).

    /**
     * @brief Vetor de nós que compõem o caminho que a criatura deve seguir.
     */
    std::vector<PathNode> _currentPath;

    // --- Funções de IA a serem implementadas pela Pessoa 3 ---

    /**
     * @brief Encontra um novo caminho de patrulha aleatório e o armazena em _currentPath.
     * @param [in] level Referência ao objeto Level para consultar paredes e espaços livres.
     */
    void findNewPatrolPath(Level& level);

    /**
     * @brief Encontra o caminho mais curto da posição atual até o jogador.
     * @param [in] playerPos A posição do jogador a ser usada como destino.
     * @param [in] level Referência ao objeto Level para o algoritmo de pathfinding.
     */
    void findPathToPlayer(const Vector3f& playerPos, Level& level);
};

#endif // CREATURE_H
