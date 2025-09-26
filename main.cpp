// main.cpp
#include <GL/freeglut.h>
#include "include/Game.h"
#include "include/Config.h"

// --- Inst�ncia Global do Jogo ---
// Necess�ria para que as fun��es de callback do GLUT possam acess�-la.
Game game;

// --- Fun��es de Callback (Wrappers) ---
// Estas s�o as fun��es que o GLUT chamar� diretamente.
// Elas simplesmente repassam a chamada para o m�todo correspondente na nossa inst�ncia 'game'.

void renderCallback() {
    game.render();
}

void updateCallback(int value) {
    game.update(16); // Passamos um deltaTime fixo de 16ms
    glutTimerFunc(16, updateCallback, 0); // Reagenda o pr�ximo update
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

// --- Fun��o Principal ---

int main(int argc, char** argv) {
    // 1. Inicializa��o do GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glutCreateWindow(Config::GAME_TITLE);
    glutSetCursor(GLUT_CURSOR_NONE); // Oculta o cursor do mouse

    // 2. Registro dos Callbacks
    glutDisplayFunc(renderCallback);
    glutKeyboardFunc(keyboardDownCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    glutPassiveMotionFunc(mouseMotionCallback);
    glutTimerFunc(16, updateCallback, 0); // Inicia o primeiro 'update'

    // 3. Inicializa��o do nosso jogo (configura��es do OpenGL)
    game.init();

    // --- ADICIONE ESTA LINHA ---
    // Centraliza o ponteiro do mouse para o estado inicial
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);

    // 4. Inicia o Loop Principal do GLUT
    glutMainLoop();
    return 0;
}
