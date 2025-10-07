/**
 * @file Room.cpp
 * @brief Implementação da classe Room, que gerencia os objetos de uma sala no jogo.
 */
#include "../include/Room.h"
#include "../include/InteractableObject.h"
#include <algorithm>

/**
 * @brief Construtor da classe Room.
 *
 * O construtor é inicializado sem ações. No futuro, ele poderia
 * ser expandido para receber um identificador ou nome para a sala.
 */
Room::Room() {
    // O construtor está vazio por enquanto.
}

/**
 * @brief Destrutor da classe Room.
 *
 * O destrutor é responsável por liberar a memória de todos os objetos
 * armazenados no vetor `_objects`, prevenindo vazamentos de memória.
 * Ele itera sobre cada objeto e o deleta.
 */
Room::~Room() {
    // Como o vetor `_objects` armazena ponteiros, nós somos responsáveis
    // por liberar a memória alocada para cada um deles.
    for (GameObject* obj : _objects) {
        delete obj; // Libera a memória do objeto.
    }
    // Limpa o vetor para remover os ponteiros inválidos.
    _objects.clear();
}

/**
 * @brief Adiciona um objeto à sala.
 *
 * O objeto é adicionado ao vetor principal de objetos. Se o objeto for
 * interativo (uma subclasse de `InteractableObject`), ele também é
 * adicionado a um vetor separado para fácil acesso.
 *
 * @param object Um ponteiro para o objeto a ser adicionado.
 */
void Room::addObject(GameObject* object) {
    if (object != nullptr) {
        _objects.push_back(object);

        // Tenta converter o GameObject para um InteractableObject
        InteractableObject* interactable = dynamic_cast<InteractableObject*>(object);
        if (interactable) {
            // Se a conversão deu certo, adiciona na lista de interativos
            _interactables.push_back(interactable);
        }
    }
}

/**
 * @brief Atualiza o estado de todos os objetos na sala.
 *
 * Este método delega a chamada de `update` para cada `GameObject` na sala,
 * permitindo que a lógica de cada objeto seja processada a cada quadro.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 * @param gameStateManager O gerenciador de estado do jogo.
 */
void Room::update(float deltaTime, GameStateManager& gameStateManager) {
    // Delega a chamada de 'update' para cada objeto na sala.
    for (GameObject* obj : _objects) {
        obj->update(deltaTime, gameStateManager);
    }
}

/**
 * @brief Renderiza todos os objetos na sala.
 *
 * Delega a chamada de `render` para cada `GameObject`, permitindo que
 * cada objeto desenhe a si mesmo na cena.
 */
void Room::render() {
    // Delega a chamada de 'render' para cada objeto na sala.
    for (GameObject* obj : _objects) {
        obj->render();
    }
}

/**
 * @brief Obtém uma lista de objetos interativos na sala.
 * @return Uma referência para o vetor de objetos interativos.
 */
std::vector<InteractableObject*>& Room::getInteractableObjects() {
    return _interactables;
}

/**
 * @brief Obtém uma lista de todos os objetos na sala.
 * @return Uma referência constante para o vetor de todos os objetos.
 */
const std::vector<GameObject*>& Room::getObjects() const { return _objects; }
