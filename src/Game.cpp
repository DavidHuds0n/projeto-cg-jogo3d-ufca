/**
 * @file Game.cpp
 * @brief Implementa��o da classe principal Game.
 */
#include "../include/Game.h"
#include "../include/Config.h"
#include <GL/freeglut.h>
#include <string>

// --- Fun��es de Teste e Auxiliares ---

/**
 * @brief Desenha um cen�rio de teste com v�rios objetos e um grid.
 * @note ESTA FUN��O � TEMPOR�RIA. Deve ser removida quando a renderiza��o
 * do Level estiver funcional.
 */
// --- A FUN��O DO MUNDO DE TESTE (ser� removida quando o Level for implementado) ---
void drawTestbed() {
    // Desenha um Grid no Ch�o
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (int i = -20; i <= 20; i++) {
        glVertex3f((float)i, 0, -20);
        glVertex3f((float)i, 0, 20);
        glVertex3f(-20, 0, (float)i);
        glVertex3f(20, 0, (float)i);
    }
    glEnd();
    glEnable(GL_LIGHTING);

    // --- Desenha Objetos de Refer�ncia COM MATERIAL ---
    GLfloat white_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, white_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);

    // Cubo Vermelho
    GLfloat red_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_diffuse);
    glPushMatrix();
    glTranslatef(0, 1, -10);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cubo Verde
    GLfloat green_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green_diffuse);
    glPushMatrix();
    glTranslatef(10, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cubo Azul
    GLfloat blue_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diffuse);
    glPushMatrix();
    glTranslatef(-10, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Esfera Amarela
    GLfloat yellow_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow_diffuse);
    glPushMatrix();
    glTranslatef(-5, 1, 5);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();

    // Cone Roxo
    GLfloat purple_diffuse[] = { 0.5f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple_diffuse);
    glPushMatrix();
    glTranslatef(5, 0, 5);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.0, 2.0, 32, 32);
    glPopMatrix();

    // Torus Ciano
    GLfloat cyan_diffuse[] = { 0.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan_diffuse);
    glPushMatrix();
    glTranslatef(0, 1, 10);
    glutSolidTorus(0.5, 1.0, 32, 32);
    glPopMatrix();
}

/**
 * @brief Desenha a Interface do Usu�rio (HUD).
 * @param health A vida atual do jogador a ser exibida.
 * @note Esta fun��o � um placeholder para a implementa��o da Pessoa 4.
 */
void drawHUD(float health) {
    /*
     * TAREFA (Pessoa 4): Implementar a HUD.
     * 1. Mudar para o modo de proje��o 2D (glOrtho2D).
     * 2. Desabilitar ilumina��o e profundidade (glDisable LIGHTING/DEPTH_TEST).
     * 3. Definir a cor do texto.
     * 4. Usar glRasterPos e glutBitmapCharacter para desenhar as strings na tela.
     * - Exibir a vida do jogador.
     * - Exibir "GAME OVER" ou "YOU WIN" se o estado do jogo mudar.
     * 5. Restaurar os modos de proje��o e estados do OpenGL.
     */
}

// --- Implementa��o da Classe Game ---

Game::Game() {
    // O construtor � mantido simples. A inicializa��o pesada ocorre no init().
}

void Game::init() {
    // 1. Configura��es iniciais de estado do OpenGL.
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f); // Cor de fundo.
    glEnable(GL_DEPTH_TEST);       // Habilita teste de profundidade para renderiza��o 3D correta.
    glShadeModel(GL_SMOOTH);       // Habilita sombreamento suave.
    glEnable(GL_NORMALIZE);        // Normaliza vetores normais (importante para ilumina��o).
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Melhora o c�lculo do brilho especular.

    // 2. Configura a proje��o da c�mera (perspectiva).
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);

    // 3. Volta para a matriz de vis�o do modelo (ModelView).
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 4. Inicializa os sistemas do jogo.
    lightManager.init();
    // TAREFA (Pessoa 2): A inicializa��o do Level viria aqui.

    // 5. Inicia o jogo.
    resetGame();
}

