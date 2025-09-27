/**
 * @file Player.h
 * @brief Define a classe Player, que representa o jogador no jogo.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "FPSCamera.h"
#include <map>

// Nota: A forward declaration 'class Level;' foi removida, o que � bom.
// Manter os includes diretos e claros � uma �tima pr�tica.

/**
 * @class Player
 * @brief Gerencia o estado, a entrada (teclado/mouse) e a c�mera do jogador.
 *
 * Esta classe encapsula a l�gica de movimento, a c�mera em primeira pessoa
 * e o estado das teclas pressionadas para controlar o personagem principal.
 */
class Player {
public:
    /**
     * @brief Construtor padr�o do Player.
     * Inicializa a posi��o, velocidade e o estado das teclas.
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
     * @brief Lida com o movimento do mouse para controlar a c�mera.
     * @param [in] x A nova coordenada X do cursor do mouse.
     * @param [in] y A nova coordenada Y do cursor do mouse.
     */
    void handleMouseMotion(int x, int y);

    /**
     * @brief Atualiza o estado do jogador com base no tempo decorrido.
     * @param [in] deltaTime O tempo (em segundos) desde o �ltimo frame.
     * @note Esta fun��o calcula o movimento do jogador com base nas teclas pressionadas.
     */
    void update(float deltaTime);

    /**
     * @brief Define a posi��o inicial ou atual do jogador no mundo.
     * @param [in] pos Um Vector3f com as novas coordenadas do jogador.
     */
    void setPosition(const Vector3f& pos);

    /**
     * @brief Obt�m uma refer�ncia para o objeto de c�mera do jogador.
     * @return Uma refer�ncia para a inst�ncia FPSCamera associada ao jogador.
     */
    FPSCamera& getCamera();

private:
    Vector3f _position;         ///< Posi��o atual do jogador.
    FPSCamera _camera;          ///< A c�mera em primeira pessoa do jogador.
    float _movementSpeed;       ///< Velocidade de movimento do jogador.
    float _collisionRadius;     ///< Raio de colis�o para f�sica simples.

    /**
     * @brief Mapa que armazena o estado de cada tecla (pressionada ou n�o).
     * true se a tecla est� pressionada, false caso contr�rio.
     */
    std::map<unsigned char, bool> _keyState;
};

#endif // PLAYER_H
