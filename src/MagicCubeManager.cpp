#include "MagicCubeManager.h"
#include <iostream>

MagicCubeManager::MagicCubeManager(int rows, int cols, const Vector3f& startPos, float spacing, float cubeSize)
    : _rows(rows), _cols(cols) {
    _cubes.resize(rows);
    for (int i = 0; i < rows; ++i) {
        _cubes[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            Vector3f pos = {startPos.x + j * spacing, startPos.y, startPos.z + i * spacing};
            _cubes[i][j] = new MagicCube(pos, cubeSize, 0.0f);
        }
    }
}

MagicCubeManager::~MagicCubeManager() {
    for (auto& row : _cubes)
        for (auto* cube : row)
            delete cube;
}

MagicCube* MagicCubeManager::getCube(int row, int col) {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) return nullptr;
    return _cubes[row][col];
}

void MagicCubeManager::onCubeClicked(int row, int col, GameStateManager& gameStateManager) {
    // Rotaciona o cubo clicado e os adjacentes (cima, baixo, esquerda, direita)
    const int dr[] = {0, -1, 1, 0, 0};
    const int dc[] = {0, 0, 0, -1, 1};
    for (int k = 0; k < 5; ++k) {
        int nr = row + dr[k];
        int nc = col + dc[k];
        MagicCube* cube = getCube(nr, nc);
        if (cube) cube->onClick(gameStateManager);
    }
}
