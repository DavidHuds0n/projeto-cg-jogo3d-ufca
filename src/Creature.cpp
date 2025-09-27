/**
 * @file Creature.cpp
 * @brief Implementação da classe Creature.
 */
#include "../include/Creature.h"
#include "../include/Level.h"
#include "../include/Config.h"
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <queue>

Creature::Creature() {
    // O construtor é simples, a inicialização principal da lógica e estado
    // ocorre na função reset().
}

void Creature::reset(const Vector3f& playerPos, Level& level) {
    _speed = Config::CREATURE_SPEED;
    _currentState = PATROLLING; // Começa sempre patrulhando.
    _currentPath.clear();       // Garante que não há um caminho antigo.

    /*
     * TAREFA (Pessoa 3): Encontrar um ponto de spawn inicial.
     * 1. Percorrer o mapa do 'level' para encontrar uma posição válida (ex: um 'chão').
     * 2. Garantir que esta posição esteja a uma distância segura do 'playerPos'.
     * 3. Definir o `_position` inicial da criatura com base nesse ponto.
     * 4. Chamar findNewPatrolPath() para que ela já comece com um objetivo.
     */
}

void Creature::update(float deltaTime, const Vector3f& playerPos, Level& level) {
    /*
     * TAREFA (Pessoa 3): Lógica Principal da IA.
     * O fluxo de decisão da criatura a cada frame deve ser:
     *
     * 1. CÁLCULO DE DISTÂNCIA:
     * - Calcule a distância em linha reta entre a criatura e 'playerPos'.
     *
     * 2. TRANSIÇÃO DE ESTADO:
     * - SE a distância < CREATURE_DETECTION_RADIUS E o estado atual é PATROLLING:
     * - Mude o estado para CHASING.
     * - O caminho atual é invalidado. Chame `findPathToPlayer(playerPos, level)`.
     * - SE a distância > CREATURE_DETECTION_RADIUS E o estado atual é CHASING:
     * - Mude o estado para PATROLLING.
     * - O caminho para o jogador é descartado.
     *
     * 3. LÓGICA DE MOVIMENTO:
     * - SE o estado é CHASING:
     * - (Opcional) A cada X segundos, chame `findPathToPlayer` novamente para atualizar o caminho.
     * - SE o estado é PATROLLING e `_currentPath` está vazio:
     * - Chame `findNewPatrolPath(level)` para encontrar um novo destino aleatório.
     *
     * 4. EXECUÇÃO DO MOVIMENTO:
     * - SE `_currentPath` NÃO estiver vazio:
     * - Calcule a direção para o próximo nó no caminho.
     * - Mova a criatura nessa direção, usando `_speed` e `deltaTime`.
     * - Verifique se a criatura alcançou o nó. Se sim, remova o nó do `_currentPath`.
     * - Implemente a colisão com paredes para que ela contorne os obstáculos.
     */
}

void Creature::render() {
    // Renderiza um modelo simples para a criatura na sua posição atual.
    glPushMatrix();
    {
        /*
         * TAREFA (Pessoa 3): Adicionar material.
         * - Defina um material (cor ambiente, difusa, especular) para a criatura
         * antes de desenhá-la, para que ela reaja à luz da lanterna.
         * - Ex: GLfloat creature_diffuse[] = { 0.8f, 0.1f, 0.1f, 1.0f };
         * glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, creature_diffuse);
         */

        // Translada para a posição da criatura no mundo.
        glTranslatef(_position.x, 0.5f, _position.z); // 0.5f no Y para ficar um pouco acima do chão.

        // Cor de fallback (caso a iluminação esteja desativada).
        glColor3f(0.8f, 0.2f, 0.2f);
        glutSolidSphere(0.6, 20, 20); // Desenha uma esfera como placeholder.
    }
    glPopMatrix();
}

Vector3f Creature::getPosition() const {
    return _position;
}

// --- Funções de Pathfinding (Busca de Caminho) ---

void Creature::findNewPatrolPath(Level& level) {
    /*
     * TAREFA (Pessoa 3): Encontrar um caminho de patrulha.
     * 1. Escolha uma coordenada (x, z) aleatória dentro dos limites do mapa do `level`.
     * 2. Verifique se a coordenada escolhida é um local válido para andar (chão).
     * 3. Use um algoritmo de busca de caminho (como BFS ou A*) para encontrar a rota
     * entre a posição atual da criatura e o destino aleatório.
     * 4. Se um caminho for encontrado, armazene a sequência de nós em `_currentPath`.
     */
}

void Creature::findPathToPlayer(const Vector3f& playerPos, Level& level) {
    /*
     * TAREFA (Pessoa 3): Encontrar o caminho até o jogador.
     * 1. Converta a `_position` da criatura e a `playerPos` para coordenadas de grid (índices da matriz do mapa).
     * 2. Use um algoritmo de busca de caminho (BFS é uma boa escolha para o caminho mais curto em grids)
     * para encontrar a rota entre a criatura e o jogador.
     * 3. Armazene o caminho retornado em `_currentPath`.
     *
     * @note O BFS (Busca em Largura) é ideal aqui. Ele usa uma fila (std::queue)
     * para explorar o labirinto e garante encontrar o caminho com o menor número de passos.
     */
}
