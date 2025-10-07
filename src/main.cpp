/**
 * @file main.cpp
 * @brief Ponto de entrada principal do programa e configuração do GLUT.
 *
 * Este arquivo é responsável por inicializar a biblioteca GLUT, criar a janela do jogo,
 * registrar as funções de callback (render, update, teclado, mouse) e iniciar o loop principal.
 */
#include <GL/freeglut.h>
#include "../include/Game.h"
#include "../include/Config.h"

// --- Instância Global do Jogo ---
/**
 * @brief Instância global da classe Game.
 * @note É necessária uma instância global para que as funções de callback do GLUT,
 * que são funções C simples, possam acessar os métodos da nossa classe Game.
 */
Game game;

// --- Funções de Callback (Wrappers) ---
/**
 * @brief Função de callback para renderização.
 *
 * Esta função é chamada pelo GLUT quando a janela precisa ser redesenhada.
 * Ela repassa a chamada para o método `render` da instância global do jogo.
 */
void renderCallback() {
    game.render();
}

/**
 * @brief Função de callback para o loop de atualização do jogo.
 *
 * Esta função é chamada periodicamente por um temporizador do GLUT.
 * Ela atualiza o estado do jogo e, em seguida, se reagenda para ser chamada novamente.
 *
 * @param value Valor inteiro passado pelo temporizador do GLUT (não utilizado).
 */
void updateCallback(int value) {
    // Define um deltaTime fixo de 16ms, visando uma taxa de ~60 frames por segundo.
    game.update(16);
    // Reagenda esta mesma função para ser chamada novamente após 16ms.
    glutTimerFunc(16, updateCallback, 0);
}

/**
 * @brief Função de callback para teclas pressionadas.
 * @param key O caractere da tecla pressionada.
 * @param x A coordenada x do cursor do mouse.
 * @param y A coordenada y do cursor do mouse.
 */
void keyboardDownCallback(unsigned char key, int x, int y) {
    game.processKeyDown(key, x, y);
}

/**
 * @brief Função de callback para teclas liberadas.
 * @param key O caractere da tecla liberada.
 * @param x A coordenada x do cursor do mouse.
 * @param y A coordenada y do cursor do mouse.
 */
void keyboardUpCallback(unsigned char key, int x, int y) {
    game.processKeyUp(key, x, y);
}

/**
 * @brief Função de callback para o movimento do mouse.
 *
 * É usada para gerenciar a rotação da câmera do jogador.
 *
 * @param x A nova coordenada x do cursor.
 * @param y A nova coordenada y do cursor.
 */
void mouseMotionCallback(int x, int y) {
    game.processMouseMotion(x, y);
}

// --- Função Principal ---
/**
 * @brief Ponto de entrada principal do programa.
 *
 * Configura e inicializa a biblioteca GLUT, a janela do jogo e
 * todos os callbacks necessários. Inicia o loop principal que
 * mantém o jogo em execução.
 *
 * @param argc O número de argumentos da linha de comando.
 * @param argv Um array de strings com os argumentos.
 * @return Retorna 0 ao finalizar a execução.
 */
int main(int argc, char** argv) {
    // 1. Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glutCreateWindow(Config::GAME_TITLE);
    glutSetCursor(GLUT_CURSOR_NONE); // Oculta o cursor do mouse.

    // 2. Registro dos Callbacks
    glutDisplayFunc(renderCallback);
    glutKeyboardFunc(keyboardDownCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    glutPassiveMotionFunc(mouseMotionCallback);
    glutTimerFunc(16, updateCallback, 0);

    // 3. Inicialização do nosso jogo
    game.init();

    // Centraliza o ponteiro do mouse no início para evitar um pulo da câmera.
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);

    // 4. Inicia o Loop Principal do GLUT
    glutMainLoop();
    return 0;
}
