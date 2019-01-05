/*               ***** GAME OF THE AMAZONS 计算概论A 大作业 崔斌老师班 *****

 Made by Sunghyun Yoon (尹星铉 1800094617) & Joonwoo Jang (张晙优 1800094804）, Peking University*/

#include <iostream>
#include<stdio.h>
#include<cmath>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include<fstream>

#define GRIDSIZE 8
#define OBSTACLE 2
#define grid_black 1
#define grid_white -1

using namespace std;

double K = 0.2; //当black_min_step 和 white_min_step 相等且不等于无穷时的参数
int currBotColor; // 电脑的颜色
int player = 0;   //玩家的颜色
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // 棋盘
//控制移动方向
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

int Qwhite[GRIDSIZE][GRIDSIZE] = { 0 };
int Qblack[GRIDSIZE][GRIDSIZE] = { 0 };
int Kwhite[GRIDSIZE][GRIDSIZE] = { 0 };
int Kblack[GRIDSIZE][GRIDSIZE] = { 0 };
int startX, startY, resultX, resultY, obstacleX, obstacleY;
int turn = 0;   //记录步数
int ord;      //玩家的命令

int temp[GRIDSIZE][GRIDSIZE] = { 0 };   //模拟的棋盘

int mobility[GRIDSIZE][GRIDSIZE] = { 0 };

struct node1
{
    int x, y;
    int step;
};

int visK_W[GRIDSIZE][GRIDSIZE] = { 0 }, visK_B[GRIDSIZE][GRIDSIZE] = { 0 };            //用来记录各自的queen move 和 king move
int visQ_W[GRIDSIZE][GRIDSIZE] = { 0 }, visQ_B[GRIDSIZE][GRIDSIZE] = { 0 };

inline bool inMap(int x, int y)                   //张晙优 1800094804
{
    if (x >= 0 && x < GRIDSIZE&&y >= 0 && y < GRIDSIZE)
        return true;
    else
        return false;
}

void K_move_W(node1 pre)                 //尹星铉 1800094617
{
    node1 st, next;
    queue<node1>W;
    W.push(pre);
    
    while (!W.empty())
    {
        st = W.front();
        W.pop();
        for (int k = 0; k < 8; k++)
        {
            next.x = st.x + dx[k];
            next.y = st.y + dy[k];
            next.step = st.step + 1;
            
            if (temp[next.x][next.y] == 0 && visK_W[next.x][next.y] == 0 && inMap(next.x, next.y))
            {
                Kwhite[next.x][next.y] = min(Kwhite[next.step][next.y], next.step);
                visK_W[next.x][next.y] = 1;
                W.push(next);
            }
        }
    }
}

void K_move_B(node1 pre)                //尹星铉 1800094617
{
    node1 st, next;
    queue<node1>B;
    B.push(pre);
    
    while (!B.empty())
    {
        st = B.front();
        B.pop();
        for (int k = 0; k < 8; k++)
        {
            next.x = st.x + dx[k];
            next.y = st.y + dy[k];
            next.step = st.step + 1;
            
            if (temp[next.x][next.y] == 0 && visK_B[next.x][next.y] == 0 && inMap(next.x, next.y))
            {
                Kblack[next.x][next.y] = min(Kblack[next.step][next.y], next.step);
                visK_B[next.x][next.y] = 1;
                B.push(next);
            }
        }
    }
}

void Q_move_W(node1 pre)                //张俊优 1800094804
{
    node1 st, next;
    queue<node1>W;
    W.push(pre);
    
    while (!W.empty())
    {
        st = W.front();
        W.pop();
        for (int k = 0; k < 8; k++)
        {
            next.x = st.x;
            next.y = st.y;
            next.step = st.step + 1;
            while (1)
            {
                next.x += dx[k];
                next.y += dy[k];
                if (visQ_W[next.x][next.y] == 1)
                {
                    continue;
                }
                if (temp[next.x][next.y] == 0 && visQ_W[next.x][next.y] == 0 && inMap(next.x, next.y))
                {
                    //pre_map_Q[next.x][next.y].white_min_step = min(pre_map_Q[next.x][next.y].white_min_step, next.step);
                    Qwhite[next.x][next.y] = min(Qwhite[next.x][next.y], next.step);
                    visQ_W[next.x][next.y] = 1;
                    W.push(next);
                }
                else
                    break;
                
            }
        }
    }
}

