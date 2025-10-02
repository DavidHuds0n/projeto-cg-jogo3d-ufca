#include "../include/Floor.h"
#include <GL/freeglut.h>

Floor::Floor(const Vector3f& position, const Vector2f& size) {
    _position = position;
    _size = size;
}

void Floor::update(float deltaTime, GameStateManager& gameStateManager) {
    // Estático
}

void Floor::render() {
    GLfloat floor_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat floor_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floor_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);

    int divisions = 70;
    float halfWidth = _size.x / 2.0f;
    float halfDepth = _size.y / 2.0f;
    float startX = _position.x - halfWidth;
    float startZ = _position.z - halfDepth;
    float segmentWidth = _size.x / divisions;
    float segmentDepth = _size.y / divisions;

    glBegin(GL_QUADS);
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {
            float currentX = startX + i * segmentWidth;
            float currentZ = startZ + j * segmentDepth;
            glVertex3f(currentX, _position.y, currentZ);
            glVertex3f(currentX + segmentWidth, _position.y, currentZ);
            glVertex3f(currentX + segmentWidth, _position.y, currentZ + segmentDepth);
            glVertex3f(currentX, _position.y, currentZ + segmentDepth);
        }
    }
    glEnd();

    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    float grid_y = _position.y + 0.01f;
    for (int i = 0; i <= divisions; i++) {
        float currentX = startX + i * segmentWidth;
        glVertex3f(currentX, grid_y, -halfDepth);
        glVertex3f(currentX, grid_y,  halfDepth);
    }
    for (int j = 0; j <= divisions; j++) {
        float currentZ = startZ + j * segmentDepth;
        glVertex3f(-halfWidth, grid_y, currentZ);
        glVertex3f( halfWidth, grid_y, currentZ);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

BoundingBox Floor::getBoundingBox() const {
    // O chão não é um obstáculo colidível.
    return {{0,0,0}, {0,0,0}};
}
