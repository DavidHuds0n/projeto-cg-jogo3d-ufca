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
    // --- ETAPA 1: DESENHAR O CHÃO SÓLIDO COM ILUMINAÇÃO SUAVE ---
    glEnable(GL_LIGHTING);

    GLfloat floor_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat floor_specular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floor_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glNormal3f(0.0f, 1.0f, 0.0f);

    // Mantemos a alta densidade de polígonos para a suavidade da iluminação.
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
            glVertex3f(currentX,              _position.y, currentZ);
            glVertex3f(currentX,              _position.y, currentZ + segmentDepth);
            glVertex3f(currentX + segmentWidth, _position.y, currentZ + segmentDepth);
            glVertex3f(currentX + segmentWidth, _position.y, currentZ);
        }
    }
    glEnd();

    // --- ETAPA 2: DESENHAR O GRID VISUAL (COM QUADRADOS MAIORES) ---
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);

    // --- AJUSTE AQUI ---
    // Define o tamanho de cada quadrado do grid visual. Aumente para quadrados maiores.
    const float gridSquareSize = 1.0f;

    glBegin(GL_LINES);
    float grid_y = _position.y + 0.01f;

    // Desenha as linhas verticais (ao longo do eixo Z)
    for (float x = -halfWidth; x <= halfWidth; x += gridSquareSize) {
        glVertex3f(x, grid_y, -halfDepth);
        glVertex3f(x, grid_y,  halfDepth);
    }

    // Desenha as linhas horizontais (ao longo do eixo X)
    for (float z = -halfDepth; z <= halfDepth; z += gridSquareSize) {
        glVertex3f(-halfWidth, grid_y, z);
        glVertex3f( halfWidth, grid_y, z);
    }

    glEnd();
    glEnable(GL_LIGHTING);
}

BoundingBox Floor::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
