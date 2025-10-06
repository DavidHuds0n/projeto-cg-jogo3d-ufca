// Implementação da classe MagicCube
#include "MagicCube.h"
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>

// Construtor do cubo
MagicCube::MagicCube(const Vector3f& position, float size, float rotation)
	: InteractableObject(position), _size(size), _rotation(rotation) {}

MagicCube::~MagicCube() {}

void MagicCube::update(float deltaTime, GameStateManager& gameStateManager) {
	// Aqui pode-se adicionar lógica de animação, se necessário
}

void MagicCube::onClick(GameStateManager& gameStateManager) {
	// Gira 90 graus ao ser clicado
	_rotation += 90.0f;
	if (_rotation >= 360.0f) _rotation -= 360.0f;
	// std::cout << "MagicCube girou para " << _rotation << " graus.\n";
}

void MagicCube::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation, 0, 1, 0);
    glScalef(_size, _size, _size);

    // Materiais para as faces
    GLfloat gray[]   = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat yellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glBegin(GL_QUADS);
    // Face +Z (amarela)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f,  0.5f, 0.5f);
    glVertex3f(-0.5f,  0.5f, 0.5f);

    // Outras faces (cinza)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
    // Face -Z
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    // Face +Y
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    // Face -Y
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    // Face +X
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    // Face -X
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

BoundingBox MagicCube::getBoundingBox() const {
	// Retorna o bounding box do quadrado/cubo
	BoundingBox box;
	float half = _size / 2.0f;
	box.min = {_position.x - half, _position.y - half, _position.z - half};
	box.max = {_position.x + half, _position.y + half, _position.z + half};
	return box;
}

float MagicCube::getCollisionRadius() const {
	return _size / 2.0f;
}
