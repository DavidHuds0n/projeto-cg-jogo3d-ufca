/**
 * @file Game.cpp
 * @brief Implementa��o da classe principal Game.
 */
#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h" // Inclui a struct Ray para o Ray Casting
#include "../include/InteractableObject.h"
#include <GL/freeglut.h>
#include <iostream>        // Para std::cout (usado nos testes de intera��o)
#include <cmath>           // Para sqrt (usado na matem�tica de vetores)
#include <limits>          // Para std::numeric_limits (usado para encontrar o objeto mais pr�ximo)

// --- FUN��ES AUXILIARES DE RAY CASTING ---

/**
 * @brief Calcula um raio 3D a partir das coordenadas 2D da tela.
 * Usa gluUnProject para converter as coordenadas da tela para coordenadas do mundo.
 * @param mouseX Coordenada X do mouse na janela.
 * @param mouseY Coordenada Y do mouse na janela.
 * @param player O objeto jogador, para obter a posi��o e matrizes da c�mera.
 * @return Um objeto Ray com origem na c�mera e dire��o apontando para o cursor.
 */
Ray calculateMouseRay(int mouseX, int mouseY, Player& player) {
    // 1. Obter matrizes e viewport atuais do OpenGL
    GLdouble modelviewMatrix[16];
    GLdouble projectionMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // A coordenada Y do mouse (que cresce para baixo) precisa ser invertida para o OpenGL (que cresce para cima).
    mouseY = viewport[3] - mouseY;

    // 2. "Desprojetar" o ponto 2D duas vezes para obter 2 pontos no espa�o 3D
    GLdouble nearX, nearY, nearZ; // Ponto no plano de corte pr�ximo (near plane)
    GLdouble farX, farY, farZ;   // Ponto no plano de corte distante (far plane)

    // Ponto pr�ximo (Z=0.0 na coordenada de tela)
    gluUnProject(mouseX, mouseY, 0.0, modelviewMatrix, projectionMatrix, viewport, &nearX, &nearY, &nearZ);
    // Ponto distante (Z=1.0 na coordenada de tela)
    gluUnProject(mouseX, mouseY, 1.0, modelviewMatrix, projectionMatrix, viewport, &farX, &farY, &farZ);

    // 3. Calcular a dire��o do raio subtraindo o ponto distante do pr�ximo
    Vector3f rayDirection = {
        (float)(farX - nearX),
        (float)(farY - nearY),
        (float)(farZ - nearZ)
    };

    // Normalizar o vetor de dire��o para que seu comprimento seja 1
    float length = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
    if (length > 0) {
        rayDirection.x /= length;
        rayDirection.y /= length;
        rayDirection.z /= length;
    }

    // A origem do raio � a posi��o da c�mera
    return {player.getCamera().getPosition(), rayDirection};
}

/**
 * @brief Verifica se um raio intercepta uma esfera usando a f�rmula matem�tica de interse��o.
 * @param ray O raio a ser testado.
 * @param sphereCenter O centro da esfera de colis�o.
 * @param sphereRadius O raio da esfera de colis�o.
 * @return A dist�ncia da origem do raio at� a interse��o, ou um valor negativo se n�o houver interse��o.
 */
float rayIntersectsSphere(const Ray& ray, const Vector3f& sphereCenter, float sphereRadius) {
    Vector3f oc = {
        ray.origin.x - sphereCenter.x,
        ray.origin.y - sphereCenter.y,
        ray.origin.z - sphereCenter.z
    };
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z; // Deve ser 1.0 se a dire��o for normalizada
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    float c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f; // Nenhuma interse��o real
    } else {
        // Retorna a dist�ncia da interse��o mais pr�xima (a menor raiz positiva da equa��o quadr�tica)
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}


// --- IMPLEMENTA��O DA CLASSE GAME ---

Game::Game() {
    // Estado inicial do jogo.
    _currentState = PLAYING;
}

void Game::init() {
    // 1. Configura��es iniciais de estado do OpenGL.
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // 2. Configura a proje��o da c�mera (perspectiva).
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);

    // 3. Volta para a matriz de vis�o do modelo (ModelView).
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 4. Inicializa os sistemas do jogo.
    _lightManager.init();
    _sceneManager.init(); // Inicializa o novo gerenciador de cenas
}

void Game::update(float deltaTime) {
    // A l�gica de atualiza��o agora � delegada.
    // O SceneManager, por sua vez, atualizar� a sala atual.
    if (_currentState == PLAYING) {
        _player.update(deltaTime);
        _sceneManager.update(deltaTime);
    }

    // For�a a tela a ser redesenhada no pr�ximo ciclo.
    glutPostRedisplay();
}

void Game::render() {
    // 1. Limpa os buffers de cor e profundidade.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 2. Configura a c�mera e a ilumina��o para a cena.
    // A c�mera precisa ser atualizada ANTES de pegarmos as matrizes para o Ray Casting.
    _player.getCamera().updateView();
    _lightManager.updateFlashlight(_player.getCamera().getPosition(), _player.getCamera().getFrontVector());

    // 3. Renderiza a cena atual atrav�s do SceneManager.
    _sceneManager.render();

    // 4. Troca os buffers para exibir o frame.
    glutSwapBuffers();
}

void Game::processInteraction() {
    std::cout << "Tecla 'E' pressionada! Calculando Ray Casting..." << std::endl;

    // 1. Calcula o raio a partir do centro da tela
    Ray ray = calculateMouseRay(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, _player);

    // 2. L�gica para encontrar o objeto interativo mais pr�ximo
    InteractableObject* closestObject = nullptr;
    float closestHitDistance = std::numeric_limits<float>::max();

    // 3. Pede ao SceneManager a lista de objetos interativos da cena atual
    std::vector<InteractableObject*>& interactables = _sceneManager.getInteractableObjects();

    for (auto* obj : interactables) {
        if (obj->isInteractable()) {
            // Teste de colis�o Ray-Sphere
            float hitDistance = rayIntersectsSphere(ray, obj->getPosition(), obj->getCollisionRadius());

            // Se o raio atingiu o objeto (dist > 0) e � o mais pr�ximo at� agora
            if (hitDistance > 0 && hitDistance < closestHitDistance) {
                closestHitDistance = hitDistance;
                closestObject = obj;
            }
        }
    }

    // 4. Se um objeto foi encontrado, verifica a dist�ncia e interage
    if (closestObject) {
        // Verifica se a dist�ncia do jogador at� o objeto � curta o suficiente
        if (closestHitDistance <= Config::PLAYER_INTERACTION_DISTANCE) {
            closestObject->onClick();
        } else {
            std::cout << "Objeto encontrado, mas esta longe demais para interagir!" << std::endl;
        }
    } else {
        std::cout << "Nenhum objeto interativo na mira." << std::endl;
    }
}


// --- Processamento de Entrada ---

void Game::processKeyDown(unsigned char key, int x, int y) {
    key = tolower(key); // Converte a tecla para min�scula para facilitar a verifica��o

    if (key == 27) { // Tecla ESC
        glutLeaveMainLoop(); // Fecha o jogo.
    }

    if (key == 'e') {
        processInteraction();
    }

    // Apenas repassa a entrada para o jogador para o movimento.
    _player.handleKeyDown(key);
}

void Game::processKeyUp(unsigned char key, int x, int y) {
    key = tolower(key);
    _player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    // Ignora o evento se o mouse estiver exatamente no centro (evita loops).
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    _player.handleMouseMotion(x, y);

    // For�a o cursor a voltar para o centro da tela.
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
