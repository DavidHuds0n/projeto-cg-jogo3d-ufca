#include "../include/Wall.h"
#include "../include/TextureManager.h"
#include <GL/freeglut.h>
#include <iostream>

Wall::Wall(const Vector3f& position, const Vector3f& size, const std::string& textureFile)
    : _position(position), _size(size)
{
    _textureID = TextureManager::loadTexture(textureFile);
}

Wall::Wall(const Vector3f& position, const Vector3f& size)
    : Wall(position, size, "") {}

void Wall::update(float deltaTime, GameStateManager& gameStateManager) {
    // Paredes são estáticas
}

// --- FUNÇÃO RENDER ATUALIZADA ---
void Wall::render() {
    // Define a cor base da parede como branco.
    // Com GL_COLOR_MATERIAL ativo, a iluminação será calculada sobre esta cor
    // e depois multiplicada pela textura. Branco é a cor neutra ideal.
    glColor3f(1.0f, 1.0f, 1.0f);

    if (_textureID) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    // REMOVEMOS os glMaterialfv daqui, pois agora usamos glColorMaterial.

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);

    float hx = _size.x / 2.0f;
    float hy = _size.y / 2.0f;
    float hz = _size.z / 2.0f;

    // --- CORREÇÃO DA ESCALA DA TEXTURA ---
    // Este valor controla o tamanho da textura.
    // Números maiores = textura menor e mais repetida.
    // Números menores = textura maior e menos repetida.
    float textureScale = 4.0f;

    float u_repeat_x = _size.x / textureScale;
    float v_repeat_y = _size.y / textureScale;
    float w_repeat_z = _size.z / textureScale;

    glBegin(GL_QUADS);
        // Face da frente (+Z)
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0, 0);          glVertex3f(-hx, -hy, hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, -hy, hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f( hx,  hy, hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy, hz);

        // Face de trás (-Z)
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0, 0);          glVertex3f( hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f( hx,  hy, -hz);

        // Face da direita (+X)
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0);          glVertex3f(hx, -hy, -hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(hx, -hy,  hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(hx,  hy,  hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(hx,  hy, -hz);

        // Face da esquerda (-X)
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0);          glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy,  hz);

        // Face de cima (+Y)
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0, 0);          glVertex3f(-hx, hy,  hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, hy,  hz);
        glTexCoord2f(u_repeat_x, w_repeat_z); glVertex3f( hx, hy, -hz);
        glTexCoord2f(0, w_repeat_z); glVertex3f(-hx, hy, -hz);

        // Face de baixo (-Y)
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0, 0);          glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, w_repeat_z); glVertex3f( hx, -hy,  hz);
        glTexCoord2f(0, w_repeat_z); glVertex3f(-hx, -hy,  hz);
    glEnd();

    glPopMatrix();

    if (_textureID) {
        glDisable(GL_TEXTURE_2D);
    }
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
