#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif 

void dfs (int ex, int ey, int x, int y);
void creatroad (int house);
void creatmap(int house);
void creatmonsters();
void makenewmonster(int num, struct monster_body *a);
void creatitems();
void makenewitem(struct item_body *a, struct item_node b);
void makenewplayitem(struct item_body *a, struct item_body *b);

void creatmap(int house){
	srand((unsigned) time(&t));
	time_t t;
	srand((unsigned) time(&t));
	
	int now_house, ti, tii, remain;
	int isup, isdown;//楼梯入口和出口
	
	reset:
	
	//初始化
	for (int i = 0; i < SIZE_H; i++){
		memset(map_item+i, -1, sizeof(int) * SIZE_L);
		memset(map_monster+i, -1, sizeof(int) * SIZE_L); 
		memset(see+i, 0, sizeof(int) * SIZE_L);
		memset(geography+i, 0, sizeof(int) * SIZE_L);
		memset(history+i, 0, sizeof(int) * SIZE_L);
	}
	
	items = &items_head;
	if (player_items == NULL)
		player_items = &player_items_head;
	
	now_house = 0;
	tii = 0;
	remain = SIZE_L * SIZE_H;
	
	isup = rand() % house + 1;
	isdown = rand() % house + 1;
	
	if (house != 1)
		while (isup == isdown){
			isup = rand() % house + 1;
			isdown = rand() % house + 1;
		}
	
	while (now_house != house){
		int l, h, x, y, ac;//l = 房间长度, h = 房间宽度,  x = 房间起始x坐标, y = 房间起始y坐标, ac = accept
		
		house_size_set:
		if (tii == 1000)
			goto reset;
		
		ac = 0;
		
		do{//创建房间的长和宽
			l = rand() % HOUSE_SIZE_L_MAX + HOUSE_SIZE_MIN;
			h = rand() % HOUSE_SIZE_H_MAX + HOUSE_SIZE_MIN;
			
			if (remain > l * h)//剩余的空间是否足够
				ac = 1;
		}while (ac == 0);
		
		ac = 0;
		ti = 0;
		
		do{
			if (ti == 1000){//尝试次数 <= 1000
				tii++;
				goto house_size_set;//不成功再次创建房间的长和宽 
			}
			 
			x = rand() % SIZE_L;
			y = rand() % SIZE_H;
			
			if (x + l >= SIZE_L || y + h >= SIZE_H)//越界
				continue;
			
			int isclose = 0;
			for (int i = x - 1; i <= x + l; i++)
				if (geography[y-1][i] != 0 || geography[y+h][i] != 0){//房间上边和下边是否是不和其他房间紧贴
						isclose = 1;
						break;
					}
			if (isclose == 1)
				continue;
			for (int i = y - 1; i <= y + h; i++)
				if (geography[i][x-1] != 0 || geography[i][x+l] != 0){//房间左边和右边是否是不和其他房间紧贴
						isclose = 1;
						break;
					}
			if (isclose == 1)
				continue;
			
			int isfull = 0;
			for (int i = 0; i < l; i++){
				for (int j = 0; j < h; j++)
					if (geography[y+j][x+i] != 0){//房中房
						isfull = 1;
						break;
					}
				if (isfull == 1)
					break;
			}
			if (isfull == 0)
				ac = 1;
			
			ti++;
		}while (ac == 0);
		
		now_house++;
		
		struct item_body *item_temp;
		for (int i = 0; i < l; i++)
			for (int j = 0; j < h; j++){
				if ((i == 0 || i == l - 1) && j != 0 && j != h - 1) 
					geography[y+j][x+i] = LWALL;
				else if ((j == 0 || j == h - 1) && i != 0 && i != l - 1)
					geography[y+j][x+i] = UWALL;
				else if (i == 0 && j == 0)
					geography[y+j][x+i] = ULWALL;
				else if (i == 0 && j == h - 1)
					geography[y+j][x+i] = DLWALL;
				else if (i == l - 1 && j == 0)
					geography[y+j][x+i] = URWALL;
				else if (i == l - 1 && j == h - 1)
					geography[y+j][x+i] = DRWALL;
				else
					geography[y+j][x+i] = now_house;
				//物品
				if (geography[y+j][x+i] == now_house)
					for (int k = 0; k <= item_num; k++)
						if (abs(rand() % 10000 - rand() % 10000) <= item[k].create){
							item_temp = (struct item_body *) malloc (sizeof (struct item_body));
							makenewitem(item_temp, item[k]);
							item_temp->x = x + i;
							item_temp->y = y + j;
							item_temp->next = items->next;
							items->next = item_temp;
							map_item[item_temp->y][item_temp->x] = k;
						}
			}
		//出入口
		if (now_house == isup){
			int endx = x + rand() % (l - 2) + 1, endy = y + rand() % (h - 2) + 1;
			geography[endy][endx] = STAIR_UP;
			stair[0] = endx;
			stair[1] = endy;
		}
		
		if (now_house == isdown){
			int endx, endy;
			do{
				endx = x + rand() % (l - 2) + 1;
				endy = y + rand() % (h - 2) + 1;
			}while (geography[endy][endx] == STAIR_UP);
			geography[endy][endx] = STAIR_DOWN;
			stair[2] = endx;
			stair[3] = endy;
		}
		//记录房间信息
		houses[now_house][0] = x;
		houses[now_house][1] = y;
		houses[now_house][2] = l;
		houses[now_house][3] = h;
	}
	
	int ac, doorsx, doorsy, doorex, doorey, doordis, rsx, rsy, rex, rey;
	for (int now = 1; now <= house; now++){
		
		ac = 0;
		
		int sx, sy, sl, sh, ex, ey, el, eh;
		
		if (now == 1){
			sx = houses[house][0]; sy =  houses[house][1]; sl = houses[house][2]; sh = houses[house][3];
			ex = houses[now][0]; ey =  houses[now][1]; el = houses[now][2]; eh = houses[now][3];
		} 
		else{
			sx = houses[now-1][0]; sy =  houses[now-1][1]; sl = houses[now-1][2]; sh = houses[now-1][3];
			ex = houses[now][0]; ey =  houses[now][1]; el = houses[now][2]; eh = houses[now][3];
		}
		
		int corner_s_UL = 0, corner_s_UR = sl - 1, corner_s_DR = sl + sh - 2, corner_s_DL = sh + sl * 2 - 3;
		int corner_e_UL = 0, corner_e_UR = el - 1, corner_e_DR = el + eh - 2, corner_e_DL = eh + el * 2 - 3;
		
		int bowl;
		bowl = (sh + sl) * 2 - 4;
		
		while (1){
			doordis = rand() % bowl;
			
			if (doordis == corner_s_UL || doordis == corner_s_UR || doordis == corner_s_DR || doordis == corner_s_DL)//角
				continue;
			if (doordis < corner_s_UR){//上
				rsy = sy - 1;
				rsx = sx + doordis;
				if (rsy < 0 || geography[sy][rsx-1] >= CLOSE_DOOR && geography[sy][rsx-1] <= HIDE_DOOR || geography[sy][rsx+1] >= CLOSE_DOOR && geography[sy][rsx+1] <= HIDE_DOOR || geography[sy][rsx] >= CLOSE_DOOR && geography[sy][rsx] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[sy][rsx] = rand() % 4 + CLOSE_DOOR;
			}
			else if (doordis < corner_s_DR){//右
				rsy = sy + doordis - corner_s_UR;
				rsx = sx + corner_s_UR + 1;
				if (rsx > SIZE_L || geography[rsy-1][rsx-1] >= CLOSE_DOOR && geography[rsy-1][rsx-1] <= HIDE_DOOR || geography[rsy+1][rsx-1] >= CLOSE_DOOR && geography[rsy+1][rsx-1] <= HIDE_DOOR || geography[rsy][rsx-1] >= CLOSE_DOOR && geography[rsy][rsx-1] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rsy][rsx-1] = rand() % 4 + CLOSE_DOOR;
			}
			else if (doordis < corner_s_DL){//下
				rsy = sy + sh - 1 + 1;
				rsx = sx + doordis - corner_s_DR;
				if (rsy > SIZE_H || geography[rsy-1][rsx-1] >= CLOSE_DOOR && geography[rsy-1][rsx-1] <= HIDE_DOOR || geography[rsy-1][rsx+1] >= CLOSE_DOOR && geography[rsy-1][rsx+1] <= HIDE_DOOR || geography[rsy-1][rsx] >= CLOSE_DOOR && geography[rsy-1][rsx] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rsy-1][rsx] = rand() % 4 + CLOSE_DOOR;
			}
			else{//左
				rsy = sy + doordis - corner_s_DL;
				rsx = sx - 1;
				if (rsx < 0 || geography[rsy-1][sx] >= CLOSE_DOOR && geography[rsy-1][sx] <= HIDE_DOOR || geography[rsy+1][sx] >= CLOSE_DOOR && geography[rsy+1][sx] <= HIDE_DOOR || geography[rsy][sx] >= CLOSE_DOOR && geography[rsy][sx] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rsy][sx] = rand() % 4 + CLOSE_DOOR;
			}
			
			if (rand() % 100 >= Hide_Probability)
				geography[rsy][rsx] = HIDE_ROAD;
			else
				geography[rsy][rsx] = ROAD;
			
			break;
		}
		bowl = (eh + el) * 2 - 4;
		
		while (1){
			doordis = rand() % bowl;
			
			if (doordis == corner_e_UL || doordis == corner_e_UR || doordis == corner_e_DR || doordis == corner_e_DL)//角
				continue;
			if (doordis < corner_e_UR){//上
				rey = ey - 1;
				rex = ex + doordis;
				if (rey < 0 || geography[ey][rex-1] >= CLOSE_DOOR && geography[ey][rex-1] <= HIDE_DOOR || geography[ey][rex+1] >= CLOSE_DOOR && geography[ey][rex+1] <= HIDE_DOOR || geography[ey][rex] >= CLOSE_DOOR && geography[ey][rex] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[ey][rex] = rand() % 4 + CLOSE_DOOR;
			}
			else if (doordis < corner_e_DR){//右
				rey = ey + doordis - corner_e_UR;
				rex = ex + corner_e_UR + 1;
				if (rex > SIZE_L || geography[rey-1][rex-1] >= CLOSE_DOOR && geography[rey-1][rex-1] <= HIDE_DOOR || geography[rey+1][rex-1] >= CLOSE_DOOR && geography[rey+1][rex-1] <= HIDE_DOOR || geography[rey][rex-1] >= CLOSE_DOOR && geography[rey][rex-1] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rey][rex-1] = rand() % 4 + CLOSE_DOOR;
			}
			else if (doordis < corner_e_DL){//下
				rey = ey + eh - 1 + 1;
				rex = ex + doordis - corner_e_DR;
				if (rey > SIZE_H || geography[rey-1][rex-1] >= CLOSE_DOOR && geography[rey-1][rex-1] <= HIDE_DOOR || geography[rey-1][rex+1] >= CLOSE_DOOR && geography[rey-1][rex+1] <= HIDE_DOOR || geography[rey-1][rex] >= CLOSE_DOOR && geography[rey-1][rex] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rey-1][rex] = rand() % 4 + CLOSE_DOOR;
			}
			else{//左
				rey = ey + doordis - corner_e_DL;
				rex = ex - 1;
				if (rex < 0 || geography[rey-1][ex] >= CLOSE_DOOR && geography[rey-1][ex] <= HIDE_DOOR || geography[rey+1][ex] >= CLOSE_DOOR && geography[rey+1][ex] <= HIDE_DOOR || geography[rey][ex] >= CLOSE_DOOR && geography[rey][ex] <= HIDE_DOOR)//越界或附近是否为门 
					continue;
				geography[rey][ex] = rand() % 4 + CLOSE_DOOR;
			}
			
			if (rand() % 100 >= Hide_Probability)
				geography[rey][rex] = HIDE_ROAD;
			else
				geography[rey][rex] = ROAD;
			
			break;
		}
		dfs(rex, rey, rsx, rsy);
		
	}
}

void dfs (int ex, int ey, int x, int y){
	if (x == ex && y == ey)//终点
		return;
	
	int nx, ny;
	
	int Type = rand() % 2, type, typee;
	
	if (Type == 1){//先上下后左右
		if (y < ey) type = DOWN;//现在位置在终点上边
		else if (y > ey) type = UP;//现在位置在终点下边
		else if (x < ex) type = RIGHT;//现在位置在终点左边
		else if (x > ex) type = LEFT;//现在位置在终点右边
	}
	else{//先左右后上下
		if (x < ex) type = RIGHT;//现在位置在终点左边
		else if (x > ex) type = LEFT;//现在位置在终点右边
		else if (y < ey) type = DOWN;//现在位置在终点上边
		else if (y > ey) type = UP;//现在位置在终点下边
	}
	nx = x + dirx[type];
	ny = y + diry[type];
	if (geography[ny][nx] == ROAD || geography[ny][nx] == HIDE_ROAD || geography[ny][nx] == 0){//现在位置的对应方向是否为路径或空白
		if (rand() % 100 >= 95)
			geography[ny][nx] = HIDE_ROAD;
		else
			geography[ny][nx] = ROAD;
		dfs (ex, ey, nx, ny);
	}
	else{//绕道
		if (type == DOWN || type == UP){
			if (x < ex) typee = RIGHT;//现在位置在终点左边
			else typee = LEFT;//现在位置在终点右边或相等
		}
		else{
			if (y < ey) typee = DOWN;//现在位置在终点下边
			else typee = UP;//现在位置在终点上边或相等
		}
		nx = x; ny = y;
		do{
			nx += dirx[typee];
			ny += diry[typee];
			if (ny >= SIZE_H || ny < 0 || nx >= SIZE_L || nx < 0){//越界
				ny = y; nx = x;
				//换方向
				if (typee == DOWN) typee = UP;
				else if (typee == UP) typee = DOWN;
				else if (typee == RIGHT) typee = LEFT;
				else if (typee == LEFT) typee = RIGHT;
				continue;//重来
			}
			if (rand() % 100 >= 95)
				geography[ny][nx] = HIDE_ROAD;
			else
				geography[ny][nx] = ROAD;
		}while (!(geography[ny+diry[type]][nx+dirx[type]] == ROAD || geography[ny+diry[type]][nx+dirx[type]] == HIDE_ROAD || geography[ny+diry[type]][nx+dirx[type]] == 0));//现在位置的对应方向是否为路径或空白
		if (rand() % 100 >= 95)
			geography[ny+diry[type]][nx+dirx[type]] = HIDE_ROAD;
		else
			geography[ny+diry[type]][nx+dirx[type]] = ROAD;
		dfs (ex, ey, nx+dirx[type], ny+diry[type]);
	}
}

void creatmonsters(){
	//creat monster
	FILE *fp = fopen("monster.txt", "r+");
	
	for (monster_num = 1; ~fscanf(fp, "%d", &monster[monster_num].color) && monster[monster_num].color != INF; monster_num++){
		fgetc(fp);
		fscanf(fp, "%s %c%d%d%d%d%d%d%d%d", monster[monster_num].name, &monster[monster_num].symbol, &monster[monster_num].frequency, &monster[monster_num].corpse, &monster[monster_num].power, &monster[monster_num].magic, &monster[monster_num].attack, &monster[monster_num].fance, &monster[monster_num].speed, &monster[monster_num].party);
	}
	
	fclose(fp);
}

void makenewmonster(int num, struct monster_body *a){
	a->num = num;
	strcpy(a->name, monster[num].name);
	a->symbol = monster[num].symbol;
	a->color = monster[num].color;
	a->frequency = monster[num].frequency;
	a->corpse = monster[num].corpse;
	a->power = monster[num].power;
	a->magic = monster[num].magic;
	a->attack = monster[num].attack;
	a->fance = monster[num].fance;
	a->speed = 0;
	a->party = monster[num].party;
	a->next = NULL;
}

void creatitems(){
	//creat item
	
	FILE *fp = fopen("item.txt", "r+");
	
	for (item_num = 0; ~fscanf(fp, "%d", &item[item_num].color) && item[item_num].color != INF; item_num++){
		fgetc(fp);
		fscanf(fp, "%c %s%d%d%d%d%d%d%d%d%d", &item[item_num].symbol, item[item_num].name, &item[item_num].s1, &item[item_num].s2, &item[item_num].d, &item[item_num].corpse, &item[item_num].create, &item[item_num].num, &item[item_num].r, &item[item_num].state, &item[item_num].time);
	}
	
	fclose(fp);
}

void makenewitem(struct item_body *a, struct item_node b){
	strcpy(a->name, b.name);
	a->symbol = b.symbol;
	a->color = b.color;
	a->s1 = b.s1;
	a->corpse = b.corpse;
	a->s2 = b.s2;
	a->d = b.d;
	a->create = b.create;
	a->num = rand() % b.num + 1;
	a->r = b.r;
	a->state = b.state;
	a->time = rand() % b.time;
}

void makenewplayitem(struct item_body *a, struct item_body *b){
	strcpy(a->name, b->name);
	a->symbol = b->symbol;
	a->color = b->color;
	a->s1 = b->s1;
	a->corpse = b->corpse;
	a->s2 = b->s2;
	a->d = b->d;
	a->create = b->create;
	a->num = b->num;
	a->x = b->x;
	a->y = b->y;
	a->r = b->r;
	a->state = b->state;
	a->time = b->time;
}
