#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>

PrimitiveObject::PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale) {
    _shape = shape;
    _position = position;
    _color = color;
    _scale = scale;
}

void PrimitiveObject::update(float deltaTime) {
    // Objetos de teste são estáticos.
}

void PrimitiveObject::render() {
    // Define o material do objeto com a cor especificada.
    GLfloat diffuse_material[] = { _color.x, _color.y, _color.z, 1.0f };
    GLfloat specular_material[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Um brilho branco genérico
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse_material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glPushMatrix();

    // Aplica as transformações de posição e escala.
    glTranslatef(_position.x, _position.y, _position.z);
    glScalef(_scale.x, _scale.y, _scale.z);

    // Usa um switch para decidir qual primitiva do GLUT desenhar.
    switch (_shape) {
        case PrimitiveShape::SPHERE:
            // Parâmetros: (raio, fatias, pilhas)
            glutSolidSphere(1.0, 32, 32);
            break;

        case PrimitiveShape::CONE:
            // O cone do GLUT é desenhado deitado no eixo Z, então o rotacionamos
            // -90 graus no eixo X para que ele fique "em pé".
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            // Parâmetros: (raio da base, altura, fatias, pilhas)
            glutSolidCone(1.0, 2.0, 32, 32);
            break;

        case PrimitiveShape::TORUS:
            // Parâmetros: (raio interno, raio externo, lados, anéis)
            glutSolidTorus(0.5, 1.0, 32, 32);
            break;

        case PrimitiveShape::TEAPOT:
            // Parâmetros: (tamanho)
            glutSolidTeapot(1.0);
            break;
    }

    glPopMatrix();
}
