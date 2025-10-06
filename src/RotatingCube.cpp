#include "../include/RotatingCube.h"
#include "../include/CubePuzzle.h"
#include <GL/freeglut.h>
#include <cmath>

RotatingCube::RotatingCube(const Vector3f& position, float size, int row, int col, CubePuzzle* puzzleManager)
    : InteractableObject(position), _size(size), _row(row), _col(col), _puzzleManager(puzzleManager) {
    // Estado inicial aleatório
    _rotationState = rand() % 4;
    _currentAngle = _rotationState * 90.0f;
    _targetAngle = _currentAngle;
}

void RotatingCube::update(float deltaTime, GameStateManager&) {
    // Animação suave
    if (std::abs(_currentAngle - _targetAngle) > 0.1f) {
        float diff = _targetAngle - _currentAngle;
        _currentAngle += diff * std::min(1.0f, deltaTime * 10.0f);
    } else {
        _currentAngle = _targetAngle;
    }
}

void RotatingCube::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_currentAngle, 0, 1, 0);
    glScalef(_size, _size, _size);

    // Cores para as faces
    GLfloat colors[6][4] = {
        {1, 1, 0, 1}, // Amarelo
        {1, 1, 1, 1}  // Branco
    };
    glBegin(GL_QUADS);
    // +Z
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[0]);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f,  0.5f, 0.5f);
    glVertex3f(-0.5f,  0.5f, 0.5f);
    // -Z
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[1]);
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    // +Y
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[1]);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    // -Y
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[1]);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    // +X
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[1]);
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    // -X
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors[1]);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();
    glPopMatrix();
}

void RotatingCube::onClick(GameStateManager&) {
    // Apenas avisa o gerente
    if (_puzzleManager) {
        _puzzleManager->onCubeClicked(_row, _col);
    }
}

void RotatingCube::rotate() {
    _rotationState = (_rotationState + 1) % 4;
    _targetAngle = _rotationState * 90.0f;
}

BoundingBox RotatingCube::getBoundingBox() const {
    float half = _size / 2.0f;
    BoundingBox box;
    box.min = {_position.x - half, _position.y - half, _position.z - half};
    box.max = {_position.x + half, _position.y + half, _position.z + half};
    return box;
}

float RotatingCube::getCollisionRadius() const {
    return _size / 2.0f;
}
