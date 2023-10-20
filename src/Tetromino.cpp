#include "Tetromino.h"
#include <cstdlib>
#include <cmath>

Tetromino::Tetromino()
{
    tetraPivotX = 0;
    tetraPivotZ = 0;

    //blockPivot initialization
    blockPivot.resize(2, vector<float>(4, 0.0));
}

void Tetromino::place_blocks(Model* choco)
{
    chocoList.resize(4, nullptr);

    //srand((unsigned)time(NULL));
    int chocoType = rand() % 3;

    for (int i = 0; i < 4; i++) {
        switch (chocoType) {
            case 0:
                chocoList[i] = new Milk_chocolate(choco, blockPivot[0][i] + tetraPivotX, blockPivot[1][i] + tetraPivotZ);
                break;

            case 1:
                chocoList[i] = new White_chocolate(choco, blockPivot[0][i] + tetraPivotX, blockPivot[1][i] + tetraPivotZ);
                break;

            default:
                chocoList[i] = new Dark_chocolate(choco, blockPivot[0][i] + tetraPivotX, blockPivot[1][i] + tetraPivotZ);
                break;
        }
    }
}

void Tetromino::set_tetraPivotX(float x)
{
    tetraPivotX = x;
}

void Tetromino::set_tetraPivotZ(float z)
{
    tetraPivotZ = z;
}

void Tetromino::set_min_z_position(int minz)
{
    min_z_position = minz;
}

void Tetromino::set_blocks()
{
    for (int i = 0; i < 4; i++) {
        chocoList[i]->set_x(blockPivot[0][i] + tetraPivotX);
        chocoList[i]->set_z(blockPivot[1][i] + tetraPivotZ);
    }
}

bool Tetromino::wallKick(float xT, const vector<vector<float>>& newPivot, const Grid& board)
{
    //Apply horizontal translation (left or right)

    //Checking if positions are not already filled
    for (int i = 0; i < 4; i++)
        if (!board.isEmptyPosition(newPivot[0][i] + tetraPivotX - xT, newPivot[1][i] + tetraPivotZ))
            return false;

    int minZ = 20;
    //Updating Coordinates
    for (int i = 0; i < 4; i++) {
        chocoList[i]->set_x(newPivot[0][i] + tetraPivotX - xT);
        chocoList[i]->set_z(newPivot[1][i] + tetraPivotZ);
        blockPivot[0][i] = newPivot[0][i];
        blockPivot[1][i] = newPivot[1][i];
        if (chocoList[i]->get_z() < minZ)
            minZ = chocoList[i]->get_z();
    }
    min_z_position = minZ;
    tetraPivotX -= xT;
    return true;
}

void Tetromino::drawObject(bool withBoundingBox) const
{
    for (int i = 0; i < 4; i++)
        chocoList[i]->drawBlock(withBoundingBox);
}

void Tetromino::drawAsNext() const
{
    for (int i = 0; i < 4; i++)
        chocoList[i]->drawBlock(0.02f);
}

bool Tetromino::horizontalTranslation(float xT, const Grid& board)
{
    //Applies a horizontal translation (left or right)
    //Returns true if it is executable, false otherwise.

    float edge, newX;

    if (xT < 0)
        edge = abs(board.get_leftEdge());
    else
        edge = board.get_rightEdge();

    for (int i = 0; i < 4; i++) {
        newX = chocoList[i]->get_x() + xT;

    	// check whether the new co-ordinates overlap the grid
        // or if the new co-ordinates overlap other grid blocks
        if (abs(newX) >= edge || !board.isEmptyPosition(newX, chocoList[i]->get_z()))
            return false;
    }

    for (int i = 0; i < 4; i++)
        chocoList[i]->set_x(chocoList[i]->get_x() + xT);

    tetraPivotX += xT;
    return true;
}

int Tetromino::moveDown(const Grid& board)
{
    //Translates (+2 units downwards) the tetramine to the imminent free position if it exists (safe position).
    
    //Returns 1 if the safe position exists (tetramino translates and continues its life cycle).
    //Returns 0 if the tetrahmin had already reached its last safe position (the tetrahmin stops and the next tetrahmin must be managed).
    //Returns -1 if the safe position is not even on the 'roof' which is already occupied (Game Over).
    int returnCode = 1;
    
    //tetraPivotZ += safe_z_position[0] - chocoList[0]->get_z();
    //min_z_position += safe_z_position[0] - chocoList[0]->get_z();
    //vector <int> temp_z_position = safe_z_position;

    //check whether each tetramino block overlaps with other blocks in the grid as a result of the hypothetical translation.
    //or whether the new co-ordinates touch the bottom or the top of the grid.
    for(int i = 0; i < 4; i++) {


        bool isEmpty = board.isEmptyPosition(chocoList[i]->get_x(), chocoList[i]->get_z() + 2);
        //cout << "[updatePosition->moveDown] safe_z_position[" << i << "]: " << safe_z_position[i] << endl;

        if (isEmpty)
            continue;
      
        //If the next cell is unavailable, two cases must be distinguished:
        //cout << "safe_z_position[" << i << "] is to be blocked: " << safe_z_position[i] << endl;

        //1] If the tetromino fails to move to the first row of the grid (roof) right away, then throw the game over code.
        if (min_z_position < -board.get_bottomEdge()) //Upper edge
           returnCode = -1;
        else
            //2] By exclusion the next cell is not available because it is already occupied or you are at the bottom of the grid, but the game continues.            if (returnCode > 0)
            returnCode = 0;
    }

    // If the checks are passed without any problems, then the tetramino coordinates are updated.
    if (returnCode == 1)
    {
        for (int i = 0; i < 4; i++)
            chocoList[i]->set_z(chocoList[i]->get_z() + 2);
        min_z_position += 2;
        tetraPivotZ += 2;
    }

    return returnCode;
}

bool Tetromino::rotateObject(bool isClockwiseRotation, const Grid& board)
{
    //Application of a 45 degree rotation clockwise or anticlockwise.
    //Return true if rotation is applicable, false otherwise.

    vector < vector <float>> newPivot(2, vector<float>(4, 0.0));
    int sin_a;
    float tMax = 0.0;

    if (isClockwiseRotation)
        sin_a = -1; //sin(-90 degree)
    else
        sin_a = 1; //sin(90 degree)

    for (int i = 0; i < 4; i++) {
        //Linear combination to update x = cos(alpha)x + sin(alpha)z
        //Angle alpha = 90 degrees or -90 degrees, so cos(alpha) is always 0
        //Simplicity x = sin(alpha)z
        newPivot[0][i] = sin_a * blockPivot[1][i];

        //linear combination to update z = -sin(alpha)x + cos(alpha)z = -sin(alpha)x
        newPivot[1][i] = -sin_a * blockPivot[0][i];
        float t = 0.0;
        //check if new co-ordinates cross the side borders
        if ((newPivot[0][i] + tetraPivotX) < board.get_leftEdge())
            t = newPivot[0][i] + tetraPivotX - (board.get_leftEdge() + 1);
        else
            if((newPivot[0][i] + tetraPivotX) > board.get_rightEdge())
                t = newPivot[0][i] + tetraPivotX - (board.get_rightEdge() - 1);

        //if the rotation makes you go over the edge, try the 'wall kick' technique
        if (abs(t) > abs(tMax))
            tMax = t;
    }

    //Upgrade positions due to rotation.
    return wallKick(tMax, newPivot, board);
}

Block* Tetromino::get_chocoBlock(int ind) const
{
    if (ind < 4)
        return chocoList[ind];
    else {
        cout << "chocoList Overflow" << endl;
        exit(-1);
    }
}
