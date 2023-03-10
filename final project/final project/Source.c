#include <stdio.h>
#include <stdlib.h>	
#include <conio.h>	
#include <time.h>
#define X 1
#define O 2

char toSymbol(int num) {
	switch (num) {
	case 0:
		return '.';		//空交叉點
	case X:
		return 'X';		//棋子X
	case O:
		return 'O';		//棋子O
	case 9:
		return '+';		//星位
	}
}

int check_hor(int panel[][15], int y, int x, int object) {	//檢查x軸方向上是否連成五子
	int stoneCount = 0;
	for (int i = x - 4; i <= x + 4; i++) {
		if (panel[y][i] == object) {
			stoneCount++;
			if (stoneCount == 5) {
				break;
			}
		}
		else {
			stoneCount = 0;
		}
	}
	if (stoneCount >= 5) {
		return 1;
	}
	else {
		return 0;
	}
}

int check_ver(int panel[][15], int y, int x, int object) {	//檢查y軸方向上是否連成五子
	int stoneCount = 0;
	for (int i = y - 4; i <= y + 4; i++) {
		if (panel[i][x] == object) {
			stoneCount++;
			if (stoneCount == 5) {
				break;
			}
		}
		else {
			stoneCount = 0;
		}
	}
	if (stoneCount >= 5) {
		return 1;
	}
	else {
		return 0;
	}
}

int check_slash(int panel[][15], int y, int x, int object) {	//檢查函數y=-x的影象所在直線方向上是否連成五子
	int stoneCount = 0;
	for (int i = y - 4, j = x - 4; i <= y + 4; i++, j++) {
		if (panel[i][j] == object) {
			stoneCount++;
			if (stoneCount == 5) {
				break;
			}
		}
		else {
			stoneCount = 0;
		}
	}
	if (stoneCount >= 5) {
		return 1;
	}
	else {
		return 0;
	}
}

int check_backslash(int panel[][15], int y, int x, int object) {	//檢查函數y=x的影象所在直線方向上是否連成五子
	int stoneCount = 0;
	for (int i = y + 4, j = x - 4; i >= y - 4; i--, j++) {
		if (panel[i][j] == object) {
			stoneCount++;
			if (stoneCount == 5) {
				break;
			}
		}
		else {
			stoneCount = 0;
		}
	}
	if (stoneCount >= 5) {
		return 1;
	}
	else {
		return 0;
	}
}

