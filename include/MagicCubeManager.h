#ifndef MAGICCUBEMANAGER_H
#define MAGICCUBEMANAGER_H

#include "MagicCube.h"
#include <vector>

class MagicCubeManager {
public:
    MagicCubeManager(int rows, int cols, const Vector3f& startPos, float spacing, float cubeSize);
    ~MagicCubeManager();

    void onCubeClicked(int row, int col, GameStateManager& gameStateManager);
    MagicCube* getCube(int row, int col);
    int getRows() const { return _rows; }
    int getCols() const { return _cols; }

private:
    int _rows, _cols;
    std::vector<std::vector<MagicCube*>> _cubes;
};

#endif // MAGICCUBEMANAGER_H
