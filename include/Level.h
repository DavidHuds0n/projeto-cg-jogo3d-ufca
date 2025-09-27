/**
 * @file Level.h
 * @brief Define a classe Level, respons�vel por carregar e renderizar o cen�rio do jogo.
 */
#ifndef LEVEL_H
#define LEVEL_H

/**
 * @class Level
 * @brief Gerencia a geometria do labirinto, incluindo o carregamento a partir de um arquivo e sua renderiza��o.
 */
class Level {
public:
    /**
     * @brief Construtor padr�o da classe Level.
     */
    Level();

    /**
     * @brief Carrega a estrutura do labirinto a partir de um arquivo de texto.
     * @param [in] filePath O caminho para o arquivo .txt que cont�m o layout do labirinto.
     * @note A implementa��o desta fun��o � tarefa da Pessoa 3.
     */
    void loadFromFile(const char* filePath);

    /**
     * @brief Desenha todos os componentes visuais do labirinto (paredes, ch�o, etc.).
     * @note A implementa��o desta fun��o � tarefa da Pessoa 3.
     */
    void render();
};

#endif // LEVEL_H
