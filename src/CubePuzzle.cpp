#include "../include/CubePuzzle.h"
#include "../include/GameStateManager.h"
#include "../include/GameObject.h"
#include <iostream>

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

CubePuzzle::~CubePuzzle() {
    for (auto& row : _cubes)
        for (auto* cube : row)
            delete cube;
}

void CubePuzzle::update(float deltaTime, GameStateManager& gameStateManager) {
    // Atualiza cada cubo individualmente (isso já existe)
    for (auto& row : _cubes)
        for (auto* cube : row)
            cube->update(deltaTime, gameStateManager);

    // --- ADICIONE ESTA LINHA AQUI ---
    // Chama a função de verificação a cada frame.
    checkSolution(gameStateManager);
}

void CubePuzzle::render() {
    for (auto& row : _cubes)
        for (auto* cube : row)
            cube->render();
}

void CubePuzzle::onCubeClicked(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) return;
    _cubes[row][col]->rotate();
    if (col > 0) _cubes[row][col - 1]->rotate();
    if (col < _cols - 1) _cubes[row][col + 1]->rotate();
    if (row > 0) _cubes[row - 1][col]->rotate();
    if (row < _rows - 1) _cubes[row + 1][col]->rotate();
    // Checa solução após cada jogada
    // O GameStateManager deve ser passado de fora, então use um ponteiro temporário se necessário
    // Aqui, apenas marca para checar na próxima update
    _solved = false;
}

void CubePuzzle::checkSolution(GameStateManager& gameStateManager) {
    for (auto& row : _cubes)
        for (auto* cube : row)
            if (cube->getRotationState() != 0)
                return;
    // Se chegou aqui, está resolvido
    if (!_solved) {
        gameStateManager.setPuzzleState(_puzzleId, true);
        std::cout << "Puzzle dos cubos resolvido!" << std::endl;

        /* --- COMENTE ESTE BLOCO DE CÓDIGO ---
        // Exemplo: animação - todos os cubos sobem
        for (auto& row : _cubes)
            for (auto* cube : row) {
                Vector3f pos = cube->getPosition();
                cube->moveTo({pos.x, pos.y + 2.0f, pos.z});
            }
        */

        _solved = true;
    }
}
