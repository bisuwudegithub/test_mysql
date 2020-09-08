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
#define FOOD_NUM 1000 //ʳ������
#define AI_NUM 500 //�˹���������
//�������ս  esayxͼ�ο�

//�ñ�����ʾ��ҵ�����
struct Ball
{
	int x;
	int y;
	int r;
	int flag;//�Ƿ���ڱ�־
	DWORD color;//С����ɫ
}player,food[FOOD_NUM],ai[AI_NUM];//�������

//int a;ͼƬ IMAGE map��
IMAGE map(MAP_WIDTH,MAP_HEIGHT);

//�����λ��
POINT cameraPos;

void CameraUpdate()
{
	//������Ϊ���ģ������������λ��
	cameraPos.x = player.x - WIN_WIDTH / 2;
	cameraPos.y = player.y - WIN_HEIGHT / 2;

	if(cameraPos.x < 0) cameraPos.x = 0;
	if(cameraPos.y < 0) cameraPos.y = 0;
	if(cameraPos.x > MAP_WIDTH - WIN_WIDTH) cameraPos.x = MAP_WIDTH - WIN_WIDTH;
	if(cameraPos.y > MAP_HEIGHT - WIN_HEIGHT) cameraPos.y = MAP_HEIGHT - WIN_HEIGHT;
}
//��ʼ������
void GameInit()
{
	//��������
	mciSendString("open ./΢΢.mp3 alias BGM",0,0,0);
	mciSendString("play BGM repeat", 0 , 0, 0);
	//�������������
	srand((unsigned)time(NULL));

	player.x = rand()%MAP_WIDTH;
	player.y = rand()%MAP_HEIGHT;
	player.r = 15;
	player.flag = true;
	player.color = RGB(rand() % 256,rand() % 256,rand() % 256);
	//��ʼ��ʳ������
	for (int i = 0; i < FOOD_NUM;i++)
	{
		food[i].x = rand() % MAP_WIDTH;
		food[i].y = rand() % MAP_HEIGHT;
		food[i].r = rand() % 5 + 1;
		food[i].flag = true;
		food[i].color = RGB(rand() % 256,rand() % 256,rand() % 256);
	}
	//��ʼ��AI
	for (int i = 0; i < AI_NUM;i++)
	{
		ai[i].x = rand() % MAP_WIDTH;
		ai[i].y = rand() % MAP_HEIGHT;
		ai[i].r = rand() % 15 + 1;
		ai[i].flag = true;
		ai[i].color = RGB(rand() % 256,rand() % 256,rand() % 256);
	}

}
//�������
void GameDraw()
{
	//����˫���л�ͼ����ֹ����
	BeginBatchDraw();
	//���ù�����
	SetWorkingImage(&map);
	//���ñ�����ɫ
	setbkcolor(WHITE);
	//����
	cleardevice();
	
	//����ʳ��
	for (int i =0; i < FOOD_NUM ; i++)
	{
		if(food[i].flag)
		{
			setfillcolor(food[i].color);
			solidcircle(food[i].x,food[i].y,food[i].r);
		}
	}
	//��������
	for (int i =0; i < AI_NUM ; i++)
	{
		if(ai[i].flag)
		{
			setfillcolor(ai[i].color);
			solidcircle(ai[i].x,ai[i].y,ai[i].r);
		}
	}
	//�������
	if(player.flag)
	{
		setfillcolor(player.color);
		solidcircle(player.x,player.y,player.r);
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		outtextxy(player.x,player.y,"������");//��Ҫ����:�����Ŀ�����ԣ����棬�ַ�����ʹ�ö��ֽ��ַ���

	}
	SetWorkingImage();//�ָ�Ĭ�Ϲ�����
	CameraUpdate();

	putimage(0,0,WIN_WIDTH,WIN_HEIGHT,&map,cameraPos.x,cameraPos.y);

	EndBatchDraw();//����˫�����ͼ
}
//�������
void PlayerContrl(int speed)
{
	//�����ƶ���ʲô�����ı䣿y�����
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

//������֮��ľ���
double DisTance(struct Ball b1,struct Ball b2)
{
	return sqrt((double)(b1.x - b2.x) *(b1.x + b2.x)  + (b1.y - b2.y)*(b1.y + b2.y)); 
}
//��ҳ�ʳ��
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

//׷���㷨
void Chase(struct Ball *chase,struct Ball run)
{
	chase->x < run.x ? chase->x += 2 : chase -> x -= 2;//x�ı�
	chase->y < run.y ? chase->y += 2 : chase -> y -= 2;//�ı�
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
	//��������
	initgraph(WIN_WIDTH,WIN_HEIGHT);

	GameInit();
	
	//��Ҫ���ϵĴ������ͼ���Լ���ȡ������Ϣ...ѭ��
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
���迪��
1.���ϳ�����
2.���ϳ�ʳ��
3.��ҳ�����
4.���ϳ����
5.���ѣ��ϲ�
*/