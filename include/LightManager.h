/**
 * @file LightManager.h
 * @brief Define a classe LightManager, que controla as fontes de luz do jogo.
 */
#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Player.h" // Inclui para ter acesso � struct Vector3f

/**
 * @class LightManager
 * @brief Gerencia a configura��o e atualiza��o das luzes do cen�rio, como a lanterna do jogador e tochas.
 */
class LightManager {
public:
    /**
     * @brief Construtor padr�o do LightManager.
     */
    LightManager();

    /**
     * @brief Inicializa as configura��es globais de ilumina��o do OpenGL.
     */
    void init();

    /**
     * @brief Atualiza a posi��o e dire��o da luz da lanterna.
     * @param [in] pos A posi��o atual da fonte de luz (geralmente, a c�mera).
     * @param [in] dir O vetor de dire��o para onde a luz est� apontando.
     */
    void updateFlashlight(const Vector3f& pos, const Vector3f& dir);

    void setFlashlightColor(const Vector3f& color);
};

#endif // LIGHTMANAGER_H
