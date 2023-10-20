#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include "soil.h"

void writeBitmapString(void* font, char* string);
void loadTexture(unsigned int& textureId, const char* fileName, unsigned int flags);