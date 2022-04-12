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

void show();
void action(struct monster_body *);

void move(int &x, int &y, char step){
	struct monster_body *monsterstemp;
	struct item_body *item_temp0, *item_temp1;
	for (monsterstemp = monsters; monsterstemp->next; monsterstemp = monsterstemp->next)
		if (monsterstemp->x == x && monsterstemp->y == y)
			break;
	
	if (step == 'c' || step == 'k'){
		char type = step;
		int temp = rand() % 10;
		gotoxy (0, SIZE_H+2);
		printf("�ĸ�����");
		gotoxy(monsters->x, monsters->y);
		step = getch();
		if (step == 's' || step == '2')
			step = DOWN;
		else if (step == 'w' || step == '8')
			step = UP;
		else if (step == 'a' || step == '4')
			step = LEFT;
		else if (step == 'd' || step == '6')
			step = RIGHT;
		else if (step == '7'){
			monsters->speed -= 50;
			step = UPLEFT;
		}
		else if (step == '9'){
			monsters->speed -= 50;
			step = UPRIGHT;
		}
		else if (step == '1'){
			monsters->speed -= 50;
			step = DOWNLEFT;
		}
		else if (step == '3'){
			monsters->speed -= 50;
			step = DOWNRIGHT;
		}
		if (!(step >= UP && step <= DOWNRIGHT)){
			strcpy(news[news_long++], "��Ч�ķ���");
			monsters->speed += 100; ti--;
			gotoxy (0, SIZE_H+2);
			printf("%s", clss);
			return;
		}
		if (x+dirx[step] < 0 || x+dirx[step] >= SIZE_L || y+diry[step] < 0 || y+diry[step] >= SIZE_H)//Խ�� 
			strcpy(news[news_long++], "��Կ���������һ��");
		else if (type == 'k' && geography[y+diry[step]][x+dirx[step]] == CLOSE_DOOR){
			if (temp >= 1 && temp <= 3){
				geography[y+diry[step]][x+dirx[step]] = BAD_DOOR;
				strcpy(news[news_long++], "\"������\"���߿�����");
			}
			else
				strcpy(news[news_long++], "\"������\"");
		}
		else if (type == 'c' && geography[y+diry[step]][x+dirx[step]] == CLOSE_DOOR){
			if (temp >= 3 && temp <= 7){
				geography[y+diry[step]][x+dirx[step]] = OPEN_DOOR;
				strcpy(news[news_long++], "�������");
			}
			else
				strcpy(news[news_long++], "���ڵֿ�");
		}
		else if (type == 'c' && geography[y+diry[step]][x+dirx[step]] == OPEN_DOOR){
			if (map_monster[y+diry[step]][x+dirx[step]] != -1 || map_item[y+diry[step]][x+dirx[step]] != -1)
				strcpy(news[news_long++], "ʲô������ס����");
			else if (temp >= 4 && temp <= 9){
				geography[y+diry[step]][x+dirx[step]] = CLOSE_DOOR;
				strcpy(news[news_long++], "���������");
			}
			else
				strcpy(news[news_long++], "���ڵֿ�");
		}
		else
			strcpy(news[news_long++], "��Կ���������һ��");
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	} 
	else if (step == ' '){
		for (int i = x - 1; i <= x + 1; i++)
			for (int j = y - 1; j <= y + 1; j++)
				if (i < 0 || i >= SIZE_L || j < 0 || j >= SIZE_H) continue;//Խ�� 
				else if (geography[j][i] == HIDE_ROAD && rand() % 10 == 4){
					geography[j][i] = ROAD;
					strcpy(news[news_long++], "���ҵ���һ�����ص�·��");
				}
				else if (geography[j][i] == HIDE_DOOR && rand() % 10 == 5){
					geography[j][i] = CLOSE_DOOR;
					strcpy(news[news_long++], "���ҵ���һ�����ص���");
				}
		return;
	}
	else if (step == 'S'){
		save(); saveplayer();
		monsters->speed += 100; ti--;
		strcpy(news[news_long++], "����ɹ�");
	}
	else if (step == 'x'){
		char aaa[100] = "װ��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->symbol == ')'){//������ 
					if (item_temp0->state == IN_HAND){
						strcpy(news[news_long], "���Ѿ�װ���� ");
						strcat(news[news_long++], item_temp0->name);
						monsters->speed += 100; ti--;
					}
					else{
						for (item_temp1 = player_items->next; item_temp1; item_temp1 = item_temp1->next){//ж������ 
							if (item_temp1->state == IN_HAND){
								item_temp1->state = EMPTY;
								monsters->attack += item_temp1->s1;
								monsters->speed -= 100; ti++;
								strcpy(news[news_long], "��ж���� ");
								strcat(news[news_long++], item_temp1->name);
								break;
							} 
						}
						item_temp0->state = IN_HAND;
						monsters->attack -= item_temp0->s1;
						strcpy(news[news_long], "��װ���� ");
						strcat(news[news_long++], item_temp0->name);
					} 
				}
				else{
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ��������");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 't'){
		char aaa[100] = "Ͷ��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				strcat(aaa, "\t������Ͷ����");
				gotoxy (0, SIZE_H+2);
				printf("%s", aaa);
				gotoxy(monsters->x, monsters->y);
				step = getch();
				if (step == 's' || step == '2')
					step = DOWN;
				else if (step == 'w' || step == '8')
					step = UP;
				else if (step == 'a' || step == '4')
					step = LEFT;
				else if (step == 'd' || step == '6')
					step = RIGHT;
				else if (step == '7'){
					monsters->speed -= 50;
					step = UPLEFT;
				}
				else if (step == '9'){
					monsters->speed -= 50;
					step = UPRIGHT;
				}
				else if (step == '1'){
					monsters->speed -= 50;
					step = DOWNLEFT;
				}
				else if (step == '3'){
					monsters->speed -= 50;
					step = DOWNRIGHT;
				}
				
				if (step >= UP && step <= DOWNRIGHT){
					//������Ʒ 
					if (item_temp0->state == IN_HAND){
						item_temp0->state = EMPTY; 
						monsters->attack += item_temp0->s1;
					} 
					else if (item_temp0->state == BEING_WORN){
						item_temp0->state = EMPTY; 
						monsters->fance -= item_temp0->d;
						monsters->speed -= 100; ti++;
						strcpy(news[news_long], "��ж���� ");
						strcat(news[news_long++], item_temp0->name);
					}
					else if (item_temp0->state == RIGHT_HAND || item_temp0->state == LEFT_HAND){
						item_temp0->state = EMPTY; 
						monsters->attack += item_temp0->s1;
						monsters->fance -= item_temp0->d;
						monsters->speed -= 100; ti++;
						strcpy(news[news_long], "��ж���� ");
						strcat(news[news_long++], item_temp0->name);
					}
				
					//��ֵ���� 
					item_temp0->x = monsters->x;
					item_temp0->y = monsters->y;
					
					strcpy(news[news_long], "��Ͷ���� ");
					strcat(news[news_long++], item_temp0->name); 
					
					for (int i = 0; i < item_temp0->r; i++){//���
						if (item_temp0->x+dirx[step] < 0 || item_temp0->x+dirx[step] >= SIZE_L || item_temp0->y+diry[step] < 0 || item_temp0->y+diry[step] >= SIZE_H) break;//Խ�� 
						else if (geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == 0 || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] >= UWALL && geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] <= DRWALL || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == CLOSE_DOOR || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_ROAD || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_DOOR) break;//��һ����ǽ
						else if (map_monster[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] != -1){//��һ���ǹ���
							//����һ������ 
							item_temp0->x += dirx[step];
							item_temp0->y += diry[step];
							
							struct monster_body *m;
							struct monster_body *mm;
							mm = monsters;
							for (m = monsters->next; m; m = m->next){
								if (item_temp0->x == m->x && item_temp0->y == m->y){
									if (item_temp0->s2 > 0)
										m->power = (item_temp0->s2 + m->power < monster[m->num].power) ? item_temp0->s2 + m->power : monster[m->num].power;
									else
										m->power = (-item_temp0->s2 > m->fance) ? m->power + item_temp0->s2 + m->fance : m->power - 1;
									strcpy(news[news_long], item_temp0->name); 
									strcat(news[news_long], "������ ");
									strcat(news[news_long++], monster[m->num].name); 
									if (m->power <= 0){//����
										strcpy(news[news_long], "��ɱ���� ");
										strcat(news[news_long++], monster[m->num].name); 
										mm->next = m->next;
										map_monster[item_temp0->y][item_temp0->x] = -1;
										if (m->next == NULL)
											monsters_tail = mm;
										free(m);
										total_anamy--;
									}
									break;
								}
								mm = m;
							}
							break;
						}
						item_temp0->x += dirx[step];
						item_temp0->y += diry[step];
					} 
					
					if (--(item_temp0->num) == 0){//ɾ�������Ʒ 
						for (item_temp1 = player_items; item_temp1; item_temp1 = item_temp1->next)
							if (item_temp1->next == item_temp0){
									item_temp1->next = item_temp0->next;
									break;
								}
						player_items_long--;
					}
					
					if (rand() % 100 >= item_temp0->corpse){//���� 
						if (item_temp0->num == 0) free(item_temp0);
						break;
					}
					
					for (item_temp1 = items->next; item_temp1; item_temp1 = item_temp1->next)
						if (strcmp(item_temp1->name, item_temp0->name) == 0 && item_temp0->x == item_temp1->x && item_temp0->y == item_temp1->y){//�ҵ��˵�����Ʒ 
								item_temp1->num += 1;
								if (item_temp0->num == 0) free(item_temp0);
								break;
							}
					
					if (item_temp1 == NULL){//û���ҵ�������Ʒ 
						item_temp1 = (struct item_body *) malloc (sizeof (struct item_body));
						makenewplayitem(item_temp1, item_temp0);
						item_temp1->num = 1;
						if (item_temp0->num == 0) free(item_temp0);
						
						item_temp1->next = items->next;
						items->next = item_temp1;
					}
					
					for (int i = 0; i <= item_num; i++)
						if (strcmp(item[i].name, item_temp1->name) == 0){
							map_item[item_temp0->y][item_temp0->x] = i;
							break;
						}
					
				}
				else{
					strcpy(news[news_long++], "��Ч�ķ���");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'f'){
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (item_temp0->state == READY){//�ҵ������׼������Ʒ
				char aaa[100] = "�����﷢�䣿";
				gotoxy (0, SIZE_H+2);
				printf("%s", aaa);
				gotoxy(monsters->x, monsters->y);
				step = getch();
				if (step == 's' || step == '2')
					step = DOWN;
				else if (step == 'w' || step == '8')
					step = UP;
				else if (step == 'a' || step == '4')
					step = LEFT;
				else if (step == 'd' || step == '6')
					step = RIGHT;
				else if (step == '7'){
					monsters->speed -= 50;
					step = UPLEFT;
				}
				else if (step == '9'){
					monsters->speed -= 50;
					step = UPRIGHT;
				}
				else if (step == '1'){
					monsters->speed -= 50;
					step = DOWNLEFT;
				}
				else if (step == '3'){
					monsters->speed -= 50;
					step = DOWNRIGHT;
				}
				
				if (step >= UP && step <= DOWNRIGHT){
					//��ֵ���� 
					item_temp0->x = monsters->x;
					item_temp0->y = monsters->y;
					
					strcpy(news[news_long], "�㷢���� ");
					strcat(news[news_long++], item_temp0->name); 
					
					for (int i = 0; i < item_temp0->r; i++){//��� 
						if (item_temp0->x+dirx[step] < 0 || item_temp0->x+dirx[step] >= SIZE_L || item_temp0->y+diry[step] < 0 || item_temp0->y+diry[step] >= SIZE_H) break;//Խ�� 
						else if (geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == 0 || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] >= UWALL && geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] <= DRWALL || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == CLOSE_DOOR || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_ROAD || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_DOOR) break;//��һ����ǽ
						else if (map_monster[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] != -1){//��һ���ǹ���
							//����һ������ 
							item_temp0->x += dirx[step];
							item_temp0->y += diry[step];
							
							struct monster_body *m;
							struct monster_body *mm;
							mm = monsters;
							for (m = monsters->next; m; m = m->next){
								if (item_temp0->x == m->x && item_temp0->y == m->y){
									if (item_temp0->s2 > 0)
										m->power = (item_temp0->s2 + m->power < monster[m->num].power) ? item_temp0->s2 + m->power : monster[m->num].power;
									else
										m->power = (-item_temp0->s2 > m->fance) ? m->power + item_temp0->s2 + m->fance : m->power - 1;
									strcpy(news[news_long], item_temp0->name); 
									strcat(news[news_long], "������ ");
									strcat(news[news_long++], monster[m->num].name); 
									if (m->power <= 0){//����
										strcpy(news[news_long], "��ɱ���� ");
										strcat(news[news_long++], monster[m->num].name); 
										mm->next = m->next;
										map_monster[item_temp0->y][item_temp0->x] = -1;
										if (m->next == NULL)
											monsters_tail = mm;
										free(m);
										total_anamy--;
									}
									break;
								}
								mm = m;
							}
							break;
						}
						item_temp0->x += dirx[step];
						item_temp0->y += diry[step];
					} 
					
					if (--(item_temp0->num) == 0){//ɾ�������Ʒ 
						for (item_temp1 = player_items; item_temp1; item_temp1 = item_temp1->next)
							if (item_temp1->next == item_temp0){
									item_temp1->next = item_temp0->next;
									break;
								}
						player_items_long--;
					}
					
					if (rand() % 100 >= item_temp0->corpse){//���� 
						if (item_temp0->num == 0) free(item_temp0);
						break;
					}
					
					for (item_temp1 = items->next; item_temp1; item_temp1 = item_temp1->next)
						if (strcmp(item_temp1->name, item_temp0->name) == 0 && item_temp0->x == item_temp1->x && item_temp0->y == item_temp1->y){//�ҵ��˵�����Ʒ 
								item_temp1->num += 1;
								if (item_temp0->num == 0) free(item_temp0);
								break;
							}
					
					if (item_temp1 == NULL){//û���ҵ�������Ʒ 
						item_temp1 = (struct item_body *) malloc (sizeof (struct item_body));
						makenewplayitem(item_temp1, item_temp0);
						item_temp1->num = 1;
						if (item_temp0->num == 0) free(item_temp0);
						
						item_temp1->next = items->next;
						items->next = item_temp1;
					}
					
					for (int i = 0; i <= item_num; i++)
						if (strcmp(item[i].name, item_temp1->name) == 0){
							map_item[item_temp0->y][item_temp0->x] = i;
							break;
						}
					
				}
				else{
					strcpy(news[news_long++], "��Ч�ķ���");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "��û��׼����Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'z'){
		char aaa[100] = "�Ӷ�ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->symbol == '/'){//�Ƿ���
					strcat(aaa, "\t������Ӷ���");
					gotoxy (0, SIZE_H+2);
					printf("%s", aaa);
					gotoxy(monsters->x, monsters->y);
					step = getch();
					if (step == 's' || step == '2')
						step = DOWN;
					else if (step == 'w' || step == '8')
						step = UP;
					else if (step == 'a' || step == '4')
						step = LEFT;
					else if (step == 'd' || step == '6')
						step = RIGHT;
					else if (step == '7'){
						monsters->speed -= 50;
						step = UPLEFT;
					}
					else if (step == '9'){
						monsters->speed -= 50;
						step = UPRIGHT;
					}
					else if (step == '1'){
						monsters->speed -= 50;
						step = DOWNLEFT;
					}
					else if (step == '3'){
						monsters->speed -= 50;
						step = DOWNRIGHT;
					}
					if (step >= UP && step <= DOWNRIGHT){
						//��ֵ���� 
						item_temp0->x = monsters->x;
						item_temp0->y = monsters->y;
						
						strcpy(news[news_long], "��Ӷ��� ");
						strcat(news[news_long++], item_temp0->name);
						if (item_temp0->time == 0){
							strcat(news[news_long], item_temp0->name);
							strcpy(news[news_long++], " �ƺ�û�з�Ӧ");
							gotoxy (0, SIZE_H+2);
							printf("%s", clss);
							return; 
						}
						item_temp0->time--;
						
						for (int i = 0; i < item_temp0->r; i++){//��� 
						if (item_temp0->x+dirx[step] < 0 || item_temp0->x+dirx[step] >= SIZE_L || item_temp0->y+diry[step] < 0 || item_temp0->y+diry[step] >= SIZE_H) break;//Խ�� 
						else if (geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == 0 || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] >= UWALL && geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] <= DRWALL || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == CLOSE_DOOR || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_ROAD || geography[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] == HIDE_DOOR){//��һ����ǽ
								item_temp0->x += dirx[step];
								item_temp0->y += diry[step];
								if (step == UP) step = DOWN;
								else if (step == DOWN) step = UP;
								else if (step == LEFT) step = RIGHT;
								else if (step == RIGHT) step = LEFT;
//								else if (step == UPRIGHT) step = UPLEFT;
//								else if (step == DOWNLEFT) step = DOWNRIGHT;
//								else if (step == UPLEFT) step = UPRIGHT;
//								else if (step == DOWNRIGHT) step = DOWNLEFT;
								continue;
							}
							else if (map_monster[item_temp0->y+diry[step]][item_temp0->x+dirx[step]] != -1){//��һ���ǹ���
								//����һ������ 
								item_temp0->x += dirx[step];
								item_temp0->y += diry[step];
								
								struct monster_body *m;
								struct monster_body *mm;
								mm = monsters;
								for (m = monsters; m; m = m->next){
									if (item_temp0->x == m->x && item_temp0->y == m->y){
										if (item_temp0->s2 > 0)
											m->power = (item_temp0->s2 + m->power < monster[m->num].power) ? item_temp0->s2 + m->power : monster[m->num].power;
										else
											m->power = (-item_temp0->s2 > m->fance) ? m->power + item_temp0->s2 + m->fance : m->power - 1;
										strcpy(news[news_long], item_temp0->name); 
										strcat(news[news_long], " ������ ");
										strcat(news[news_long++], monster[m->num].name); 
										if (m->power <= 0){//����
											strcpy(news[news_long], "��ɱ���� ");
											strcat(news[news_long++], monster[m->num].name); 
											mm->next = m->next;
											map_monster[item_temp0->y][item_temp0->x] = -1;
											if (m->next == NULL)
												monsters_tail = mm;
											free(m);
											total_anamy--;
										}
										break;
									}
									mm = m;
								}
							}
							item_temp0->x += dirx[step];
							item_temp0->y += diry[step];
							if (see[item_temp0->y][item_temp0->x] == 1){
								gotoxy(item_temp0->x, item_temp0->y);
								if (step == UP || step == DOWN)
									printf("|");
								else if (step == LEFT || step == RIGHT) 
									printf("-");
								else if (step == UPLEFT || step == DOWNRIGHT) 
									printf("\\");
								else
									printf("/");
							}
						}
						
					}
					else{
						strcpy(news[news_long++], "��Ч�ķ���");
						monsters->speed += 100; ti--;
					}
				}
				else{
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ���Ƿ���");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'Q'){
		char aaa[100] = "׼��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->state == READY){ 
					strcpy(news[news_long], "���Ѿ�׼���� ");
					strcat(news[news_long++], item_temp0->name);
					monsters->speed += 100; ti--;
					break;
				}
				for (item_temp1 = player_items->next; item_temp1; item_temp1 = item_temp1->next)
					if (item_temp1->state == READY)
						item_temp1->state = EMPTY;
				
				//������Ʒ 
				if (item_temp0->state == IN_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
				} 
				else if (item_temp0->state == BEING_WORN){
					item_temp0->state = EMPTY; 
					monsters->fance -= item_temp0->d;
					monsters->speed -= 100; ti++;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				else if (item_temp0->state == RIGHT_HAND || item_temp0->state == LEFT_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
					monsters->fance -= item_temp0->d;
					monsters->speed -= 100; ti++;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				item_temp0->state = READY;
				strcpy(news[news_long], "��׼���� ");
				strcat(news[news_long++], item_temp0->name); 
				break;
			}
		}
		if (item_temp0 == NULL)
			strcpy(news[news_long++], "û�������Ʒ");
		monsters->speed += 100; ti--;
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'W'){
		char aaa[100] = "װ��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->symbol == '['){//�Ƿ��� 
					if (item_temp0->state == BEING_WORN){
						strcpy(news[news_long], "���Ѿ�װ���� ");
						strcat(news[news_long++], item_temp0->name);
						monsters->speed += 100; ti--;
					}
					else{
						for (item_temp1 = player_items->next; item_temp1; item_temp1 = item_temp1->next){
							if (item_temp1->state == BEING_WORN){//ж�ط���
								item_temp1->state = EMPTY; 
								monsters->fance -= item_temp1->d;
								monsters->speed -= 100; ti++;
								strcpy(news[news_long], "��ж���� ");
								strcat(news[news_long++], item_temp0->name);
								break;
							} 
						}
						item_temp0->state = BEING_WORN;
						monsters->fance += item_temp0->d;
						strcpy(news[news_long], "��װ���� ");
						strcat(news[news_long++], item_temp0->name);
					} 
				}
				else{
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ���Ƿ���");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'A'){
		char aaa[100] = "ж��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->state == IN_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				} 
				else if (item_temp0->state == BEING_WORN){
					item_temp0->state = EMPTY; 
					monsters->fance -= item_temp0->d;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				else if (item_temp0->state == RIGHT_HAND || item_temp0->state == LEFT_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
					monsters->fance -= item_temp0->d;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				else if (item_temp0->state == EMPTY){
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ��û��װ�����������");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'P'){
		char aaa[100] = "���ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->symbol == '='){//�ǽ�ָ 
					if (item_temp0->state == RIGHT_HAND || item_temp0->state == LEFT_HAND){
						strcpy(news[news_long], "���Ѿ������ ");
						strcat(news[news_long++], item_temp0->name);
						monsters->speed += 100; ti--;
					}
					else{
						int ac0 = 0, ac1 = 0; 
						for (item_temp1 = player_items->next; item_temp1; item_temp1 = item_temp1->next){
							if (item_temp1->state == RIGHT_HAND)
								ac0 = 1;
							else if (item_temp1->state == LEFT_HAND)
								ac1 = 1;
							if (ac0 == 1 && ac1 == 1)
								break;
						}
						if (ac0 == 0){
							item_temp0->state = RIGHT_HAND;
							monsters->attack -= item_temp0->s1;
							monsters->fance += item_temp0->d;
							strcpy(news[news_long], "������������ ");
							strcat(news[news_long++], item_temp0->name);
						}
						else if (ac1 == 0){
							item_temp0->state = LEFT_HAND;
							monsters->attack -= item_temp0->s1;
							monsters->fance += item_temp0->d;
							strcpy(news[news_long], "������������ ");
							strcat(news[news_long++], item_temp0->name);
						}
						else{
							strcpy(news[news_long++], "���Ѿ������������ָ");
							monsters->speed += 100; ti--;
						}
					} 
				}
				else{
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ���ǽ�ָ");
					monsters->speed += 100; ti--;
				}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "û�������Ʒ");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == 'q'){
		char aaa[100] = "��ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		item_temp1 = player_items; 
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				if (item_temp0->symbol == '!'){//��ҩˮ 
					strcpy(news[news_long], "������� ");
					strcat(news[news_long++], item_temp0->name);
					if (strcmp(item_temp0->name, "healing") == 0)
						monsters->power = (monsters->power + item_temp0->s1 <= monster[0].power) ? monsters->power + item_temp0->s1 : monster[0].power;
					else if (strcmp(item_temp0->name, "extra_healing") == 0){
						if (monsters->power == monster[0].power)
							monsters->power = monster[0].power = monster[0].power + rand() % 3 + 1;
						else
							monsters->power = (monsters->power + item_temp0->s1 <= monster[0].power) ? monsters->power + item_temp0->s1 : monster[0].power;
					}
					if (--(item_temp0->num) == 0){//ɾ�������Ʒ
						item_temp1->next = item_temp0->next;
						free(item_temp0);
					}
					item_temp1 = item_temp0;
				} 
				else{
					strcat(news[news_long], item_temp0->name);
					strcpy(news[news_long++], " ���ܺ�");
					monsters->speed += 100; ti--;
				}
				break; 
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "����˿�������");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	}
	else if (step == ','){
		if (player_items_long > 40){
			strcpy(news[news_long++], "��װ������ô����Ʒ");
			monsters->speed += 100; ti--;
			return; 
		}
		if (map_item[monsters->y][monsters->x] != -1){
			for (item_temp1 = items->next; item_temp1; item_temp1 = item_temp1->next){
				if (item_temp1->x == monsters->x && item_temp1->y == monsters->y){//�ҵ��˵�����Ʒ
					strcpy(news[news_long], "�������");
					strcat(news[news_long++], item_temp1->name);
					struct item_body *item_temp2;
					for (item_temp0 = items; item_temp0; item_temp0 = item_temp0->next)//ɾ��������Ʒ 
						if (item_temp0->next == item_temp1){
							item_temp0->next = item_temp1->next;
							break;
						}
					for (item_temp2 = player_items->next; item_temp2; item_temp2 = item_temp2->next)
						if (strcmp(item_temp2->name, item_temp1->name) == 0 && (item_temp2->symbol == ')' || item_temp2->symbol == '!')){//�ҵ��������Ʒ���ɵ��� 
							item_temp2->num += item_temp1->num;
							free(item_temp1);
							break;
						}
					if (item_temp2 == NULL){//û���ҵ������Ʒ
						item_temp0 = (struct item_body *) malloc (sizeof (struct item_body));
						makenewplayitem(item_temp0, item_temp1);
						free(item_temp1);
						
						item_temp0->next = player_items->next;
						player_items->next = item_temp0;
						
						while (item_temp0->operation = 'A' + rand() % 64){//��Ӳ����� 
							if (!(item_temp0->operation >= 'A' && item_temp0->operation <= 'Z' || item_temp0->operation >= 'a' && item_temp0->operation <= 'z'))
								continue;
							for (item_temp2 = player_items->next; item_temp2; item_temp2 = item_temp2->next)
								if (item_temp2->operation == item_temp0->operation && item_temp2 != item_temp0)
									break;
							if (item_temp2 == NULL)
								break;
						}
						player_items_long++;
					}
				}
			}
			map_item[monsters->y][monsters->x] = -1;
		}
		else{
			strcpy(news[news_long++], "����˸���į");
			monsters->speed += 100; 
		}
		return; 
	} 
	else if (step == 'D'){
		char aaa[100] = "����ʲô����������Ʒ��ţ�";
		gotoxy (0, SIZE_H+2);
		printf("%s", aaa);
		gotoxy(monsters->x, monsters->y);
		step = getch();
		for (item_temp0 = player_items->next; item_temp0; item_temp0 = item_temp0->next){
			if (step == item_temp0->operation){//�ҵ��������Ʒ
				//������Ʒ 
				if (item_temp0->state == IN_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
				} 
				else if (item_temp0->state == BEING_WORN){
					item_temp0->state = EMPTY; 
					monsters->fance -= item_temp0->d;
					monsters->speed -= 100; ti++;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				else if (item_temp0->state == RIGHT_HAND || item_temp0->state == LEFT_HAND){
					item_temp0->state = EMPTY; 
					monsters->attack += item_temp0->s1;
					monsters->fance -= item_temp0->d;
					monsters->speed -= 100; ti++;
					strcpy(news[news_long], "��ж���� ");
					strcat(news[news_long++], item_temp0->name);
				}
				
				for (item_temp1 = player_items; item_temp1; item_temp1 = item_temp1->next)//ɾ�������Ʒ
					if (item_temp1->next == item_temp0){
						item_temp1->next = item_temp0->next;
						break;
					}
				//��ֵ��Ʒ���� 
				item_temp0->x = monsters->x;
				item_temp0->y = monsters->y;
				
				for (item_temp1 = items->next; item_temp1; item_temp1 = item_temp1->next)
					if (strcmp(item_temp1->name, item_temp0->name) == 0 && item_temp0->x == item_temp1->x && item_temp0->y == item_temp1->y){//�ҵ��˵�����Ʒ
							item_temp1->num += item_temp0->num;
							free(item_temp0);
							break;
						}
				
				if (item_temp1 == NULL){//û���ҵ�������Ʒ
					item_temp1 = (struct item_body *) malloc (sizeof (struct item_body));
					makenewplayitem(item_temp1, item_temp0);
					free(item_temp0);
					
					item_temp1->next = items->next;
					items->next = item_temp1;
				}
				player_items_long--;
				strcpy(news[news_long], "�㶪����");
				strcat(news[news_long++], item_temp1->name);
				for (int i = 0; i <= item_num; i++)
					if (strcmp(item[i].name, item_temp1->name) == 0){
						map_item[monsters->y][monsters->x] = i;
						break;
					}
				break;
			}
		}
		if (item_temp0 == NULL){
			strcpy(news[news_long++], "�㶪�˸���į");
			monsters->speed += 100; ti--;
		}
		gotoxy (0, SIZE_H+2);
		printf("%s", clss);
		return;
	} 
	else if (step == '<'){//�� 
		if (geography[monsters->y][monsters->x] == STAIR_DOWN){
			nextunit = 1;
			save();
		}
		else
			strcpy(news[news_long++], "��޲����ڸ��Ӱ��Լ�������");
		return;
	} 
	else if (step == '>'){//�� 
		if (geography[monsters->y][monsters->x] == STAIR_UP){
			if (lvl == 1){
				system("cls");
				printf("�������ǳ�����,һ�����Ʊ㻯��\nYOU WIN");
				exit(0);
			}
			nextunit = 1;
			save();
			lvl -= 2;
		}
		else
			strcpy(news[news_long++], "�����˷��ȥ���ֿ���¥����");
		return;
	}
	else if (step == 'i'){
		int itemy = 0, itemi = 0;
		if (isi == 0){
			gotoxy (SIZE_L+20, itemy++);
			printf("----------------------------------------");
			gotoxy (SIZE_L+20, itemy);
			printf("|                ����");
			gotoxy (SIZE_L+20+39, itemy++);
			printf("|");
			for (int i = 0; i < ITEM_KIND; i++){
				gotoxy (SIZE_L+20, itemy++);
				printf("|--------------------------------------|");
				gotoxy (SIZE_L+20, itemy);
				printf("| %s", item_name[i]);
				gotoxy (SIZE_L+20+39, itemy++);
				printf("|");
				gotoxy (SIZE_L+20, itemy++);
				printf("|--------------------------------------|");
				for (item_temp1 = player_items->next; item_temp1; item_temp1 = item_temp1->next)
					if (item_temp1->symbol == item_symbol[i]){
						gotoxy (SIZE_L+20, itemy);
						printf("| %c - %d %s", item_temp1->operation, item_temp1->num, item_temp1->name);
						if (item_temp1->state == IN_HAND)
							printf(" (weapon in hand)");
						else if (item_temp1->state == BEING_WORN)
							printf(" (being worn)");
						else if (item_temp1->state == RIGHT_HAND)
							printf(" (on right hand)");
						else if (item_temp1->state == LEFT_HAND)
							printf(" (on left hand)");
						else if (item_temp1->state == READY)
							printf(" (being ready)");
						gotoxy (SIZE_L+20+39, itemy++);
						printf("|");
					}
				gotoxy (SIZE_L+20, itemy);
				printf("|");
				gotoxy (SIZE_L+20+39, itemy++);
				printf("|");
			}
			gotoxy (SIZE_L+20, itemy++);
			printf("----------------------------------------");
			isi = 1;
		}
		else{
			for (int i = 0; i < ITEM_KIND + player_items_long + 38; i++){
				gotoxy (SIZE_L+20, itemy++);
				printf("%s", clss);
			}
			isi = 0;
		}
		monsters->speed += 100; ti--;
		return;
	}
	else if (step == 's' || step == '2')
		step = DOWN;
	else if (step == 'w' || step == '8')
		step = UP;
	else if (step == 'a' || step == '4')
		step = LEFT;
	else if (step == 'd' || step == '6')
		step = RIGHT;
	else if (step == '7'){
		monsters->speed -= 50;
		step = UPLEFT;
	}
	else if (step == '9'){
		monsters->speed -= 50;
		step = UPRIGHT;
	}
	else if (step == '1'){
		monsters->speed -= 50;
		step = DOWNLEFT;
	}
	else if (step == '3'){
		monsters->speed -= 50;
		step = DOWNRIGHT;
	}
	else if (step == '.' || step == '5')
		return;
	else if (monsterstemp == monsters){
		monsters->speed += 100;
		return;
	}
	if (x+dirx[step] < 0 || x+dirx[step] >= SIZE_L || y+diry[step] < 0 || y+diry[step] >= SIZE_H){//Խ�� 
		monsters->speed += 100; ti--;
	}
	else if (map_monster[y+diry[step]][x+dirx[step]] == -1){
		if ((geography[y+diry[step]][x+dirx[step]] <= 100 && geography[y+diry[step]][x+dirx[step]] > 0 || geography[y+diry[step]][x+dirx[step]] == ROAD) || geography[y+diry[step]][x+dirx[step]] == BAD_DOOR || geography[y+diry[step]][x+dirx[step]] == OPEN_DOOR || geography[y+diry[step]][x+dirx[step]] == STAIR_UP || geography[y+diry[step]][x+dirx[step]] == STAIR_DOWN){
			map_monster[y][x] = -1;
			x += dirx[step];
			y += diry[step];
			map_monster[y][x] = monsterstemp->num;
		}
		else if (monsterstemp == monsters){
			monsters->speed += 100; ti--;
		}
	}
	else if (monsterstemp == monsters){
		struct monster_body *m;
		struct monster_body *mm;
		mm = monsters;
		for (m = monsters->next; m; m = m->next){
			if (x+dirx[step] == m->x && y+diry[step] == m->y){
				m->power = (monsters->attack > m->fance) ? m->power - monsters->attack + m->fance : m->power - 1;
				strcpy(news[news_long], "�㹥���� ");
				strcat(news[news_long++], monster[m->num].name); 
				if (m->power <= 0){//����
					strcpy(news[news_long], "��ɱ���� ");
					strcat(news[news_long++], monster[m->num].name); 
					mm->next = m->next;
					map_monster[y+diry[step]][x+dirx[step]] = -1;
					if (m->next == NULL)
						monsters_tail = mm;
					free(m);
					total_anamy--;
				}
				break;
			}
			mm = m;
		}
	}
}

