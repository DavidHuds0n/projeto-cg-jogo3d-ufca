/**
 * @file Game.cpp
 * @brief Implementação da classe principal Game, que gerencia o estado e o loop do jogo.
 */

#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h"
#include "../include/InteractableObject.h"
#include "../include/Door.h"
#include "../include/Wall.h" // Mantido para a colisão
#include "../include/PuzzleDoor.h" // Mantido da branch main
#include "../include/SceneManager.h" // Mantido da branch main
#include "../include/GameStateManager.h" // Mantido da branch main
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

// --- FUNÇÕES AUXILIARES ESTÁTICAS ---
/**
 * @brief Desenha texto centralizado na tela.
 * @param msg A string de caracteres a ser desenhada.
 * @param x A coordenada X do centro do texto.
 * @param y A coordenada Y do centro do texto.
 */
static void drawCenteredBitmapText(const char* msg, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* p = msg; *p; ++p) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    }
}

// --- FUNÇÕES AUXILIARES DE RAY CASTING ---
/**
 * @brief Calcula um raio a partir da posição da câmera na tela.
 *
 * Utiliza as matrizes de projeção e modelview do OpenGL para "des-projetar"
 * as coordenadas 2D do mouse para o espaço 3D, criando um vetor de direção para o raio.
 *
 * @param mouseX A coordenada X do mouse na tela.
 * @param mouseY A coordenada Y do mouse na tela.
 * @param player A instância do jogador, para obter a posição da câmera.
 * @return Um objeto Ray contendo a origem e a direção.
 */
Ray calculateMouseRay(int mouseX, int mouseY, Player& player) {
    GLdouble modelviewMatrix[16];
    GLdouble projectionMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    mouseY = viewport[3] - mouseY;

    GLdouble nearX, nearY, nearZ;
    GLdouble farX, farY, farZ;

    gluUnProject(mouseX, mouseY, 0.0, modelviewMatrix, projectionMatrix, viewport, &nearX, &nearY, &nearZ);
    gluUnProject(mouseX, mouseY, 1.0, modelviewMatrix, projectionMatrix, viewport, &farX, &farY, &farZ);

    Vector3f rayDirection = {
        (float)(farX - nearX),
        (float)(farY - nearY),
        (float)(farZ - nearZ)
    };

    float length = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
    if (length > 0) {
        rayDirection.x /= length;
        rayDirection.y /= length;
        rayDirection.z /= length;
    }

    return {player.getCamera().getPosition(), rayDirection};
}

/**
 * @brief Calcula a interseção de um raio com uma esfera.
 *
 * Utiliza uma fórmula quadrática para determinar se e a que distância
 * o raio colide com a superfície da esfera.
 *
 * @param ray O raio a ser testado.
 * @param sphereCenter A posição central da esfera.
 * @param sphereRadius O raio da esfera.
 * @return A distância até o ponto de colisão mais próximo, ou -1.0f se não houver colisão.
 */
float rayIntersectsSphere(const Ray& ray, const Vector3f& sphereCenter, float sphereRadius) {
    Vector3f oc = {
        ray.origin.x - sphereCenter.x,
        ray.origin.y - sphereCenter.y,
        ray.origin.z - sphereCenter.z
    };
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    float c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

// --- IMPLEMENTAÇÃO DA CLASSE GAME ---

/**
 * @brief Construtor da classe Game.
 *
 * Inicializa o estado do jogo para PLAYING.
 */
Game::Game() {
    _currentState = PLAYING;
}

/**
 * @brief Inicializa as configurações do OpenGL e os componentes do jogo.
 *
 * Configura o viewport, a projeção, a iluminação e as matrizes de cor.
 * Em seguida, inicializa o gerenciador de luzes e de cena.
 */
void Game::init() {
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _lightManager.init();
    _sceneManager.init(_player);
}

/**
 * @brief Atualiza o estado do jogo a cada quadro.
 *
 * Se o jogo estiver em estado PLAYING, atualiza a lógica do jogador,
 * do gerenciador de cena e da luz da lanterna.
 *
 * @param deltaTime O tempo decorrido desde o último quadro.
 */
void Game::update(float deltaTime) {
    if (_currentState == PLAYING) {
        _player.update(deltaTime, _sceneManager.getCurrentRoomObjects(), _gameStateManager);
        _sceneManager.update(deltaTime, _gameStateManager);
        // A chamada de processamento de pendências foi removida
        Vector3f currentColor = _gameStateManager.getCurrentFlashlightColor();
        _lightManager.setFlashlightColor(currentColor);
    }
    glutPostRedisplay();
}

/**
 * @brief Renderiza a cena do jogo.
 *
 * O processo de renderização inclui:
 * 1. Desenhar a cena 3D (jogadores, objetos, etc.).
 * 2. Opcionalmente, desenhar as hitboxes de debug.
 * 3. Desenhar a interface 2D, como a mira e as mensagens de status.
 */
void Game::render() {
    // 1. Limpa a tela e desenha a cena 3D principal
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    _player.getCamera().updateView();
    _lightManager.updateFlashlight(_player.getCamera().getPosition(), _player.getCamera().getFrontVector());
    _sceneManager.render();

    // 2. Desenha as hitboxes de debug, se a opção estiver ativa
    if (Config::DEBUG_DRAW_HITBOXES) {
        // Desabilita a iluminação para que a hitbox tenha uma cor sólida
        glDisable(GL_LIGHTING);
        // Habilita o "blending" para permitir a semi-transparência
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::vector<InteractableObject*>& interactables = _sceneManager.getInteractableObjects();

        // Define a cor da hitbox (Verde com 40% de opacidade)
        glColor4f(0.0f, 1.0f, 0.0f, 0.4f); // R, G, B, Alpha

        for (const auto* obj : interactables) {
            Vector3f pos = obj->getPosition();
            float radius = obj->getCollisionRadius();

            glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glutWireSphere(radius, 16, 16);
            glPopMatrix();
        }

        // Reabilita a iluminação e desabilita o blending
        glEnable(GL_LIGHTING);
        glDisable(GL_BLEND);
    }

    // 3. Prepara para desenhar os elementos 2D (interface) por cima de tudo

    // Bloco para desenhar a Crosshair
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, Config::SCREEN_WIDTH, 0, Config::SCREEN_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glColor3f(1.0f, 1.0f, 1.0f); // Cor: Branco
        glLineWidth(2.0f);

        float centerX = Config::SCREEN_WIDTH / 2.0f;
        float centerY = Config::SCREEN_HEIGHT / 2.0f;
        float tamanho = 10.0f;

        glBegin(GL_LINES);
        // Linha vertical
        glVertex2f(centerX, centerY - tamanho);
        glVertex2f(centerX, centerY + tamanho);
        // Linha horizontal
        glVertex2f(centerX - tamanho, centerY);
        glVertex2f(centerX + tamanho, centerY);
        glEnd();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

    // Bloco para desenhar o texto de Fim de Jogo ou Vitória
    if (_currentState != PLAYING) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, Config::SCREEN_WIDTH, 0, Config::SCREEN_HEIGHT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0f, 1.0f, 1.0f);
        const char* msg = (_currentState == GAME_OVER) ? "GAME OVER - Pressione ESC para sair" : "VOCE VENCEU! - Pressione ESC para sair";
        drawCenteredBitmapText(msg, 200, 300);
        glEnable(GL_DEPTH_TEST);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    // 4. Mostra tudo na tela
    glutSwapBuffers();
}

