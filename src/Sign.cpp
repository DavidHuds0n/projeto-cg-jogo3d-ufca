/**
 * @file Sign.cpp
 * @brief Implementação da classe Sign, que representa uma placa de madeira com texto.
 */
#include "../include/Sign.h"
#include <GL/freeglut.h>

#include <sstream>   // istringstream
#include <algorithm> // std::max
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

// =======================
// VISUAL DA PLACA
// =======================

/**
 * @brief Desenha uma corda simples como um cilindro.
 * @param x A coordenada x do topo da corda.
 * @param yTop A coordenada y do topo da corda.
 * @param z A coordenada z do topo da corda.
 * @param length O comprimento da corda.
 */
static void drawRope(float x, float yTop, float z, float length) {
    GLUquadric* q = gluNewQuadric();
    glColor3f(0.55f, 0.38f, 0.20f);
    glPushMatrix();
      glTranslatef(x, yTop - length*0.5f, z);
      glRotatef(90, 1,0,0);
      gluCylinder(q, 0.03, 0.03, length, 10, 1);
    glPopMatrix();
    gluDeleteQuadric(q);
}

/**
 * @brief Desenha a placa de madeira com ripas e cordas.
 *
 * A placa é composta por múltiplas tábuas horizontais com uma leve variação de cor.
 * É desenhada com as cordas para pendurar.
 *
 * @param pos A posição do centro da placa.
 * @param width A largura total da placa.
 * @param height A altura total da placa.
 * @param thick A espessura da placa.
 */
