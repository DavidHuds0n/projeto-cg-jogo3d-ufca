/**
 * @file Level.h
 * @brief Define a classe Level, responsável por carregar e renderizar o cenário do jogo.
 */
#ifndef LEVEL_H
#define LEVEL_H

/**
 * @class Level
 * @brief Gerencia a geometria do labirinto, incluindo o carregamento a partir de um arquivo e sua renderização.
 */
class Level {
public:
    /**
     * @brief Construtor padrão da classe Level.
     */
    Level();

    /**
     * @brief Carrega a estrutura do labirinto a partir de um arquivo de texto.
     * @param [in] filePath O caminho para o arquivo .txt que contém o layout do labirinto.
     * @note A implementação desta função é tarefa da Pessoa 3.
     */
    void loadFromFile(const char* filePath);

    /**
     * @brief Desenha todos os componentes visuais do labirinto (paredes, chão, etc.).
     * @note A implementação desta função é tarefa da Pessoa 3.
     */
    void render();
};

#endif // LEVEL_H
