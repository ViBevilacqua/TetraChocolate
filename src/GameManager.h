#pragma once
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "model.h"
#include "grid.h"
#include "Tetromino.h"
#include "Tetra_O.h"
#include "Tetra_S.h"
#include "Tetra_J.h"
#include "Tetra_I.h"
#include "Tetra_L.h"
#include "Tetra_T.h"
#include "Tetra_Z.h"
#include <irrKlang.h>
#include <chrono>
#include <string>
#include "soil.h"
#include "utils.h"

using namespace objloader;
using namespace std;
using namespace irrklang;
using namespace std::chrono;

class GameManager
{
	bool deleteRow;
	vector <unsigned int> texture; // Array of texture indices.
	vector <Tetromino*> tetra;
	high_resolution_clock::time_point startLight;
	high_resolution_clock::time_point speedTime;
	Model cuttingBoard;
	Model chocolate;
	Grid* gridTable;
	ISoundEngine* engine;
	ISound* inGameSound;
	ISoundEngine* rowEngine;
	ISound* rowSound;
	vector <int> fullRow;
	int score;
	float speed;
	int minutesOfPlay;
	int tetraId;
	float audio;
	bool lastChance;
	bool gameOver;
	unsigned int interval;

	void drawGrid();
	void drawScore();
	void drawMinutes();
	void drawInfoBar();
	void drawSteel();
	void drawCanvas();
	void drawBase();
	void drawWall();
	void drawPostIt(int textId, float coordX, float coordY);
	void generateTetra(int i);

public:
	GameManager();
	~GameManager();

	void drawScene();
	bool updateGameScene(int value);
	bool keyboard_special(int key);
	void keyboard(unsigned char key);
	unsigned int getTime();
	int get_score();
	void setPlaySound();
	void clear();
	void reset();
};

