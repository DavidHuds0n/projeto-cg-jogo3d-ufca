#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>

PrimitiveObject::PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale) {
    _shape = shape;
    _position = position;
    _color = color;
    _scale = scale;
}

void PrimitiveObject::update(float deltaTime) {
    // Objetos de teste s�o est�ticos.
}

void PrimitiveObject::render() {
    // Define o material do objeto com a cor especificada.
    GLfloat diffuse_material[] = { _color.x, _color.y, _color.z, 1.0f };
    GLfloat specular_material[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Um brilho branco gen�rico
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse_material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glPushMatrix();

    // Aplica as transforma��es de posi��o e escala.
    glTranslatef(_position.x, _position.y, _position.z);
    glScalef(_scale.x, _scale.y, _scale.z);

    // Usa um switch para decidir qual primitiva do GLUT desenhar.
    switch (_shape) {
        case PrimitiveShape::SPHERE:
            // Par�metros: (raio, fatias, pilhas)
            glutSolidSphere(1.0, 32, 32);
            break;

        case PrimitiveShape::CONE:
            // O cone do GLUT � desenhado deitado no eixo Z, ent�o o rotacionamos
            // -90 graus no eixo X para que ele fique "em p�".
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            // Par�metros: (raio da base, altura, fatias, pilhas)
            glutSolidCone(1.0, 2.0, 32, 32);
            break;

        case PrimitiveShape::TORUS:
            // Par�metros: (raio interno, raio externo, lados, an�is)
            glutSolidTorus(0.5, 1.0, 32, 32);
            break;

        case PrimitiveShape::TEAPOT:
            // Par�metros: (tamanho)
            glutSolidTeapot(1.0);
            break;
    }

    glPopMatrix();
}
