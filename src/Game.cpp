/**
 * @file Game.cpp
 * @brief Implementação da classe principal Game.
 */
#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h"
#include "../include/InteractableObject.h"
#include "../include/Door.h" // Incluído para a lógica de transição de sala
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <limits>

// --- FUNÇÕES AUXILIARES DE RAY CASTING ---

/**
 * @brief Calcula um raio 3D a partir das coordenadas 2D da tela.
 * Usa gluUnProject para converter as coordenadas da tela para coordenadas do mundo.
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
 * @brief Verifica se um raio intercepta uma esfera.
 * @return A distância da origem do raio até a interseção, ou um valor negativo se não houver.
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

Game::Game() {
    _currentState = PLAYING;
}

void Game::init() {
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _lightManager.init();
    _sceneManager.init();
}

void Game::update(float deltaTime) {
    if (_currentState == PLAYING) {
        _player.update(deltaTime);
        _sceneManager.update(deltaTime);
    }
    glutPostRedisplay();
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    _player.getCamera().updateView();
    _lightManager.updateFlashlight(_player.getCamera().getPosition(), _player.getCamera().getFrontVector());

    _sceneManager.render();

    glutSwapBuffers();
}

void Game::processInteraction() {
    std::cout << "Tecla 'E' pressionada! Calculando Ray Casting..." << std::endl;

    // 1. Calcula um raio 3D que "sai" da câmera, passando pelo centro da tela.
    Ray ray = calculateMouseRay(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, _player);

    // 2. Prepara variáveis para encontrar o objeto interativo mais próximo que foi atingido.
    InteractableObject* closestObject = nullptr;
    float closestHitDistance = std::numeric_limits<float>::max();

    // 3. Pede ao SceneManager a lista de todos os objetos interativos da sala atual.
    std::vector<InteractableObject*>& interactables = _sceneManager.getInteractableObjects();

    // 4. Percorre a lista de interativos, testando a colisão do raio com cada um.
    for (auto* obj : interactables) {
        if (obj->isInteractable()) {
            // Testa a colisão do raio com a esfera de colisão do objeto.
            float hitDistance = rayIntersectsSphere(ray, obj->getPosition(), obj->getCollisionRadius());

            // Se o raio atingiu o objeto (dist > 0) e este é o mais próximo até agora...
            if (hitDistance > 0 && hitDistance < closestHitDistance) {
                // ...guarda a distância e o ponteiro para este objeto.
                closestHitDistance = hitDistance;
                closestObject = obj;
            }
        }
    }

    // 5. Após testar todos os objetos, verifica se algum foi atingido.
    if (closestObject) {
        // 5a. Verifica se o objeto atingido está perto o suficiente do jogador.
        if (closestHitDistance <= Config::PLAYER_INTERACTION_DISTANCE) {
            // Se estiver perto, chama a função de interação específica do objeto.
            closestObject->onClick();

            // 5b. Caso especial: Se o objeto for uma porta, executa a lógica de transição.
            Door* door = dynamic_cast<Door*>(closestObject);
            if (door) {
                // Pega o índice da sala de destino da porta.
                int targetRoom = door->getTargetRoomIndex();
                // Manda o SceneManager trocar de sala.
                _sceneManager.switchToRoom(targetRoom);

                // Reposiciona o jogador na coordenada de spawn definida na porta.
                _player.setPosition(door->getSpawnPosition());
            }
        } else {
            std::cout << "Objeto encontrado, mas esta longe demais para interagir!" << std::endl;
        }
    } else {
        std::cout << "Nenhum objeto interativo na mira." << std::endl;
    }
}

// --- Processamento de Entrada ---

void Game::processKeyDown(unsigned char key, int x, int y) {
    key = tolower(key);

    if (key == 27) { // Tecla ESC
        glutLeaveMainLoop();
    }

    if (key == 'e') {
        processInteraction();
    }

    _player.handleKeyDown(key);
}

void Game::processKeyUp(unsigned char key, int x, int y) {
    key = tolower(key);
    _player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    _player.handleMouseMotion(x, y);
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
