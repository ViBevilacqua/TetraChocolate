#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#endif
#include "GameManager.h"
#include "RankManager.h"
#include "MenuManager.h"

#define COD_MENU 4282927598
#define COD_PLAY 4282030798
#define COD_RANKING 4289527913
#define COD_EXIT 4292723954

using namespace std;

static struct {
    int height, width;
} monitorSize;
static const float lightPosition[] = { 0.0f, 180.0f, -14.0f, 1.0f };
GameManager* game = nullptr;
RankManager* ranking = nullptr;
MenuManager* menu = nullptr;
bool isInGame = false;
bool isInMenu = false;
bool isInSaveScore = false;
bool ready = false;
static bool picking = false; //variable for color picking
static GLint mouseClickX = 0, mouseClickY = 0; //mouse coordinates


GLuint GetRGB(int x, int y) {
    GLint viewport[4];
    GLfloat winX, winY;
    GLuint color;

    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (GLfloat)x;
    winY = (GLfloat)viewport[3] - (GLfloat)y; // height - y  

    glReadPixels(GLint(winX), GLint(winY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
    return color;
}

void mouseClick(GLint button, GLint state, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //Activate colour picking in all scenes except during a game and initial loading.
        if (!isInGame && ready) { 
            mouseClickX = x;
            mouseClickY = y;
            picking = true;
        }
    }
}

void endGame()
{
    game->clear();
    ranking->loadFile();
    ranking->findPosition(game->get_score());
    isInSaveScore = true;
}

void updateScene(int value)
{
    if (isInGame)
    {
        isInGame = game->updateGameScene(value);
        //If the game continues, it re-arms the callback.
        if (isInGame)
            glutTimerFunc(game->getTime(), updateScene, 0);
        else //otherwise activates the score screen
            endGame();
    }

}

void playSound(int val)
{
    game->setPlaySound();
}

void manageScenes() {
    //Pincking is not needed during game play.
    //Serves only in the menu scenes, saveScore and Ranking.
    if (!isInGame)
    {
        GLuint color = GetRGB(mouseClickX, mouseClickY);
        //cout << "Color picked " << "0x" << color << ";" << endl;
        picking = false;
        switch (color)
        {
        case COD_MENU:
            cout << "Return to menu" << endl;
            isInSaveScore = false;
            isInMenu = true;
            isInGame = false;
            break;

        case COD_PLAY:
            isInMenu = false;
            isInSaveScore = false;
            isInGame = true;
            game->reset();
            glutTimerFunc(game->getTime(), updateScene, 0); //automatic tetramino descent
            glutTimerFunc(1000, playSound, 0); //in one second activates the game sound
            break;

        case COD_RANKING:
            isInMenu = false;
            isInSaveScore = false;
            isInGame = false;
            ranking->loadFile();
            break;

        case COD_EXIT:
            delete game;
            delete ranking;
            delete menu;
            cout << "EXIT" << endl;
            exit(0);

        default:
            break;
        }
    }
}

// OpenGL window reshape routine
void resize(int w, int h)
{
    glutReshapeWindow(int(monitorSize.width / 3), monitorSize.height - int(monitorSize.height * 0.06));
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 80.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    if (isInGame)
        game->keyboard(key);
    else
        if(isInSaveScore)
            ranking->keyboard(key);

    if (key == 27) //Esc
    {
        delete game;
        delete ranking;
        delete menu;
        cout << "EXIT" << endl;
        exit(0);
    }
}

void keyboard_special(int key, int x, int y) {
    if (isInGame)
    {
        isInGame = game->keyboard_special(key);
        if (!isInGame)
            endGame();
    }
}

void position(int x, int y)
{ //force window position
    if (y > 2)
        glutPositionWindow(x, 0);
    if (x < 0)
        glutPositionWindow(0, 0);
    if (x > (monitorSize.width /3)*2)
        glutPositionWindow(int(monitorSize.width /3) + int(monitorSize.width /3), 0);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    //if is in game
    if (isInGame)
    {
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        gluLookAt(0.0, 31.0, 26.0, 0.0, 0.0, -9.0, 0.0, 1.0, 0.0);
        game->drawScene();
    }else
        if (isInMenu)
        {
            //drawMenu
            menu->drawMenu(picking);
        }else
            if (isInSaveScore)
            {
                //drawSaveScore
                ranking->drawSaveScore(picking);
            }
            else //is in ranking scene
            {
                //draw ranking
                ranking->drawRanking(picking);
            }
    if (picking)
        manageScenes();
    else
        glutSwapBuffers(); //swap the buffers
}

void readyFunc(int val) {
    ready = true;
}

// Main routine
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    monitorSize.width = glutGet(GLUT_SCREEN_WIDTH);
    monitorSize.height = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(int(monitorSize.width /3), int(monitorSize.height -(monitorSize.height*0.06)));
    glutInitWindowPosition(monitorSize.width / 3, 0);
    glutCreateWindow("Tetra Chocolate");


    //Initialising and loading game objects.
    //Contain readings from files, 3d models and textures.
    menu = new MenuManager();
    game = new GameManager();
    ranking = new RankManager();
    isInMenu = true;

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutPositionFunc(position);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(keyboard_special);

    //To avoid activating colour picking unintentionally during initial loading (white screen)
    //Colour picking can only be activated half a second after completion of loading (of models and textures).
    glutTimerFunc(500, readyFunc, 0);

    glutMainLoop();
    return 0;
}