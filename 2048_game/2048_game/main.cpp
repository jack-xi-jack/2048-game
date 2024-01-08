#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>




#define MAX_GRID 4 //每行格子数
#define	GRID_WIDTH 100 //格子宽度
#define INTERVAL 15 //间隔
enum Color  //枚举格子颜色
{
	zero = RGB(205,193,180),  //0的颜色
	twoTo1 = RGB(230,228,218),//2的颜色
	twoTo2 = RGB(237, 224, 200),//4的颜色
	twoTo3 = RGB(242, 177, 121),//8的颜色
	twoTo4 = RGB(245, 149, 99),//16的颜色
	twoTo5 = RGB(246, 124, 95),//32的颜色
	twoTo6 = RGB(246, 94, 59),//64的颜色
	twoTo7 = RGB(242, 177, 121),//128的颜色
	twoTo8 = RGB(237, 204, 97),//256的颜色
	twoTo9 = RGB(255, 0, 218),//512的颜色
	twoTo10 = RGB(145, 0, 72),//1024的颜色
	twoTo11 = RGB(242, 17, 158),//2048的颜色
	back = RGB(187, 173, 160),//背景颜色
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];  //全局变量自动初始化为0
POINT pos[MAX_GRID][MAX_GRID];//为了方便，先保存每个格子的左上角的坐标
bool flag = false;
//定义函数，随机返回2或者4
int twoOrFour()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
//在数组的随机位置产生，把数放到数组里面
void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0)
		{
			map[x][y] = twoOrFour();
			break;
		}
	}
}

void GameInit()
{

	//设置随机数种子
	srand(GetTickCount());
	
	//计算格子坐标
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			pos[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
			pos[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
		}
	}
	//游戏开始随机生成两个数
	CreateNumber();
	CreateNumber();
}
void GameDraw()
{
	setbkcolor(back);
	cleardevice();
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			
			for (int q = 0; q < 12; q++)
			{
				if (map[i][k] == num[q])
				{
					setfillcolor(arr[q]);
					solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_WIDTH); //设置矩形
					if (map[i][k] != 0)
					{
						char number[5] = " ";
						settextcolor(RGB(119,110,101));
						settextstyle(50, 0, "楷体");
						setbkmode(TRANSPARENT);//设置背景模式，透明
						sprintf(number, "%d", map[i][k]);
						//用格子的一半减去字符串宽度的一半,为了文字居中显示
						int tempx= GRID_WIDTH / 2 - textwidth(number) / 2;
						int tempy = GRID_WIDTH / 2 - textheight(number) / 2;	
						outtextxy(pos[i][k].x+tempx, pos[i][k].y+tempy, number);
					}
				}
			}
			////判断map值是多少
			//if (map[i][k] == num[?])
			//{
			//	setfillcolor(zero);//初始化颜色
			//}
			//else
			//{
			//	setfillcolor(twoTo4);
			//}
			
			
		} 
	}
	
}	
//上移
void moveup()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{ 
			if (map[begin][i]!=0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp++; 
				flag = true;
				
			}
		}
	}
	printf("up\n");
}
//下移
void movedown()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID-1;
		for (int begin = MAX_GRID-2; begin >=0; begin--)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp--;
				flag = true;

			}
		}
	}
	printf("down\n");
}
//左移
void moveleft()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp+1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp++;
				flag = true;

			}
		}
	}

	printf("left\n");
}

//右移
void moveright()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID - 1;
		for (int begin = MAX_GRID - 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp--;
				flag = true;

			}
		}
	}
	printf("right\n");
}
void GameJude()
{
	if (flag)
	{
		CreateNumber();
		flag = false;
	}
}
//键盘控制数字移动
void GameContorl()
{
	 //获取键盘输入，_getch();
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		moveup();
		break;
	case's':
	case 'S':
	case 80:
		movedown();
		break;
	case'a':
	case 'A':
	case 75:
		moveleft(); 
		break;
	case'd':
	case 'D':
	case 77:
		moveright();
		break;
	}
}
int main()
{

	//创建窗口
	initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL,1);
	GameInit();
	while (1)
	{
		GameDraw();
		GameContorl();
		GameJude();
	}
	getchar();
	return 0;
}