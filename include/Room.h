#ifndef ROOM_H
#define ROOM_H


#include <vector>

#include "GameObject.h"


/**
 * @file Room.h
 * @brief Define a classe Room, que representa uma �nica sala no jogo.
 *
 * A classe Room � um cont�iner para todos os GameObjects que existem dentro
 * dela. � respons�vel por gerenciar o ciclo de vida (update, render) desses objetos.
 */

class InteractableObject;
class Room {
public:
    /**
     * @brief Construtor da classe Room.
     */
    Room();

    /**
     * @brief Destrutor da classe Room.
     * @note Respons�vel por liberar a mem�ria de todos os GameObjects contidos nela.
     */
    ~Room();

    /**
     * @brief Adiciona um novo objeto � sala.
     * @param object Um ponteiro para uma inst�ncia de GameObject.
     */
    void addObject(GameObject* object);

    /**
     * @brief Atualiza a l�gica de todos os objetos na sala.
     * @param deltaTime O tempo decorrido desde o �ltimo frame.
     */
    // ATUALIZE A ASSINATURA AQUI
    void update(float deltaTime, GameStateManager& gameStateManager);

    /**
     * @brief Renderiza todos os objetos na sala.
     */
    void render();
    std::vector<InteractableObject*>& getInteractableObjects(); // <-- ADICIONE ESTE M�TODO
    const std::vector<GameObject*>& getObjects() const;

    void setSpawnPoint(const Vector3f& pos) { _spawnPoint = pos; }
    const Vector3f& getSpawnPoint() const { return _spawnPoint; }
private:
    Vector3f _spawnPoint = {0.0f, 1.6f, 0.0f};
    // Um vetor de ponteiros para GameObject. Armazena todas as entidades da sala.
    std::vector<GameObject*> _objects;
    std::vector<InteractableObject*> _interactables; // <-- ADICIONE ESTE VETOR
};

#endif // ROOM_H
