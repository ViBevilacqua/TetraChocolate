#pragma once
#include "Grid.h"
#include <stdlib.h> 
#include "milk_chocolate.h"
#include "Model.h"

using namespace std;
 
tuple<int, int> Grid::xzToId(float x, float z) const
{
    //x and y are positions
    //convert x and y in grid indices
    int idx, idz;

    if (x > 0)
        idx = int(x / 2) + 4;
    else
        idx = 3 - int(abs(x) / 2);

    if (z > 0)
        idz = int(z / 2) + 6;
    else
        idz = 6 - int(abs(z) / 2);

    return make_tuple(idx, idz);
}

int Grid::addBlock(Block* chocoBlock)
{
    int idx, idz;
    tie(idx, idz) = xzToId(chocoBlock->get_x(), chocoBlock->get_z());

    if (!blockMat[idz][idx]) {
        blockMat[idz][idx] = chocoBlock;
    }
    else
    {
        cout << "The Block (" << idz << ", " << idx << ") already exists" << endl;
        cout << "Premi un tasto per uscire...";
        cin >> idx;
        exit(-1);
    }
    return idz;
}

bool Grid::isFullRow(int id) const
{
    for (int i = 0; i < 8; i++)
        if(!blockMat[id][i])
            return false;
    return true;
}

Grid::Grid(float left, float right, float bottom, Model* choco)
{
    leftEdge = left;
    rightEdge = right;
    bottomEdge = bottom;
    blockMat.resize(13, vector<Block*>(8, nullptr));

    //blockMat[8][5] = new Milk_chocolate(choco, 3, 4);
}

Grid::~Grid()
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 8; j++)
            if (blockMat[i][j])
                delete blockMat[i][j];
}

bool Grid::isEmptyPosition(float x, float z) const
{
    int idx, idz;
    tie(idx, idz) = xzToId(x, z);
    
    if (idz < 0)
        return true;

    //return false if block exist or indeces are in underflow/overflow
    if (idx < 0 || idx > 7 || idz > 12 || blockMat[idz][idx])
    {
        //cout << "[isEmptyPosition] blockMat[" << idz << "][" << idx << "] is not empty" << endl;
        return false;
    }
    else
    {
        //cout << "[isEmptyPosition] blockMat[" << idz << "][" << idx << "]: " << blockMat[idz][idx] << endl;
        return true;
    }
}

float Grid::get_leftEdge() const
{
    return leftEdge;
}

float Grid::get_rightEdge() const
{
    return rightEdge;
}

float Grid::get_bottomEdge() const
{
    return bottomEdge;
}

int Grid::pushBlock(Block* chocoBlock)
{
    //cout << "[pushBlock] Insert block chocoBlock->get_z(): " << chocoBlock->get_z() << endl;
    int idRow = addBlock(chocoBlock);
    if (isFullRow(idRow))
        return idRow;
    else
        return -1;
}

int Grid::clearRow(int idRow)
{
    vector <int> chocoType;
    int count = 0;
    //delete blocks in idRow

    for (int i = 0; i < 8; i++) {
        if (find(chocoType.begin(), chocoType.end(), blockMat[idRow][i]->get_chocoType()) == chocoType.end()) {
            chocoType.push_back(blockMat[idRow][i]->get_chocoType());
            count += 1;
        }
        //deallocate memory of old block
        delete blockMat[idRow][i];
        blockMat[idRow][i] = nullptr;

        //shifted other blocks
        for (int j = idRow - 1; j >= 0; j--) {
            if (blockMat[j][i]) {
                blockMat[j][i]->set_z(blockMat[j][i]->get_z() + 2);
                blockMat[j + 1][i] = blockMat[j][i];
                blockMat[j][i] = nullptr;
            }
        }
    }
    //Return bonus score
    switch (count) {
    case 1:
        return 1000;
    case 2:
        return 250;
    default:
        return 500;
     }
}

void Grid::drawBlockOnGrid() const
{

    bool drawFlag;
    for (int i = 12; i >= 0; i--)
    {
        drawFlag = false;
        for (int j = 7; j >= 0; j--)
        {
            if (blockMat[i][j])
            {
                drawFlag = true;
                //cout << "[drawBlockOnGrid] Disegno blocco i: " << i << " j: " << j << " blockMat[i][j]->get_z():" << blockMat[i][j]->get_z() << endl;
                blockMat[i][j]->drawBlock(false);
            }
        }
        if (!drawFlag)
            break;
    }
}

void Grid::drawBlockOnGrid(const vector <int> & fullRow) const
{
    bool drawFlag;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = 12; i >= 0; i--)
    {
        drawFlag = false;
        for (int j = 7; j >= 0; j--)
        {
            if (blockMat[i][j])
            {
                drawFlag = true;
                if (find(fullRow.begin(), fullRow.end(), i) != fullRow.end())
                    blockMat[i][j]->drawGoodBlock(0.5);
                else
                    blockMat[i][j]->drawBlock(false);
            }
        }
        if (!drawFlag)
            break;
    }
    glDisable(GL_BLEND);
   //glEnable(GL_DEPTH_TEST);
}

