#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>

PrimitiveObject::PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale) {
    _shape = shape;
    _position = position;
    _color = color;
    _scale = scale;
}

void PrimitiveObject::update(float deltaTime, GameStateManager& gameStateManager) {
    // Objetos de teste são estáticos.
}

void PrimitiveObject::render() {
    GLfloat diffuse_material[] = { _color.x, _color.y, _color.z, 1.0f };
    GLfloat specular_material[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse_material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glScalef(_scale.x, _scale.y, _scale.z);

    switch (_shape) {
        case PrimitiveShape::SPHERE:
            glutSolidSphere(1.0, 32, 32);
            break;
        case PrimitiveShape::CONE:
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            glutSolidCone(1.0, 2.0, 32, 32);
            break;
        case PrimitiveShape::TORUS:
            glutSolidTorus(0.5, 1.0, 32, 32);
            break;
        case PrimitiveShape::TEAPOT:
            glutSolidTeapot(1.0);
            break;
    }
    glPopMatrix();
}

// Método implementado
BoundingBox PrimitiveObject::getBoundingBox() const {
    // Retorna uma caixa "inválida" porque este objeto é apenas visual.
    return {{0,0,0}, {0,0,0}};
}
