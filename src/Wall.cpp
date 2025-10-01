#include "../include/Wall.h"
#include <GL/freeglut.h>

Wall::Wall(const Vector3f& position, const Vector3f& size) {
    _position = position;
    _size = size;
}

void Wall::update(float deltaTime) {
    // As paredes s�o est�ticas.
}

void Wall::render() {
    // Define o material da parede.
    GLfloat wall_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat wall_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glPushMatrix();

    // --- CORRE��O AQUI: C�lculo din�mico da normal ---
    bool isHorizontal = (_size.x > _size.z);
    if (isHorizontal) { // Parede de frente ou fundo
        // Se a parede est� na frente (Z > 0), a normal aponta para dentro (-Z).
        // Se est� atr�s (Z < 0), a normal aponta para dentro (+Z).
        if (_position.z > 0) {
            glNormal3f(0.0f, 0.0f, -1.0f);
        } else {
            glNormal3f(0.0f, 0.0f, 1.0f);
        }
    } else { // Parede da esquerda ou direita
        // Se a parede est� � direita (X > 0), a normal aponta para dentro (-X).
        // Se est� � esquerda (X < 0), a normal aponta para dentro (+X).
        if (_position.x > 0) {
            glNormal3f(-1.0f, 0.0f, 0.0f);
        } else {
            glNormal3f(1.0f, 0.0f, 0.0f);
        }
    }

    // O resto do c�digo para desenhar a grade continua o mesmo
    int divisions = 70;

    float halfWidth = _size.x / 2.0f;
    float halfHeight = _size.y / 2.0f;
    float halfDepth = _size.z / 2.0f;

    float startX = _position.x - halfWidth;
    float startY = _position.y - halfHeight;
    float startZ = _position.z - halfDepth;

    float segmentWidth = _size.x / divisions;
    float segmentHeight = _size.y / divisions;
    float segmentDepth = _size.z / divisions;

    glBegin(GL_QUADS);
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {
            if (isHorizontal) { // Parede orientada no eixo X
                float currentX = startX + i * segmentWidth;
                float currentY = startY + j * segmentHeight;

                glVertex3f(currentX,              currentY,               _position.z);
                glVertex3f(currentX + segmentWidth, currentY,               _position.z);
                glVertex3f(currentX + segmentWidth, currentY + segmentHeight, _position.z);
                glVertex3f(currentX,              currentY + segmentHeight, _position.z);

            } else { // Parede orientada no eixo Z
                float currentZ = startZ + i * segmentDepth;
                float currentY = startY + j * segmentHeight;

                glVertex3f(_position.x, currentY,               currentZ);
                glVertex3f(_position.x, currentY,               currentZ + segmentDepth);
                glVertex3f(_position.x, currentY + segmentHeight, currentZ + segmentDepth);
                glVertex3f(_position.x, currentY + segmentHeight, currentZ);
            }
        }
    }
    glEnd();

    glPopMatrix();
}
