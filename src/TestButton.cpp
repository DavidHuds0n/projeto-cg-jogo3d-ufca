/**
 * @file TestButton.cpp
 * @brief Implementação da classe TestButton, um objeto interativo usado para testes.
 */

#include "../include/TestButton.h"
#include "../include/PrimitiveObject.h"
#include <iostream>

/**
 * @brief Construtor da classe TestButton.
 *
 * Inicializa um botão de teste com uma forma visual de esfera e define
 * um raio de colisão fixo.
 *
 * @param position A posição do botão no espaço 3D.
 */
TestButton::TestButton(const Vector3f& position)
    : InteractableObject(position),
      _visual(PrimitiveShape::SPHERE, position, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f})
{
    _collisionRadius = 0.5f;
}

/**
 * @brief Atualiza o estado do botão de teste.
 *
 * Este método não realiza nenhuma ação, pois o botão é um objeto estático
 * e não reage a eventos no ciclo de atualização.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void TestButton::update(float deltaTime, GameStateManager& gameStateManager) {
    // Botão é estático, não precisa reagir a estados no update.
}

/**
 * @brief Renderiza o botão na tela.
 *
 * Delega o desenho do objeto visual (`_visual`) para sua própria função de renderização.
 */
void TestButton::render() {
    _visual.render();
}

/**
 * @brief Lida com o evento de clique no botão de teste.
 *
 * Quando o botão é clicado, uma mensagem de depuração é exibida no console.
 * Este método serve como um ponto de entrada para testar outras funcionalidades.
 *
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void TestButton::onClick(GameStateManager& gameStateManager) {
    std::cout << ">>> BOTAO DE TESTE PRESSIONADO! <<<" << std::endl;
    // Exemplo de como poderia ser usado:
    // gameStateManager.setPuzzleState("algum_puzzle_de_teste", true);
}

/**
 * @brief Obtém o raio de colisão do botão de teste.
 * @return O raio de colisão, que é um valor fixo de 0.5f.
 */
float TestButton::getCollisionRadius() const {
    return _collisionRadius;
}

/**
 * @brief Obtém a caixa delimitadora (Bounding Box) do botão de teste.
 *
 * A caixa delimitadora é calculada com base na posição do botão e no seu
 * raio de colisão.
 *
 * @return Um objeto BoundingBox que representa os limites do botão.
 */
BoundingBox TestButton::getBoundingBox() const {
    return {{_position.x - _collisionRadius, _position.y - _collisionRadius, _position.z - _collisionRadius},
            {_position.x + _collisionRadius, _position.y + _collisionRadius, _position.z + _collisionRadius}};
}
