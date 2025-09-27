/**
 * @file Creature.cpp
 * @brief Implementa��o da classe Creature.
 */
#include "../include/Creature.h"
#include "../include/Level.h"
#include "../include/Config.h"
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <queue>

Creature::Creature() {
    // O construtor � simples, a inicializa��o principal da l�gica e estado
    // ocorre na fun��o reset().
}

void Creature::reset(const Vector3f& playerPos, Level& level) {
    _speed = Config::CREATURE_SPEED;
    _currentState = PATROLLING; // Come�a sempre patrulhando.
    _currentPath.clear();       // Garante que n�o h� um caminho antigo.

    /*
     * TAREFA (Pessoa 3): Encontrar um ponto de spawn inicial.
     * 1. Percorrer o mapa do 'level' para encontrar uma posi��o v�lida (ex: um 'ch�o').
     * 2. Garantir que esta posi��o esteja a uma dist�ncia segura do 'playerPos'.
     * 3. Definir o `_position` inicial da criatura com base nesse ponto.
     * 4. Chamar findNewPatrolPath() para que ela j� comece com um objetivo.
     */
}

void Creature::update(float deltaTime, const Vector3f& playerPos, Level& level) {
    /*
     * TAREFA (Pessoa 3): L�gica Principal da IA.
     * O fluxo de decis�o da criatura a cada frame deve ser:
     *
     * 1. C�LCULO DE DIST�NCIA:
     * - Calcule a dist�ncia em linha reta entre a criatura e 'playerPos'.
     *
     * 2. TRANSI��O DE ESTADO:
     * - SE a dist�ncia < CREATURE_DETECTION_RADIUS E o estado atual � PATROLLING:
     * - Mude o estado para CHASING.
     * - O caminho atual � invalidado. Chame `findPathToPlayer(playerPos, level)`.
     * - SE a dist�ncia > CREATURE_DETECTION_RADIUS E o estado atual � CHASING:
     * - Mude o estado para PATROLLING.
     * - O caminho para o jogador � descartado.
     *
     * 3. L�GICA DE MOVIMENTO:
     * - SE o estado � CHASING:
     * - (Opcional) A cada X segundos, chame `findPathToPlayer` novamente para atualizar o caminho.
     * - SE o estado � PATROLLING e `_currentPath` est� vazio:
     * - Chame `findNewPatrolPath(level)` para encontrar um novo destino aleat�rio.
     *
     * 4. EXECU��O DO MOVIMENTO:
     * - SE `_currentPath` N�O estiver vazio:
     * - Calcule a dire��o para o pr�ximo n� no caminho.
     * - Mova a criatura nessa dire��o, usando `_speed` e `deltaTime`.
     * - Verifique se a criatura alcan�ou o n�. Se sim, remova o n� do `_currentPath`.
     * - Implemente a colis�o com paredes para que ela contorne os obst�culos.
     */
}

void Creature::render() {
    // Renderiza um modelo simples para a criatura na sua posi��o atual.
    glPushMatrix();
    {
        /*
         * TAREFA (Pessoa 3): Adicionar material.
         * - Defina um material (cor ambiente, difusa, especular) para a criatura
         * antes de desenh�-la, para que ela reaja � luz da lanterna.
         * - Ex: GLfloat creature_diffuse[] = { 0.8f, 0.1f, 0.1f, 1.0f };
         * glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, creature_diffuse);
         */

        // Translada para a posi��o da criatura no mundo.
        glTranslatef(_position.x, 0.5f, _position.z); // 0.5f no Y para ficar um pouco acima do ch�o.

        // Cor de fallback (caso a ilumina��o esteja desativada).
        glColor3f(0.8f, 0.2f, 0.2f);
        glutSolidSphere(0.6, 20, 20); // Desenha uma esfera como placeholder.
    }
    glPopMatrix();
}

Vector3f Creature::getPosition() const {
    return _position;
}

// --- Fun��es de Pathfinding (Busca de Caminho) ---

void Creature::findNewPatrolPath(Level& level) {
    /*
     * TAREFA (Pessoa 3): Encontrar um caminho de patrulha.
     * 1. Escolha uma coordenada (x, z) aleat�ria dentro dos limites do mapa do `level`.
     * 2. Verifique se a coordenada escolhida � um local v�lido para andar (ch�o).
     * 3. Use um algoritmo de busca de caminho (como BFS ou A*) para encontrar a rota
     * entre a posi��o atual da criatura e o destino aleat�rio.
     * 4. Se um caminho for encontrado, armazene a sequ�ncia de n�s em `_currentPath`.
     */
}

void Creature::findPathToPlayer(const Vector3f& playerPos, Level& level) {
    /*
     * TAREFA (Pessoa 3): Encontrar o caminho at� o jogador.
     * 1. Converta a `_position` da criatura e a `playerPos` para coordenadas de grid (�ndices da matriz do mapa).
     * 2. Use um algoritmo de busca de caminho (BFS � uma boa escolha para o caminho mais curto em grids)
     * para encontrar a rota entre a criatura e o jogador.
     * 3. Armazene o caminho retornado em `_currentPath`.
     *
     * @note O BFS (Busca em Largura) � ideal aqui. Ele usa uma fila (std::queue)
     * para explorar o labirinto e garante encontrar o caminho com o menor n�mero de passos.
     */
}
