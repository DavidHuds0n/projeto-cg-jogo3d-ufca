#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>

// Enum para todos os itens que o jogador pode coletar
enum class ItemType {
    CHAVE_SALA_1,
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
