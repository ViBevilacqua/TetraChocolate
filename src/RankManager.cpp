#include "RankManager.h"


void RankManager::loadFile()
{
	string line, word;
	scoreList.clear();

	//open file in read mode
	fstream file("rank.csv", ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();
			stringstream str(line);
			while (getline(str, word, ';'))
				row.push_back(word);
			scoreList.push_back(row);
		}
	}
	else
	{
		cout << "Create file\n";
		//create a file if not exist
		file.open("rank.csv", ios::out);
		file << flush;
		file.close();
	}
	listLen = scoreList.size();
}

void RankManager::saveFile()
{
	ofstream scorFile("rank.csv", ofstream::out | ofstream::trunc);

	int cont = 0;
	int i = 0;
	while (cont < scoreList.size() + 1)
	{
		if (cont == position)
			scorFile << nickname + ";" + to_string(playerScore) + ";" + string(date_string) + "\n";
		else {
			scorFile << scoreList[i][0] + ";" + scoreList[i][1] + ";" + scoreList[i][2] + "\n";
			i++;
		}
		cont++;
	}

	scorFile.close();
	cout << "data saving completed" << endl;
}


RankManager::RankManager()
{
	playerScore = 0;
	texture.resize(4, 0);
	GLuint previous_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&previous_texture);
	loadTexture(texture[0], "texture/rankBackground.jpg", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	loadTexture(texture[1], "texture/gameOver.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	loadTexture(texture[2], "texture/MenuButton.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	loadTexture(texture[3], "texture/top22.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, previous_texture);
	loadFile();
	position = scoreList.size(); //worst case last in ranking
}

void RankManager::findPosition(int score)
{
	//Check ranking
	for (int i = 0; i < scoreList.size(); i++)
		if (score >= stoi(scoreList[i][1])) {
			position = i;
			break;
		}
	playerScore = score;

	//Find date
	time_t curr_time;
	tm* curr_tm;
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 18, "%d/%m/%Y %H:%M", curr_tm);

}

void RankManager::drawBackground() {
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_POLYGON);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-10.0, -15.0, -15.0);

			glTexCoord2f(1.0, 0.0);
			glVertex3f(10.0, -15.0, -15.0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(10.0, 15, -15.0);

			glTexCoord2f(0.0, 1.0);
			glVertex3f(-10.0, 15.0, -15.0);
		glEnd();
	glPopMatrix();
}

void RankManager::drawScore(float coordY, int id, int rank)
{
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos3f(-2.3, coordY, -12.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)(to_string(rank) + ")").c_str());
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos3f(-1.7, coordY, -12.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)scoreList[id][0].c_str());
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos3f(-0.5, coordY, -12.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)scoreList[id][1].c_str());
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos3f(1.0, coordY, -12.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)scoreList[id][2].c_str());
	glPopMatrix();
}


void RankManager::drawSaveScore(bool picking)
{
	if (picking) { //disable textures, lights, transparency and draw only the colour mask of the pick button.
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);

		//menu button
		glPushMatrix();
			glBegin(GL_POLYGON);
			glColor4f(0.933333, 0.2862745098039216, 00.2823529411764706, 1.0); //picking mask color (coral red).
			glVertex3f(-2.0, -6.0, -14.0);
			glVertex3f(2.0, -6.0, -14.0);
			glVertex3f(2.0, -4.5, -14.0);
			glVertex3f(-2.0, -4.5, -14.0);
			glEnd();
		glPopMatrix();
	}
	else { //otherwise draw the whole scene
		glEnable(GL_TEXTURE_2D);
		//Draw background
		drawBackground();
	
		glEnable(GL_BLEND);
		//Draw game Over
		glPushMatrix();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			glBegin(GL_POLYGON);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-4.0, 0.0, -14.0);

				glTexCoord2f(1.0, 0.0);
				glVertex3f(4.0, 0.0, -14.0);

				glTexCoord2f(1.0, 1.0);
				glVertex3f(4.0, 8, -14.0);

				glTexCoord2f(0.0, 1.0);
				glVertex3f(-4.0, 8.0, -14.0);
			glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		//Draw position and score
		glPushMatrix();
			glColor4f(0.1, 0.1, 0.6, 1.0);
			glBegin(GL_POLYGON);
				glVertex3f(-4.0, -3.0, -13.0);
				glVertex3f(4.0, -3.0, -13.0);
				glVertex3f(4.0, 0.0, -13.0);
				glVertex3f(-4.0, 0.0, -13.0);
			glEnd();
		glPopMatrix();

		string info;
	
		glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos3f(-2.4, -0.5, -12.0);
			info = "Enter your nickname (3 characters) to save this score.";
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos3f(-1.8, -0.9, -12.0);
			info = "PLAYER";
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos3f(-0.45, -0.9, -12.0);
			info = "SCORE";
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos3f(1.5, -0.9, -12.0);
			info = "DATE";
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		//player score
		glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glRasterPos3f(-2.59, -1.6, -12.0);
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*) ("-> "+to_string(position+1) + ")").c_str());
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glRasterPos3f(-1.75, -1.61, -12.0);
			info = "____";
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glRasterPos3f(-1.7, -1.6, -12.0);
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)nickname.c_str());
		glPopMatrix();

		glPushMatrix();
		glColor4f(0.0, 1.0, 0.0, 1.0);
		glRasterPos3f(-0.5, -1.6, -12.0);
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)to_string(playerScore).c_str());
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glRasterPos3f(1.0, -1.6, -12.0);
			writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)&date_string[0]);
		glPopMatrix();

		if (position > 0)
			//draws the upper position
			drawScore(-1.3, position - 1, position);

		if(position < scoreList.size())
			//draws the lower position
			drawScore(-1.9, position, position + 2);

		//Draw Menu button
	
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_POLYGON);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-2.0, -6.0, -14.0);

				glTexCoord2f(1.0, 0.0);
				glVertex3f(2.0, -6.0, -14.0);

				glTexCoord2f(1.0, 1.0);
				glVertex3f(2.0, -4.5, -14.0);

				glTexCoord2f(0.0, 1.0);
				glVertex3f(-2.0, -4.5, -14.0);
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	}
}

