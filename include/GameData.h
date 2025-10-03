#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>

// Enum para todos os itens que o jogador pode coletar
enum class ItemType {
    NENHUM,               // Representa a ausência de um item

    // Chaves para progredir entre as salas
    CHAVE_SALA_1,         // Abre a porta da Sala 1 para a 2
    CHAVE_SALA_2,         // Abre a porta da Sala 2 para a 3

    // Itens de puzzle específicos
    FORMA_ESFERA,
    FORMA_CUBO,
    FORMA_PIRAMIDE
};
// Identificadores únicos para cada puzzle
namespace PuzzleID {
    const std::string Sala1_CodigoCaixa = "S1_CodigoCaixa";
    const std::string Sala2_FormasEncaixadas = "S2_FormasEncaixadas";
    const std::string Sala3_SequenciaBotoes = "S3_SequenciaBotoes";
}

#endif // GAMEDATA_H
