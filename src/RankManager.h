#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

class RankManager
{
	int position;
	int playerScore;
	int listLen;
	char date_string[18];
	vector<vector<string>> scoreList;
	vector<string> row;
	vector <unsigned int> texture;
	string nickname;
	bool fullName;

	void drawBackground();
	void drawScore(float coordY, int id, int rank);
	void saveFile();
public:
	RankManager();
	~RankManager() = default;
	void loadFile();
	void findPosition(int score);
	void drawSaveScore(bool picking);
	void keyboard(unsigned char key);
	void drawRanking(bool picking);
};

