#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <unordered_map>
#include <GL/glut.h>

class TextureManager {
public:
    static GLuint loadTexture(const std::string& filename); // carrega ou retorna existente
    static void clear(); // limpa todas as texturas carregadas

private:
    static std::unordered_map<std::string, GLuint> _textures; // mapa: arquivo -> ID da textura
};

#endif // TEXTUREMANAGER_H
