/**
 * @file Keypad.cpp
 * @brief Implementação da classe Keypad, um objeto interativo para entrada de código.
 */

#include "../include/Keypad.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Objeto visual estático para representar o keypad.
 *
 * O objeto é um 'PrimitiveObject' do tipo 'TEAPOT' (bule) com
 * posições, cores e brilho predefinidos.
 */
static PrimitiveObject visualKeypad(PrimitiveShape::TEAPOT, {0,0,0}, {0.3f, 0.3f, 0.3f}, {0.5f, 0.5f, 0.5f});

/**
 * @brief Construtor da classe Keypad.
 * @param position A posição do teclado numérico no espaço 3D.
 */
Keypad::Keypad(const Vector3f& position) : InteractableObject(position) {}

/**
 * @brief Atualiza o estado do teclado numérico.
 *
 * Este método é chamado a cada quadro, mas a implementação atual
 * não realiza nenhuma ação, pois o teclado numérico é estático.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void Keypad::update(float deltaTime, GameStateManager& gameStateManager) {
    // Keypad é estático, não precisa reagir a estados no update.
}

/**
 * @brief Renderiza o teclado numérico no ambiente 3D.
 *
 * Utiliza glPushMatrix e glPopMatrix para isolar as transformações
 * de renderização.
 */
void Keypad::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    visualKeypad.render();
    glPopMatrix();
}

/**
 * @brief Lida com o evento de clique no teclado numérico.
 *
 * Altera o estado de atividade do teclado numérico no gerenciador de estado do jogo.
 * Se estiver ativo, desativa; se estiver inativo, ativa.
 *
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void Keypad::onClick(GameStateManager& gameStateManager) {
    if (gameStateManager.isKeypadActive()) {
        gameStateManager.setActiveKeypad(false);
        std::cout << "Keypad desativado." << std::endl;
    } else {
        gameStateManager.setActiveKeypad(true);
        std::cout << "Keypad ativado! Digite o codigo de 3 digitos." << std::endl;
    }
}

/**
 * @brief Obtém o raio de colisão do teclado numérico.
 * @return O raio de colisão, que é um valor fixo de 0.5f.
 */
float Keypad::getCollisionRadius() const { return 0.5f; }

/**
 * @brief Obtém a caixa delimitadora do teclado numérico.
 *
 * A caixa delimitadora é calculada com base na posição do objeto e
 * no seu raio de colisão.
 *
 * @return Um objeto BoundingBox que representa os limites do teclado.
 */
BoundingBox Keypad::getBoundingBox() const {
    float radius = 0.5f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
