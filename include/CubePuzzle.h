#ifndef CUBEPUZZLE_H
#define CUBEPUZZLE_H

#include "GameObject.h"
#include "RotatingCube.h"
#include <vector>
#include <string>

class CubePuzzle : public GameObject {
public:
    CubePuzzle(int rows, int cols, const Vector3f& startPos, float spacing, float cubeSize, const std::string& puzzleId);
    ~CubePuzzle() override;

    void update(float deltaTime, GameStateManager& gameStateManager) override;
    void render() override;
    void onCubeClicked(int row, int col);
    const std::vector<std::vector<RotatingCube*>>& getCubes() const { return _cubes; }
    const std::string& getPuzzleId() const { return _puzzleId; }
    BoundingBox getBoundingBox() const override;

private:
    void checkSolution(GameStateManager& gameStateManager);
    int _rows, _cols;
    std::vector<std::vector<RotatingCube*>> _cubes;
    std::string _puzzleId;
    bool _solved = false;
};

#endif // CUBEPUZZLE_H
