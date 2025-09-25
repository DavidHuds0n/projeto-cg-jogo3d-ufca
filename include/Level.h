#ifndef LEVEL_H
#define LEVEL_H

class Level {
public:
    Level();

    // Métodos para a Pessoa 3 implementar
    void loadFromFile(const char* filePath); // Carrega o labirinto do .txt
    void render();                            // Desenha o labirinto (paredes, chão)
};

#endif
