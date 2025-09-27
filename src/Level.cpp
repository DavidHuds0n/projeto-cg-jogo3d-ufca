/**
 * @file Level.cpp
 * @brief Implementa��o da classe Level.
 */
#include "../include/Level.h"
#include <GL/freeglut.h>

Level::Level() {
    // Construtor pode ser usado no futuro para inicializar vari�veis do n�vel.
}

void Level::loadFromFile(const char* filePath) {
    /*
     * TAREFA (Pessoa 3): Implementar o carregamento do labirinto.
     * 1. Abrir o arquivo de texto localizado em 'filePath'.
     * 2. Ler o conte�do do arquivo (geralmente uma matriz de caracteres ou n�meros)
     * e armazen�-lo em uma estrutura de dados interna (ex: std::vector<std::string>).
     * 3. Identificar as posi��es de spawn do jogador, criatura e sa�da.
     */
}

void Level::render() {
    /*
     * TAREFA (Pessoa 3): Implementar a renderiza��o do labirinto.
     * 1. Percorrer a estrutura de dados do mapa.
     * 2. Para cada c�lula que representa uma parede, desenhar um cubo (glutSolidCube)
     * na posi��o correspondente do mundo.
     * 3. (Opcional) Desenhar um plano grande para o ch�o.
     * @note Lembre-se de definir um material para as paredes para que reajam � luz.
     */
}