int main(void) {
	int count1 = 0, count2 = 0, fun, rou, cnt = 90;
	FILE* fptr;


	//時間
	time_t time_ptr;
	struct tm* tmp_ptr = NULL;
	int year, month, day, hour, minute, sec;
	time(&time_ptr);// 獲取當前時間
	tmp_ptr = localtime(&time_ptr);

	year = tmp_ptr->tm_year + 1900;
	month = tmp_ptr->tm_mon + 1;
	day = tmp_ptr->tm_mday;

	hour = tmp_ptr->tm_hour;
	minute = tmp_ptr->tm_min;
	sec = tmp_ptr->tm_sec;


	fptr = fopen("index.txt", "a");
	fprintf(fptr, "[%d-%d-%d %d:%d:%d]\n ", year, month, day, hour, minute, sec);
	fprintf(fptr, "        X    O\n");
	fprintf(fptr, "----------------\n");
	printf("***************************\n");
	printf("*        五子棋遊戲       *\n");
	printf("***************************\n");
	printf("*說明:                    *\n");
	printf("*  可以任意選擇局數       *\n");
	printf("*  (偶數局先贏一半獲勝)   *\n");
	printf("*  wsad空白鍵與24685控制  *\n");
	printf("*  l直接結束遊戲          *\n");
	printf("*  結果會存在外部檔案     *\n");
	printf("***************************\n");
	printf("請輸入遊玩局數；");

	scanf("%d", &fun);
	if (fun % 2 == 0)
		rou = (fun / 2);
	else
		rou = (fun / 2 + 1);
	printf("%d戰%d勝\n", fun, rou);
	for (int i = 1; i <= fun; i++)
	{
		int key = 0;

		//棋盤初始狀態
		int panel[15][15] =
		{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,9,0,0,0,0,0,0,0,9,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,9,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,9,0,0,0,0,0,0,0,9,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

		int cus[] = { 7,7 };	//遊標初始位置
		int turn = X;		//初始玩家
		int winner = 0, equal = 0, start, end;		//贏家：預設暫時沒有
		int total = 0;
		printf("按1開始:");
		scanf("%d", &start);
		if (start == 1)
		{
			while (1) {
				//清屏，並顯示現在是誰走棋
				system("cls");
				printf("現在是【%c】方走棋……\n", toSymbol(turn));
				//顯示棋盤
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (i == cus[0] && j == cus[1]) {
							printf("[ %c ]", toSymbol(panel[i][j]));
						}
						else {
							printf("  %c  ", toSymbol(panel[i][j]));
						}
					}//next j
					printf("\n\n");
				}//next i

				//平手
				if (equal != 0)
				{
					printf("平局\n");
					if (i != fun)
					{
						fprintf(fptr, "第%d局   平   平\n", i);
						fprintf(fptr, "----------------\n");
						break;
					}
					else
					{
						fprintf(fptr, "第%d局   平   平\n", i);
						fprintf(fptr, "----------------\n");
						if (count1 == rou)
						{
							printf("玩家X獲勝!\n");
							fprintf(fptr, "   玩家X獲勝\n");
							fprintf(fptr, "====================\n");
							return 0;

						}
						else if (count2 == rou)
						{
							printf("玩家O獲勝!\n");
							fprintf(fptr, "   玩家O獲勝\n");
							fprintf(fptr, "====================\n");
							return 0;
						}
						else
						{
							if (count1 == count2)
							{
								printf("平手");
								fprintf(fptr, "     平手\n");
								fprintf(fptr, "====================\n");
								return 0;
							}
							else if (count1 > count2)
							{
								printf("玩家X獲勝!\n");
								fprintf(fptr, "   玩家X獲勝\n");
								fprintf(fptr, "====================\n");
								return 0;
							}
							else if (count1 < count2)
							{
								printf("玩家O獲勝!\n");
								fprintf(fptr, "   玩家O獲勝\n");
								fprintf(fptr, "====================\n");
								return 0;
							}
						}

					}
				}
				//如果 有人贏了，顯示贏家是誰
				if (winner != 0) {
					printf("五子連珠！玩家【%c】贏第%d局\n", toSymbol(winner), i);
					if (toSymbol(winner) == 'X')
					{
						count1++;
						fprintf(fptr, "第%d局   勝   敗\n", i);
						fprintf(fptr, "----------------\n");
					}

					else
					{
						count2++;
						fprintf(fptr, "第%d局   敗   勝\n", i);
						fprintf(fptr, "----------------\n");
					}
					//if (fun % 2 != 0)
					//{
					if (count1 == rou)
					{
						printf("玩家X獲勝!\n");
						fprintf(fptr, "   玩家X獲勝\n");
						fprintf(fptr, "====================\n");
						return 0;

					}
					else if (count2 == rou)
					{
						printf("玩家O獲勝!\n");
						fprintf(fptr, "   玩家O獲勝\n");
						fprintf(fptr, "====================\n");
						return 0;
					}
					if (i == fun)
						if (count1 == (rou - 1) && count2 == (rou - 1))
						{
							printf("平手");
							fprintf(fptr, "     平手\n");
							fprintf(fptr, "====================\n");
							return 0;
						}


					//}
					/*else {
						if (count1 == rou)
						{
							printf("玩家X獲勝!\n");
							fprintf(fptr, "   玩家X獲勝\n");
							fprintf(fptr, "====================\n");
							return 0;

						}
						else if (count2 == rou)
						{
							printf("玩家O獲勝!\n");
							fprintf(fptr, "   玩家O獲勝\n");
							fprintf(fptr, "====================\n");
							return 0;
						}
						if (count1 == (rou - 1) && count2 == (rou - 1))
						{
							printf("平手");
							fprintf(fptr, "     平手\n");
							fprintf(fptr, "====================\n");
							return 0;
						}
					}*/
					break;
				}

				//接收鍵盤事件
				key = getch();

				//按WASD進行控制，空格鍵落子，L鍵結束遊戲
				switch (key) {
				case 'w': case 'W':case '8':
					if (cus[0] == 0) cus[0] = 14;
					else cus[0]--;
					break;
				case 'a': case 'A':case'4':
					if (cus[1] == 0) cus[1] = 14;
					else cus[1]--;
					break;
				case 's': case 'S':case'2':
					if (cus[0] == 14) cus[0] = 0;
					else cus[0]++;
					break;
				case 'd': case 'D':case'6':
					if (cus[1] == 14) cus[1] = 0;
					else cus[1]++;
					break;
				case 32: case'5':

					if (panel[cus[0]][cus[1]] != X && panel[cus[0]][cus[1]] != O) {
						total++;
						panel[cus[0]][cus[1]] = turn;
						if (check_hor(panel, cus[0], cus[1], turn) == 1
							|| check_ver(panel, cus[0], cus[1], turn) == 1
							|| check_slash(panel, cus[0], cus[1], turn) == 1
							|| check_backslash(panel, cus[0], cus[1], turn) == 1) {
							winner = turn;
							break;
						}
						if (total == 225)
						{
							equal = turn;
							break;
						}


						if (turn == X) turn = O;
						else turn = X;
					}
					else {
						printf("這裡已經有子了，重來！\n");
						system("pause");
					}
					break;
				case 'l': case 'L':
					printf("結束程式……\n");
					system("pause");
					return 0;
				default:
					printf("無效按鍵！\n");
					system("pause");
					break;
				}
			}
		}

	}
	fclose(fptr);
	return 0;
}