void Game::update(float deltaTime) {
    // A l�gica principal do jogo � controlada pelo estado atual.
    switch (currentState) {
        case PLAYING:
            // O jogo est� ativo, ent�o atualizamos todos os objetos din�micos.
            player.update(deltaTime);
            // TAREFA (Pessoa 3): Chamar creature.update(...) aqui.
            // TAREFA (Pessoa 4): Chamar checkCollisions() aqui.
            break;

        case GAME_OVER:
        case WIN:
            // O jogo terminou. A l�gica de atualiza��o de Player e Creature � pausada.
            // O jogo apenas espera pela entrada do jogador para reiniciar (tecla 'R').
            // TAREFA (Pessoa 4): A verifica��o da tecla 'R' est� em processKeyDown.
            break;
    }
    // For�a a tela a ser redesenhada no pr�ximo ciclo.
    glutPostRedisplay();
}

void Game::render() {
    // 1. Limpa os buffers de cor e profundidade antes de desenhar o novo frame.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Reseta a matriz de ModelView.

    // 2. Configura a c�mera e a ilumina��o para a cena.
    player.getCamera().updateView();
    lightManager.updateFlashlight(player.getCamera().getPosition(), player.getCamera().getFrontVector());

    // 3. Renderiza os objetos do mundo.
    // TAREFA (Integra��o): Substituir drawTestbed() pelas chamadas reais.
    drawTestbed();
    // level.render();
    // creature.render();

    // 4. Renderiza a interface do usu�rio (HUD) por cima de tudo.
    // TAREFA (Pessoa 4): Chamar a fun��o drawHUD aqui.
    // drawHUD(player.getHealth());

    // 5. Troca os buffers para exibir o frame que acabamos de desenhar.
    glutSwapBuffers();
}

void Game::resetGame() {
    /*
     * TAREFA (Integra��o): Esta fun��o deve restaurar tudo para o estado inicial.
     * 1. (Pessoa 4) Definir o estado do jogo para PLAYING.
     * 2. (Pessoa 2) Carregar o labirinto do arquivo.
     * 3. (Pessoa 4) Resetar o jogador (vida, posi��o inicial do mapa).
     * 4. (Pessoa 3) Resetar a criatura (encontrar um ponto de spawn).
     */
    currentState = PLAYING;
}

void Game::checkCollisions() {
    /*
     * TAREFA (Pessoa 4): Implementar a detec��o de colis�es.
     * 1. Colis�o Jogador vs. Criatura:
     * - Calcular a dist�ncia entre jogador e criatura.
     * - Se a dist�ncia for menor que o raio de colis�o, aplicar dano ao jogador.
     * - Se a vida do jogador chegar a zero, mudar `currentState` para GAME_OVER.
     *
     * 2. (Integra��o com Pessoa 2) Condi��o de Vit�ria:
     * - Calcular a dist�ncia entre o jogador e a posi��o de sa�da do labirinto.
     * - Se for pequena o suficiente, mudar `currentState` para WIN.
     */
}

// --- Processamento de Entrada ---

void Game::processKeyDown(unsigned char key, int x, int y) {
    if (key == 27) { // Tecla ESC
        glutLeaveMainLoop(); // Fecha o jogo.
    }
    /*
     * TAREFA (Pessoa 4): Implementar o rein�cio do jogo.
     * - Verificar se o estado � GAME_OVER ou WIN.
     * - Se for, e a tecla for 'r' ou 'R', chamar resetGame().
     */
    player.handleKeyDown(key);
}

void Game::processKeyUp(unsigned char key, int x, int y) {
    player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    // Ignora o evento se o mouse estiver exatamente no centro (causado por n�s mesmos).
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    player.handleMouseMotion(x, y);

    // For�a o cursor a voltar para o centro da tela ap�s cada movimento.
    // Isso cria a ilus�o de movimento infinito do mouse, essencial para jogos FPS.
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
