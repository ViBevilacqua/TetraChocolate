
#include "GameManager.h"

void GameManager::drawGrid()
{ //draw blocks on the grid
    int bonus = 00;
    if (deleteRow) { //if the flag to delete a line is active
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - startLight);
        auto diff = duration.count();

        //Part animation to delete the line (intermittent transparency for a few milliseconds)
        if ((diff > 200000 && diff < 400000) || (diff > 600000 && diff < 800000))
            gridTable->drawBlockOnGrid();
        else
            if (diff < 200000 || diff < 600000)
                gridTable->drawBlockOnGrid(fullRow);
            else
            { //after the animation permanently delete the line
                deleteRow = false;
                //for each line to be deleted
                for (int i = fullRow.size() - 1; i >= 0; i--)
                {
                    bonus = gridTable->clearRow(fullRow[i]);
                    score += bonus + int(round(bonus * speed)); //increases the score
                    fullRow.pop_back();
                }
                rowSound->setIsPaused(true);
            }
    }
    else //otherwise draws the blocks on the grid normally.
        gridTable->drawBlockOnGrid();
}

void GameManager::drawScore()
{
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glRasterPos3f(-9.0, 18.45, -28.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)("SCORE: " + to_string(score)).c_str());
    glPopMatrix();
}

void GameManager::drawMinutes()
{
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glRasterPos3f(4.0, 18.45, -28.0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, (char*)("MINUTES: " + to_string(minutesOfPlay)).c_str());
    glPopMatrix();
}

void GameManager::drawInfoBar()
{
    drawScore();
    drawMinutes();

    glPushMatrix();
    glTranslatef(0, 18.5, -29);
    glRotatef(-38, 1, 0, 0);
    glColor4f(0.13333, 0.5764705882352941, 0.803921568627451, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -0.7, 0.0);
    glVertex3f(10.0, -0.7, 0.0);
    glVertex3f(10.0, 0.7, 0.0);
    glVertex3f(-10.0, 0.7, 0.0);
    glEnd();
    glPopMatrix();
}

void GameManager::drawSteel()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-40.0, -0.01, -28.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(40.0, -0.01, -28.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(40.0, 3.0, -30.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-40.0, 3.0, -30.0);
    glEnd();
    glPopMatrix();
}

void GameManager::drawCanvas()
{
    //Draw canvas
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(9.0, 0.0, -18.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(19.0, 0.0, -18.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(19.0, 0.0, -27.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(9.0, 0.0, -27.0);
    glEnd();
    glPopMatrix();
}

void GameManager::drawBase()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-40.0, -0.01, 30.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(40.0, -0.1, 30.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(40.0, -0.01, -30.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-40.0, -0.01, -30.0);
    glEnd();
    glPopMatrix();
}

void GameManager::drawWall()
{
    //Draw wall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-40.0, -0.1, -30.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(40.0, -0.1, -30.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(40.0, 50.0, -30.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-40.0, 50.0, -30.0);
    glEnd();
    glPopMatrix();
}

void GameManager::drawPostIt(int textId, float coordX, float coordY)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture[textId]);
    glPushMatrix();
    glRotatef(0.7, 1, 0, 0);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(coordX, coordY, -29.9);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(coordX + 6.0, coordY, -29.9);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(coordX + 6.0, coordY + 6, -29.9);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(coordX, coordY + 6, -29.9);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

void GameManager::drawScene()
{
    float coordX[6] = { -13.0, 7.0, -3.0, -13.0,  7.0, -3.0 };
    float coordY[6] = { 11.0, 11.0, 4.0,  4.0, 4.0, 11.1 };

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //draw the chocolate blocks already on the grid.
    drawGrid();

    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //draw information (score and minutes) at the top.
    drawInfoBar();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    //draws the tetromino which is moving on the cutting board.
    tetra[tetraId]->drawObject(true);
    //draws the next tetromino in the top right-hand corner in the 'next' position.
    tetra[(tetraId + 1) % 2]->drawAsNext();

    glPushMatrix();//design the chopping board with the wood texture
    cuttingBoard.render();
    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);



    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);


    //design background elements
    //the central steel bar
    drawSteel();
    //the cloth handkerchief with next written on it.
    drawCanvas();
    //draw the base of with marble textures
    drawBase();
    //the brick-textured wall
    drawWall();

    //draw Sticky Notes for instructions
    for (int i = 0; i < 5; i++)
        drawPostIt(i + 4, coordX[i], coordY[i]);

    if (audio == 0.0)
        drawPostIt(10, coordX[5], coordY[5]);
    else
        drawPostIt(9, coordX[5], coordY[5]);

    glPopMatrix();
}

