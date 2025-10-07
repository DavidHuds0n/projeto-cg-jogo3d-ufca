/**
 * @file ControlPanel.cpp
 * @brief Implementação da classe ControlPanel, que representa um objeto interativo no ambiente 3D.
 */

#include "../include/ControlPanel.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Objeto visual estático para representar o painel de controle.
 *
 * O objeto é um 'PrimitiveObject' do tipo 'SPHERE' (esfera)
 * com posições, cores e brilho predefinidos.
 */
static PrimitiveObject visual(PrimitiveShape::SPHERE, {0,0,0}, {0.1f, 0.1f, 0.8f}, {0.8f, 0.8f, 0.1f});

/**
 * @brief Construtor da classe ControlPanel.
 * @param position Posição do painel de controle no espaço 3D.
 */
ControlPanel::ControlPanel(const Vector3f& position) : InteractableObject(position) {}

/**
 * @brief Atualiza o estado do painel de controle.
 *
 * Este método é chamado a cada quadro, mas a implementação atual
 * não realiza nenhuma ação, pois o painel é estático.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void ControlPanel::update(float deltaTime, GameStateManager& gameStateManager) {
    // O painel é estático, não reage a estados no update.
}

/**
 * @brief Renderiza o painel de controle no ambiente 3D.
 *
 * Usa as funções glPushMatrix e glPopMatrix para isolar as transformações
 * de renderização do painel, garantindo que elas não afetem outros objetos.
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
 * Quando o painel é clicado, uma mensagem é impressa no console
 * e o método 'cycleFlashlightColor' da classe 'GameStateManager' é chamado.
 *
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void ControlPanel::onClick(GameStateManager& gameStateManager) {
    std::cout << "Painel de controle clicado! Mudando a cor da lanterna." << std::endl;
    gameStateManager.cycleFlashlightColor();
}

/**
 * @brief Obtém o raio de colisão do painel.
 * @return O raio de colisão, que é um valor fixo de 1.0f.
 */
float ControlPanel::getCollisionRadius() const { return 1.0f; }

/**
 * @brief Obtém a caixa delimitadora do painel de controle.
 *
 * A caixa delimitadora é calculada com base na posição do painel
 * e no seu raio de colisão.
 *
 * @return Um objeto BoundingBox que representa os limites do painel.
 */
BoundingBox ControlPanel::getBoundingBox() const {
    float radius = 1.0f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