/**
 * @brief Processa a interação do jogador com o ambiente.
 *
 * Lança um raio a partir do centro da tela para detectar o objeto interativo mais
 * próximo dentro de um raio de alcance. Se um objeto for encontrado, seu método
 * `onClick` é chamado.
 */
void Game::processInteraction() {
    Ray ray = calculateMouseRay(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, _player);
    InteractableObject* closestObject = nullptr;
    float closestHitDistance = std::numeric_limits<float>::max();
    std::vector<InteractableObject*>& interactables = _sceneManager.getInteractableObjects();

    for (auto* obj : interactables) {
        if (obj->isInteractable()) {
            float hitDistance = rayIntersectsSphere(ray, obj->getPosition(), obj->getCollisionRadius());

            // MUDANÇA: Verificamos se a distância é diferente de -1 (o valor de "sem colisão"),
            // em vez de > 0. Isso permite interações quando estamos dentro da esfera de colisão.
            if (hitDistance != -1.0f && hitDistance < closestHitDistance) {
                closestHitDistance = hitDistance;
                closestObject = obj;
            }
        }
    }

    if (closestObject && closestHitDistance <= Config::PLAYER_INTERACTION_DISTANCE) {
        closestObject->onClick(_gameStateManager);

        Door* door = dynamic_cast<Door*>(closestObject);
        if (door) {
            if (door->canBeOpenedBy(_gameStateManager)) {
                int targetRoom = door->getTargetRoomIndex();

                // LÓGICA DE TELEPORTE CENTRALIZADA
                // Pegamos a posição de spawn da porta...
                Vector3f spawnPos = door->getSpawnPosition();
                // ...e a passamos para a função que troca de sala.
                _sceneManager.switchToRoom(targetRoom, _player, spawnPos);

            } else {
                std::cout << "A porta esta trancada." << std::endl;
            }
        }
    }
}

/**
 * @brief Processa o evento de uma tecla ser pressionada.
 *
 * Se o teclado numérico estiver ativo, lida com a entrada de números.
 * Caso contrário, processa comandos como `Esc` para sair ou `E` para interagir.
 *
 * @param key A tecla pressionada.
 * @param x A coordenada X do mouse.
 * @param y A coordenada Y do mouse.
 */
void Game::processKeyDown(unsigned char key, int x, int y) {
    if (_gameStateManager.isKeypadActive()) {
        if (key >= '0' && key <= '9') {
            _gameStateManager.appendToKeypadInput(key);
            if (_gameStateManager.getKeypadInput().length() == 3) {
                if (_gameStateManager.checkKeypadCode("742")) {
                    _gameStateManager.setPuzzleState(PuzzleID::Sala1_CodigoCaixa, true);
                }
                _gameStateManager.setActiveKeypad(false);
            }
        } else if (key == 27 || key == 'e') {
            _gameStateManager.setActiveKeypad(false);
        }
        return;
    }

    key = tolower(key);
    if (key == 27) {
        glutLeaveMainLoop();
    }
    if (key == 'e') {
        processInteraction();
    }
    _player.handleKeyDown(key);
}

/**
 * @brief Processa o evento de uma tecla ser liberada.
 * @param key A tecla liberada.
 * @param x A coordenada X do mouse.
 * @param y A coordenada Y do mouse.
 */
void Game::processKeyUp(unsigned char key, int x, int y) {
    key = tolower(key);
    _player.handleKeyUp(key);
}

/**
 * @brief Processa o movimento do mouse para rotacionar a câmera.
 *
 * O mouse é reposicionado no centro da tela após cada movimento para
 * permitir rotação contínua e ilimitada.
 *
 * @param x A coordenada X do mouse.
 * @param y A coordenada Y do mouse.
 */
void Game::processMouseMotion(int x, int y) {
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    _player.handleMouseMotion(x, y);
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
