/**
 * @file LightManager.h
 * @brief Define a classe LightManager, que controla as fontes de luz do jogo.
 */
#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "Player.h" // Inclui para ter acesso à struct Vector3f

/**
 * @class LightManager
 * @brief Gerencia a configuração e atualização das luzes do cenário, como a lanterna do jogador e tochas.
 */
class LightManager {
public:
    /**
     * @brief Construtor padrão do LightManager.
     */
    LightManager();

    /**
     * @brief Inicializa as configurações globais de iluminação do OpenGL.
     */
    void init();

    /**
     * @brief Atualiza a posição e direção da luz da lanterna.
     * @param [in] pos A posição atual da fonte de luz (geralmente, a câmera).
     * @param [in] dir O vetor de direção para onde a luz está apontando.
     */
    void updateFlashlight(const Vector3f& pos, const Vector3f& dir);

    /**
     * @brief Ativa uma fonte de luz de uma tocha específica no cenário.
     * @param [in] torchID O identificador único da tocha a ser ativada.
     */
    void enableTorch(int torchID);
};

#endif // LIGHTMANAGER_H
