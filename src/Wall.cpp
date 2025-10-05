#include "../include/Wall.h"
#include "../include/TextureManager.h"
#include <GL/freeglut.h>
#include <iostream>

Wall::Wall(const Vector3f& position, const Vector3f& size, const std::string& textureFile)
    : _position(position), _size(size)
{
    _textureID = TextureManager::loadTexture(textureFile);
}

void Wall::update(float deltaTime, GameStateManager& gameStateManager) {
    // Paredes são estáticas, nada a atualizar
}

void Wall::render() {
    // Habilita textura se tiver
    if (_textureID) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureID);
    }

    // Define material (opcional, para iluminação)
    GLfloat wall_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat wall_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glPushMatrix();

    bool isHorizontal = (_size.x > _size.z);
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
            float u0 = i / float(divisions);
            float v0 = j / float(divisions);
            float u1 = (i + 1) / float(divisions);
            float v1 = (j + 1) / float(divisions);

            if (isHorizontal) { // Parede frente/trás
                float currentX = startX + i * segmentWidth;
                float currentY = startY + j * segmentHeight;
                float z = _position.z;

                glNormal3f(0.0f, 0.0f, (_position.z > 0 ? -1.0f : 1.0f));
                if (_position.z > 0) {
                    glTexCoord2f(u0, v0); glVertex3f(currentX, currentY, z);
                    glTexCoord2f(u0, v1); glVertex3f(currentX, currentY + segmentHeight, z);
                    glTexCoord2f(u1, v1); glVertex3f(currentX + segmentWidth, currentY + segmentHeight, z);
                    glTexCoord2f(u1, v0); glVertex3f(currentX + segmentWidth, currentY, z);
                } else {
                    glTexCoord2f(u0, v0); glVertex3f(currentX, currentY, z);
                    glTexCoord2f(u1, v0); glVertex3f(currentX + segmentWidth, currentY, z);
                    glTexCoord2f(u1, v1); glVertex3f(currentX + segmentWidth, currentY + segmentHeight, z);
                    glTexCoord2f(u0, v1); glVertex3f(currentX, currentY + segmentHeight, z);
                }

            } else { // Parede esquerda/direita
                float currentZ = startZ + i * segmentDepth;
                float currentY = startY + j * segmentHeight;
                float x = _position.x;

                glNormal3f((_position.x > 0 ? -1.0f : 1.0f), 0.0f, 0.0f);
                if (_position.x > 0) {
                    glTexCoord2f(u0, v0); glVertex3f(x, currentY, currentZ + segmentDepth);
                    glTexCoord2f(u0, v1); glVertex3f(x, currentY + segmentHeight, currentZ + segmentDepth);
                    glTexCoord2f(u1, v1); glVertex3f(x, currentY + segmentHeight, currentZ);
                    glTexCoord2f(u1, v0); glVertex3f(x, currentY, currentZ);
                } else {
                    glTexCoord2f(u0, v0); glVertex3f(x, currentY, currentZ + segmentDepth);
                    glTexCoord2f(u1, v0); glVertex3f(x, currentY, currentZ);
                    glTexCoord2f(u1, v1); glVertex3f(x, currentY + segmentHeight, currentZ);
                    glTexCoord2f(u0, v1); glVertex3f(x, currentY + segmentHeight, currentZ + segmentDepth);
                }
            }
        }
    }
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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