void action(struct monster_body *a){
	char step;
	if (a == monsters){//player
		show();
		gotoxy (monsters->x, monsters->y);
		
		step = getch();
		
		int px = monsters->x, py = monsters->y;
		
		move(monsters->x, monsters->y, step);
		
		if (nextunit == 1)
			return;
		
		if (seee > 0 && seee < 100){//���� 
			for (int i = 0; i < houses[seee][3]; i++)
				for (int j = 0; j < houses[seee][2]; j++){
					if (j == 0)
						gotoxy (houses[seee][0] + j, houses[seee][1] + i);
					if (map_item[houses[seee][1]+i][houses[seee][0]+j] != -1){
						landcolor(item[map_item[houses[seee][1]+i][houses[seee][0]+j]].color);
						printf("%c", item[map_item[houses[seee][1]+i][houses[seee][0]+j]].symbol);
						txtcolor(16);
					}
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] >= UWALL && geography[houses[seee][1]+i][houses[seee][0]+j] <= DRWALL || geography[houses[seee][1]+i][houses[seee][0]+j] == HIDE_DOOR)
						printf("#");
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] == CLOSE_DOOR){
						txtcolor(12);
						printf("+");
						txtcolor(16);
						see[houses[seee][1]+i][houses[seee][0]+j] = 0;
					}
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] == OPEN_DOOR){
						landcolor(848);
						printf(" ");
						txtcolor(16);
						see[houses[seee][1]+i][houses[seee][0]+j] = 0;
					}
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] == BAD_DOOR){
						printf(".");
						see[houses[seee][1]+i][houses[seee][0]+j] = 0;
					}
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] == STAIR_UP)
						printf(">");
					else if (geography[houses[seee][1]+i][houses[seee][0]+j] == STAIR_DOWN)
						printf("<");
					else
						printf(".");
					if (i != 0 && i != houses[seee][3] - 1 && j != 0 && j != houses[seee][2] - 1)
						see[houses[seee][1]+i][houses[seee][0]+j] = 0;
				}
		}
		else{//· 
			for (int i = -1; i <= 1; i++){
				if (py + i >= SIZE_H)
					continue;
				int qwe = 1;
				for (int j = -1; j <= 1; j++){
					if (px + j >= SIZE_L || py + i < 0 || px + j < 0)
						continue;
					else if (qwe == 1){
						gotoxy (px + j, py + i);
						qwe = 0;
					}
					if (map_item[py+i][px+j] != -1){
						landcolor(item[map_item[py+i][px+j]].color);
						printf("%c", item[map_item[py+i][px+j]].symbol);
						txtcolor(16);
					}
					else if (geography[py+i][px+j] == 0 || geography[py+i][px+j] == HIDE_ROAD)
						printf(" ");
					else if (geography[py+i][px+j] == ROAD)
						printf(":");
					else if (geography[py+i][px+j] == CLOSE_DOOR){
						txtcolor(12);
						printf("+");
						txtcolor(16);
					}
					else if (geography[py+i][px+j] == OPEN_DOOR){
						landcolor(848);
						printf(" ");
						txtcolor(16);
					}
					else if (geography[py+i][px+j] == BAD_DOOR)
						printf(".");
					else if ((seee == OPEN_DOOR || seee == BAD_DOOR || see[py+i][px+j] == 1) && (geography[py+i][px+j] >= UWALL && geography[py+i][px+j] <= DRWALL || geography[py+i][px+j] == HIDE_DOOR))
						printf("#");
					else if (geography[py+i][px+j] >= UWALL && geography[py+i][px+j] <= DRWALL || geography[py+i][px+j] == HIDE_DOOR)
						printf(" ");
					else
						printf(".");
					if (!(geography[py+i][px+j] >= UWALL && geography[py+i][px+j] <= DRWALL || geography[py+i][px+j] == HIDE_DOOR))
						see[py+i][px+j] = 0;
				}
				
			}
		}
		
		if (geography[monsters->y][monsters->x] == STAIR_UP || geography[monsters->y][monsters->x] == STAIR_DOWN){
			for (int i = monsters->y - 1; i <= monsters->y + 1; i++)
				for (int j = monsters->x - 1; j <= monsters->x + 1; j++)
					if (geography[i][j] > 0 && geography[i][j] < 100)
						seee = geography[i][j];
		}
		else
			seee = geography[monsters->y][monsters->x];
		
		if (seee > 0 && seee < 100){//���� 
			for (int i = 0; i < houses[seee][3]; i++)
				for (int j = 0; j < houses[seee][2]; j++)
					see[houses[seee][1]+i][houses[seee][0]+j] = history[houses[seee][1]+i][houses[seee][0]+j] = 1;
		}
		else{//· 
			for (int i = -1; i <= 1; i++){
				if (monsters->y + i >= SIZE_H)
					continue;
				for (int j = -1; j <= 1; j++){
					if (monsters->x + j >= SIZE_L || monsters->y + i < 0 || monsters->x + j < 0)
						continue;
					if (!(geography[monsters->y+i][monsters->x+j] >= UWALL && geography[monsters->y+i][monsters->x+j] <= DRWALL || geography[monsters->y+i][monsters->x+j] == HIDE_DOOR))
						see[monsters->y+i][monsters->x+j] = history[monsters->y+i][monsters->x+j] = 1;
				}
			}
		}
		
		
	}
	else{
		int ac = 1;
		for (int q = a->x - 1; q <= a->x + 1; q++){
			if (q < 0 || q >= SIZE_L) continue;
			for (int w = a->y - 1; w <= a->y + 1; w++)
				if (w < 0 || w >= SIZE_H) continue;
				else if (map_monster[w][q] == 0 && ((w == a->y - 1 || w == a->y + 1) && q == a->x || w == a->y && (q == a->x - 1 || q == a->x + 1))){
					monsters->power = (a->attack > monsters->fance) ? monsters->power - a->attack + monsters->fance : monsters->power - 1;
					strcpy(news[news_long], a->name);
					strcat(news[news_long++], " ��������");
					ac = 0;
					break;
				}
				else if (map_monster[w][q] == 0 && a->speed >= 50){
					a->speed -= 50;
					monsters->power = (a->attack > monsters->fance) ? monsters->power - a->attack + monsters->fance : monsters->power - 1;
					strcpy(news[news_long], a->name);
					strcat(news[news_long++], " ��������");
					ac = 0;
					break;
				}
			if (ac == 0)
				break;
		}
		if (ac == 0)
			return;
		int nx = a->x, ny = a->y;
		if (abs(a->x-monsters->x) > abs(a->y-monsters->y)){
			if (a->x < monsters->x)
				step = RIGHT;
			else
				step = LEFT;
			move(a->x, a->y, step);
			if (nx == a->x && ny == a->y){//û�� 
				if (a->y < monsters->y)
					step = DOWN; 
				else
					step = UP;
				move(a->x, a->y, step);
			}
		}
		else{
			if (a->y < monsters->y)
				step = DOWN; 
			else
				step = UP;
			move(a->x, a->y, step);
			if (nx == a->x && ny == a->y){//û�� 
				if (a->x < monsters->x)
					step = RIGHT;
				else
					step = LEFT;
				move(a->x, a->y, step);
			}
		}
	}
} 
void show(){
	if (geography[monsters->y][monsters->x] == STAIR_UP || geography[monsters->y][monsters->x] == STAIR_DOWN){
		for (int i = monsters->y - 1; i <= monsters->y + 1; i++)
			for (int j = monsters->x - 1; j <= monsters->x + 1; j++)
				if (geography[i][j] > 0 && geography[i][j] < 100)
					seee = geography[i][j];
	}
	else
		seee = geography[monsters->y][monsters->x];
	
	if (seee > 0 && seee < 100){//���� 
		for (int i = 0; i < houses[seee][3]; i++)
			for (int j = 0; j < houses[seee][2]; j++){
				if (j == 0)
					gotoxy (houses[seee][0] + j, houses[seee][1] + i);
				if (map_monster[houses[seee][1]+i][houses[seee][0]+j] != -1){
					landcolor(monster[map_monster[houses[seee][1]+i][houses[seee][0]+j]].color);
					printf("%c", monster[map_monster[houses[seee][1]+i][houses[seee][0]+j]].symbol);
					txtcolor(16);
				}
				else if (map_item[houses[seee][1]+i][houses[seee][0]+j] != -1){
					landcolor(item[map_item[houses[seee][1]+i][houses[seee][0]+j]].color);
					printf("%c", item[map_item[houses[seee][1]+i][houses[seee][0]+j]].symbol);
					txtcolor(16);
				}
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] >= UWALL && geography[houses[seee][1]+i][houses[seee][0]+j] <= DRWALL || geography[houses[seee][1]+i][houses[seee][0]+j] == HIDE_DOOR)
					printf("#");
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] == CLOSE_DOOR){
					txtcolor(12);
					printf("+");
					txtcolor(16);
				}
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] == OPEN_DOOR){
					landcolor(848);
					printf(" ");
					txtcolor(16);
				}
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] == BAD_DOOR)
					printf(".");
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] == STAIR_UP)
					printf(">");
				else if (geography[houses[seee][1]+i][houses[seee][0]+j] == STAIR_DOWN)
					printf("<");
				else
					printf(".");
				see[houses[seee][1]+i][houses[seee][0]+j] = history[houses[seee][1]+i][houses[seee][0]+j] = 1;
			}
	}
	else{//· 
		for (int i = -1; i <= 1; i++){
			if (monsters->y + i >= SIZE_H)
				continue;
			int qwe = 1;
			for (int j = -1; j <= 1; j++){
				if (monsters->x + j >= SIZE_L || monsters->y + i < 0 || monsters->x + j < 0)
					continue;
				else if (qwe == 1){
					gotoxy (monsters->x + j, monsters->y + i);
					qwe = 0;
				}
				if (map_monster[monsters->y+i][monsters->x+j] != -1){
					landcolor(monster[map_monster[monsters->y+i][monsters->x+j]].color);
					printf("%c", monster[map_monster[monsters->y+i][monsters->x+j]].symbol);
					txtcolor(16);
				}
				else if (map_item[monsters->y+i][monsters->x+j] != -1){
					landcolor(item[map_item[monsters->y+i][monsters->x+j]].color);
					printf("%c", item[map_item[monsters->y+i][monsters->x+j]].symbol);
					txtcolor(16);
				}
				else if (geography[monsters->y+i][monsters->x+j] == 0 || geography[monsters->y+i][monsters->x+j] == HIDE_ROAD)
					printf(" ");
				else if (geography[monsters->y+i][monsters->x+j] == ROAD)
					printf(":");
				else if (geography[monsters->y+i][monsters->x+j] == CLOSE_DOOR){
					txtcolor(12);
					printf("+");
					txtcolor(16);
				}
				else if (geography[monsters->y+i][monsters->x+j] == OPEN_DOOR){
					landcolor(848);
					printf(" ");
					txtcolor(16);
				}
				else if (geography[monsters->y+i][monsters->x+j] == BAD_DOOR)
					printf(".");
				else if ((seee == OPEN_DOOR || seee == BAD_DOOR || see[monsters->y+i][monsters->x+j] == 1) && (geography[monsters->y+i][monsters->x+j] >= UWALL && geography[monsters->y+i][monsters->x+j] <= DRWALL || geography[monsters->y+i][monsters->x+j] == HIDE_DOOR))
					printf("#");
				else if (geography[monsters->y+i][monsters->x+j] >= UWALL && geography[monsters->y+i][monsters->x+j] <= DRWALL || geography[monsters->y+i][monsters->x+j] == HIDE_DOOR)
					printf(" ");
				else
					printf(".");
				if (!(geography[monsters->y+i][monsters->x+j] >= UWALL && geography[monsters->y+i][monsters->x+j] <= DRWALL || geography[monsters->y+i][monsters->x+j] == HIDE_DOOR))
					see[monsters->y+i][monsters->x+j] = history[monsters->y+i][monsters->x+j] = 1;
			}
		}
	}
	
	gotoxy (0, SIZE_H);
	txtcolor (16);
	printf("%s (the %s)", player_name, monsters->name);
	gotoxy(14+strlen(player_name)+strlen(monsters->name), SIZE_H);
	printf("HP:%d(%d)[", monsters->power, monster[0].power);
	for (int i = 0; i < 10; i++){
		if (i <= monsters->power * 10 / monster[0].power)
			if (monsters->power * 10 / monster[0].power >= 5)
				landcolor(47);
			else
				landcolor(79);
			printf(" ");
			txtcolor(16);
	}
	printf("] Pw:%d(%d)[", monsters->magic, monster[0].magic);
	for (int i = 0; i < 10; i++){
		if (i <= monsters->magic * 10 / monster[0].magic)
			landcolor(240);
			printf(" ");
			txtcolor(16);
	}
	printf("]      \ndungeon level:%d $:%d strength:%d defance:%d %s round:%d monster:%d\n", lvl, 0, monsters->attack, monsters->fance, "lawful", ti, total_anamy);
	
	gotoxy (0, SIZE_H+3);
	while (del_news){
		puts(clss);
		del_news--;
	}
	gotoxy (0, SIZE_H+3);
	for (int i = 0; i < news_long; i++){
		puts(news[i]);
		news[i][0] = '\0';
		del_news++;
	}
	news_long = 0;
}

