#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
    Level();

    // M�todos para a Pessoa 3 implementar
    void loadFromFile(const char* filePath); // Carrega o labirinto do .txt
    void render();                            // Desenha o labirinto (paredes, ch�o)
};

#endif
