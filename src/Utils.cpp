#pragma once
#include "utils.h"

void writeBitmapString(void* font, char* string)
{
    char* c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void loadTexture(unsigned int& textureId, const char* fileName, unsigned int flags)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    SOIL_load_OGL_texture(
        fileName,
        SOIL_LOAD_AUTO,
        textureId,
        flags
    );
}