void Q_move_B(node1 pre)                 //尹星铉 1800094617
{
    node1 st, next;
    queue<node1>B;
    B.push(pre);
    
    while (!B.empty())
    {
        st = B.front();
        B.pop();
        for (int k = 0; k < 8; k++)
        {
            next.x = st.x;
            next.y = st.y;
            next.step = st.step + 1;
            while (1)
            {
                next.x += dx[k];
                next.y += dy[k];
                if (visQ_B[next.x][next.y] == 1)
                {
                    continue;
                }
                if (temp[next.x][next.y] == 0 && visQ_B[next.x][next.y] == 0 && inMap(next.x, next.y))
                {
                    //pre_map_Q[next.x][next.y].black_min_step = min(pre_map_Q[next.x][next.y].black_min_step, next.step);
                    Qblack[next.x][next.y] = min(Qblack[next.x][next.y], next.step);
                    visQ_B[next.x][next.y] = 1;
                    B.push(next);
                }
                else
                    break;
                
            }
        }
    }
}

void getMove()                   //尹星铉 1800094617
{
    node1 w;
    
    for (int i = 0; i < GRIDSIZE; i++)                //«Ûø’∏Òµƒ∫⁄£¨∞◊queen move
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if (temp[i][j] == grid_white)
            {
                w.x = i;        //
                w.y = j;
                w.step = 0;
                
                //memset(visQ_W, 0, sizeof(visQ_W)); //
                //memset(visK_W, 0, sizeof(visK_W));
                for (int i = 0; i < GRIDSIZE; i++)
                    for (int j = 0; j < GRIDSIZE; j++)
                    {
                        visQ_W[i][j] = 0;
                        visK_W[i][j] = 0;
                    }
                visQ_W[i][j] = 1;
                visK_W[i][j] = 1;
                Q_move_W(w);
                K_move_W(w);
            }
            if (temp[i][j] == grid_black)
            {
                w.x = i;
                w.y = j;
                w.step = 0;
                //memset(visQ_B, 0, sizeof(visQ_B));
                //memset(visK_B, 0, sizeof(visK_B));
                for (int i = 0; i < GRIDSIZE; i++)
                    for (int j = 0; j < GRIDSIZE; j++)
                    {
                        visQ_B[i][j] = 0;
                        visK_B[i][j] = 0;
                    }
                visQ_B[i][j] = 1;
                visK_B[i][j] = 1;
                Q_move_B(w);
                K_move_B(w);
            }
        }
}

double m()           //尹星铉  1800094617        求空格的灵活度的函数
{
    double mob = 0;
    
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
        {
            mobility[i][j] = 0;
        }
    
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
        {
            for (int k = 0; k < 8; k++)           //求每一个空格的灵活度
            {
                if (i + dx[k] >= 0 && i + dx[k] < GRIDSIZE&&j + dy[k] >= 0 && j + dy[k] < GRIDSIZE)
                {
                    if (temp[i + dx[k]][j + dy[k]] == 0)
                    {
                        mobility[i][j]++;
                    }
                    else
                        break;
                }
            }
        }
    
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if (temp[i][j] == 0)
            {
                for (int k = 0; k < 8; k++)
                {
                    
                    int m1 = i, m2 = j;
                    int count = 0;
                    while (1)
                    {
                        count++;
                        m1 += dx[k];
                        m2 += dy[k];
                        if (m1 >= 0 && m1 < GRIDSIZE&&m2 >= 0 && m2 < GRIDSIZE)
                        {
                            if (temp[m1][m2] == grid_black)
                            {
                                mob += mobility[i][j] / count * 1.0*currBotColor;
                                break;
                            }
                            else if (temp[m1][m2] == grid_white)
                            {
                                mob -= mobility[i][j] / count * 1.0*currBotColor;
                                break;
                            }
                            else if (temp[m1][m2] == OBSTACLE)
                            {
                                break;
                            }
                            else
                                continue;
                            
                        }
                        else
                            break;
                    }
                }
            }
        }
    return mob;
}