void RankManager::keyboard(unsigned char key)
{
	if (nickname.size() < 3 && ((key >= 65 && key <= 90) || (key >= 97 && key <= 122))) {
		if (key >= 97 && key <= 122)
			key -= 32;
		nickname.push_back(key);
		if (nickname.size() == 3)
			saveFile();
	}
	else
		if ((key == 127 || key == 8) && nickname.size() != 0)
			nickname.pop_back();
}

void RankManager::drawRanking(bool picking)
{
	if (picking) {//disable textures, lights, transparency and draw only the colour mask of the pick button.
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor4f(0.933333, 0.2862745098039216, 00.2823529411764706, 1.0); //picking mask color (coral red).
				glVertex3f(-2.0, -5.5, -13.0);
				glVertex3f(2.0, -5.5, -13.0);
				glVertex3f(2.0, -4.0, -13.0);
				glVertex3f(-2.0, -4.0, -13.0);
			glEnd();
		glPopMatrix();
	}
	else {
		glEnable(GL_TEXTURE_2D);
		//Draw background
		drawBackground();

		glEnable(GL_BLEND);
		//Draw TOP 10
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_POLYGON);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-4.0, 2.0, -14.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(4.0, 2.0, -14.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(4.0, 10, -14.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-4.0, 10.0, -14.0);
		glEnd();
		glPopMatrix();

		//draw menu button
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_POLYGON);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.0, -5.5, -13.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.0, -5.5, -13.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.0, -4.0, -13.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.0, -4.0, -13.0);
		glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);

		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		//draw blue rectangle
		glPushMatrix();
		glColor4f(0.1, 0.1, 0.6, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(-4.0, -3.1, -13.0);
		glVertex3f(4.0, -3.1, -13.0);
		glVertex3f(4.0, 4.5, -13.0);
		glVertex3f(-4.0, 4.5, -13.0);
		glEnd();
		glPopMatrix();

		string info;
		glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glRasterPos3f(-1.8, 3.9, -12.0);
		info = "PLAYER";
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glRasterPos3f(-0.45, 3.9, -12.0);
		info = "SCORE";
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		glPushMatrix();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glRasterPos3f(1.5, 3.9, -12.0);
		info = "DATE";
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
		glPopMatrix();

		int cont = 0;
		while (cont < 22)
		{
			if (cont < listLen)
				drawScore(3.6 - (0.3 * cont), cont, cont + 1);
			else
			{
				glPushMatrix();
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRasterPos3f(-2.3, 3.6 - (0.3 * cont), -12.0);
				writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)(to_string(cont + 1) + ")").c_str());
				glPopMatrix();

				glPushMatrix();
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRasterPos3f(-1.7, 3.6 - (0.3 * cont), -12.0);
				info = "- - -";
				writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
				glPopMatrix();

				glPushMatrix();
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRasterPos3f(-0.5, 3.6 - (0.3 * cont), -12.0);
				info = "- - - -";
				writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
				glPopMatrix();

				glPushMatrix();
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glRasterPos3f(1.0, 3.6 - (0.3 * cont), -12.0);
				info = "- - - - - - - - -"; //12
				writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)info.c_str());
				glPopMatrix();
			}
			cont++;
		}

	}
}
