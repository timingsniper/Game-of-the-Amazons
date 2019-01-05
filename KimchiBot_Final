#include <iostream>
#include<cmath>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define GRIDSIZE 8
#define OBSTACLE 2
#define grid_black 1
#define grid_white -1

using namespace std;

double K = 0.2; //??¡­???0.5

int currBotColor; // ?¡°¨¤?¡Â£¤?¡±¡ª¡¯¡­¡ä¡ê?1??¡Ò?¡ê¡§-1??¡Þ?¡ê¡§??¡Ö??£¤?¡§¡°??¡§¡ê?
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // ??x¡Ò?y¡ê¡§o??o??¡Ö??£¤?¡§
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
int Qwhite[GRIDSIZE][GRIDSIZE] = { 0 };
int Qblack[GRIDSIZE][GRIDSIZE] = { 0 };
int Kwhite[GRIDSIZE][GRIDSIZE] = { 0 };
int Kblack[GRIDSIZE][GRIDSIZE] = { 0 };

/*
 struct node1
 {
 int white_min_step;
 int black_min_step;
 };

 node1 pre_map_K[GRIDSIZE][GRIDSIZE], pre_map_Q[GRIDSIZE][GRIDSIZE];

 */
int temp[GRIDSIZE][GRIDSIZE] = { 0 };   //o??o??¡Ö??£¤?¡§

int mobility[GRIDSIZE][GRIDSIZE] = { 0 };

struct node2
{
	int x, y;
	int step;
};

int visK_W[GRIDSIZE][GRIDSIZE] = { 0 }, visK_B[GRIDSIZE][GRIDSIZE] = { 0 };
int visQ_W[GRIDSIZE][GRIDSIZE] = { 0 }, visQ_B[GRIDSIZE][GRIDSIZE] = { 0 };

inline bool inMap(int x, int y)
{
	if (x >= 0 && x < GRIDSIZE&&y >= 0 && y < GRIDSIZE)
		return true;
	else
		return false;
}

