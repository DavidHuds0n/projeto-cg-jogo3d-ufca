#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Room.h"
#include "InteractableObject.h"

/**
 * @file SceneManager.h
 * @brief Define a classe SceneManager, respons�vel por gerenciar as salas (n�veis) do jogo.
 *
 * Esta classe controla qual sala est� atualmente ativa, delegando as chamadas
 * de atualiza��o (update) e renderiza��o (render) para a sala correta.
 */
class SceneManager {
public:
    /**
     * @brief Construtor da classe SceneManager.
     */
    SceneManager();

    /**
     * @brief Destrutor da classe SceneManager.
     * @note Respons�vel por liberar a mem�ria de todas as salas criadas.
     */
    ~SceneManager();

    /**
     * @brief Inicializa o gerenciador de cenas.
     * � aqui que as salas do jogo s�o criadas e configuradas.
     */
    void init();

    /**
     * @brief Atualiza a l�gica da sala atualmente ativa.
     * @param deltaTime O tempo decorrido desde o �ltimo frame.
     */
    void update(float deltaTime);

    /**
     * @brief Renderiza a sala atualmente ativa.
     */
    void render();

    std::vector<InteractableObject*>& getInteractableObjects(); // <-- ADICIONE ESTE M�TODO


private:
    // Vetor que armazena ponteiros para todas as salas do jogo.
    std::vector<Room*> _rooms;
    // �ndice que aponta para a sala atualmente ativa no vetor _rooms.
    int _currentRoomIndex;
};

#endif // SCENEMANAGER_H