double t1 = 0, t2 = 0, p1 = 0, p2 = 0, mob = 0;

void getValue()                    //尹星铉   1800094617      求territory 参数的函数
{
    double tempB = 1, tempW = 1;
    t1 = t2 = p1 = p2 = mob = 0;
    
    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if (temp[i][j] == 0)
            {
                for (int k = 0; k < Qblack[i][j]; k++)     //       求position 特征值
                {
                    tempB *= 0.5;
                }
                for (int k = 0; k < Qwhite[i][j]; k++)
                {
                    tempW *= 0.5;
                }
                p1 += (tempB - tempW)*currBotColor*1.0;
                
                
                p2 += min(1.0, max(-1.0, ((Kwhite[i][j] - Kblack[i][j]) / 6.0)))*currBotColor*1.0;
                
                if (Qblack[i][j] < Qwhite[i][j])    //求territory 特征值
                {
                    t1 += 1 * currBotColor;
                }
                if (Qblack[i][j] > Qwhite[i][j])
                {
                    t1 -= 1 * currBotColor;
                }
                if (Qblack[i][j] == Qwhite[i][j] && Qblack[i][j] != 10000)
                {
                    t1 -= K * currBotColor;
                    
                }
                if (Kblack[i][j] < Kwhite[i][j])
                {
                    t2 += 1 * currBotColor;
                    ;
                }
                if (Kblack[i][j] > Kwhite[i][j])
                {
                    t2 -= 1 * currBotColor;
                }
                if (Kblack[i][j] == Kwhite[i][j] && Kblack[i][j] != 10000)
                {
                    t2 -= K * currBotColor;           //«Ût2
                }
            }
        }
    p1 *= 2;
    p2 *= 2;
    mob = m();
}

double v(int turn)      //尹星铉   1800094617   求最终评估值的函数
{
    double value = 0;
    int turn1 = turn;
    if (currBotColor == grid_white)
    {
        if (turn1 <= 14)
        {
            value = 0.2*t1 + 0.48*t2 + 0.11*p1 + 0.11*p2 + 0.2*mob;
        }
        else if (turn1 >= 15 && turn1 <= 48)
        {
            value = 0.4*t1 + 0.25*t2 + 0.2*p1 + 0.2*p2 + 0.05*mob;
        }
        else if (turn1 >= 49)
        {
            value = 0.8*t1 + 0.1*t2 + 0.05*p1 + 0.05*p2;
        }
    }
    else
    {
        if (turn1 <= 14)
        {
            value = 0.2*t1 + 0.48*t2 + 0.11*p1 + 0.11*p2 + 0.2*mob;
        }
        else if (turn1 >= 15 && turn1 <= 48)
        {
            value = 0.4*t1 + 0.25*t2 + 0.2*p1 + 0.2*p2 + 0.05*mob;
        }
        else if (turn1 >= 49)
        {
            value = 0.8*t1 + 0.1*t2 + 0.05*p1 + 0.05*p2;
        }
    }
    
    return value;
}


bool Move(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool check_only)  //张俊优 1800094804
{
    if ((!inMap(x0, y0)) || (!inMap(x1, y1)) || (!inMap(x2, y2)))
        return false;
    if (gridInfo[x0][y0] != color || gridInfo[x1][y1] != 0)
        return false;
    if ((gridInfo[x2][y2] != 0) && !(x2 == x0 && y2 == y0))
        return false;
    if (!check_only)
    {
        gridInfo[x0][y0] = 0;
        gridInfo[x1][y1] = color;
        gridInfo[x2][y2] = OBSTACLE;
    }
    return true;
}


bool checkCanmove(int x, int y)             //张俊优 1800094804
{
    int x1, y1;
    for (int k = 0; k < 8; k++)
    {
        x1 = x + dx[k];
        y1 = y + dy[k];
        if (gridInfo[x1][y1] == 0 && inMap(x, y))
        {
            return true;
        }
    }
    
    return false;
}

