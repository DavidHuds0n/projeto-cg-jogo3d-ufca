/**
 * @file RotatingCube.cpp
 * @brief Implementação da classe RotatingCube, um objeto interativo que pode ser rotacionado.
 */

#include "../include/RotatingCube.h"
#include "../include/CubePuzzle.h"
#include <GL/freeglut.h>
#include <cmath>

/**
 * @brief Construtor da classe RotatingCube.
 *
 * Inicializa um cubo com uma posição, tamanho, coordenadas de linha/coluna e
 * uma referência ao gerenciador do quebra-cabeça. O estado de rotação inicial
 * é definido de forma aleatória.
 *
 * @param position A posição do cubo no espaço 3D.
 * @param size O tamanho do cubo.
 * @param row A linha do cubo na grade do quebra-cabeça.
 * @param col A coluna do cubo na grade do quebra-cabeça.
 * @param puzzleManager Um ponteiro para o gerenciador do quebra-cabeça.
 */


RotatingCube::RotatingCube(const Vector3f& position, float size, int row, int col, CubePuzzle* puzzleManager)
    : InteractableObject(position), _size(size), _row(row), _col(col), _puzzleManager(puzzleManager) {

    // --- CÓDIGO PARA RESOLVER O PUZZLE INSTANTANEAMENTE ---
    _rotationState = rand() % 4 * 90.0f; // Estado inicial aleatório

    _currentAngle = _rotationState * 90.0f;
    _targetAngle = _currentAngle;
    _currentPosition = position;
    _targetPosition = position;
}


/**
 * @brief Atualiza o estado do cubo a cada quadro.
 *
 * Anima a rotação e o movimento do cubo de forma suave. A rotação
 * utiliza interpolação linear para se mover em direção ao ângulo alvo.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo (não utilizado diretamente aqui).
 */
void RotatingCube::update(float deltaTime, GameStateManager&) {
    // Animação suave de rotação
    if (std::abs(_currentAngle - _targetAngle) > 0.1f) {
        float diff = _targetAngle - _currentAngle;
        _currentAngle += diff * std::min(1.0f, deltaTime * 10.0f);
    } else {
        _currentAngle = _targetAngle;
    }
    // Animação suave de movimento (LERP)
    float speed = 5.0f;
    _currentPosition.x += (_targetPosition.x - _currentPosition.x) * std::min(1.0f, deltaTime * speed);
    _currentPosition.y += (_targetPosition.y - _currentPosition.y) * std::min(1.0f, deltaTime * speed);
    _currentPosition.z += (_targetPosition.z - _currentPosition.z) * std::min(1.0f, deltaTime * speed);
}

/**
 * @brief Renderiza o cubo na tela.
 *
 * O método define as cores de cada face (uma face especial e as outras normais),
 * aplica as transformações de translação e rotação e desenha o cubo com `GL_QUADS`.
 */
void RotatingCube::render() {
    glPushMatrix();
    glTranslatef(_currentPosition.x, _currentPosition.y, _currentPosition.z);
    glRotatef(_currentAngle, 0, 1, 0);
    glScalef(_size, _size, _size);

    // Define as cores para as faces
    Vector3f corEspecial = {1.0f, 1.0f, 0.0f};
    Vector3f corNormal = {0.4f, 0.4f, 0.4f};

    glBegin(GL_QUADS);
    // +Z (Face Especial)
    glColor3f(corEspecial.x, corEspecial.y, corEspecial.z);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f( 0.5f, -0.5f, 0.5f); glVertex3f( 0.5f,  0.5f, 0.5f); glVertex3f(-0.5f,  0.5f, 0.5f);

    // As outras 5 faces usam a cor normal
    glColor3f(corNormal.x, corNormal.y, corNormal.z);
    // -Z
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f,  0.5f, -0.5f); glVertex3f( 0.5f,  0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f);
    // +Y
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f,  0.5f); glVertex3f( 0.5f, 0.5f,  0.5f); glVertex3f( 0.5f, 0.5f, -0.5f);
    // -Y
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f, -0.5f); glVertex3f( 0.5f, -0.5f,  0.5f); glVertex3f(-0.5f, -0.5f,  0.5f);
    // +X
    glNormal3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f,  0.5f, -0.5f); glVertex3f(0.5f,  0.5f,  0.5f); glVertex3f(0.5f, -0.5f,  0.5f);
    // -X
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, -0.5f,  0.5f); glVertex3f(-0.5f,  0.5f,  0.5f); glVertex3f(-0.5f,  0.5f, -0.5f);

    glEnd();
    glPopMatrix();
}

/**
 * @brief Lida com o evento de clique no cubo.
 *
 * Este método delega a chamada para o gerenciador do quebra-cabeça (`CubePuzzle`)
 * para que a lógica do jogo seja processada.
 *
 * @param gameStateManager O gerenciador de estado do jogo (não utilizado diretamente aqui).
 */
void RotatingCube::onClick(GameStateManager&) {
    // Apenas avisa o gerente
    if (_puzzleManager) {
        _puzzleManager->onCubeClicked(_row, _col);
    }
}

/**
 * @brief Inicia a rotação do cubo.
 *
 * Altera o estado de rotação do cubo e define um novo ângulo alvo para a animação.
 */
void RotatingCube::rotate() {
    _rotationState = (_rotationState + 1) % 4;
    _targetAngle = _rotationState * 90.0f;
    // Apenas animação suave de rotação, sem alterar posição
}

/**
 * @brief Obtém a caixa delimitadora (Bounding Box) do cubo.
 * @return Um objeto BoundingBox que representa a área de colisão do cubo.
 */
BoundingBox RotatingCube::getBoundingBox() const {
    float half = _size / 2.0f;
    BoundingBox box;
    box.min = {_position.x - half, _position.y - half, _position.z - half};
    box.max = {_position.x + half, _position.y + half, _position.z + half};
    return box;
}

/**
 * @brief Obtém o raio de colisão do cubo.
 * @return O raio de colisão, que é a metade do tamanho do cubo.
 */
float RotatingCube::getCollisionRadius() const {
    return _size / 2.0f;
}
