#include "../include/RotatingCube.h"
#include "../include/CubePuzzle.h"
#include <GL/freeglut.h>
#include <cmath>


RotatingCube::RotatingCube(const Vector3f& position, float size, int row, int col, CubePuzzle* puzzleManager)
    : InteractableObject(position), _size(size), _row(row), _col(col), _puzzleManager(puzzleManager) {

    // Linhas antigas comentadas para a alteração temporária
    // _rotationState = rand() % 4;
    // if (row == 0 && col == 0) {
    //     _rotationState = 0;
    // }

    // --- NOVA LINHA TEMPORÁRIA ---
    // Força TODOS os cubos a começarem no estado 0 (a solução do puzzle)
    _rotationState = 0;

    // O resto do código continua igual, atualizando os ângulos com base no _rotationState
    _currentAngle = _rotationState * 90.0f;
    _targetAngle = _currentAngle;
    _currentPosition = position;
    _targetPosition = position;
}

void RotatingCube::update(float deltaTime, GameStateManager&) {
    // Animação suave de rotação
    if (std::abs(_currentAngle - _targetAngle) > 0.1f) {
        float diff = _targetAngle - _currentAngle;
        _currentAngle += diff * std::min(1.0f, deltaTime * 10.0f);
    } else {
        _currentAngle = _targetAngle;
    }
    // Animação suave de movimento (LERP)
    float speed = 0.1f; // quanto maior, mais rápido
    _currentPosition.x += (_targetPosition.x - _currentPosition.x) * std::min(1.0f, deltaTime * speed);
    _currentPosition.y += (_targetPosition.y - _currentPosition.y) * std::min(1.0f, deltaTime * speed);
    _currentPosition.z += (_targetPosition.z - _currentPosition.z) * std::min(1.0f, deltaTime * speed);
}

void RotatingCube::render() {
    glPushMatrix();
    glTranslatef(_currentPosition.x, _currentPosition.y, _currentPosition.z);
    glRotatef(_currentAngle, 0, 1, 0);
    glScalef(_size, _size, _size);

    // --- LÓGICA DE COR CORRIGIDA ---
    // Cores definidas para as faces
    Vector3f corEspecial;
    Vector3f corNormal;

    // Define as cores com base se é o cubo especial (vermelho) ou normal (amarelo)
    if (_row == 0 && _col == 0) {
        corEspecial = {1.0f, 0.0f, 0.0f}; // Vermelho
        corNormal = {0.4f, 0.4f, 0.4f};   // Cinza
    } else {
        corEspecial = {1.0f, 1.0f, 0.0f}; // Amarelo
        corNormal = {1.0f, 1.0f, 1.0f};   // Branco
    }

    glBegin(GL_QUADS);
    // +Z (Face Especial)
    glColor3f(corEspecial.x, corEspecial.y, corEspecial.z);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f( 0.5f, -0.5f, 0.5f); glVertex3f( 0.5f,  0.5f, 0.5f); glVertex3f(-0.5f,  0.5f, 0.5f);

    // As outras 5 faces usam a cor normal
    glColor3f(corNormal.x, corNormal.y, corNormal.z);
    // -Z
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
    // +Y
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f,  0.5f); glVertex3f( 0.5f, 0.5f,  0.5f); glVertex3f( 0.5f, 0.5f, -0.5f);
    // -Y
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
    // +X
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f,  0.5f, -0.5f); glVertex3f(0.5f,  0.5f,  0.5f); glVertex3f(0.5f, -0.5f,  0.5f);
    // -X
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);

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
    // Apenas animação suave de rotação, sem alterar posição
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
