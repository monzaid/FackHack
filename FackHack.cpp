#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif
#ifndef CREATE_H
#define CREATE_H
#include "create.h"
#endif
#ifndef DATA_H
#define DATA_H
#include "data.h"
#endif
#include "act.h"

int main (){
	system("mode con cols=140 lines=66");
	monsters = (struct monster_body *) malloc (sizeof (struct monster_body));
	struct monster_body player;
	monsters_tail = monsters = &player;
	player.next = NULL;
	struct monster_body *monsters_temp;
	creatmonsters();
	creatitems();
	start:
	system("cls");
	printf(
	"$$$$$$$$\\  $$$$$$\\  $$\\   $$\\ $$$$$$$$\\ $$\\   $$\\  $$$$$$\\   $$$$$$\\  $$\\   $$\\ \n"
	"$$  _____|$$  __$$\\ $$ | $$  |$$  _____|$$ |  $$ |$$  __$$\\ $$  __$$\\ $$ | $$  |\n"
	"$$ |      $$ /  $$ |$$ |$$  / $$ |      $$ |  $$ |$$ /  $$ |$$ /  \\__|$$ |$$  /\n"
	"$$$$$\\    $$$$$$$$ |$$$$$  /  $$$$$\\    $$$$$$$$ |$$$$$$$$ |$$ |      $$$$$  /\n"
	"$$  __|   $$  __$$ |$$  $$<   $$  __|   $$  __$$ |$$  __$$ |$$ |      $$  $$<\n"
	"$$ |      $$ |  $$ |$$ |\\$$\\  $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$\\ $$ |\\$$\\ \n"
	"$$ |      $$ |  $$ |$$ | \\$$\\ $$$$$$$$\\ $$ |  $$ |$$ |  $$ |\\$$$$$$  |$$ | \\$$\\ \n"
	"\\__|      \\__|  \\__|\\__|  \\__|\\________|\\__|  \\__|\\__|  \\__| \\______/ \\__|  \\__|\n"
	"\n\t\t\t      welcome to fakehack\n--------------------------------------------------------------------------------\n\t\t    [1 - start]    [2 - help]    [3 - end]\n");
	while(choice = getch()){
		if (choice == '1'){
			system("cls");
			FILE *fp = fopen("player.txt", "r+");
			if (fp != NULL){
				printf("continue game?(y/n)\n");
				while(choice = getch()){
					if (choice == 'y' || choice == 'Y'){
						fclose(fp);
						loadplayer();
						break;
					}
					else if (choice == 'n' || choice == 'N')
						break;
				}
			}
			if (player.symbol != '@'){
				system("cls");
				printf("whis you name?\n");
				gets(player_name);
				system("cls");
				printf("picking yours profession:\n\t1 - caveman\n\t2 - monk\n\t3 - tourist\n");
				while(choice = getch())
					if (choice == '1'){
						strcpy(monster[0].name, "caveman");
						monster[0].power = 20;
						monster[0].magic = 3;
						monster[0].attack = 3;
						monster[0].fance = 2;
						monster[0].speed = 100;
						break;
					}
					else if (choice == '2'){
						strcpy(monster[0].name, "monk");
						monster[0].power = 15;
						monster[0].magic = 7;
						monster[0].attack = 4;
						monster[0].fance = 1;
						monster[0].speed = 105;
						break;
					}
					else if (choice == '3'){
						strcpy(monster[0].name, "tourist");
						monster[0].power = 10;
						monster[0].magic = 6;
						monster[0].attack = 2;
						monster[0].fance = 0;
						monster[0].speed = 120;
						break;
					}
				system("cls");
				monster[0].party = LAWFUL;
				ti = 1;
				lvl = 1;
				memset(book, 0, sizeof(book));
				
				strcpy(monsters->name, monster[0].name);
				monsters->num = 0;
				monsters->power = monster[0].power;
				monsters->magic = monster[0].magic;
				monsters->attack = monster[0].attack;
				monsters->fance = monster[0].fance;
				monsters->speed = 0;
				monsters->party = monster[0].party;
				monsters->color = monster[0].color = 929;
				monsters->symbol = monster[0].symbol = '@';
				
				system("cls");
				
				printf("请输入关卡个数：");
				scanf("%d", &unit);
				printf("请输入房间个数：");
				scanf("%d", &hou);
			}
			break;
		}
		else if (choice == '2'){
			system("cls");
			printf("w 或 8\t上\n"
					"s 或 2\t下\n"
					"a 或 4\t左\n"
					"d 或 6\t右\n"
					". 或 5\t休息\n"
					"7\t左上\n"
					"9\t右上\n"
					"1\t左下\n"
					"3\t右下\n"
					"c\t开门 或 关门\n"
					"k\t踢门\n"
					" (空格)\t搜索\n"
					"i\t物品\n"
					"<\t下楼梯\n"
					">\t上楼梯\n"
					"S\t保存游戏\n"
					",\t捡起\n"
					"x\t手持\n"
					"W\t穿戴\n"
					"P\t佩戴\n"
					"A\t脱下\n"
					"Q\t准备\n"
					"f\t发射\n"
					"t\t投置\n"
					"D\t扔下\n"
					"q\t喝\n"
					"\n按任意键返回主菜单\n");
			getch(); 
			goto start;
		}
		else if (choice == '3')
			return 0;
	}
	
	
	for ( ; lvl <= unit; lvl++){
		nextunit = 0;
		total_anamy = 0;
		for (monsters_temp = monsters->next; monsters_temp; monsters_temp = monsters_temp->next)
			free(monsters_temp);
		monsters->next = NULL;
		monsters_tail = &player;
		
		system("cls");
		if (book[lvl] == 1){
			load();
			for (int i = 0; i < SIZE_H; i++){
				for (int j = 0; j < SIZE_L; j++)
					if (history[i][j] == 1){
						if (map_monster[i][j] == 0){
							monsters->x = j;
							monsters->y = i;
						}
						if (map_item[i][j] != -1){
							landcolor(item[map_item[i][j]].color);
							printf("%c", item[map_item[i][j]].symbol);
							txtcolor(16);
						}
						else if (geography[i][j] >= UWALL && geography[i][j] <= DRWALL || geography[i][j] == HIDE_DOOR)
							printf("#");
						else if (geography[i][j] == CLOSE_DOOR){
							txtcolor(12);
							printf("+");
							txtcolor(16);
						}
						else if (geography[i][j] == OPEN_DOOR){
							landcolor(848);
							printf(" ");
							txtcolor(16);
						}
						else if (geography[i][j] == BAD_DOOR)
							printf(".");
						else if (geography[i][j] == STAIR_UP)
							printf(">");
						else if (geography[i][j] == STAIR_DOWN)
							printf("<");
						else if (geography[i][j] == 0 || geography[i][j] == HIDE_ROAD)
							printf(" ");
						else if (geography[i][j] == ROAD)
							printf(":");
						else
							printf(".");
					}
					else
						printf(" ");
				printf("\n");
			}printf("1");
		}
		else{
			creatmap(hou);
			book[lvl] = 1;
			if (lvl == 1){
				save();
				saveplayer();
			}
			monsters->x = stair[0];
			monsters->y = stair[1];
			map_monster[monsters->y][monsters->x] = 0;
		}
		
		show();
		
		while (ti){
			for (monsters_temp = monsters; monsters_temp; monsters_temp = monsters_temp->next){
				monsters_temp->speed += monster[monsters_temp->num].speed;
				while (monsters_temp->speed >= 100){
					monsters_temp->speed -= 100;
					action(monsters_temp);
					if (monsters_temp == monsters)
						ti++;
					if (ti % 4 == 0 && monsters_temp == monsters && ti / 4 != ttt){
						ttt = ti / 4;
						monsters_temp->power = (monsters_temp->power < monster[0].power) ? monsters_temp->power + 1 : monster[0].power;
					}
				}
				if (monsters->power <= 0){
					system("cls");
					printf("Game Over");
					exit(0);
				}
				if (nextunit == 1)
					break;
			}
			if (nextunit == 1)
				break;
			int frequency0, frequency1;
			for (int i = 1; i < monster_num; i++){
				if (total_anamy >= MAXANAMY)
					break;
				frequency0 = rand() * monsters->x % 10000;
				frequency1 = rand() * monsters->y % 10000;
				if (abs(frequency0 - frequency1) <= monster[i].frequency * 1.0 * (MAXANAMY - total_anamy) / MAXANAMY){
					int ac = 0;
					struct monster_body *a = (struct monster_body *) malloc (sizeof(struct monster_body));
					makenewmonster(i, a);
					do{
						if (++ac == 10000){
							free(a);
							break;
						}
						a->x = rand() % SIZE_L;
						a->y = rand() % SIZE_H;
					}while (geography[a->y][a->x] == 0 || map_monster[a->y][a->x] >= 0 || geography[a->y][a->x] >= HIDE_ROAD && geography[a->y][a->x] <= DRWALL && see[a->y][a->x] == 1);
					if (ac == 10000)
						break;
					map_monster[a->y][a->x] = a->num;
					total_anamy++;
					monsters_tail->next = a;
					monsters_tail = monsters_tail->next;
				}
			}
			
			gotoxy (monsters->x, monsters->y);
		}
	}
	system("cls");
	printf("YOU WIN!!!");
	
	free(monsters);
	free(monsters_tail);
	free(monsters_temp);
	
	return 0;
}


