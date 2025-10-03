#include "../include/Wall.h"
#include <GL/freeglut.h>

Wall::Wall(const Vector3f& position, const Vector3f& size) {
    _position = position;
    _size = size;
}

void Wall::update(float deltaTime, GameStateManager& gameStateManager) {
    // Paredes são estáticas.
}

void Wall::render() {
    // Define o material da parede.
    GLfloat wall_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat wall_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glPushMatrix();

    bool isHorizontal = (_size.x > _size.z);

    // Define a normal correta para a iluminação
    if (isHorizontal) {
        if (_position.z > 0) glNormal3f(0.0f, 0.0f, -1.0f);
        else glNormal3f(0.0f, 0.0f, 1.0f);
    } else {
        if (_position.x > 0) glNormal3f(-1.0f, 0.0f, 0.0f);
        else glNormal3f(1.0f, 0.0f, 0.0f);
    }

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
            if (isHorizontal) { // Parede orientada no eixo X (frente/fundo)
                float currentX = startX + i * segmentWidth;
                float currentY = startY + j * segmentHeight;

                if (_position.z > 0) { // Parede da FRENTE (Z > 0) - Ordem invertida
                    glVertex3f(currentX,              currentY,               _position.z);
                    glVertex3f(currentX,              currentY + segmentHeight, _position.z);
                    glVertex3f(currentX + segmentWidth, currentY + segmentHeight, _position.z);
                    glVertex3f(currentX + segmentWidth, currentY,               _position.z);
                } else { // Parede de TRÁS (Z < 0) - Ordem normal
                    glVertex3f(currentX,              currentY,               _position.z);
                    glVertex3f(currentX + segmentWidth, currentY,               _position.z);
                    glVertex3f(currentX + segmentWidth, currentY + segmentHeight, _position.z);
                    glVertex3f(currentX,              currentY + segmentHeight, _position.z);
                }
            } else { // Parede orientada no eixo Z (esquerda/direita)
                float currentZ = startZ + i * segmentDepth;
                float currentY = startY + j * segmentHeight;

                if (_position.x > 0) { // Parede da DIREITA (X > 0) - Ordem invertida
                    glVertex3f(_position.x, currentY,               currentZ + segmentDepth);
                    glVertex3f(_position.x, currentY + segmentHeight, currentZ + segmentDepth);
                    glVertex3f(_position.x, currentY + segmentHeight, currentZ);
                    glVertex3f(_position.x, currentY,               currentZ);
                } else { // Parede da ESQUERDA (X < 0) - Ordem normal
                    glVertex3f(_position.x, currentY,               currentZ + segmentDepth);
                    glVertex3f(_position.x, currentY,               currentZ);
                    glVertex3f(_position.x, currentY + segmentHeight, currentZ);
                    glVertex3f(_position.x, currentY + segmentHeight, currentZ + segmentDepth);
                }
            }
        }
    }
    glEnd();
    glPopMatrix();
}

BoundingBox Wall::getBoundingBox() const {
    BoundingBox box;
    float halfWidth = _size.x / 2.0f;
    float halfHeight = _size.y / 2.0f;
    float halfDepth = _size.z / 2.0f;

    box.min = { _position.x - halfWidth, _position.y - halfHeight, _position.z - halfDepth };
    box.max = { _position.x + halfWidth, _position.y + halfHeight, _position.z + halfDepth };

    return box;
}