void GameManager::generateTetra(int i)
{ //pseudo-randomly generate the next tetromino
    int tetraShape = rand() % 7;
    //polymorphism
    switch (tetraShape)
    {
    case 0:
        tetra[i] = new Tetra_I(&chocolate);
        break;
    case 1:
        tetra[i] = new Tetra_J(&chocolate);
        break;
    case 2:
        tetra[i] = new Tetra_L(&chocolate);
        break;
    case 3:
        tetra[i] = new Tetra_O(&chocolate);
        break;
    case 4:
        tetra[i] = new Tetra_S(&chocolate);
        break;
    case 5:
        tetra[i] = new Tetra_T(&chocolate);
        break;
    case 6:
        tetra[i] = new Tetra_Z(&chocolate);
        break;
    }
}

bool GameManager::updateGameScene(int value) {
    //Method called every TOTAL milliseconds to make the tetromino move
    //if a line is being deleted the next tetromino must wait before translating.
    if (!deleteRow) {
        //if no line is being deleted then the tetromino can move.
        int translationResult;
        translationResult = tetra[tetraId]->moveDown(*gridTable);  //update coordinates

        //if translation is not possible (-1 or 0)
        if (translationResult != 1 && !lastChance) {
            //last possibility is activated
            lastChance = true;
            interval = 200;
        }
        else
        {
            if (lastChance)
            {
                //deactivates the last possibility
                lastChance = false;
                interval = 400;
            }

            if (translationResult == 0) //end of life of tetromino 
            {
                int idRow;
                for (int i = 0; i < 4; i++) {
                    //insert tetramino blocks on the grid
                    idRow = gridTable->pushBlock(tetra[tetraId]->get_chocoBlock(i));
                    //If a line is full, returns the corresponding line index.
                    if (idRow != -1)
                    {
                        fullRow.push_back(idRow);
                        deleteRow = true;
                        rowSound->setPlayPosition(0);
                        rowSound->setIsPaused(false);
                    }
                }
                sort(fullRow.begin(), fullRow.end(), greater<int>());

                //Destroys the old tetramine 'container' that is no longer needed
                delete tetra[tetraId];

                //Generate a new tetramino by placing it at the top right of the scene (next).
                generateTetra(tetraId);

                //The other tetramino that was waiting in the 'next' position
                //The other tetramino that was waiting at the 'next' position is selected and prepared to do the descent.
                tetraId = (tetraId + 1) % 2;
                tetra[tetraId]->shapeReadyToStart();
                startLight = high_resolution_clock::now();
            }
            else
                if (translationResult == -1) //game over
                {
                    char a;
                    cout << "GAME OVER" << endl;
                    gameOver = true;
                    return false;
                }
        }
    }
    if (!gameOver && value == 0)
    {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<minutes>(stop - speedTime);
        minutesOfPlay = duration.count();
        speed = 0.05 * minutesOfPlay; //increases game speed by 5% every minute
        inGameSound->setPlaybackSpeed(1.0 + speed);
        interval -= unsigned int(round(interval * speed));
    }
    return true;
}