void K_move_W(node2 pre)
{
	node2 st, next;
	queue<node2>W;
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

void K_move_B(node2 pre)
{
	node2 st, next;
	queue<node2>B;
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

void Q_move_W(node2 pre)
{
	node2 st, next;
	queue<node2>W;
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

void Q_move_B(node2 pre)
{
	node2 st, next;
	queue<node2>B;
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

void getMove()
{
	node2 w;

	for (int i = 0; i < GRIDSIZE; i++)                //???¡¯¡Ç¨°¦Ì?¡Ò?¡ê¡§¡Þ?queen move
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if (temp[i][j] == grid_white)
			{
				w.x = i;        //¡Ý? oa?node w
				w.y = j;
				w.step = 0;

				//memset(visQ_W, 0, sizeof(visQ_W)); //¡Ý? oa??¡¯¡Ç¨°¦Ì?queen move
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

/*
 void reset(node1 a[GRIDSIZE][GRIDSIZE])
 {
 for (int i = 0; i < GRIDSIZE; i++)
 for (int j = 0; j < GRIDSIZE; j++)
 {
 a[i][j].black_min_step = 1000;
 a[i][j].white_min_step = 1000;
 }
 }
 */

double m()           //???¨¨a¨®??
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
			for (int k = 0; k < 8; k++)           //???¡¯¡Ç¨°¦Ì??¨¨a¨®??
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

void getValue()
{
	double tempB = 1, tempW = 1;
	t1 = t2 = p1 = p2 = mob = 0;

	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
		{
			if (temp[i][j] == 0)
			{
				for (int k = 0; k < Qblack[i][j]; k++)     //??p1
				{
					tempB *= 0.5;
				}
				for (int k = 0; k < Qwhite[i][j]; k++)
				{
					tempW *= 0.5;
				}
				p1 += (tempB - tempW)*currBotColor*1.0;

				//??p2
				p2 += min(1.0, max(-1.0, ((Kwhite[i][j] - Kblack[i][j]) / 6.0)))*currBotColor*1.0;

				if (Qblack[i][j] < Qwhite[i][j])    //??t1
				{
					t1 += 1 * currBotColor;
				}
				if (Qblack[i][j] > Qwhite[i][j])
				{
					t1 -= 1 * currBotColor;
				}
				if (Qblack[i][j] == Qwhite[i][j] && Qblack[i][j] != 10000)
				{
					t1 -= K * currBotColor;         //?? t1

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
					t2 -= K * currBotColor;           //??t2
				}
			}
		}
	p1 *= 2;
	p2 *= 2;
	mob = m();
}

double v(int turn)      //??value ¡Ò? ?
{
	double value = 0;
	int turn1 = turn * 2;
	if (currBotColor == grid_white)
	{
		if (turn1 <= 10)
		{
			value = 0.2*t1 + 0.48*t2 + 0.11*p1 + 0.11*p2 + 0.2*mob;
		}
		else if (turn1 >= 11 && turn1 <= 30)
		{
			value = 0.4*t1 + 0.25*t2 + 0.2*p1 + 0.2*p2 + 0.05*mob;
		}
		else if (turn1 >= 31)
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


bool Move(int x0, int y0, int x1, int y1, int x2, int y2, int color, bool check_only)// ¡®??¡¥¡À¨ª£¤??¡ë?¡±¡ê¡§o?¡Ü¨¨ ?¡Æ¨°¡Ò?¡Æ?a¨²?¡ê???¡ë?¡±
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

int main()
{
	int x0, y0, x1, y1, x2, y2;

	// ¡Ý? oa???¡Ö?
	gridInfo[0][(GRIDSIZE - 1) / 3] = gridInfo[(GRIDSIZE - 1) / 3][0]
		= gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][0]
		= gridInfo[GRIDSIZE - 1][(GRIDSIZE - 1) / 3] = grid_black;
	gridInfo[0][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)] = gridInfo[(GRIDSIZE - 1) / 3][GRIDSIZE - 1]
		= gridInfo[GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)][GRIDSIZE - 1]
		= gridInfo[GRIDSIZE - 1][GRIDSIZE - 1 - ((GRIDSIZE - 1) / 3)] = grid_white;


	int turnID;
	cin >> turnID;

	// ????¦Ì¦¸¦Ì¡À?¡Þa?¡Ò???¡Â¦Ð¡ê¡§?¡®o¡Ò¡Ò??¡® ¡Â¦Ì?¨¤?¡±¨C¨C¨C??¡ê¡§£¤¡±?¡¥¡Þ¡ª?¡Â¡Ì¨ºa¡Â¡Ç£¤¦Ì¦¸¦Ì¡À?¡Þa?¡Ò?
	currBotColor = grid_white; // o?¡­??¡®o¡Ò ?¡Æ¦¸
	for (int i = 0; i < turnID; i++)
	{
		// ¡Ç???¡¯?¨C? ¡ë?? ¡ë¡Ý?¡Â?¦¸?a¡Â¡Ç£¤?£¤?¡§¦Ì¦¸¦Ì¡À?¡Þa?¡Ò?

		//  ??? ??¡® ¡Â¨C¨C??
		cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
		if (x0 == -1)
			currBotColor = grid_black; // ¦Ì?¡°aa?¡Ò? ¡¯¦Ì¦¸?¡¥¡À¨ª ?-1, -1¡ê¡§¨¤¦Ì¡Ì??¡° ?¡Ò?¡Æ¦¸
		else
		{
			// ?¡ê???¡®¡Æ¦¸?¡ë?¡±
			Move(x0, y0, x1, y1, x2, y2, -currBotColor, false);
		}
		// ?a¡Ò? ??¡®o¡Ò¦Ì¡À ¡À¦Ì?¨C¨C??
		// ?¡® ¡Â¨C¨C????¡À??¡®o¡Ò¨C¨C????¡°a¡Ç?
		if (i < turnID - 1)
		{
			cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
			if (x0 >= 0)
				Move(x0, y0, x1, y1, x2, y2, currBotColor, false); // ?¡ê??o¡Ò¡Æ¦¸?¡ë?¡±
		}

	}
	//if (currBotColor == grid_white)
		//K = 0.4;

	int startX = -1, startY = -1, resultX = -1, resultY = -1, obstacleX = -1, obstacleY = -1;
	double maxValue = -1000;
	//double minValue = 1000;
	double valueP = 0;
	for (int i0 = 0; i0 < GRIDSIZE; ++i0) {
		for (int j0 = 0; j0 < GRIDSIZE; ++j0) {
			for (int k1 = 0; k1 < 8; ++k1) {
				for (int delta1 = 1; delta1 < GRIDSIZE; delta1++) {
					int xx = i0 + dx[k1] * delta1;
					int yy = j0 + dy[k1] * delta1;
					if (gridInfo[xx][yy] != 0 || !inMap(xx, yy))
						break;//¡±¨C¡À?¦Ì????¡±¡ê¡§¡®¦¸¦¸¨¢
					for (int l = 0; l < 8; ++l) {
						for (int delta2 = 1; delta2 < GRIDSIZE; delta2++) {
							int xxx = xx + dx[l] * delta2;
							int yyy = yy + dy[l] * delta2;         //¡Æ¡Ö¡¯?¡Þ¡Ù¡°¡®¦Ì???¡Ç????o
							if (!inMap(xxx, yyy))
								break;
							if (gridInfo[xxx][yyy] != 0 && !(i0 == xxx && j0 == yyy))//¡Üa??¡Æ¡Ö¦Ì¦¸¡À??£¤¦Ì??a¡Â¡Ì
								break;
							if (Move(i0, j0, xx, yy, xxx, yyy, currBotColor, true))
							{            //¡®¡Ù¡±¨C¡ê¡§¦¸¡ä¡Æ¡Ö¡ê¡§¡ê¡§¡¯?¡Þ¡Ù¡ê¡§¡ê¡§¡ê¡§¡ê¡§¡ª¡¯¡­¡ä
								//¡®? ¡À£¤¨º¡Æ¡Ö??¡Ö? ¡ê¡§¡®?¡Ç¡Ì??¡Ö?¡­??¡ê??????
								memcpy(temp, gridInfo, sizeof(gridInfo));//¡±?¡Ç¡Ì¡Âa¡±¨C¡°a¡Ç?temp¡ê¡§¡®?¡­?¡Ì¨º?¡ê??¡Ò¡Ì??¦Ð?¦Ì?¡Ü¦¸?¡±¡ê¡§?a¡Ò?¡Æ¡Â¡À???¦Ð?

								temp[i0][j0] = 0;
								temp[xx][yy] = currBotColor;
								temp[xxx][yyy] = OBSTACLE;      //?¡ê?????¨ª???¨¤¡ê¡§temp¡­?¡°¡ª?¡Ù¡±¨C?¨¤??¡°a¡Ü¦¸¦Ì??¡Â¡Ì¨º
								//¡Ç¡Ì??¦Ð??¨¤

								for (int i = 0; i < GRIDSIZE; i++)
									for (int j = 0; j < GRIDSIZE; j++)
									{
										Qblack[i][j] = 1000;
										Qwhite[i][j] = 1000;
										Kblack[i][j] = 1000;
										Kwhite[i][j] = 1000;
									}
								//reset(pre_map_K);
								//reset(pre_map_Q);
								getMove();
								getValue();
								valueP = v(turnID);
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
								/*
								if (currBotColor == grid_black)
								{
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
								if (currBotColor == grid_white)
								{
									if (minValue > valueP)
									{
										minValue = valueP;
										startX = i0;
										startY = j0;
										resultX = xx;
										resultY = yy;
										obstacleX = xxx;
										obstacleY = yyy;
									}
								}*/
							}
						}

					}
				}

			}
		}
	}

	// ??¡Ü?¦¸¡¤ ¡¥¡ê¡§ ¡ë¡Ý?¦¸¡¤¦Ð?¡ê???¡Âa¨C?¨C?¡Ç?¡°¡®¡­?¡Ü?¡Æ¡Â¡ê?
	cout << startX << ' ' << startY << ' ' << resultX << ' ' << resultY << ' ' << obstacleX << ' ' << obstacleY << endl;

}
