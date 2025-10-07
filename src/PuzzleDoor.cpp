/**
 * @file PuzzleDoor.cpp
 * @brief Implementa��o da classe PuzzleDoor, que representa uma porta com um �cone visual de puzzle.
 */

#include "../include/PuzzleDoor.h"
#include <GL/freeglut.h>
#include <cmath>
#include <algorithm> // Inclu�do para compatibilidade

//================================================================================
// Fun��es Auxiliares de Desenho
//================================================================================

/**
 * @struct BlendGuard
 * @brief Uma classe auxiliar para gerenciar temporariamente o estado de blending do OpenGL.
 *
 * O construtor desabilita a ilumina��o e o teste de profundidade, habilita o blending
 * com uma fun��o aditiva ("neon") e armazena os estados originais. O destrutor restaura
 * os estados de volta para o que eram antes.
 */
struct BlendGuard {
    GLboolean lighting, depth, blend;
    GLint src, dst;
    BlendGuard() {
        lighting = glIsEnabled(GL_LIGHTING);
        depth    = glIsEnabled(GL_DEPTH_TEST);
        blend    = glIsEnabled(GL_BLEND);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glGetIntegerv(GL_BLEND_SRC, &src);
        glGetIntegerv(GL_BLEND_DST, &dst);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); // aditivo = brilho
    }
    ~BlendGuard() {
        glBlendFunc(src, dst);
        if (!blend)  glDisable(GL_BLEND);
        if (depth)   glEnable(GL_DEPTH_TEST);
        if (lighting) glEnable(GL_LIGHTING);
    }
};

/**
 * @brief Desenha o corpo principal da porta.
 *
 * A porta � modelada usando cubos s�lidos para a moldura, a folha e os pain�is.
 * Tamb�m � adicionada uma ma�aneta.
 *
 * @param color A cor base da porta.
 */
static void drawDoorBody(const Vector3f& color) {
    const float W = 1.1f;
    const float H = 2.2f;
    const float T = 0.10f;

    // moldura
    glColor3f(color.x*0.9f, color.y*0.9f, color.z*0.9f);
    glPushMatrix();
      glScalef(W+0.12f, H+0.12f, T);
      glutSolidCube(1.0);
    glPopMatrix();

    // folha
    glColor3f(color.x, color.y, color.z);
    glPushMatrix();
      glScalef(W, H, T*0.6f);
      glutSolidCube(1.0);
    glPopMatrix();

    // pain�is
    glColor3f(color.x*0.85f, color.y*0.85f, color.z*0.85f);
    glPushMatrix();
      glTranslatef(0.0f, 0.45f, T*0.35f);
      glScalef(W*0.75f, H*0.32f, 0.02f);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0.0f, -0.40f, T*0.35f);
      glScalef(W*0.78f, H*0.36f, 0.02f);
      glutSolidCube(1.0);
    glPopMatrix();

    // ma�aneta � esquerda
    glColor3f(0.95f, 0.95f, 0.95f);
    glPushMatrix();
      glTranslatef(-W*0.48f, -0.05f, T*0.35f);
      glScalef(0.06f, 0.30f, 0.06f);
      glutSolidCube(1.0);
    glPopMatrix();
}

/**
 * @brief Desenha o �cone de onda.
 * @param scale O fator de escala para o �cone.
 */
static void drawIconWave(float scale) {
    const float A = 0.30f, B = 0.22f;
    const int   N = 64;
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<=N;i++){
        float t = (float)i/N; float x = (t-0.5f) * 0.9f;
        float y = 0.10f + A * std::sin(6.28318f*(t+0.05f));
        glVertex3f(scale*x, scale*y, 0.0f);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<=N;i++){
        float t = (float)i/N; float x = (t-0.5f) * 0.9f;
        float y = -0.10f + B * std::sin(6.28318f*(t+0.20f));
        glVertex3f(scale*x, scale*y, 0.0f);
    }
    glEnd();
}

/**
 * @brief Desenha o �cone de sol.
 * @param scale O fator de escala para o �cone.
 */
static void drawIconSun(float scale) {
    const int N = 48; const float R = 0.28f;
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<N;i++){
        float a = 2.0f*3.14159f*i/N;
        glVertex3f(scale*R*std::cos(a), scale*R*std::sin(a), 0.0f);
    }
    glEnd();
    glBegin(GL_LINES);
    for (int i=0;i<12;i++){
        float a = 2.0f*3.14159f*i/12.0f; float r1 = R*1.15f, r2 = R*1.45f;
        glVertex3f(scale*r1*std::cos(a), scale*r1*std::sin(a), 0.0f);
        glVertex3f(scale*r2*std::cos(a), scale*r2*std::sin(a), 0.0f);
    }
    glEnd();
}