void GameManager::clear() {
    //delete and empty game objects.
    engine->drop();
    rowEngine->drop();
    delete gridTable;
    engine = nullptr;
    rowEngine = nullptr;
    gridTable = nullptr;
    delete tetra[0];
    delete tetra[1];
    tetra.clear();
}

void GameManager::reset() {
    //resets the game variables for the next game.
    deleteRow = false;
    tetra.resize(2, nullptr);
    startLight = high_resolution_clock::now();
    gridTable = new Grid(-8, 8, 12, &chocolate);
    score = 0;
    speed = 0.0f;
    engine = createIrrKlangDevice();
    rowEngine = createIrrKlangDevice();
    inGameSound = engine->play2D("audio/soundtrack.mp3", true, true, true);
    inGameSound->setVolume(0.05);
    rowSound = rowEngine->play2D("audio/fullRowSound.mp3", false, true, true);
    rowSound->setVolume(0.10);
    minutesOfPlay = 0;
    tetraId = 0;
    audio = 1.0;
    lastChance = false;
    gameOver = false;
    interval = 400;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    generateTetra(0);
    generateTetra(1);
    tetra[tetraId]->shapeReadyToStart();

    speedTime = high_resolution_clock::now();
}

GameManager::GameManager()
{
    //Initialization.
    engine = nullptr;
    rowEngine = nullptr;
    gridTable = nullptr;

    //Load 3d models
    cuttingBoard.load("obj_models/", "board.obj", "board.mtl");
    chocolate.load("obj_models/", "choco.obj");

    //Load textures
    texture.resize(11, 0);
    GLuint previous_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&previous_texture);
    string fileName[11] = { "base.jpg", "wall.jpg", "steel.jpg", "canvas.jpg",
        "Move_Left.png", "Move_Right.png", "Move_Down.png",
        "Rotate_Counterclockwise.png", "Rotate_Clockwise.png", "Mute.png", "Turn_on.png" };
    for (int i = 0; i < 4; i++)
        loadTexture(texture[i], ("texture/" + fileName[i]).c_str(), SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    for (int i = 4; i < 11; i++)
        loadTexture(texture[i], ("texture/" + fileName[i]).c_str(), SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, previous_texture);

    //set the seed
    srand((unsigned)time(NULL));
}

void GameManager::keyboard(unsigned char key) {
    if (!gameOver && !deleteRow)
    {
        switch (key)
        {
        case 'A':
        case 'a': //rotate to the left (anti-clockwise)
            if (tetra[tetraId]->rotateObject(false, *gridTable))
                glutPostRedisplay();
            break;

        case 'D':
        case 'd': //rotate to the right (clockwise)
            if (tetra[tetraId]->rotateObject(true, *gridTable))
                glutPostRedisplay();
            break;

        default:
            break;
        }
    }
}

bool GameManager::keyboard_special(int key)
{
    if (!gameOver && !deleteRow)
    {
        switch (key)
        {
        case GLUT_KEY_DOWN: //get down fast
            return updateGameScene(1);
            break;

        case GLUT_KEY_LEFT: //turn left
            if (tetra[tetraId]->horizontalTranslation(-2.0f, *gridTable))
                glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT: //translate to the right
            if (tetra[tetraId]->horizontalTranslation(2.0f, *gridTable))
                glutPostRedisplay();
            break;

        case GLUT_KEY_UP: // Deactivate/Activate audio
            if (audio == 00)
                audio = 1.0;
            else
                audio = 0.0;
            inGameSound->setVolume(0.05 * audio);
            rowSound->setVolume(0.1 * audio);
            break;
        }
    }
    return true;
}

unsigned int GameManager::getTime() {
    return interval - unsigned int(round(interval * speed));
}

void GameManager::setPlaySound()
{
    inGameSound->setIsPaused(false);
}

int GameManager::get_score()
{
    return score;
}

GameManager::~GameManager()
{
    if(engine)
        engine->drop();
    if(rowEngine)
        rowEngine->drop();
    if(gridTable)
        delete gridTable;
}