static void drawWoodBoard(const Vector3f& pos, float width=2.9f, float height=1.25f, float thick=0.10f) {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    // cordas
    drawRope(-width*0.35f, 2.3f, 0.0f, 0.8f);
    drawRope( width*0.35f, 2.3f, 0.0f, 0.8f);

    // tábuas
    int boards = 5;
    float h = height / boards;
    for (int i=0;i<boards;i++){
        float y = 1.5f + ( (boards-1)/2.0f - i ) * h; // centro de cada ripa
        float t = 0.78f + 0.05f*std::sin(i*1.7f);
        glColor3f(0.55f*t, 0.33f*t, 0.18f*t);
        glPushMatrix();
          glTranslatef(0.0f, y, 0.0f);
          glScalef(width, h*0.95f, thick);
          glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();
}

// ===============
// HELPERS de TEXTO
// ===============

/**
 * @brief Calcula a largura de uma string na fonte GLUT_STROKE_ROMAN.
 * @param s A string a ser medida.
 * @return A largura da string em unidades de stroke.
 */
static int strokeWidth(const std::string& s) {
    int w = 0; for (unsigned char c : s) w += glutStrokeWidth(GLUT_STROKE_ROMAN, c); return w;
}

/**
 * @brief Quebra uma string de texto em linhas, respeitando uma largura máxima.
 *
 * A função quebra o texto em linhas para que caiba em uma largura predefinida,
 * priorizando quebras entre palavras, mas também quebrando palavras longas
 * se necessário.
 *
 * @param text O texto a ser quebrado.
 * @param maxWidthStroke A largura máxima da linha em unidades de stroke.
 * @return Um vetor de strings, onde cada string é uma linha de texto.
 */
static std::vector<std::string> wrapStroke(const std::string& text, int maxWidthStroke) {
    std::istringstream iss(text);
    std::string word, line;
    std::vector<std::string> out;
    auto fits = [&](const std::string& s){ return strokeWidth(s) <= maxWidthStroke; };

    while (iss >> word) {
        std::string t = line.empty()? word : (line + " " + word);
        if (fits(t)) line = t;
        else {
            if (!line.empty()) out.push_back(line);
            if (!fits(word)) { // palavra maior que a linha -> quebra bruta
                std::string cut;
                for (char c : word) {
                    std::string tt = cut + c;
                    if (!fits(tt)) { out.push_back(cut); cut.clear(); }
                    cut += c;
                }
                line = cut;
            } else {
                line = word;
            }
        }
    }
    if (!line.empty()) out.push_back(line);
    return out;
}

/**
 * @brief Desenha uma única linha de texto centralizada.
 *
 * Desenha o texto com a fonte GLUT_STROKE_ROMAN e aplica um efeito de
 * "negrito" desenhando a linha múltiplas vezes com um pequeno deslocamento.
 *
 * @param s A string a ser desenhada.
 * @param cx A coordenada x do centro horizontal.
 * @param cy A coordenada y do centro vertical.
 * @param cz A coordenada z.
 * @param scale O fator de escala do texto.
 * @param rgb Um array de 3 floats para a cor do texto.
 */
static void drawStrokeCenteredLine(const std::string& s,
                                   float cx, float cy, float cz,
                                   float scale, const float rgb[3]) {
    glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_LINE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // cor e espessura do traço
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glLineWidth(1.5f);

    // centraliza horizontalmente
    int w = 0; for (unsigned char c : s) w += glutStrokeWidth(GLUT_STROKE_ROMAN, c);
    float x = cx - (w * 0.5f * scale);
    float z = cz + 0.065f; // à frente da madeira

    // desenha 3 passadas com micro-offset para reforçar o contraste
    const float off = 0.0007f;
    for (int pass = 0; pass < 3; ++pass) {
        float ox = (pass == 1 ? off : 0.0f);
        float oy = (pass == 2 ? off : 0.0f);
        glPushMatrix();
          glTranslatef(x + ox, cy + oy, z);
          glScalef(scale, scale, scale);
          for (unsigned char c : s) glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        glPopMatrix();
    }

    glPopAttrib();
}


// =======================
// Sign (impl.)
// =======================

/**
 * @brief Construtor da classe Sign.
 * @param pos A posição da placa.
 * @param text A string de texto a ser exibida.
 */
Sign::Sign(const Vector3f& pos, const std::string& text)
: InteractableObject(pos), _pos(pos), _text(text) {}

/**
 * @brief Renderiza a placa e o texto na tela.
 *
 * O método desenha a base de madeira e, em seguida, quebra e desenha o texto
 * de forma que ele se ajuste à placa.
 */
void Sign::render() {
    // dimensões da placa
    const float BOARD_W = 3.0f;
    const float BOARD_H = 1.30f;
    const float THICK   = 0.10f;
    const int   BOARDS  = 5;

    // desenha a madeira
    drawWoodBoard(_pos, BOARD_W, BOARD_H, THICK);

    // centros das 5 tábuas em coordenadas de mundo
    std::vector<float> yCenter(BOARDS);
    {
        const float yMid = _pos.y + 1.5f;
        const float step = BOARD_H / BOARDS;
        for (int i = 0; i < BOARDS; ++i) {
            float top    =  (BOARD_H*0.5f) - i*step;
            float bottom =  top - step;
            float yLocalCenter = (top + bottom) * 0.5f;
            yCenter[i] = yMid + yLocalCenter;
        }
    }

    // área útil horizontal (margem dentro da madeira)
    const float MARGIN_X = 0.30f;
    const float usableW  = BOARD_W - 2.0f * MARGIN_X;

    // base scale (tamanho “confortável”); reduzimos se precisar
    float baseScale = 0.0026f;

    // wrap visando caber 1 linha por tábua
    int maxStrokeForWrap = std::max(50, int(usableW / baseScale));
    auto wrapped = wrapStroke(_text, maxStrokeForWrap);

    // se sobrou mais que 5 linhas, re-tentamos com scale menor até caber
    if ((int)wrapped.size() > BOARDS) {
        std::string all = wrapped[0];
        for (size_t i = 1; i < wrapped.size(); ++i) all += " " + wrapped[i];

        float s = baseScale;
        for (int tries = 0; tries < 8 && (int)wrapped.size() > BOARDS; ++tries) {
            s *= 0.85f; // -15%
            int mw = std::max(30, int(usableW / s));
            wrapped = wrapStroke(all, mw);
        }
        baseScale = std::max(0.0016f, s);
    }

    // auto-fit final: garante que a maior linha caiba na largura útil
    int wmax = 1; for (auto &s : wrapped) wmax = std::max(wmax, strokeWidth(s));
    float scaleFit     = usableW / float(wmax);
    float finalScale = std::min(baseScale, scaleFit);

    // cor do texto
    const float rgb[3] = {0.07f, 0.06f, 0.05f};

    // desenha centralizado: usa as tábuas do MEIO quando houver < 5 linhas
    const int linesToDraw = std::min((int)wrapped.size(), BOARDS);
    int startBoard = (BOARDS - linesToDraw) / 2;
    const float TOP_NUDGE = 0.030f;

    for (int i = 0; i < linesToDraw; ++i) {
        int boardIndex = startBoard + i;

        // se esta for a PRIMEIRA linha do parágrafo, desce um pouco
        float y = yCenter[boardIndex];
        if (i == 0) y -= TOP_NUDGE;

        drawStrokeCenteredLine(
            wrapped[i],
            _pos.x,
            y,
            _pos.z,
            finalScale,
            rgb
        );
    }
}