bool checkCanMoveTo(int x0, int y0, int x1, int y1){    //张俊优 1800094804
    
    if(inMap(x1,y1) && checkCanmove(x0, y0)){
        int tx1, ty1;
        for(int i = 0; i<8; i++){
            for(int b = 1; b<=8; b++){
                tx1 = x0 + dx[i]*b;
                ty1 = y0 + dy[i]*b;
                
                if(tx1 == x1 && ty1 == y1){
                    return true;
                }
            }
        }
    }
    
    return false;

}
    

void reset()              //尹星铉    1800094617
{
    gridInfo[0][(GRIDSIZE - 1) / 3] = gridInfo[(GRIDSIZE - 1) / 3][0]
    = gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][0]
    = gridInfo[GRIDSIZE - 1][(GRIDSIZE - 1) / 3] = grid_black;
    gridInfo[0][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)] = gridInfo[(GRIDSIZE - 1) / 3][GRIDSIZE - 1]
    = gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][GRIDSIZE - 1]
    = gridInfo[GRIDSIZE - 1][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)] = grid_white;
    
    startX = -1, startY = -1, resultX = -1, resultY = -1, obstacleX = -1, obstacleY = -1;
    turn = 1;
    currBotColor = grid_white;    // 先假设己方的颜色为白色
}

void printBoard(int gridinfo[8][8])  // 张俊优 1800094804
{
    system("cls");
    
    cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int a = 0; a < 8; a++) {
        cout << "                |                |                |                |                |                |                |                |" << endl;
        cout << "                |                |                |                |                |                |                |                |" << endl;
        for (int b = 0; b < 8; b++) {
            if (gridinfo[a][b]==0) {
                printf("  x = %d, y = %d  |", a, b);
            }
            else if (gridinfo[a][b]!=0) {
                if (gridinfo[a][b]!=2) {
                    if (gridinfo[a][b] == -1) {
                        printf("        W       |");
                    }
                    else if (gridinfo[a][b] == 1) {
                        printf("        B       |");
                    }
                }
                else
                {
                    printf("        *       |");
                }
            }
        }
        cout << endl;
        cout << "                |                |                |                |                |                |                |                |" << endl;
        cout << "                |                |                |                |                |                |                |                |" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void printMenu()                //张俊优 1800094804
{
    cout << "Welcome to the Game of Amazons!" << endl;
    cout << "*Created by Joonwoo Jang & Sunghyun Yoon of PKU EECS 2018*" << endl;
    cout << "\nMenu Screen" << endl;
}


void Save()               //尹星铉     1800094617
{
    char a[100];
    cout << "Please input the file name" << endl;
    cin >> a;
    
    ofstream fout(a);
    fout << turn << ' ';
    fout << player << ' ';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fout << gridInfo[i][j] << ' ';
        }
    }
    fout.close();
}

void getSave()          //张俊优 1800094804
{
    char a[100];
    cout << "Which file do you want to load?" << endl;
    cin >> a;
    
    ifstream fin(a);//打开文件
    fin >> turn;
    fin >> player;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fin >> gridInfo[i][j];
        }
    }
    fin.close();
}

void printM()         //张俊优 1800094804
{
    cout << "1. Restart " << endl;
    cout << "2. Save  " << endl;
    cout << "3. End  " << endl;
}


void playerMove()                              //张晙优 1800094804
{
    int x0, y0, x1, y1, x2, y2;   //玩家的下棋法
    
    cout << "Which stone do you want to move?" << endl;
    cin >> x0 >> y0;
    if (gridInfo[x0][y0] != player)
    {
        while (1)
        {
            cout << "Wrong stone, Which stone do you want to move?" << endl;
            cin >> x0 >> y0;
            if (gridInfo[x0][y0] == player)
                break;
        }
    }
    cout << endl;
    cout << "Which position do you want to move the stone to?" << endl;
    cin >> x1 >> y1;
    if (gridInfo[x1][y1] != 0 || !inMap(x1, y1) || !checkCanMoveTo(x0, y0, x1, y1))
    {
        while (1)
        {
            cout << "Invalid move, Which position do you want to move?" << endl;
            cin >> x1 >> y1;
            if (gridInfo[x1][y1] == 0 && inMap(x1, y1) && checkCanMoveTo(x0, y0, x1, y1))
                break;
        }
    }
    
    cout << "To which position do you want to place the arrow?" << endl;
    cin >> x2 >> y2;
    
    if (gridInfo[x2][y2] != 0 || !inMap(x1, y1) || !checkCanMoveTo(x1, y1, x2, y2))
    {
        while (1)
        {
            if(x2 == x0 && y2 == y0){
                break;
            }
            cout << "Wrong move, Which position do you want to place the arrow?" << endl;
            cin >> x2 >> y2;
            if (gridInfo[x2][y2] != 0 || !inMap(x1, y1) || checkCanMoveTo(x1, y1, x2, y2))
                break;
        }
    }
    
    
    Move(x0, y0, x1, y1, x2, y2, player, false);
}

