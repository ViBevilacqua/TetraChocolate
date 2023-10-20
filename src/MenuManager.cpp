#include "MenuManager.h"


MenuManager::MenuManager()
{
	texture.resize(5, 0);
	GLuint previous_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&previous_texture);
	loadTexture(texture[0], "texture/menuBackground.jpg", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	loadTexture(texture[1], "texture/title.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	loadTexture(texture[2], "texture/PlayButton.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	loadTexture(texture[3], "texture/RankingButton.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	loadTexture(texture[4], "texture/exitButton.png", SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, previous_texture);
}

void MenuManager::drawMenu(bool picking)
{
	if(picking)//disable textures, lights, transparency and draw only the colour masks of the buttons for picking.
	{
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_LIGHTING);

		//draw play button
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor4f(0.807843137254902, 0.603921568627451, 0.2274509803921569, 1.0); //picking mask color (gold yellow).
				glVertex3f(-2.5, -0.4, -13.0);
				glVertex3f(2.5, -0.4, -13.0);
				glVertex3f(2.5, 1.4, -13.0);
				glVertex3f(-2.5, 1.4, -13.0);
			glEnd();
		glPopMatrix();

		//draw rancking button
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor4f(0.4117647058823529, 0.0, 0.6784313725490196, 1.0); //picking mask color (violet).
				glVertex3f(-2.5, -3.2, -13.0);
				glVertex3f(2.5, -3.2, -13.0);
				glVertex3f(2.5, -1.4, -13.0);
				glVertex3f(-2.5, -1.4, -13.0);
			glEnd();
		glPopMatrix();

		//draw exit button
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor4f(0.9490196078431373, 0.7686274509803922, 0.8666666666666667, 1.0); //picking mask color (pink).
				glVertex3f(-2.5, -5.8, -13.0);
				glVertex3f(2.5, -5.8, -13.0);
				glVertex3f(2.5, -4.2, -13.0);
				glVertex3f(-2.5, -4.2, -13.0);
			glEnd();
		glPopMatrix();
	}
	else {//altrimenti disegna tutta la scena completa
		glEnable(GL_TEXTURE_2D);

		//draw background
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

		glEnable(GL_BLEND);
		//draw title
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
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

		//draw play button
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_POLYGON);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.5, -0.4, -13.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.5, -0.4, -13.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.5, 1.4, -13.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.5, 1.4, -13.0);
		glEnd();
		glPopMatrix();

		//draw rancking button
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_POLYGON);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.5, -3.2, -13.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.5, -3.2, -13.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.5, -1.4, -13.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.5, -1.4, -13.0);
		glEnd();
		glPopMatrix();

		//draw exit button
		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_POLYGON);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-2.5, -5.8, -13.0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(2.5, -5.8, -13.0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(2.5, -4.2, -13.0);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-2.5, -4.2, -13.0);
		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}
