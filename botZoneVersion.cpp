//
//  main.cpp
//  AmazonsProject_Botzone_NewStructure
//
//  Created by 장준우 on 27/12/2018.
//  Copyright © 2018 Joonwoo Percy Jang. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <cmath>
#include <cstring>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define GRIDSIZE 8
#define OBSTACLE 2
#define EMPTY 0
#define grid_black 1
#define grid_white -1

using namespace std;
int currBotColor; // Current color of the bot（1 = black ，-1 = white）
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };

struct Grid{
    int xPos;         //Variable to indicate the X-coordinate of the grid on the board
    int yPos;         //Variable to indicate the X-coordinate of the grid on the board
    
    bool occupied;    //variable to indicate if anything is on the grid (blockingstones, stones)
    
    int gridState;   //OBSTACLE,
};

Grid gridInfo[8][8];

bool checkInBoard(int x1, int y1){
    if((x1<8 && x1>=0) && (y1<8 && y1>=0)){
        return true;
    }
    return false;
}

bool moveStone(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool check_only)
{
    if ((!checkInBoard(x0, y0)) || (!checkInBoard(x1, y1)) || (!checkInBoard(x2, y2)))
        return false;
    if (gridInfo[x0][y0].gridState != color || gridInfo[x1][y1].gridState != EMPTY)
        return false;
    if ((gridInfo[x2][y2].gridState != 0) && !(x2 == x0 && y2 == y0))
        return false;
    if (!check_only)
    {
        gridInfo[x0][y0].gridState = 0;
        gridInfo[x1][y1].gridState = color;
        gridInfo[x2][y2].gridState = OBSTACLE;
    }
    return true;
}


int main(){
    int x0, y0, x1, y1, x2, y2;
    
    // 初始化棋盘
    gridInfo[0][(GRIDSIZE - 1) / 3].gridState = gridInfo[(GRIDSIZE - 1) / 3][0].gridState
    = gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][0].gridState
    = gridInfo[GRIDSIZE - 1][(GRIDSIZE - 1) / 3].gridState = grid_black;
    gridInfo[0][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)].gridState = gridInfo[(GRIDSIZE - 1) / 3][GRIDSIZE - 1].gridState
    = gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][GRIDSIZE - 1].gridState
    = gridInfo[GRIDSIZE - 1][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)].gridState = grid_white;
    
    
    int turnID;
    cin >> turnID;
    
    // 读入到当前回合为止，自己和对手的所有行动，从而把局面恢复到当前回合
    currBotColor = grid_white; // 先假设自己是白方
    for (int i = 0; i < turnID; i++)
    {
        // 根据这些输入输出逐渐恢复状态到当前回合
        
        // 首先是对手行动
        cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
        if (x0 == -1)
            currBotColor = grid_black; // 第一回合收到坐标是-1, -1，说明我是黑方
        else
            moveStone(x0, y0, x1, y1, x2, y2, -currBotColor, false); // 模拟对方落子
        
        // 然后是自己当时的行动
        // 对手行动总比自己行动多一个
        if (i < turnID - 1)
        {
            cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
            if (x0 >= 0)
                moveStone(x0, y0, x1, y1, x2, y2, currBotColor, false); // 模拟己方落子
        }
    }
    
    // 做出决策（你只需修改以下部分）
    
    // 这里枚举了所有可能的下法，以便之后随机用……
    
    int beginPos[3000][2], possiblePos[3000][2], obstaclePos[3000][2];
    int posCount = 0, choice;
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            for (int k = 0; k < 8; ++k) {
                for (int delta1 = 1; delta1 < GRIDSIZE; delta1++) {
                    int xx = i + dx[k] * delta1;
                    int yy = j + dy[k] * delta1;
                    if (gridInfo[xx][yy].gridState != 0 || !checkInBoard(xx, yy))
                        break;
                    for (int l = 0; l < 8; ++l) {
                        for (int delta2 = 1; delta2 < GRIDSIZE; delta2++) {
                            int xxx = xx + dx[l] * delta2;
                            int yyy = yy + dy[l] * delta2;
                            if (!checkInBoard(xxx, yyy))
                                break;
                            if (gridInfo[xxx][yyy].gridState != 0 && !(i == xxx && j == yyy))
                                break;
                            if (moveStone(i, j, xx, yy, xxx, yyy, currBotColor, true))
                            {
                                beginPos[posCount][0] = i;
                                beginPos[posCount][1] = j;
                                possiblePos[posCount][0] = xx;
                                possiblePos[posCount][1] = yy;
                                obstaclePos[posCount][0] = xxx;
                                obstaclePos[posCount++][1] = yyy;
                            }
                        }
                        
                    }
                }
                
            }
        }
    }
    
    int startX, startY, resultX, resultY, obstacleX, obstacleY;
    if (posCount > 0)
    {
        srand(time(0));
        choice = rand() % posCount;
        startX = beginPos[choice][0];
        startY = beginPos[choice][1];
        resultX = possiblePos[choice][0];
        resultY = possiblePos[choice][1];
        obstacleX = obstaclePos[choice][0];
        obstacleY = obstaclePos[choice][1];
    }
    else
    {
        startX = -1;
        startY = -1;
        resultX = -1;
        resultY = -1;
        obstacleX = -1;
        obstacleY = -1;
    }
    
    // 决策结束，输出结果（你只需修改以上部分）
    cout << startX << ' ' << startY << ' ' << resultX << ' ' << resultY << ' ' << obstacleX << ' ' << obstacleY << endl;
    return 0;
}
