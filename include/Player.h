/**
 * @file Player.h
 * @brief Define a classe Player, que representa o jogador no jogo.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"
#include <map>

// Nota: A forward declaration 'class Level;' foi removida, o que é bom.
// Manter os includes diretos e claros é uma ótima prática.

/**
 * @class Player
 * @brief Gerencia o estado, a entrada (teclado/mouse) e a câmera do jogador.
 *
 * Esta classe encapsula a lógica de movimento, a câmera em primeira pessoa
 * e o estado das teclas pressionadas para controlar o personagem principal.
 */
class Player {
public:
    /**
     * @brief Construtor padrão do Player.
     * Inicializa a posição, velocidade e o estado das teclas.
     */
    Player();

    /**
     * @brief Lida com o evento de uma tecla ser pressionada.
     * @param [in] key O caractere da tecla que foi pressionada.
     */
    void handleKeyDown(unsigned char key);

    /**
     * @brief Lida com o evento de uma tecla ser solta.
     * @param [in] key O caractere da tecla que foi solta.
     */
    void handleKeyUp(unsigned char key);

    /**
     * @brief Lida com o movimento do mouse para controlar a câmera.
     * @param [in] x A nova coordenada X do cursor do mouse.
     * @param [in] y A nova coordenada Y do cursor do mouse.
     */
    void handleMouseMotion(int x, int y);

    /**
     * @brief Atualiza o estado do jogador com base no tempo decorrido.
     * @param [in] deltaTime O tempo (em segundos) desde o último frame.
     * @note Esta função calcula o movimento do jogador com base nas teclas pressionadas.
     */
    void update(float deltaTime);

    /**
     * @brief Define a posição inicial ou atual do jogador no mundo.
     * @param [in] pos Um Vector3f com as novas coordenadas do jogador.
     */
    void setPosition(const Vector3f& pos);

    /**
     * @brief Obtém uma referência para o objeto de câmera do jogador.
     * @return Uma referência para a instância FPSCamera associada ao jogador.
     */
    FPSCamera& getCamera();

private:
    Vector3f _position;         ///< Posição atual do jogador.
    FPSCamera _camera;          ///< A câmera em primeira pessoa do jogador.
    float _movementSpeed;       ///< Velocidade de movimento do jogador.
    float _collisionRadius;     ///< Raio de colisão para física simples.

    /**
     * @brief Mapa que armazena o estado de cada tecla (pressionada ou não).
     * true se a tecla está pressionada, false caso contrário.
     */
    std::map<unsigned char, bool> _keyState;
};

#endif // PLAYER_H
