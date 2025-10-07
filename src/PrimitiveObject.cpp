#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>

PrimitiveObject::PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale) {
    _shape = shape;
    _position = position;
    _color = color;
    _scale = scale;
}

void PrimitiveObject::update(float deltaTime, GameStateManager& gameStateManager) {
    // Objetos primitivos são estáticos.
}

// --- FUNÇÃO RENDER CORRIGIDA ---
void PrimitiveObject::render() {
    // --- LÓGICA DE COR CORRIGIDA ---
    // Removemos as chamadas a glMaterialfv e usamos glColor3f.
    // Como GL_COLOR_MATERIAL está ativo, a iluminação será calculada com base nesta cor.
    glColor3f(_color.x, _color.y, _color.z);

    // O resto do código continua igual
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glScalef(_scale.x, _scale.y, _scale.z);

    switch (_shape) {
        case PrimitiveShape::SPHERE:
            glutSolidSphere(1.0, 32, 32);
            break;
        case PrimitiveShape::CONE:
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            glutSolidCone(0.5, 1.0, 32, 32);
            break;
        case PrimitiveShape::TORUS:
            glutSolidTorus(0.5, 1.0, 32, 32);
            break;
        case PrimitiveShape::TEAPOT: {
            glutSolidTeapot(1.0f);
            break;
        }
        case PrimitiveShape::CUBE:
            glutSolidCube(1.0);
            break;
    }
    glPopMatrix();
}

BoundingBox PrimitiveObject::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
