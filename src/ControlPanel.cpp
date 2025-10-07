/**
 * @file ControlPanel.cpp
 * @brief Implementa��o da classe ControlPanel, que representa um objeto interativo no ambiente 3D.
 */

#include "../include/ControlPanel.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Objeto visual est�tico para representar o painel de controle.
 *
 * O objeto � um 'PrimitiveObject' do tipo 'SPHERE' (esfera)
 * com posi��es, cores e brilho predefinidos.
 */
static PrimitiveObject visual(PrimitiveShape::SPHERE, {0,0,0}, {0.1f, 0.1f, 0.8f}, {0.8f, 0.8f, 0.1f});

/**
 * @brief Construtor da classe ControlPanel.
 * @param position Posi��o do painel de controle no espa�o 3D.
 */
ControlPanel::ControlPanel(const Vector3f& position) : InteractableObject(position) {}

/**
 * @brief Atualiza o estado do painel de controle.
 *
 * Este m�todo � chamado a cada quadro, mas a implementa��o atual
 * n�o realiza nenhuma a��o, pois o painel � est�tico.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void ControlPanel::update(float deltaTime, GameStateManager& gameStateManager) {
    // O painel � est�tico, n�o reage a estados no update.
}

/**
 * @brief Renderiza o painel de controle no ambiente 3D.
 *
 * Usa as fun��es glPushMatrix e glPopMatrix para isolar as transforma��es
 * de renderiza��o do painel, garantindo que elas n�o afetem outros objetos.
 */
void ControlPanel::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    visual.render();
    glPopMatrix();
}

/**
 * @brief Lida com o evento de clique no painel de controle.
 *
 * Quando o painel � clicado, uma mensagem � impressa no console
 * e o m�todo 'cycleFlashlightColor' da classe 'GameStateManager' � chamado.
 *
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void ControlPanel::onClick(GameStateManager& gameStateManager) {
    std::cout << "Painel de controle clicado! Mudando a cor da lanterna." << std::endl;
    gameStateManager.cycleFlashlightColor();
}

/**
 * @brief Obt�m o raio de colis�o do painel.
 * @return O raio de colis�o, que � um valor fixo de 1.0f.
 */
float ControlPanel::getCollisionRadius() const { return 1.0f; }

/**
 * @brief Obt�m a caixa delimitadora do painel de controle.
 *
 * A caixa delimitadora � calculada com base na posi��o do painel
 * e no seu raio de colis�o.
 *
 * @return Um objeto BoundingBox que representa os limites do painel.
 */
BoundingBox ControlPanel::getBoundingBox() const {
    float radius = 1.0f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
