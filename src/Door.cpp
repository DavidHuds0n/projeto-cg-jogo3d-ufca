/**
 * @file Door.cpp
 * @brief Implementa��o da classe Door, que representa um objeto de porta interativo no ambiente 3D.
 */

#include "../include/Door.h"
#include "../include/PrimitiveObject.h"
#include "../include/GameStateManager.h" // Inclu�do para acessar os m�todos de verifica��o
#include <iostream>

// Construtores

/**
 * @brief Construtor da classe Door para portas sem requisitos.
 * @param position A posi��o da porta no espa�o 3D.
 * @param targetRoomIndex O �ndice da sala para a qual a porta leva.
 * @param spawnPosition A posi��o do jogador ao entrar na sala de destino.
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
 * @param position A posi��o da porta no espa�o 3D.
 * @param targetRoomIndex O �ndice da sala para a qual a porta leva.
 * @param spawnPosition A posi��o do jogador ao entrar na sala de destino.
 * @param requiredItem O tipo de item necess�rio para abrir a porta.
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
 * @brief Construtor da classe Door para portas que requerem m�ltiplos itens.
 * @param position A posi��o da porta no espa�o 3D.
 * @param targetRoomIndex O �ndice da sala para a qual a porta leva.
 * @param spawnPosition A posi��o do jogador ao entrar na sala de destino.
 * @param requiredItems Um vetor de tipos de itens necess�rios para abrir a porta.
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
 * @param position A posi��o da porta no espa�o 3D.
 * @param targetRoomIndex O �ndice da sala para a qual a porta leva.
 * @param spawnPosition A posi��o do jogador ao entrar na sala de destino.
 * @param requiredPuzzleId O identificador do quebra-cabe�a que deve ser resolvido para abrir a porta.
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
 * 1. N�o houver um ID de quebra-cabe�a requerido, ou se o quebra-cabe�a requerido estiver resolvido.
 * 2. N�o houver itens requeridos, ou se o jogador possuir todos os itens necess�rios.
 *
 * @param gameStateManager O gerenciador de estado do jogo, usado para verificar os requisitos.
 * @return Retorna 'true' se a porta puder ser aberta, e 'false' caso contr�rio.
 */
bool Door::canBeOpenedBy(const GameStateManager& gameStateManager) const {
    // 1. Verifica se a porta precisa de um puzzle resolvido
    if (!_requiredPuzzleId.empty()) {
        return gameStateManager.isPuzzleSolved(_requiredPuzzleId);
    }

    // 2. Verifica se a porta precisa de itens (chaves)
    if (!_requiredItems.empty()) {
        // Itera por TODOS os itens necess�rios
        for (const ItemType& item : _requiredItems) {
            // Se o jogador N�O TIVER pelo menos UM dos itens, a porta n�o abre
            if (!gameStateManager.playerHasItem(item)) {
                return false;
            }
        }
    }

    // 3. Se n�o caiu em nenhuma das condi��es acima (ou passou por elas), a porta est� aberta
    return true;
}


/**
 * @brief Atualiza o estado da porta.
 *
 * Este m�todo � chamado a cada quadro, mas a implementa��o atual
 * n�o realiza nenhuma a��o.
 *
 * @param deltaTime O tempo decorrido desde o �ltimo quadro.
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
 * @brief Obt�m o raio de colis�o da porta.
 * @return O raio de colis�o da porta.
 */
float Door::getCollisionRadius() const { return _collisionRadius; }

/**
 * @brief Obt�m o �ndice da sala de destino da porta.
 * @return O �ndice da sala de destino.
 */
int Door::getTargetRoomIndex() const { return _targetRoomIndex; }

/**
 * @brief Obt�m a posi��o de spawn do jogador na sala de destino.
 * @return A posi��o de spawn.
 */
const Vector3f& Door::getSpawnPosition() const { return _spawnPosition; }

/**
 * @brief Obt�m os itens requeridos para abrir a porta.
 * @return Uma refer�ncia constante para o vetor de itens requeridos.
 */
const std::vector<ItemType>& Door::getRequiredItems() const { return _requiredItems; }

/**
 * @brief Obt�m o ID do quebra-cabe�a requerido para abrir a porta.
 * @return Uma refer�ncia constante para o ID do quebra-cabe�a.
 */
const std::string& Door::getRequiredPuzzle() const { return _requiredPuzzleId; }

/**
 * @brief Obt�m a caixa delimitadora da porta.
 * @return Um objeto BoundingBox. Atualmente retorna um BoundingBox vazio.
 */
BoundingBox Door::getBoundingBox() const { return {{0,0,0}, {0,0,0}}; }
