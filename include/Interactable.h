/**
 * @file Interactable.h
 * @brief Define os tipos e a estrutura de objetos interativos no jogo.
 */
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

/**
 * @enum InteractableType
 * @brief Enumeração para identificar os diferentes tipos de objetos interativos.
 */
enum InteractableType {
    TORCH,   ///< Objeto do tipo Tocha.
    BATTERY  ///< Objeto do tipo Bateria para a lanterna.
};

/**
 * @struct Interactable
 * @brief Estrutura que representa um objeto interativo no mundo do jogo.
 */
struct Interactable {
    InteractableType type; ///< O tipo do objeto (Tocha, Bateria, etc.).
    float posX, posY, posZ;///< Coordenadas de posição do objeto no mundo.
    bool isActive;         ///< Estado do objeto. Ex: true se a tocha já foi acesa/coletada.
};

#endif // INTERACTABLE_H
