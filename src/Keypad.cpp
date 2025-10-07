/**
 * @file Keypad.cpp
 * @brief Implementa��o da classe Keypad, um objeto interativo para entrada de c�digo.
 */

#include "../include/Keypad.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Objeto visual est�tico para representar o keypad.
 *
 * O objeto � um 'PrimitiveObject' do tipo 'TEAPOT' (bule) com
 * posi��es, cores e brilho predefinidos.
 */
static PrimitiveObject visualKeypad(PrimitiveShape::TEAPOT, {0,0,0}, {0.3f, 0.3f, 0.3f}, {0.5f, 0.5f, 0.5f});

/**
 * @brief Construtor da classe Keypad.
 * @param position A posi��o do teclado num�rico no espa�o 3D.
 */
Keypad::Keypad(const Vector3f& position) : InteractableObject(position) {}

/**
 * @brief Atualiza o estado do teclado num�rico.
 *
 * Este m�todo � chamado a cada quadro, mas a implementa��o atual
 * n�o realiza nenhuma a��o, pois o teclado num�rico � est�tico.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void Keypad::update(float deltaTime, GameStateManager& gameStateManager) {
    // Keypad � est�tico, n�o precisa reagir a estados no update.
}

/**
 * @brief Renderiza o teclado num�rico no ambiente 3D.
 *
 * Utiliza glPushMatrix e glPopMatrix para isolar as transforma��es
 * de renderiza��o.
 */
void Keypad::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    visualKeypad.render();
    glPopMatrix();
}

/**
 * @brief Lida com o evento de clique no teclado num�rico.
 *
 * Altera o estado de atividade do teclado num�rico no gerenciador de estado do jogo.
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
 * @brief Obt�m o raio de colis�o do teclado num�rico.
 * @return O raio de colis�o, que � um valor fixo de 0.5f.
 */
float Keypad::getCollisionRadius() const { return 0.5f; }

/**
 * @brief Obt�m a caixa delimitadora do teclado num�rico.
 *
 * A caixa delimitadora � calculada com base na posi��o do objeto e
 * no seu raio de colis�o.
 *
 * @return Um objeto BoundingBox que representa os limites do teclado.
 */
BoundingBox Keypad::getBoundingBox() const {
    float radius = 0.5f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
