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
// As funções a seguir são "wrappers" ou "invólucros". O GLUT precisa chamar
// funções C padrão, então criamos estas funções que simplesmente repassam
// a chamada para o método correspondente na nossa instância 'game'.

void renderCallback() {
    game.render();
}

void updateCallback(int value) {
    // Define um deltaTime fixo de 16ms, visando uma taxa de ~60 frames por segundo (1000ms / 16ms ≈ 62.5 FPS).
    game.update(16);
    // Reagenda esta mesma função para ser chamada novamente após 16ms.
    glutTimerFunc(16, updateCallback, 0);
}

void keyboardDownCallback(unsigned char key, int x, int y) {
    game.processKeyDown(key, x, y);
}

void keyboardUpCallback(unsigned char key, int x, int y) {
    game.processKeyUp(key, x, y);
}

void mouseMotionCallback(int x, int y) {
    game.processMouseMotion(x, y);
}

// --- Função Principal ---

int main(int argc, char** argv) {
    // 1. Inicialização do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Buffer duplo, cores RGB, buffer de profundidade.
    glutInitWindowSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glutCreateWindow(Config::GAME_TITLE);
    glutSetCursor(GLUT_CURSOR_NONE); // Oculta o cursor do mouse para uma experiência de FPS imersiva.

    // 2. Registro dos Callbacks
    glutDisplayFunc(renderCallback);         // O que desenhar.
    glutKeyboardFunc(keyboardDownCallback);  // O que fazer quando uma tecla é pressionada.
    glutKeyboardUpFunc(keyboardUpCallback);    // O que fazer quando uma tecla é solta.
    glutPassiveMotionFunc(mouseMotionCallback); // O que fazer quando o mouse se move (sem clicar).
    glutTimerFunc(16, updateCallback, 0);       // Inicia o nosso "update loop" customizado.

    // 3. Inicialização do nosso jogo
    // Esta chamada configura os estados iniciais do OpenGL (iluminação, câmera, etc).
    game.init();

    // Centraliza o ponteiro do mouse no início para evitar um pulo da câmera no primeiro movimento.
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);

    // 4. Inicia o Loop Principal do GLUT
    // Esta função entrega o controle para o GLUT. O programa agora responderá a eventos
    // através dos callbacks registrados. Ela nunca retorna até que o jogo seja fechado.
    glutMainLoop();
    return 0;
}
