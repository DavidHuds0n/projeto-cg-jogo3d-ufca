/**
 * @file Creature.h
 * @brief Define a classe Creature, que controla o inimigo (IA) do jogo.
 */
#ifndef CREATURE_H
#define CREATURE_H

#include "Player.h" // Para usar Vector3f
#include <vector>

// Forward declaration para evitar depend�ncias circulares com Level.h
class Level;

/**
 * @enum AIState
 * @brief Define os poss�veis estados de comportamento da Intelig�ncia Artificial da criatura.
 */
enum AIState {
    PATROLLING, ///< A criatura est� patrulhando uma �rea aleatoriamente.
    CHASING     ///< A criatura detectou o jogador e est� o perseguindo.
};

/**
 * @struct PathNode
 * @brief Estrutura simples para representar um n� (uma coordenada) no caminho da criatura.
 */
struct PathNode {
    int x, z;
};

/**
 * @class Creature
 * @brief Gerencia o comportamento, movimento e estado da criatura inimiga.
 *
 * Esta classe cont�m a l�gica de IA, incluindo patrulha, persegui��o (usando pathfinding)
 * e intera��o com o jogador e o n�vel.
 */
class Creature {
public:
    /**
     * @brief Construtor padr�o da Criatura.
     */
    Creature();

    /**
     * @brief Reinicia o estado da criatura para uma posi��o inicial.
     * @param [in] playerPos A posi��o atual do jogador, para evitar nascer muito perto.
     * @param [in] level Refer�ncia ao objeto Level para encontrar uma posi��o v�lida.
     */
    void reset(const Vector3f& playerPos, Level& level);

    /**
     * @brief Atualiza a l�gica da criatura a cada frame.
     * @param [in] deltaTime O tempo decorrido desde o �ltimo frame.
     * @param [in] playerPos A posi��o atual do jogador, para a l�gica de detec��o.
     * @param [in] level Refer�ncia ao objeto Level para a l�gica de pathfinding.
     */
    void update(float deltaTime, const Vector3f& playerPos, Level& level);

    /**
     * @brief Renderiza a criatura no mundo.
     */
    void render();

    /**
     * @brief Obt�m a posi��o atual da criatura.
     * @return Um Vector3f representando a posi��o da criatura.
     */
    Vector3f getPosition() const;

private:
    Vector3f _position;         ///< Posi��o atual da criatura.
    float _speed;               ///< Velocidade de movimento da criatura.
    AIState _currentState;      ///< O estado atual da IA (patrulha ou persegui��o).

    /**
     * @brief Vetor de n�s que comp�em o caminho que a criatura deve seguir.
     */
    std::vector<PathNode> _currentPath;

    // --- Fun��es de IA a serem implementadas pela Pessoa 3 ---

    /**
     * @brief Encontra um novo caminho de patrulha aleat�rio e o armazena em _currentPath.
     * @param [in] level Refer�ncia ao objeto Level para consultar paredes e espa�os livres.
     */
    void findNewPatrolPath(Level& level);

    /**
     * @brief Encontra o caminho mais curto da posi��o atual at� o jogador.
     * @param [in] playerPos A posi��o do jogador a ser usada como destino.
     * @param [in] level Refer�ncia ao objeto Level para o algoritmo de pathfinding.
     */
    void findPathToPlayer(const Vector3f& playerPos, Level& level);
};

#endif // CREATURE_H
