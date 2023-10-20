#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include <string>
#include <vector>
#include "utils.h"

using namespace std;

class MenuManager
{
	vector <unsigned int> texture;

public:
	MenuManager();
	~MenuManager() = default;
	void drawMenu(bool picking);
};

