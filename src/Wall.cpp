/**
 * @file Wall.cpp
 * @brief Implementa��o da classe Wall, que representa uma parede com textura.
 */

#include "../include/Wall.h"
#include "../include/TextureManager.h"
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Construtor da classe Wall que carrega uma textura.
 *
 * Inicializa a parede com uma posi��o e tamanho, e carrega uma textura a
 * partir do arquivo especificado.
 *
 * @param position A posi��o do centro da parede no espa�o 3D.
 * @param size As dimens�es (largura, altura, profundidade) da parede.
 * @param textureFile O caminho para o arquivo de textura.
 */
Wall::Wall(const Vector3f& position, const Vector3f& size, const std::string& textureFile)
    : _position(position), _size(size)
{
    _textureID = TextureManager::loadTexture(textureFile);
}

/**
 * @brief Construtor da classe Wall sem textura.
 *
 * Delega para o construtor principal, passando uma string vazia para
 * o arquivo de textura, o que resulta em uma parede sem textura.
 *
 * @param position A posi��o do centro da parede no espa�o 3D.
 * @param size As dimens�es (largura, altura, profundidade) da parede.
 */
Wall::Wall(const Vector3f& position, const Vector3f& size)
    : Wall(position, size, "") {}

/**
 * @brief Atualiza o estado da parede.
 *
 * Este m�todo n�o realiza nenhuma a��o, pois as paredes s�o est�ticas.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void Wall::update(float deltaTime, GameStateManager& gameStateManager) {
    // Paredes s�o est�ticas
}

/**
 * @brief Renderiza a parede na tela.
 *
 * A fun��o desenha um cubo com seis faces. As quatro faces laterais
 * s�o desenhadas com v�rtices duplos para que a parede possa ser vista
 * de ambos os lados (frente e verso), o que � �til em ambientes
 * internos. A textura � aplicada se um ID de textura for v�lido.
 */
void Wall::render() {
    glColor3f(1.0f, 1.0f, 1.0f);

    if (_textureID) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);

    float hx = _size.x / 2.0f;
    float hy = _size.y / 2.0f;
    float hz = _size.z / 2.0f;

    float textureScale = 4.0f;
    float u_repeat_x = _size.x / textureScale;
    float v_repeat_y = _size.y / textureScale;
    float w_repeat_z = _size.z / textureScale;

    glBegin(GL_QUADS);
        // --- Face da frente (+Z) ---
        // Lado de fora
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, -hy, hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, -hy, hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f( hx,  hy, hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy, hz);
        // Lado de dentro (v�rtices invertidos, normal invertida)
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, -hy, hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy, hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f( hx,  hy, hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, -hy, hz);

        // --- Face de tr�s (-Z) ---
        // Lado de fora
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0, 0); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f( hx,  hy, -hz);
        // Lado de dentro
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0, 0); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f( hx,  hy, -hz);
        glTexCoord2f(u_repeat_x, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f(-hx, -hy, -hz);

        // --- Face da direita (+X) ---
        // Lado de fora
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(hx, -hy, -hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(hx, -hy,  hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(hx,  hy,  hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(hx,  hy, -hz);
        // Lado de dentro
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(hx, -hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(hx,  hy, -hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(hx,  hy,  hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(hx, -hy,  hz);

        // --- Face da esquerda (-X) ---
        // Lado de fora
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy,  hz);
        // Lado de dentro
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, -hy,  hz);
        glTexCoord2f(0, v_repeat_y); glVertex3f(-hx,  hy,  hz);
        glTexCoord2f(w_repeat_z, v_repeat_y); glVertex3f(-hx,  hy, -hz);
        glTexCoord2f(w_repeat_z, 0); glVertex3f(-hx, -hy, -hz);

        // As faces de cima e de baixo n�o precisam ser de dupla-face
        // Face de cima (+Y)
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, hy,  hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, hy,  hz);
        glTexCoord2f(u_repeat_x, w_repeat_z); glVertex3f( hx, hy, -hz);
        glTexCoord2f(0, w_repeat_z); glVertex3f(-hx, hy, -hz);
        // Face de baixo (-Y)
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0, 0); glVertex3f(-hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, 0); glVertex3f( hx, -hy, -hz);
        glTexCoord2f(u_repeat_x, w_repeat_z); glVertex3f( hx, -hy,  hz);
        glTexCoord2f(0, w_repeat_z); glVertex3f(-hx, -hy,  hz);
    glEnd();

    glPopMatrix();

    if (_textureID) {
        glDisable(GL_TEXTURE_2D);
    }
}

/**
 * @brief Obt�m a caixa delimitadora (Bounding Box) da parede.
 *
 * A caixa de colis�o � calculada com base na posi��o e no tamanho da parede.
 *
 * @return Um objeto BoundingBox que representa os limites da parede.
 */
BoundingBox Wall::getBoundingBox() const {
    BoundingBox box;
    float halfWidth = _size.x / 2.0f;
    float halfHeight = _size.y / 2.0f;
    float halfDepth = _size.z / 2.0f;

    box.min = { _position.x - halfWidth, _position.y - halfHeight, _position.z - halfDepth };
    box.max = { _position.x + halfWidth, _position.y + halfHeight, _position.z + halfDepth };
    return box;
}
