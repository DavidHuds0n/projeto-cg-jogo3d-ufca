// ===== TextureManager.cpp (versão sem <filesystem>) =====
#define STB_IMAGE_IMPLEMENTATION      // garanta que só este .cpp define isso
#include "../include/stb_image.h"

#include "../include/TextureManager.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, GLuint> TextureManager::_textures;
// Checa existência de arquivo de forma portátil (sem <filesystem>)
static bool fileExists(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (f) { fclose(f); return true; }
    return false;
}

static std::string leafName(const std::string& p) {
    size_t s1 = p.find_last_of('/');
    size_t s2 = p.find_last_of('\\');
    size_t s  = (s1 == std::string::npos) ? s2 : (s2 == std::string::npos ? s1 : std::max(s1, s2));
    return (s == std::string::npos) ? p : p.substr(s + 1);
}

// Tenta vários caminhos relativos comuns (bin/Debug, bin/Release, raiz do projeto, etc.)
static std::string resolveTexturePath(const std::string& requested) {
    const std::string leaf = leafName(requested);

    // se já veio um caminho com subpastas, tente primeiro como está e com "./"
    std::vector<std::string> tries = {
        requested,
        "./" + requested,

        // apenas o nome do arquivo dentro de "Textures/"
        "Textures/" + leaf,
        "./Textures/" + leaf,
        "../Textures/" + leaf,
        "../../Textures/" + leaf,
        "../../../Textures/" + leaf
    };

    for (const auto& t : tries) {
        if (fileExists(t)) return t;
    }

    // log de diagnóstico
    std::cerr << "[Texture] Não encontrei '" << requested << "'. Tentativas:\n";
    for (const auto& t : tries) std::cerr << "  - " << t << "\n";
    return {};
}

GLuint TextureManager::loadTexture(const std::string& filename) {
    // cache: se já carregou, retorna
    auto it = _textures.find(filename);
    if (it != _textures.end()) return it->second;

    // resolve caminho real
    std::string path = resolveTexturePath(filename);
    if (path.empty()) {
        std::cerr << "[Texture] Arquivo não encontrado: " << filename << "\n";
        return 0;
    }

    // evita textura invertida (muito comum com stb_image)
    stbi_set_flip_vertically_on_load(1);

    int width = 0, height = 0, channels = 0;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "[Texture] Falha no stbi_load: " << path << "\n";
        return 0;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // alinhamento 1 evita glitch em JPGs com largura não múltipla de 4
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    // Filtros (sem mipmap)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap padrão
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);

    _textures[filename] = tex;
    std::cerr << "[Texture] OK: " << filename << " -> " << path
              << " (" << width << "x" << height << ", ch=" << channels << ")\n";
    return tex;
}
