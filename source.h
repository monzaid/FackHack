#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define SIZE_L 60 
#define SIZE_H 45 
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UPLEFT 4
#define UPRIGHT 5
#define DOWNLEFT 6
#define DOWNRIGHT 7
#define ROAD 100
#define HIDE_ROAD 101
#define CLOSE_DOOR 102
#define OPEN_DOOR 103
#define BAD_DOOR 104
#define HIDE_DOOR 105
#define WALL 106
#define STAIR_UP 107
#define STAIR_DOWN 108
#define UWALL 109
#define LWALL 110
#define ULWALL 111
#define URWALL 112
#define DLWALL 113
#define DRWALL 114
#define HOUSE_SIZE_MIN 4
#define HOUSE_SIZE_L_MAX SIZE_L/5
#define HOUSE_SIZE_H_MAX SIZE_H/5
#define LAWFUL 1
#define NEUTRAL 0
#define CHAOSTIC -1
#define ANAMY -2
#define MAXANAMY 20
#define ITEM_KIND 11
#define Hide_Probability 97
#define name_max_long 20
#define INF -12345 
#define EMPTY 0 
#define IN_HAND 1
#define BEING_WORN 2
#define RIGHT_HAND 3
#define LEFT_HAND 4
#define READY 5
int total_anamy;
int houses[SIZE_L][4];//x,y,l,h
int dirx[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int diry[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int see[SIZE_H][SIZE_L];
int map[SIZE_H][SIZE_L];
int geography[SIZE_H][SIZE_L];
int map_monster[SIZE_H][SIZE_L];
int history[SIZE_H][SIZE_L];
int map_item[SIZE_H][SIZE_L];
int stair[6];
char player_name[name_max_long];
char item_name[ITEM_KIND][7] = {"�����", "����", "����", "����", "����", "�鱾", "��ָ", "ҩˮ", "ʳ��", "����", "��ʯ"};
char item_symbol[ITEM_KIND] = {'"', ')', '[', '?', '/', '+', '=', '!', '%', '(', '*'};
time_t t;
struct monster_node{
	char name[name_max_long];
	char symbol;
	int color;
	int frequency, corpse;
	int power, magic;
	int attack, fance, speed;
	int party;
}monster[100];
struct monster_body{
	int num;
	char name[name_max_long];
	char symbol;
	int color;
	int frequency, corpse;
	int power, magic;
	int attack, fance, speed;
	int party;
	int x, y;
	struct monster_body *next;
};
struct item_node{
	char symbol;
	int color;
	char name[name_max_long];
	int s1, s2, d;
	int corpse, create, num, r, state, time;
}item[100]; 
struct item_body{
	char symbol, operation;
	int color;
	char name[name_max_long];
	int s1, s2, d;
	int corpse, create, num, r, state, time;
	int x, y;
	struct item_body *next;
}*player_items, *items; 
/*
struct news_node{
	char a[100];
	struct news_node *next;
};
*/
struct monster_body *monsters, *monsters_tail;
int monster_num; 
//struct news_node *news, *news_tail;
char choice;
int seee;
int lvl, ti, del_news, nextunit, isi, ttt;
char clss[101] = "                                        ";
int book[SIZE_L];
int hou = 10, unit = 10;
char news[50][100];
int news_long;
int player_items_long, item_num;
struct item_body items_head = (struct item_body){'@', '@', -100, "head", -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, NULL}, player_items_head = (struct item_body){'@', '@', -100, "head", -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, NULL};
/*
int cmpascii (const void * a, const void * b){
	if ( (*(item_node *)a).language == (*(item_node *)b).language )
		return ( strcmp((*(item_node *)a).word, (*(item_node *)b).word) );
	return ( (*(item_node *)a).language - (*(item_node *)b).language );
}*/

void gotoxy(int x, int y)//��λ���λ�õ�ָ������
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

/*
��ɫ����SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ǰ��ɫ | ����ɫ | ǰ����ǿ | ������ǿ);
	ǰ��ɫ������0-15 �� FOREGROUND_XXX ��ʾ	������XXX����BLUE��RED��GREEN��ʾ�� 
	ǰ����ǿ������8 �� FOREGROUND_INTENSITY ��ʾ
	����ɫ������16 32 64 �� BACKGROUND_XXX ������ɫ��ʾ 
	������ǿ�� ����128 �� BACKGROUND_INTENSITY ��ʾ
��ҪӦ�ã��ı�ָ�����������뱳������ɫ
ǰ����ɫ��Ӧֵ�� 
����0=��ɫ                8=��ɫ����
  ��1=��ɫ                9=����ɫ        ʮ������        ����                        
����2=��ɫ                10=����ɫ       0xa        ����
����3=����ɫ              11=��ǳ��ɫ     0xb��
����4=��ɫ                12=����ɫ       0xc����
����5=��ɫ                13=����ɫ       0xd        ����
����6=��ɫ                14=����ɫ       0xe        ����
����7=��ɫ                15=����ɫ       0xf 
����Ҳ���԰���Щֵ���óɳ�����
*/
void txtcolor(short x)	//�Զ��庯���ݲ����ı���ɫ 
{
    if(x>=0 && x<=15)//������0-15�ķ�Χ��ɫ
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//ֻ��һ���������ı�������ɫ 
    else//Ĭ�ϵ���ɫ��ɫ
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void landcolor(short x)	//�Զ��庯���ݲ����ı���ɫ 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void allcolor(short txt, short land)	//�Զ��庯���ݲ����ı���ɫ 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),txt | FOREGROUND_INTENSITY | land | BACKGROUND_INTENSITY);
}
