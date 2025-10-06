#include "../include/PuzzleDoor.h"
#include <GL/freeglut.h>
#include <cmath>
#include "../include/GameStateManager.h"
#include <algorithm>

// -------- util: estado de blending “neon” ----------
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
        if (!blend)   glDisable(GL_BLEND);
        if (depth)    glEnable(GL_DEPTH_TEST);
        if (lighting) glEnable(GL_LIGHTING);
    }
};

// -------- porta “estilo foto” (igual versão anterior) ----------
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

    // painéis
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

    // maçaneta à esquerda
    glColor3f(0.95f, 0.95f, 0.95f);
    glPushMatrix();
      glTranslatef(-W*0.48f, -0.05f, T*0.35f);
      glScalef(0.06f, 0.30f, 0.06f);
      glutSolidCube(1.0);
    glPopMatrix();
}

// -------- desenhos dos ícones no plano da porta ----------
static void drawIconWave(float scale) {
    // 2 ondas sobrepostas
    const float A = 0.30f, B = 0.22f;   // amplitudes
    const int   N = 64;
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<=N;i++){
        float t = (float)i/N;
        float x = (t-0.5f) * 0.9f;
        float y = 0.10f + A * std::sin(6.28318f*(t+0.05f));
        glVertex3f(scale*x, scale*y, 0.0f);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<=N;i++){
        float t = (float)i/N;
        float x = (t-0.5f) * 0.9f;
        float y = -0.10f + B * std::sin(6.28318f*(t+0.20f));
        glVertex3f(scale*x, scale*y, 0.0f);
    }
    glEnd();
}

static void drawIconSun(float scale) {
    // círculo + raios
    const int N = 48;
    const float R = 0.28f;
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<N;i++){
        float a = 2.0f*3.14159f*i/N;
        glVertex3f(scale*R*std::cos(a), scale*R*std::sin(a), 0.0f);
    }
    glEnd();
    // raios
    glBegin(GL_LINES);
    for (int i=0;i<12;i++){
        float a = 2.0f*3.14159f*i/12.0f;
        float r1 = R*1.15f, r2 = R*1.45f;
        glVertex3f(scale*r1*std::cos(a), scale*r1*std::sin(a), 0.0f);
        glVertex3f(scale*r2*std::cos(a), scale*r2*std::sin(a), 0.0f);
    }
    glEnd();
}

static void drawIconMountain(float scale) {
    // três picos
    glBegin(GL_LINE_STRIP);
      glVertex3f(scale*-0.45f, scale*-0.25f, 0.0f);
      glVertex3f(scale*-0.15f, scale* 0.18f, 0.0f);
      glVertex3f(scale* 0.00f, scale*-0.10f, 0.0f);
      glVertex3f(scale* 0.20f, scale* 0.26f, 0.0f);
      glVertex3f(scale* 0.40f, scale*-0.25f, 0.0f);
    glEnd();
    // neve do pico do meio
    glBegin(GL_LINE_STRIP);
      glVertex3f(scale*0.13f, scale*0.20f, 0.0f);
      glVertex3f(scale*0.20f, scale*0.26f, 0.0f);
      glVertex3f(scale*0.27f, scale*0.20f, 0.0f);
    glEnd();
}

// desenha ícone com “aura” (duas passadas aumentando linewidth e alpha)
static void drawIconNeon(PuzzleDoor::Icon icon, const Vector3f& glow, float zOffset) {
    BlendGuard guard;

    auto draw = [&](float scale, float alpha, float lineWidth){
        glColor4f(glow.x, glow.y, glow.z, alpha);
        glLineWidth(lineWidth);
        glPushMatrix();
          glTranslatef(0.0f, 0.15f, zOffset); // centro do desenho
          switch (icon) {
            case PuzzleDoor::Icon::Wave:     drawIconWave(scale);     break;
            case PuzzleDoor::Icon::Sun:      drawIconSun(scale);      break;
            case PuzzleDoor::Icon::Mountain: drawIconMountain(scale); break;
            default: break;
          }
        glPopMatrix();
    };

    // “aura” (grossa, alpha baixo) + traço principal (fino, alpha alto)
    draw(/*scale*/1.0f, /*alpha*/0.18f, /*lw*/8.0f);
    draw(/*scale*/1.0f, /*alpha*/0.90f, /*lw*/2.5f);
}

// ----------------------------------------------------------

/*PuzzleDoor::PuzzleDoor(const Vector3f& position, Mode mode, const Vector3f& doorColor,
                       Icon icon, const Vector3f& iconGlow, float radius)
: InteractableObject(position),
  _position(position),
  _doorColor(doorColor),
  _iconGlow(iconGlow),
  _mode(mode),
  _icon(icon),
  _collisionRadius(radius) {}*/

PuzzleDoor::PuzzleDoor(const Vector3f& position, const Vector3f& doorColor,int nextRoomIndex,
                       Icon icon, const Vector3f& iconGlow, float radius)
: InteractableObject(position),
  _position(position),
  _doorColor(doorColor),
  _nextRoomIndex(nextRoomIndex),
  _iconGlow(iconGlow),
  _icon(icon),
  _collisionRadius(radius) {}

void PuzzleDoor::render() {
    glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING); // cores “planas” para a porta
    glPushMatrix();
      glTranslatef(_position.x, _position.y, _position.z);
      drawDoorBody(_doorColor);

      // ÍCONE (se houver)
      if (_icon != Icon::None) {
          const float T = 0.10f;
          drawIconNeon(_icon, _iconGlow, /*zOffset*/ T*0.49f);
      }
    glPopMatrix();
    glPopAttrib();
}
void PuzzleDoor::onClick(GameStateManager& gsm) {
    if (_nextRoomIndex >= 0) {
            gsm.queueRoomChange(_nextRoomIndex);   // <— pedimos pra trocar de sala
        }
}

