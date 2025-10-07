/**
 * @file Door.cpp
 * @brief Implementação da classe Door, que representa um objeto de porta interativo no ambiente 3D.
 */

#include "../include/Door.h"
#include "../include/PrimitiveObject.h"
#include "../include/GameStateManager.h" // Incluído para acessar os métodos de verificação
#include <iostream>

// Construtores

/**
 * @brief Construtor da classe Door para portas sem requisitos.
 * @param position A posição da porta no espaço 3D.
 * @param targetRoomIndex O índice da sala para a qual a porta leva.
 * @param spawnPosition A posição do jogador ao entrar na sala de destino.
 */
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

/**
 * @brief Construtor da classe Door para portas que requerem um item.
 * @param position A posição da porta no espaço 3D.
 * @param targetRoomIndex O índice da sala para a qual a porta leva.
 * @param spawnPosition A posição do jogador ao entrar na sala de destino.
 * @param requiredItem O tipo de item necessário para abrir a porta.
 */
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, ItemType requiredItem)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredItems({requiredItem}),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

/**
 * @brief Construtor da classe Door para portas que requerem múltiplos itens.
 * @param position A posição da porta no espaço 3D.
 * @param targetRoomIndex O índice da sala para a qual a porta leva.
 * @param spawnPosition A posição do jogador ao entrar na sala de destino.
 * @param requiredItems Um vetor de tipos de itens necessários para abrir a porta.
 */
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::vector<ItemType>& requiredItems)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredItems(requiredItems),
      _requiredPuzzleId("")
{
    _collisionRadius = 1.5f;
}

/**
 * @brief Construtor da classe Door para portas que requerem um puzzle resolvido.
 * @param position A posição da porta no espaço 3D.
 * @param targetRoomIndex O índice da sala para a qual a porta leva.
 * @param spawnPosition A posição do jogador ao entrar na sala de destino.
 * @param requiredPuzzleId O identificador do quebra-cabeça que deve ser resolvido para abrir a porta.
 */
Door::Door(const Vector3f& position, int targetRoomIndex, const Vector3f& spawnPosition, const std::string& requiredPuzzleId)
    : InteractableObject(position),
      _visual(PrimitiveShape::CUBE, position, {0.5f, 0.25f, 0.0f}, {1.0f, 2.0f, 0.2f}),
      _targetRoomIndex(targetRoomIndex),
      _spawnPosition(spawnPosition),
      _requiredPuzzleId(requiredPuzzleId)
{
    _collisionRadius = 1.5f;
}

/**
 * @brief Verifica se a porta pode ser aberta pelo jogador.
 *
 * A porta pode ser aberta se:
 * 1. Não houver um ID de quebra-cabeça requerido, ou se o quebra-cabeça requerido estiver resolvido.
 * 2. Não houver itens requeridos, ou se o jogador possuir todos os itens necessários.
 *
 * @param gameStateManager O gerenciador de estado do jogo, usado para verificar os requisitos.
 * @return Retorna 'true' se a porta puder ser aberta, e 'false' caso contrário.
 */
bool Door::canBeOpenedBy(const GameStateManager& gameStateManager) const {
    // 1. Verifica se a porta precisa de um puzzle resolvido
    if (!_requiredPuzzleId.empty()) {
        return gameStateManager.isPuzzleSolved(_requiredPuzzleId);
    }

    // 2. Verifica se a porta precisa de itens (chaves)
    if (!_requiredItems.empty()) {
        // Itera por TODOS os itens necessários
        for (const ItemType& item : _requiredItems) {
            // Se o jogador NÃO TIVER pelo menos UM dos itens, a porta não abre
            if (!gameStateManager.playerHasItem(item)) {
                return false;
            }
        }
    }

    // 3. Se não caiu em nenhuma das condições acima (ou passou por elas), a porta está aberta
    return true;
}


/**
 * @brief Atualiza o estado da porta.
 *
 * Este método é chamado a cada quadro, mas a implementação atual
 * não realiza nenhuma ação.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager A classe para gerenciar o estado do jogo.
 */
void Door::update(float deltaTime, GameStateManager& gameStateManager) {}

/**
 * @brief Renderiza a porta no ambiente 3D.
 */
void Door::render() { _visual.render(); }

/**
 * @brief Manipula o evento de clique na porta.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void Door::onClick(GameStateManager& gameStateManager) {
    std::cout << "Porta interagida!" << std::endl;
}

/**
 * @brief Obtém o raio de colisão da porta.
 * @return O raio de colisão da porta.
 */
float Door::getCollisionRadius() const { return _collisionRadius; }

/**
 * @brief Obtém o índice da sala de destino da porta.
 * @return O índice da sala de destino.
 */
int Door::getTargetRoomIndex() const { return _targetRoomIndex; }

/**
 * @brief Obtém a posição de spawn do jogador na sala de destino.
 * @return A posição de spawn.
 */
const Vector3f& Door::getSpawnPosition() const { return _spawnPosition; }

/**
 * @brief Obtém os itens requeridos para abrir a porta.
 * @return Uma referência constante para o vetor de itens requeridos.
 */
const std::vector<ItemType>& Door::getRequiredItems() const { return _requiredItems; }

/**
 * @brief Obtém o ID do quebra-cabeça requerido para abrir a porta.
 * @return Uma referência constante para o ID do quebra-cabeça.
 */
const std::string& Door::getRequiredPuzzle() const { return _requiredPuzzleId; }

/**
 * @brief Obtém a caixa delimitadora da porta.
 * @return Um objeto BoundingBox. Atualmente retorna um BoundingBox vazio.
 */
BoundingBox Door::getBoundingBox() const { return {{0,0,0}, {0,0,0}}; }
