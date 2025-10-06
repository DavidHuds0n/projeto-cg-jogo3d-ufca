#ifndef ROTATINGCUBE_H
#define ROTATINGCUBE_H

#include "InteractableObject.h"
#include "Vector.h"
#include <random>

class CubePuzzle; // Forward declaration

class RotatingCube : public InteractableObject {
public:
    RotatingCube(const Vector3f& position, float size, int row, int col, CubePuzzle* puzzleManager);
    ~RotatingCube() override = default;

    void update(float deltaTime, GameStateManager& gameStateManager) override;
    void render() override;
    void onClick(GameStateManager& gameStateManager) override;
    BoundingBox getBoundingBox() const override;
    float getCollisionRadius() const override;

    void rotate();
    int getRotationState() const { return _rotationState; }
    void setRotationState(int state) { _rotationState = state % 4; }
    int getRow() const { return _row; }
    int getCol() const { return _col; }

    // Animação de movimento
    void moveTo(const Vector3f& newPos) { _targetPosition = newPos; }

private:
    float _size;
    int _rotationState; // 0=0°, 1=90°, 2=180°, 3=270°
    float _currentAngle; // Para animação de rotação
    float _targetAngle;  // Para animação de rotação
    int _row, _col;
    CubePuzzle* _puzzleManager;
    Vector3f _currentPosition; // Para animação de movimento
    Vector3f _targetPosition;  // Para animação de movimento
};

#endif // ROTATINGCUBE_H
