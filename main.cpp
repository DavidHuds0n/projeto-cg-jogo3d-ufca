// main.cpp
#include <GL/freeglut.h>
#include "include/Game.h"

// --- Instância Global do Jogo ---
// Necessária para que as funções de callback do GLUT possam acessá-la.
Game game;

// --- Funções de Callback (Wrappers) ---
// Estas são as funções que o GLUT chamará diretamente.
// Elas simplesmente repassam a chamada para o método correspondente na nossa instância 'game'.

void renderCallback() {
    game.render();
}

void updateCallback(int value) {
    game.update(16); // Passamos um deltaTime fixo de 16ms
    glutTimerFunc(16, updateCallback, 0); // Reagenda o próximo update
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Jogo 3D");

    // 2. Registro dos Callbacks
    glutDisplayFunc(renderCallback);
    glutKeyboardFunc(keyboardDownCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    glutPassiveMotionFunc(mouseMotionCallback);
    glutTimerFunc(16, updateCallback, 0); // Inicia o primeiro 'update'

    // 3. Inicialização do nosso jogo (configurações do OpenGL)
    game.init();

    // 4. Inicia o Loop Principal do GLUT
    // Esta função nunca retorna até que a janela seja fechada.
    glutMainLoop();

    return 0;
}
