//
// Created by michal on 8.12.2016.
//

#ifndef PPGSO_TEXT_H
#define PPGSO_TEXT_H
#include <shader.h>
#include <map>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class texts {
    GLuint vao;
    GLuint vbo;
    ShaderPtr program;
    std::map<GLchar, Character> characters;
    std::string fontname = "FreeSansBold.ttf";
    std::string words;
    int init_resources();

public:
    texts(ShaderPtr program,std::string text);
    void render(float x,float y,float scale);
    void setWords(const std::string &words);
};
typedef std::shared_ptr<texts> TextPtr;


#endif //PPGSO_TEXT_H
