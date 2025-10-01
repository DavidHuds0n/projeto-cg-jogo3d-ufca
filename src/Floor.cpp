#include "../include/Floor.h"
#include <GL/freeglut.h>

Floor::Floor(const Vector3f& position, const Vector2f& size) {
    _position = position;
    _size = size;
}

void Floor::update(float deltaTime) {
    // O chão é estático.
}

void Floor::render() {
    // --- 1. DESENHA A BASE SÓLIDA DO CHÃO ---
    GLfloat floor_diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat floor_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floor_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glScalef(_size.x, 0.1f, _size.y);
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- 2. DESENHA O GRID POR CIMA DO CHÃO ---
    glDisable(GL_LIGHTING); // Desabilita a iluminação para as linhas do grid

    glColor3f(0.4f, 0.4f, 0.4f); // Define a cor do grid (cinza claro)
    glBegin(GL_LINES);

    // O topo do nosso chão está em Y = 0.05 (metade da altura do cubo escalado).
    // Desenhamos o grid um pouco acima disso para evitar Z-fighting.
    float grid_y = 0.051f;

    // Desenha as linhas ao longo do eixo Z
    for (float i = -_size.x / 2.0f; i <= _size.x / 2.0f; i += 1.0f) {
        glVertex3f(i, grid_y, -_size.y / 2.0f);
        glVertex3f(i, grid_y,  _size.y / 2.0f);
    }

    // Desenha as linhas ao longo do eixo X
    for (float i = -_size.y / 2.0f; i <= _size.y / 2.0f; i += 1.0f) {
        glVertex3f(-_size.x / 2.0f, grid_y, i);
        glVertex3f( _size.x / 2.0f, grid_y, i);
    }

    glEnd();
    glEnable(GL_LIGHTING); // Reabilita a iluminação para o resto da cena
}
