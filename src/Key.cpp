/**
 * @file Key.cpp
 * @brief Implementa��o da classe Key, um objeto interativo que o jogador pode coletar.
 */

#include "../include/Key.h"
#include <iostream>
#include <algorithm> // Necess�rio para usar std::max
#include <cmath>     // Necess�rio para usar std::max em algumas configura��es de compilador

/**
 * @brief Construtor da classe Key.
 *
 * A chave � inicializada com um tipo e, opcionalmente, com um ID de puzzle necess�rio.
 * A sua forma visual � definida pelo par�metro 'form' e a sua hitbox � calculada dinamicamente
 * com base na sua escala.
 *
 * @param position A posi��o da chave no espa�o 3D.
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

    // --- L�GICA DE HITBOX DIN�MICA ---
    // Em vez de um valor fixo, calculamos o raio com base no tamanho visual do objeto.

    // 1. Pega a maior dimens�o da escala do objeto (x, y, ou z).
    float maxScale = std::max({scale.x, scale.y, scale.z});

    // 2. Define um raio base para o modelo 3D (cone/bule) em escala 1.0.
    //    Este valor pode ser ajustado se o modelo for muito largo ou fino. 0.8 � um bom come�o.
    float baseModelRadius = 0.8f;

    // 3. Calcula o raio final: o raio do modelo * a maior escala * uma pequena folga (10%).
    _collisionRadius = baseModelRadius * maxScale * 1.1f;
}

/**
 * @brief Atualiza o estado da chave a cada quadro.
 *
 * Este m�todo verifica se o puzzle associado foi resolvido e, se for o caso,
 * torna a chave vis�vel e interativa.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
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
 * A chave s� � renderizada se estiver vis�vel e ainda n�o tiver sido coletada.
 */
void Key::render() {
    if (_isVisible && !_isCollected) {
        _visual.render();
    }
}

/**
 * @brief Lida com a intera��o de clique na chave.
 *
 * Quando a chave � clicada, ela � coletada e adicionada ao invent�rio do jogador,
 * tornando-se invis�vel e n�o mais interativa.
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
 * @brief Obt�m o raio de colis�o da chave.
 * @return O raio de colis�o calculado dinamicamente no construtor.
 */
float Key::getCollisionRadius() const {
    return _collisionRadius;
}

/**
 * @brief Obt�m a Bounding Box (caixa delimitadora) da chave.
 *
 * A implementa��o atual retorna uma Bounding Box vazia.
 *
 * @return Um objeto BoundingBox vazio.
 */
BoundingBox Key::getBoundingBox() const {
    return {{0,0,0}, {0,0,0}};
}
