/**
 * @file TextureManager.cpp
 * @brief Implementação da classe TextureManager, responsável por carregar e gerenciar texturas.
 *
 * Este arquivo utiliza a biblioteca stb_image para carregar arquivos de imagem
 * e o OpenGL para criar as texturas, gerenciando um cache interno para evitar
 * recargas desnecessárias.
 */

// Define a implementação da biblioteca stb_image.
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/TextureManager.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief Um mapa estático para armazenar as texturas carregadas em cache.
 *
 * A chave é o nome do arquivo da textura e o valor é o identificador OpenGL da textura (GLuint).
 */
std::unordered_map<std::string, GLuint> TextureManager::_textures;

/**
 * @brief Checa a existência de um arquivo de forma portátil.
 *
 * Este método tenta abrir o arquivo para leitura para verificar sua existência,
 * sem depender de bibliotecas modernas como `<filesystem>`.
 *
 * @param path O caminho do arquivo a ser verificado.
 * @return Retorna 'true' se o arquivo existir, 'false' caso contrário.
 */
static bool fileExists(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (f) { fclose(f); return true; }
    return false;
}

/**
 * @brief Extrai o nome do arquivo de um caminho completo.
 *
 * Localiza a última ocorrência de '/' ou '\\' no caminho para isolar o nome do arquivo.
 *
 * @param p O caminho completo do arquivo.
 * @return O nome do arquivo (ex: "imagem.jpg").
 */
static std::string leafName(const std::string& p) {
    size_t s1 = p.find_last_of('/');
    size_t s2 = p.find_last_of('\\');
    size_t s  = (s1 == std::string::npos) ? s2 : (s2 == std::string::npos ? s1 : std::max(s1, s2));
    return (s == std::string::npos) ? p : p.substr(s + 1);
}

/**
 * @brief Tenta resolver o caminho de um arquivo de textura.
 *
 * O método tenta vários caminhos relativos comuns para localizar o arquivo,
 * facilitando a portabilidade entre diferentes estruturas de projeto.
 *
 * @param requested O caminho original da textura.
 * @return O caminho de arquivo válido se encontrado, uma string vazia caso contrário.
 */
static std::string resolveTexturePath(const std::string& requested) {
    const std::string leaf = leafName(requested);

    // Tenta caminhos comuns
    std::vector<std::string> tries = {
        requested,
        "./" + requested,

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

/**
 * @brief Carrega uma textura a partir de um arquivo e a armazena em cache.
 *
 * Se a textura já foi carregada, retorna seu identificador do cache. Caso contrário,
 * ela é carregada do disco, configurada para o OpenGL e adicionada ao cache.
 *
 * @param filename O nome do arquivo da textura.
 * @return O identificador OpenGL da textura (GLuint) ou 0 em caso de falha.
 */
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

    // evita textura invertida
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
