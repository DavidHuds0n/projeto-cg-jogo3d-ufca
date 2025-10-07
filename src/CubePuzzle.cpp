/**
 * @file CubePuzzle.cpp
 * @brief Implementação da classe CubePuzzle, responsável por gerenciar um quebra-cabeça de cubos rotativos.
 */

#include "../include/CubePuzzle.h"
#include "../include/GameStateManager.h"
#include "../include/GameObject.h"
#include <iostream>

/**
 * @brief Obtém a Bounding Box (caixa delimitadora) que engloba todos os cubos do quebra-cabeça.
 * @return Um objeto BoundingBox que define os limites do quebra-cabeça.
 */
BoundingBox CubePuzzle::getBoundingBox() const {
    // Calcula o menor bounding box que engloba todos os cubos
    if (_cubes.empty() || _cubes[0].empty()) return BoundingBox{};
    BoundingBox box = _cubes[0][0]->getBoundingBox();
    for (const auto& row : _cubes) {
        for (const auto* cube : row) {
            BoundingBox cb = cube->getBoundingBox();
            box.min.x = std::min(box.min.x, cb.min.x);
            box.min.y = std::min(box.min.y, cb.min.y);
            box.min.z = std::min(box.min.z, cb.min.z);
            box.max.x = std::max(box.max.x, cb.max.x);
            box.max.y = std::max(box.max.y, cb.max.y);
            box.max.z = std::max(box.max.z, cb.max.z);
        }
    }
    return box;
}

/**
 * @brief Construtor da classe CubePuzzle.
 *
 * O construtor inicializa a matriz de cubos, criando novas instâncias de RotatingCube
 * com base nos parâmetros fornecidos.
 *
 * @param rows O número de linhas de cubos no quebra-cabeça.
 * @param cols O número de colunas de cubos no quebra-cabeça.
 * @param startPos A posição inicial do primeiro cubo.
 * @param spacing O espaçamento entre os cubos.
 * @param cubeSize O tamanho de cada cubo individual.
 * @param puzzleId Um identificador único para o quebra-cabeça.
 */
CubePuzzle::CubePuzzle(int rows, int cols, const Vector3f& startPos, float spacing, float cubeSize, const std::string& puzzleId)
    : _rows(rows), _cols(cols), _puzzleId(puzzleId) {
    _cubes.resize(rows);
    for (int i = 0; i < rows; ++i) {
        _cubes[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            Vector3f pos = {startPos.x + j * spacing, startPos.y, startPos.z + i * spacing};
            _cubes[i][j] = new RotatingCube(pos, cubeSize, i, j, this);
        }
    }
}

/**
 * @brief Destrutor da classe CubePuzzle.
 *
 * O destrutor é responsável por liberar a memória alocada para cada cubo,
 * evitando vazamentos de memória.
 */
CubePuzzle::~CubePuzzle() {
    for (auto& row : _cubes)
        for (auto* cube : row)
            delete cube;
}

/**
 * @brief Atualiza o estado de todos os cubos no quebra-cabeça.
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager A classe que gerencia o estado do jogo.
 */
void CubePuzzle::update(float deltaTime, GameStateManager& gameStateManager) {
    // Atualiza cada cubo individualmente
    for (auto& row : _cubes)
        for (auto* cube : row)
            cube->update(deltaTime, gameStateManager);

    // Chama a função de verificação a cada frame.
    checkSolution(gameStateManager);
}

/**
 * @brief Renderiza todos os cubos no quebra-cabeça.
 */
void CubePuzzle::render() {
    for (auto& row : _cubes)
        for (auto* cube : row)
            cube->render();
}

/**
 * @brief Manipula o clique em um cubo específico.
 *
 * Este método implementa a lógica do quebra-cabeça, rotacionando o cubo clicado
 * e os cubos adjacentes (superior, inferior, esquerdo e direito).
 *
 * @param row A linha do cubo clicado.
 * @param col A coluna do cubo clicado.
 */
void CubePuzzle::onCubeClicked(int row, int col) {
    if (_solved) return; // Não faz nada se já estiver resolvido
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) return;
    _cubes[row][col]->rotate();
    if (col > 0) _cubes[row][col - 1]->rotate();
    if (col < _cols - 1) _cubes[row][col + 1]->rotate();
    if (row > 0) _cubes[row - 1][col]->rotate();
    if (row < _rows - 1) _cubes[row + 1][col]->rotate();
    // Checa solução após cada jogada
    // O GameStateManager deve ser passado de fora, então usa um ponteiro temporário se necessário
    // Aqui, apenas marca para checar na próxima update
    _solved = false;
}

/**
 * @brief Verifica se o quebra-cabeça foi resolvido.
 *
 * O quebra-cabeça é considerado resolvido quando todos os cubos
 * estão no seu estado de rotação inicial (estado 0). Se resolvido,
 * o estado do jogo é atualizado.
 *
 * @param gameStateManager A classe que gerencia o estado do jogo.
 */
void CubePuzzle::checkSolution(GameStateManager& gameStateManager) {
    for (auto& row : _cubes)
        for (auto* cube : row)
            if (cube->getRotationState() != 0)
                return;
    // Se chegou aqui, está resolvido
    if (!_solved) {
        gameStateManager.setPuzzleState(_puzzleId, true);
        std::cout << "Puzzle dos cubos resolvido!" << std::endl;
        _solved = true;
    }
}
