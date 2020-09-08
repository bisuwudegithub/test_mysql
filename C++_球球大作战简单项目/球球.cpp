#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define WIN_WIDTH 1024
#define WIN_HEIGHT 640
#define MAP_WIDTH (WIN_WIDTH * 5)
#define MAP_HEIGHT (WIN_HEIGHT * 5)
#define FOOD_NUM 1000 //食物数量
#define AI_NUM 500 //人工智障数量
//球球大作战  esayx图形库

//用变量表示玩家的坐标
struct Ball
{
	int x;
	int y;
	int r;
	int flag;//是否存在标志
	DWORD color;//小球颜色
}player,food[FOOD_NUM],ai[AI_NUM];//定义变量

//int a;图片 IMAGE map；
IMAGE map(MAP_WIDTH,MAP_HEIGHT);

//摄像机位置
POINT cameraPos;

void CameraUpdate()
{
	//以人物为中心，计算摄像机的位置
	cameraPos.x = player.x - WIN_WIDTH / 2;
	cameraPos.y = player.y - WIN_HEIGHT / 2;

	if(cameraPos.x < 0) cameraPos.x = 0;
	if(cameraPos.y < 0) cameraPos.y = 0;
	if(cameraPos.x > MAP_WIDTH - WIN_WIDTH) cameraPos.x = MAP_WIDTH - WIN_WIDTH;
	if(cameraPos.y > MAP_HEIGHT - WIN_HEIGHT) cameraPos.y = MAP_HEIGHT - WIN_HEIGHT;
}
//初始化数据
void GameInit()
{
	//播放音乐
	mciSendString("open ./微微.mp3 alias BGM",0,0,0);
	mciSendString("play BGM repeat", 0 , 0, 0);
	//设置随机数种子
	srand((unsigned)time(NULL));

	player.x = rand()%MAP_WIDTH;
	player.y = rand()%MAP_HEIGHT;
	player.r = 15;
	player.flag = true;
	player.color = RGB(rand() % 256,rand() % 256,rand() % 256);
	//初始化食物数据
	for (int i = 0; i < FOOD_NUM;i++)
	{
		food[i].x = rand() % MAP_WIDTH;
		food[i].y = rand() % MAP_HEIGHT;
		food[i].r = rand() % 5 + 1;
		food[i].flag = true;
		food[i].color = RGB(rand() % 256,rand() % 256,rand() % 256);
	}
	//初始化AI
	for (int i = 0; i < AI_NUM;i++)
	{
		ai[i].x = rand() % MAP_WIDTH;
		ai[i].y = rand() % MAP_HEIGHT;
		ai[i].r = rand() % 15 + 1;
		ai[i].flag = true;
		ai[i].color = RGB(rand() % 256,rand() % 256,rand() % 256);
	}

}
//绘制玩家
void GameDraw()
{
	//加上双缓中绘图，防止闪屏
	BeginBatchDraw();
	//设置工作区
	SetWorkingImage(&map);
	//设置背景颜色
	setbkcolor(WHITE);
	//清屏
	cleardevice();
	
	//绘制食物
	for (int i =0; i < FOOD_NUM ; i++)
	{
		if(food[i].flag)
		{
			setfillcolor(food[i].color);
			solidcircle(food[i].x,food[i].y,food[i].r);
		}
	}
	//绘制智障
	for (int i =0; i < AI_NUM ; i++)
	{
		if(ai[i].flag)
		{
			setfillcolor(ai[i].color);
			solidcircle(ai[i].x,ai[i].y,ai[i].r);
		}
	}
	//绘制玩家
	if(player.flag)
	{
		setfillcolor(player.color);
		solidcircle(player.x,player.y,player.r);
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		outtextxy(player.x,player.y,"劫中甜");//需要设置:点击项目，属性，常规，字符集，使用多字节字符集

	}
	SetWorkingImage();//恢复默认工作区
	CameraUpdate();

	putimage(0,0,WIN_WIDTH,WIN_HEIGHT,&map,cameraPos.x,cameraPos.y);

	EndBatchDraw();//结束双缓冲绘图
}
//控制玩家
void PlayerContrl(int speed)
{
	//往上移动，什么发生改变？y坐标减
	if(GetAsyncKeyState(VK_UP) && player.y - player.r >= 0)
	{
		player.y -= speed;
	}
	if(GetAsyncKeyState(VK_DOWN) && player.y + player.r< MAP_HEIGHT)
	{
		player.y += speed;
	}
	if(GetAsyncKeyState(VK_LEFT) && player.x - player.r >= 0 )
	{
		player.x -= speed;
	}
	if(GetAsyncKeyState(VK_RIGHT) && player.y + player.r< MAP_WIDTH)
	{
		player.x += speed;
	}
}

//求两点之间的距离
double DisTance(struct Ball b1,struct Ball b2)
{
	return sqrt((double)(b1.x - b2.x) *(b1.x + b2.x)  + (b1.y - b2.y)*(b1.y + b2.y)); 
}
//玩家吃食物
void EatFood()
{
	for(int i = 0; i < FOOD_NUM;i++)
	{
		if(food[i].flag && DisTance(player,food[i]) < player.r)
		{
			food[i].flag = false;
			player.r += food[i].r / 4;
		}
	}
}

//追逐算法
void Chase(struct Ball *chase,struct Ball run)
{
	chase->x < run.x ? chase->x += 2 : chase -> x -= 2;//x改变
	chase->y < run.y ? chase->y += 2 : chase -> y -= 2;//改变
}
void aiMove()
{
	for(int i = 0; i < AI_NUM;i++)
	{
		if(ai[i].flag )
		{
			Chase(&ai[i],player);
		}
	}
}
int main()
{
	//创建窗口
	initgraph(WIN_WIDTH,WIN_HEIGHT);

	GameInit();
	
	//需要不断的处理绘制图，以及获取键盘消息...循环
	while (1)
	{
		aiMove();
		GameDraw();
		EatFood();
		PlayerContrl(10);
	}

	getchar();
	return 0;
}
/*
还需开发
1.智障吃智障
2.智障吃食物
3.玩家吃智障
4.智障吃玩家
5.分裂，合并
*/