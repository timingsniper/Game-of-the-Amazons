//
//  main.cpp
//  AmazonsProject
//
//  Created by 장준우 on 24/12/2018.
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

using namespace std;

struct Stones{
    int stoneColor;   // 0 = white, 1 = black
    bool canMove;     //check if the stone can move, check with checkCanMove(Stones a) method
    int xPosition;    //current x cooridnate of the stone
    int yPosition;    //current x cooridnate of the stone
};

struct Stones emptystone = {0};

struct BlockingStones{
    int xPosition;    //current x cooridnate of the blockingstone
    int yPosition;    //current y cooridnate of the blockingstone
};

struct Grid{
    int xPos;         //Variable to indicate the X-coordinate of the grid on the board
    int yPos;         //Variable to indicate the X-coordinate of the grid on the board
    
    bool occupied;    //variable to indicate if anything is on the grid (blockingstones, stones)
    
    bool stoneIsOn;   //variable to indicate if a stone is on the gird
    Stones onGrid;    //Variable to store the stone that is on the current grid
    
    bool bStoneIsOn;  //variable to indicate if a blockingStone is on the grid
    BlockingStones bOnGrid; //Variable to store the blocking stone that is on the current grid
};

struct Board{
    int playerColor;  // 0 = white, 1 = black, indicates if the player chose black to play or white to play
    bool isOver;      // variable to check if the game is over as someone won
    int winnderCode;  // 0 = white, 1 = black, -1 = no one yet
    
    //Grid** grids;   // array of grids that are on the board, 64 of them since the board is 8*8
 };

bool checkCanMove(Stones a){ //Function to check if a stone can actually *move* in any way from its current situation
    
    return true;
}

bool checkCanMove(Stones a, int x1, int y1){
    
    return true;
}

bool checkInBoard(Stones a){
    
    return false;
}

bool checkInBoard(int x1, int y1){
    
    return false;
}

void placeBlockingStone(Stones a, int x1, int y1, Grid grids[8][8]){
    if(!checkCanMove(a, x1, y1)){
        cout << "This Blocking Stone can't be placed at that position. Please choose another position to place." << endl;
    }
    else if(grids[y1][x1].occupied){
        cout << "This position is occupied. Select another coordinate to place the blocking stone" << endl;
    }

    struct BlockingStones bStone = {x1,y1};
    
    grids[y1][x1].occupied = true;
    grids[y1][x1].bStoneIsOn= true;
    grids[y1][x1].bOnGrid = bStone;
}

void moveStone(Stones a, int x1, int y1, Grid grids[8][8], int bx1, int by1){
    while(true){
        if(!checkCanMove(a)){
            cout << "This stone is not movable at this point. Please choose another stone to move." << endl;
            continue;
        }
    
        else if(!checkCanMove(a, x1,y1)){
            cout << "This movement is invalid. Please select another coordinate to move to." << endl;
            continue;
        }
    
        int currentXPos = a.xPosition;
        int currentYPos= a.yPosition;
    
        grids[currentYPos][currentXPos].occupied = false;
        grids[currentYPos][currentXPos].stoneIsOn = false;
        grids[currentYPos][currentXPos].onGrid = emptystone;
    
        grids[y1][x1].occupied = true;
        grids[y1][x1].stoneIsOn = true;
        grids[y1][x1].onGrid = a;
        
        placeBlockingStone(a, bx1, by1, grids);
        
        return;
    }
    
}



void printBoard(Grid gridss[8][8]){    // Function to print 64 Grids of the board in a user friendly interface.
    cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for(int a = 0; a<8; a++){
        cout << "                |                |                |                |                |                |                |                |" <<endl;
        cout << "                |                |                |                |                |                |                |                |" <<endl;
        for(int b = 0; b<8; b++){
            if(!gridss[a][b].occupied){
                printf("  x = %d, y = %d  |", a, b);
            }
            else if(gridss[a][b].occupied){
                if(gridss[a][b].stoneIsOn){
                    if(gridss[a][b].onGrid.stoneColor == 0){
                        printf("        W       |");
                    }
                    else if(gridss[a][b].onGrid.stoneColor == 1){
                        printf("        B       |");
                    }
                }
                else if(gridss[a][b].bStoneIsOn){
                    printf("    Blocking    |");
                }
            }
        }
        cout<< endl;
        cout << "                |                |                |                |                |                |                |                |" << endl;
        cout << "                |                |                |                |                |                |                |                |" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void printMenu(){
    cout << "Welcome to the Game of Amazons!" << endl;
    cout << "*Created by Joonwoo Jang & Sunghyun Yoon of PKU EECS 2018*" << endl;
    cout << "\nMenu Screen" << endl;
}

int main(){
    //Creation of 64 Grids as part of the board, inside a 2d array named gridds with size of 8*8
    
    Grid gridss[8][8];      // 2D Array of 64 Grids that would constitute the board
    
    //Initialize the Grids
    for(int i = 0; i<8; i++){
        for(int d = 0; d<8; d++){
            gridss[i][d] = {d, i, false, false, NULL, false, NULL};
        }
    }
    
    //Initializing Black stones on the board at the beginning of the game
    
    Stones blackStoneOne = {1, true, 2, 0};
    Stones blackStoneTwo = {1, true, 5, 0};
    Stones blackStoneThree = {1, true, 0, 2};
    Stones blackStoneFour = {1, true, 7, 2};
    
    gridss[0][2].occupied = true;
    gridss[0][2].stoneIsOn = true;
    gridss[0][2].onGrid = blackStoneOne;
    
    gridss[0][5].occupied = true;
    gridss[0][5].stoneIsOn = true;
    gridss[0][5].onGrid = blackStoneTwo;
    
    gridss[2][0].occupied = true;
    gridss[2][0].stoneIsOn = true;
    gridss[2][0].onGrid = blackStoneThree;
    
    gridss[2][7].occupied = true;
    gridss[2][7].stoneIsOn = true;
    gridss[2][7].onGrid = blackStoneFour;
    
    //Initializing White stones on the board at the beggining of the game
    
    Stones whiteStoneOne = {0, true, 0, 5};
    Stones whiteStoneTwo = {0, true, 2, 7};
    Stones whiteStoneThree = {0, true, 5, 7};
    Stones whiteStoneFour = {0, true, 7, 5};
    
    gridss[5][0].occupied = true;
    gridss[5][0].stoneIsOn = true;
    gridss[5][0].onGrid = whiteStoneOne;
    
    gridss[7][2].occupied = true;
    gridss[7][2].stoneIsOn = true;
    gridss[7][2].onGrid = whiteStoneTwo;
    
    gridss[7][5].occupied = true;
    gridss[7][5].stoneIsOn = true;
    gridss[7][5].onGrid = whiteStoneThree;
    
    gridss[5][7].occupied = true;
    gridss[5][7].stoneIsOn = true;
    gridss[5][7].onGrid = whiteStoneFour;
    
    
    
    printBoard(gridss);
    moveStone(blackStoneOne, 2, 2, gridss, 4, 4);
    cout<< endl;
    cout<<endl;
    
    //system("cls");
    printBoard(gridss);
    
    
}
