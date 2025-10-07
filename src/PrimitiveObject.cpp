/**
 * @file PrimitiveObject.cpp
 * @brief Implementação da classe PrimitiveObject, que representa objetos geométricos básicos no ambiente 3D.
 */

#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>

/**
 * @brief Construtor da classe PrimitiveObject.
 *
 * Inicializa um objeto primitivo com uma forma, posição, cor e escala específicas.
 *
 * @param shape A forma geométrica do objeto (esfera, cubo, etc.).
 * @param position A posição do objeto no espaço 3D.
 * @param color A cor RGB do objeto.
 * @param scale O vetor de escala do objeto.
 */
PrimitiveObject::PrimitiveObject(PrimitiveShape shape, const Vector3f& position, const Vector3f& color, const Vector3f& scale) {
    _shape = shape;
    _position = position;
    _color = color;
    _scale = scale;
}

/**
 * @brief Atualiza o estado do objeto primitivo.
 *
 * Este método não realiza nenhuma ação, pois os objetos primitivos são estáticos.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void PrimitiveObject::update(float deltaTime, GameStateManager& gameStateManager) {
    // Objetos primitivos são estáticos.
}

/**
 * @brief Renderiza o objeto primitivo na tela.
 *
 * Define a cor do objeto, aplica as transformações de translação e escala
 * e desenha a forma geométrica correspondente.
 */
void PrimitiveObject::render() {
    // A cor é definida usando glColor3f. Como GL_COLOR_MATERIAL está ativo,
    // a iluminação será calculada com base nesta cor.
    glColor3f(_color.x, _color.y, _color.z);

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

/**
 * @brief Obtém a caixa delimitadora (Bounding Box) do objeto primitivo.
 *
 * A implementação atual retorna uma Bounding Box vazia.
 *
 * @return Um objeto BoundingBox vazio.
 */
BoundingBox PrimitiveObject::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