/**
 * @brief Desenha o �cone de montanha.
 * @param scale O fator de escala para o �cone.
 */
static void drawIconMountain(float scale) {
    glBegin(GL_LINE_STRIP);
      glVertex3f(scale*-0.45f, scale*-0.25f, 0.0f);
      glVertex3f(scale*-0.15f, scale* 0.18f, 0.0f);
      glVertex3f(scale* 0.00f, scale*-0.10f, 0.0f);
      glVertex3f(scale* 0.20f, scale* 0.26f, 0.0f);
      glVertex3f(scale* 0.40f, scale*-0.25f, 0.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
      glVertex3f(scale*0.13f, scale*0.20f, 0.0f);
      glVertex3f(scale*0.20f, scale*0.26f, 0.0f);
      glVertex3f(scale*0.27f, scale*0.20f, 0.0f);
    glEnd();
}

/**
 * @brief Desenha o �cone em estilo neon na porta.
 *
 * Utiliza o `BlendGuard` para criar um efeito de brilho aditivo e desenha o �cone
 * duas vezes com diferentes opacidades e larguras de linha para simular o brilho.
 *
 * @param icon O tipo de �cone a ser desenhado.
 * @param glow A cor do brilho.
 * @param zOffset O deslocamento no eixo Z para o �cone.
 */
static void drawIconNeon(PuzzleDoor::Icon icon, const Vector3f& glow, float zOffset) {
    BlendGuard guard;
    auto draw = [&](float scale, float alpha, float lineWidth){
        glColor4f(glow.x, glow.y, glow.z, alpha);
        glLineWidth(lineWidth);
        glPushMatrix();
          glTranslatef(0.0f, 0.15f, zOffset);
          switch (icon) {
            case PuzzleDoor::Icon::Wave:     drawIconWave(scale);     break;
            case PuzzleDoor::Icon::Sun:      drawIconSun(scale);      break;
            case PuzzleDoor::Icon::Mountain: drawIconMountain(scale); break;
            default: break;
          }
        glPopMatrix();
    };
    draw(1.0f, 0.18f, 8.0f);
    draw(1.0f, 0.90f, 2.5f);
}


//================================================================================
// Implementa��o da Classe PuzzleDoor (Corrigido)
//================================================================================

/**
 * @brief Construtor da classe PuzzleDoor.
 *
 * Inicializa a porta com uma cor, um �cone e um brilho de �cone espec�ficos,
 * herdando as propriedades de `Door` e `InteractableObject`.
 *
 * @param position A posi��o da porta no espa�o 3D.
 * @param targetRoomIndex O �ndice da sala para a qual a porta leva.
 * @param spawnPosition A posi��o do jogador ao entrar na sala de destino.
 * @param doorColor A cor base da porta.
 * @param icon O tipo de �cone do puzzle associado.
 * @param iconGlow A cor do brilho do �cone.
 */
PuzzleDoor::PuzzleDoor(const Vector3f& position,
                       int targetRoomIndex,
                       const Vector3f& spawnPosition,
                       const Vector3f& doorColor,
                       Icon icon,
                       const Vector3f& iconGlow)
    : Door(position, targetRoomIndex, spawnPosition),
      _doorColor(doorColor),
      _iconGlow(iconGlow),
      _icon(icon)
{
    // O construtor da classe base j� fez todo o trabalho de inicializa��o
    // de posi��o, raio de colis�o, etc. O corpo pode ficar vazio.
}

/**
 * @brief Renderiza a porta na tela, incluindo o corpo e o �cone.
 *
 * O m�todo desabilita a ilumina��o e armazena os atributos atuais do OpenGL
 * antes de desenhar o corpo da porta e o �cone, restaurando-os no final.
 */
void PuzzleDoor::render() {
    glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
      // Usa a fun��o getPosition() herdada de Door/InteractableObject
      glTranslatef(getPosition().x, getPosition().y, getPosition().z);
      drawDoorBody(_doorColor);

      if (_icon != Icon::None) {
          const float T = 0.10f;
          drawIconNeon(_icon, _iconGlow, T * 0.49f);
      }
    glPopMatrix();
    glPopAttrib();
}