int main()
{
    //int x0, y0, x1, y1, x2, y2;   //玩家的下棋法
    
    printMenu();
    
    cout << "1. Start New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Exit  " << endl;
    cout << endl;
    
    cout << "Please input your command" << endl;
    while (1)
    {
        cin >> ord;
        if (ord == 1)
        {
            reset();
            printBoard(gridInfo);
            
            cout << "Please choose your side" << endl;
            cout << "Black: 1" << endl;
            cout << "White: -1" << endl;
            
            cin >> player;
            if (player != 1 && player != -1)
            {
                while (1)
                {
                    cout << "Wrong value. Please input either 1 for black or -1 for white" << endl;
                    cin >> player;
                    if (player == 1 || player == -1)
                        break;
                }
                break;
            }
            break;
        }
        else if (ord == 2)
        {
            getSave();
            printBoard(gridInfo);
            if (player == 1)
            {
                cout << "You are black, game loaded" << endl;
            }
            else if (player == -1)
                cout << "You are white, game loaded" << endl;
            else
            {
                reset();
                printBoard(gridInfo);
                
                cout << "Please choose your stone" << endl;
                cout << "black: 1" << endl;
                cout << "white: -1" << endl;
                
                cin >> player;
                if (player != 1 && player != -1)
                {
                    while (1)
                    {
                        cout << "Wrong value. Please input either 1 for black or -1 for white" << endl;
                        cin >> player;
                        if (player == 1 || player == -1)
                        {
                            currBotColor = -player;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        else if (ord == 3)
            return 0;
        else
        {
            cout << "Invalid command，please input a valid command from 1 to 3." << endl;
        }
        
    }
    
    if (ord == 1)
    {
        currBotColor = -player;
        if (player == 1)
        {
            playerMove();
            printBoard(gridInfo);
        }
    }
    
    else if (ord == 2&&player==1)
    {
        playerMove();
        printBoard(gridInfo);
    }
    
    while(1)
    {
        int flag = 0;    //做标记是否重新开始
        turn++;
        
        double maxValue = -1000;
        double valueP = 0;
        
        //电脑做决策
        for (int i0 = 0; i0 < GRIDSIZE; ++i0) {
            for (int j0 = 0; j0 < GRIDSIZE; ++j0) {
                for (int k1 = 0; k1 < 8; ++k1) {
                    for (int delta1 = 1; delta1 < GRIDSIZE; delta1++) {
                        int xx = i0 + dx[k1] * delta1;
                        int yy = j0 + dy[k1] * delta1;
                        if (gridInfo[xx][yy] != 0 || !inMap(xx, yy))
                            break;//不是空格或不在棋盘
                        for (int l = 0; l < 8; ++l) {
                            for (int delta2 = 1; delta2 < GRIDSIZE; delta2++) {
                                int xxx = xx + dx[l] * delta2;
                                int yyy = yy + dy[l] * delta2;         //实现queen move
                                if (!inMap(xxx, yyy))
                                    break;
                                if (gridInfo[xxx][yyy] != 0 && !(i0 == xxx && j0 == yyy))//不能放在原来的位置或有棋的地方
                                    break;
                                if (Move(i0, j0, xx, yy, xxx, yyy, currBotColor, true))
                                {
                                    memcpy(temp, gridInfo, sizeof(gridInfo));
                                    
                                    temp[i0][j0] = 0;
                                    temp[xx][yy] = currBotColor;
                                    temp[xxx][yyy] = OBSTACLE;      //模拟棋盘
                                    
                                    
                                    for (int i = 0; i < GRIDSIZE; i++)
                                        for (int j = 0; j < GRIDSIZE; j++)
                                        {
                                            Qblack[i][j] = 1000;
                                            Qwhite[i][j] = 1000;
                                            Kblack[i][j] = 1000;
                                            Kwhite[i][j] = 1000;
                                        }
                                    getMove();
                                    getValue();
                                    valueP = v(turn);
                                    if (maxValue < valueP)
                                    {
                                        maxValue = valueP;
                                        startX = i0;
                                        startY = j0;
                                        resultX = xx;
                                        resultY = yy;
                                        obstacleX = xxx;
                                        obstacleY = yyy;
                                    }
                                    
                                }
                            }
                            
                        }
                    }
                    
                }
            }
        }
        
        Move(startX, startY, resultX, resultY, obstacleX, obstacleY,currBotColor,false);
        
        printBoard(gridInfo);
        
        //判断游戏是否结束
        int flag1 = 0;
        int flag2 = 0;
        for (int i = 0; i < GRIDSIZE; i++)
        {
            for (int j = 0; j < GRIDSIZE; j++)
            {
                if (gridInfo[i][j] == currBotColor)
                {
                    if (checkCanmove(i, j))
                    {
                        flag1++;
                    }
                }
                if (gridInfo[i][j] == player)
                {
                    if (checkCanmove(i, j))
                    {
                        flag2++;
                    }
                }
            }
            if (flag1 != 0 && flag2 != 0)
                break;
        }
        if (flag1 == 0)
        {
            cout << "You're so clever! You have won the game! Congratulations!" << endl;
            break;
        }
        
        if (flag2 == 0)
        {
            cout << "What a pity~! You almost won the game." << endl << " You will do better in the next game!" << endl;
            break;
        }
        
        //若游戏没有结束
        cout << "If you want to continue the game please input '1'.\nIf you want to go back to the Menu, please input '2'" << endl;
        int ord1;
        cin >> ord1;
        if(ord1 != 2 || ord1!= 1){
            while(1){
                cout << "Invalid command. Please input either 1 to continue the game or 2 to go back to the menu.";
                cin >> ord1;
                if(ord1 == 1 || ord1 == 2){
                    break;
                }
            }
        }
        if (ord1 == 2)
        {
            cout << "1. Restart " << endl;
            cout << "2. Save  " << endl;
            cout << "3. End  " << endl;
            
            cout << "Please input your command." << endl;
            int ord2;
            
            while (1)
            {
                cin >> ord2;
                if (ord2 == 1)
                {
                    reset();
                    cout << "Please choose your stone" << endl;
                    cout << "black: 1" << endl;
                    cout << "white: -1" << endl;
                    
                    cin >> player;
                    if (player != 1 && player != -1)
                    {
                        while (1)
                        {
                            cout << "Wrong value. Please input either 1 for black or -1 for white" << endl;
                            cin >> player;
                            if (player == 1 || player == -1)
                                break;
                        }
                    }
                    
                    if (player == 1)
                    {
                        playerMove();
                    }
                    currBotColor = -player;
                    flag = 1;
                    break;
                }
                else if (ord2 == 2)
                {
                    Save();
                    flag = 2;
                    break;
                }
                else if (ord2 == 3)
                {
                    flag = 3;
                    break;
                }
                else
                {
                    cout << "Invalid Command." << endl;
                    cout << "1. Restart " << endl;
                    cout << "2. Save  " << endl;
                    cout << "3. End  " << endl;
                    
                    cout << "Please input your command." << endl;
                }
            }
        }
    
        
        if (flag == 1)
            continue;
        else if (flag == 2)
        {
            int ord;
            cout << "Please input your command." << endl;
            cout << "1. Continue" << endl;
            cout << "2. end" << endl;
            while (1)
            {
                cin >> ord;
                if (ord == 2)
                    return 0;
                else if (ord == 1)
                {
                    break;
                }
                else
                {
                    cout << "Wrong command" << endl;
                    cout << "Please input your command." << endl;
                    cout << "1. Continue" << endl;
                    cout << "2. end" << endl;
                }
            }
            
        }
        else if(flag==3)
            break;
        
        playerMove();
        
        printBoard(gridInfo);
    }
    
    
    return 0;
}
