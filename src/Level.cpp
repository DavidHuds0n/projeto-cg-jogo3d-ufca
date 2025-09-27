/**
 * @file Level.cpp
 * @brief Implementação da classe Level.
 */
#include "../include/Level.h"
#include <GL/freeglut.h>

Level::Level() {
    // Construtor pode ser usado no futuro para inicializar variáveis do nível.
}

void Level::loadFromFile(const char* filePath) {
    /*
     * TAREFA (Pessoa 3): Implementar o carregamento do labirinto.
     * 1. Abrir o arquivo de texto localizado em 'filePath'.
     * 2. Ler o conteúdo do arquivo (geralmente uma matriz de caracteres ou números)
     * e armazená-lo em uma estrutura de dados interna (ex: std::vector<std::string>).
     * 3. Identificar as posições de spawn do jogador, criatura e saída.
     */
}

void Level::render() {
    /*
     * TAREFA (Pessoa 3): Implementar a renderização do labirinto.
     * 1. Percorrer a estrutura de dados do mapa.
     * 2. Para cada célula que representa uma parede, desenhar um cubo (glutSolidCube)
     * na posição correspondente do mundo.
     * 3. (Opcional) Desenhar um plano grande para o chão.
     * @note Lembre-se de definir um material para as paredes para que reajam à luz.
     */
}
