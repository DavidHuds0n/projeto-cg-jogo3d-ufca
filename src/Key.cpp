/**
 * @file Key.cpp
 * @brief Implementação da classe Key, um objeto interativo que o jogador pode coletar.
 */

#include "../include/Key.h"
#include <iostream>
#include <algorithm> // Necessário para usar std::max
#include <cmath>     // Necessário para usar std::max em algumas configurações de compilador

/**
 * @brief Construtor da classe Key.
 *
 * A chave é inicializada com um tipo e, opcionalmente, com um ID de puzzle necessário.
 * A sua forma visual é definida pelo parâmetro 'form' e a sua hitbox é calculada dinamicamente
 * com base na sua escala.
 *
 * @param position A posição da chave no espaço 3D.
 * @param keyType O tipo da chave (ex: CHAVE_AZUL, CHAVE_VERMELHA).
 * @param puzzleIdRequired O ID do puzzle que deve ser resolvido para a chave aparecer.
 * @param form Um booleano que define a forma visual da chave (true para bule, false para cone).
 * @param color A cor da chave.
 * @param scale O vetor de escala da chave.
 */
Key::Key(const Vector3f& position,
         ItemType keyType,
         const std::string& puzzleIdRequired,
         bool form,
         const Vector3f& color,
         const Vector3f& scale)
    : InteractableObject(position),
      _visual(form ? PrimitiveShape::TEAPOT : PrimitiveShape::CONE,
              position,
              color,
              scale),
      _puzzleIdRequired(puzzleIdRequired),
      _keyType(keyType)
{
    _color = color;
    _visual.setColor(color);
    _isCollected = false;
    _isVisible = puzzleIdRequired.empty();
    setInteractable(puzzleIdRequired.empty());

    // --- LÓGICA DE HITBOX DINÂMICA ---
    // Em vez de um valor fixo, calculamos o raio com base no tamanho visual do objeto.

    // 1. Pega a maior dimensão da escala do objeto (x, y, ou z).
    float maxScale = std::max({scale.x, scale.y, scale.z});

    // 2. Define um raio base para o modelo 3D (cone/bule) em escala 1.0.
    //    Este valor pode ser ajustado se o modelo for muito largo ou fino. 0.8 é um bom começo.
    float baseModelRadius = 0.8f;

    // 3. Calcula o raio final: o raio do modelo * a maior escala * uma pequena folga (10%).
    _collisionRadius = baseModelRadius * maxScale * 1.1f;
}

/**
 * @brief Atualiza o estado da chave a cada quadro.
 *
 * Este método verifica se o puzzle associado foi resolvido e, se for o caso,
 * torna a chave visível e interativa.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void Key::update(float deltaTime, GameStateManager& gameStateManager) {
    if (!_isVisible && !_puzzleIdRequired.empty() && gameStateManager.isPuzzleSolved(_puzzleIdRequired)) {
        std::cout << "O puzzle foi resolvido! A chave apareceu!" << std::endl;
        _isVisible = true;
        setInteractable(true);
    }
}

/**
 * @brief Renderiza a chave na tela.
 *
 * A chave só é renderizada se estiver visível e ainda não tiver sido coletada.
 */
void Key::render() {
    if (_isVisible && !_isCollected) {
        _visual.render();
    }
}

/**
 * @brief Lida com a interação de clique na chave.
 *
 * Quando a chave é clicada, ela é coletada e adicionada ao inventário do jogador,
 * tornando-se invisível e não mais interativa.
 *
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void Key::onClick(GameStateManager& gameStateManager) {
    if (!_isVisible || _isCollected) return;

    std::cout << "*** Chave Coletada! ***" << std::endl;
    _isCollected = true;
    setInteractable(false);

    gameStateManager.addItemToInventory(_keyType);
}

/**
 * @brief Obtém o raio de colisão da chave.
 * @return O raio de colisão calculado dinamicamente no construtor.
 */
float Key::getCollisionRadius() const {
    return _collisionRadius;
}

/**
 * @brief Obtém a Bounding Box (caixa delimitadora) da chave.
 *
 * A implementação atual retorna uma Bounding Box vazia.
 *
 * @return Um objeto BoundingBox vazio.
 */
BoundingBox Key::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
