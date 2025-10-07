/**
 * @file TestButton.cpp
 * @brief Implementa��o da classe TestButton, um objeto interativo usado para testes.
 */

#include "../include/TestButton.h"
#include "../include/PrimitiveObject.h"
#include <iostream>

/**
 * @brief Construtor da classe TestButton.
 *
 * Inicializa um bot�o de teste com uma forma visual de esfera e define
 * um raio de colis�o fixo.
 *
 * @param position A posi��o do bot�o no espa�o 3D.
 */
TestButton::TestButton(const Vector3f& position)
    : InteractableObject(position),
      _visual(PrimitiveShape::SPHERE, position, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f})
{
    _collisionRadius = 0.5f;
}

/**
 * @brief Atualiza o estado do bot�o de teste.
 *
 * Este m�todo n�o realiza nenhuma a��o, pois o bot�o � um objeto est�tico
 * e n�o reage a eventos no ciclo de atualiza��o.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void TestButton::update(float deltaTime, GameStateManager& gameStateManager) {
    // Bot�o � est�tico, n�o precisa reagir a estados no update.
}

/**
 * @brief Renderiza o bot�o na tela.
 *
 * Delega o desenho do objeto visual (`_visual`) para sua pr�pria fun��o de renderiza��o.
 */
void TestButton::render() {
    _visual.render();
}

/**
 * @brief Lida com o evento de clique no bot�o de teste.
 *
 * Quando o bot�o � clicado, uma mensagem de depura��o � exibida no console.
 * Este m�todo serve como um ponto de entrada para testar outras funcionalidades.
 *
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void TestButton::onClick(GameStateManager& gameStateManager) {
    std::cout << ">>> BOTAO DE TESTE PRESSIONADO! <<<" << std::endl;
    // Exemplo de como poderia ser usado:
    // gameStateManager.setPuzzleState("algum_puzzle_de_teste", true);
}

/**
 * @brief Obt�m o raio de colis�o do bot�o de teste.
 * @return O raio de colis�o, que � um valor fixo de 0.5f.
 */
float TestButton::getCollisionRadius() const {
    return _collisionRadius;
}

/**
 * @brief Obt�m a caixa delimitadora (Bounding Box) do bot�o de teste.
 *
 * A caixa delimitadora � calculada com base na posi��o do bot�o e no seu
 * raio de colis�o.
 *
 * @return Um objeto BoundingBox que representa os limites do bot�o.
 */
BoundingBox TestButton::getBoundingBox() const {
    return {{_position.x - _collisionRadius, _position.y - _collisionRadius, _position.z - _collisionRadius},
            {_position.x + _collisionRadius, _position.y + _collisionRadius, _position.z + _collisionRadius}};
}
