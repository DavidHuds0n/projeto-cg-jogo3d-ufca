#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Room.h"
#include "InteractableObject.h"

/**
 * @file SceneManager.h
 * @brief Define a classe SceneManager, responsável por gerenciar as salas (níveis) do jogo.
 *
 * Esta classe controla qual sala está atualmente ativa, delegando as chamadas
 * de atualização (update) e renderização (render) para a sala correta.
 */
class SceneManager {
public:
    /**
     * @brief Construtor da classe SceneManager.
     */
    SceneManager();

    /**
     * @brief Destrutor da classe SceneManager.
     * @note Responsável por liberar a memória de todas as salas criadas.
     */
    ~SceneManager();

    /**
     * @brief Inicializa o gerenciador de cenas.
     * É aqui que as salas do jogo são criadas e configuradas.
     */
    void init();

    /**
     * @brief Atualiza a lógica da sala atualmente ativa.
     * @param deltaTime O tempo decorrido desde o último frame.
     */
    void update(float deltaTime);

    /**
     * @brief Renderiza a sala atualmente ativa.
     */
    void render();

    std::vector<InteractableObject*>& getInteractableObjects(); // <-- ADICIONE ESTE MÉTODO


private:
    // Vetor que armazena ponteiros para todas as salas do jogo.
    std::vector<Room*> _rooms;
    // Índice que aponta para a sala atualmente ativa no vetor _rooms.
    int _currentRoomIndex;
};

#endif // SCENEMANAGER_H
