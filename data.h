#ifndef SOURCE_H
#define SOURCE_H
#include "source.h"
#endif 

void saveplayer(){
	FILE *fp = fopen("player.txt", "w+");
	fprintf(fp, "%s %d %s %c %d %d %d %d %d %d %d %d", player_name, monster[0].color, monster[0].name, monster[0].symbol, monster[0].frequency, monster[0].corpse, monster[0].power, monster[0].magic, monster[0].attack, monster[0].fance, monster[0].speed, monster[0].party);
	fprintf(fp, " %d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d", monsters->num, monsters->name, monsters->symbol, monsters->color, monsters->frequency, monsters->corpse, monsters->power, monsters->magic, monsters->attack, monsters->fance, monsters->speed, monsters->party, monsters->x, monsters->y, lvl, ti, unit, hou);
	for (int i = 0; i < SIZE_L; i++)
		fprintf(fp, " %d", book[i]);
	fprintf(fp, "\n");
	for (struct item_body *temp = player_items; temp; temp = temp->next)
		fprintf(fp, "%d %s %c %c %d %d %d %d %d %d %d %d %d\n", temp->color, temp->name, temp->symbol, temp->operation, temp->s1, temp->s2, temp->d, temp->corpse, temp->create, temp->num, temp->r, temp->state, temp->time);
	fprintf(fp, "%d", INF);
	fclose(fp);
}

void loadplayer(){
	FILE *fp = fopen("player.txt", "r+");
	fscanf(fp, "%s %d %s %c %d %d %d %d %d %d %d %d", player_name, &monster[0].color, monster[0].name, &monster[0].symbol, &monster[0].frequency, &monster[0].corpse, &monster[0].power, &monster[0].magic, &monster[0].attack, &monster[0].fance, &monster[0].speed, &monster[0].party);
	fscanf(fp, " %d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &monsters->num, monsters->name, &monsters->symbol, &monsters->color, &monsters->frequency, &monsters->corpse, &monsters->power, &monsters->magic, &monsters->attack, &monsters->fance, &monsters->speed, &monsters->party, &monsters->x, &monsters->y, &lvl, &ti, &unit, &hou);
	for (int i = 0; i < SIZE_L; i++)
		fscanf(fp, "%d", &book[i]);
	struct item_body *temp;
	player_items_long = 0;
	do{
		temp = (struct item_body *) malloc (sizeof (struct item_body));
		fscanf(fp, "%d", &temp->color);
		if (temp->color == INF)
			break;
		fgetc(fp);
		fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d", temp->name, &temp->symbol, &temp->operation, &temp->s1, &temp->s2, &temp->d, &temp->corpse, &temp->create, &temp->num, &temp->r, &temp->state, &temp->time);
		if (player_items == NULL){
			player_items = temp;
			temp->next = NULL; 
		}
		else{
			temp->next = player_items->next;
			player_items->next = temp;
		}
	}while (++player_items_long);
	free(temp);
	player_items_long--;
	fclose(fp);
}

void load_node(char *txtname, int a[][SIZE_L]){
	int temp, size = SIZE_L * SIZE_H, size_l = SIZE_L - 1, count, l;
	FILE *fp = fopen(txtname, "r+");
	//读取前面的数据 
	for (l = 1; l < lvl; l++)
		for (int i = 0; i < size; i++)
			fscanf(fp, "%d", &temp);
	
	//读取当前的数据 
	for (int i = 0; i < SIZE_H; i++)
		for (int j = 0; j < SIZE_L; j++)
			fscanf(fp, "%d", &a[i][j]);
	
	fclose(fp);
}
void load(){
	int temp, count, l;
	char txtname[name_max_long];
	//地牢
	strcpy(txtname, "dungeon.txt");
	load_node(txtname, geography);
	
	//怪物
	strcpy(txtname, "map_monster.txt");
	load_node(txtname, map_monster);
	
	//物品
	strcpy(txtname, "map_item.txt");
	load_node(txtname, map_item);
	
	//地图
	strcpy(txtname, "see.txt");
	load_node(txtname, see);
	
	//地图
	strcpy(txtname, "history.txt");
	load_node(txtname, history);
	
	//房间
	FILE *fp = fopen("house.txt", "r+");
	
	//读取前面的数据 
	int house_size = SIZE_L * 4;
	for (l = 1; l < lvl; l++)
		for (int i = 0; i < house_size; i++)
			fscanf(fp, "%d", &temp);
	
	//读取当前的数据 
	for (int i = 0; i < SIZE_L; i++)
		for (int j = 0; j < 4; j++)
			fscanf(fp, "%d", &houses[i][j]);
	
	fclose(fp);
	
	//怪物 
	fp = fopen("monsters.txt", "r+");
	//读取前面的数据 
		struct monster_body monsterstemp;
		for (l = 1; l < lvl; l++)
			while(~fscanf(fp, "%d", &monsterstemp.num) && monsterstemp.num != INF){
				if (monsterstemp.num == INF * 2)
					fscanf(fp, "%d", &monsterstemp.num);
				fgetc(fp);
				fscanf(fp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemp.name, &monsterstemp.symbol, &monsterstemp.color, &monsterstemp.frequency, &monsterstemp.corpse, &monsterstemp.power, &monsterstemp.magic, &monsterstemp.attack, &monsterstemp.fance, &monsterstemp.speed, &monsterstemp.party, &monsterstemp.x, &monsterstemp.y);
			}
		
	//读取当前的数据 
	fscanf(fp, "%d", &monsterstemp.num);
	struct monster_body *monsterstemps;
	do{
		monsterstemps = (struct monster_body *) malloc (sizeof (struct monster_body));
		fscanf(fp, "%d", &monsterstemps->num);
		if (monsterstemps->num == INF)
			break;
		fgetc(fp);
		fscanf(fp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemps->name, &monsterstemps->symbol, &monsterstemps->color, &monsterstemps->frequency, &monsterstemps->corpse, &monsterstemps->power, &monsterstemps->magic, &monsterstemps->attack, &monsterstemps->fance, &monsterstemps->speed, &monsterstemps->party, &monsterstemps->x, &monsterstemps->y);
		monsterstemps->next = NULL;
		total_anamy++;
		monsters_tail->next = monsterstemps;
		monsters_tail = monsters_tail->next;
	}while (1);
	free(monsterstemps);
	fclose(fp);
	
	//物品 
	fp = fopen("items.txt", "r+");
	//读取前面的数据 
		struct item_body itemstemp;
		for (l = 1; l < lvl; l++)
			while(~fscanf(fp, "%d", &itemstemp.color) && itemstemp.color != INF){
				if (itemstemp.color == INF * 2)
					fscanf(fp, "%d", &itemstemp.color);
				fgetc(fp);
				fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemstemp.name, &itemstemp.symbol, &itemstemp.operation, &itemstemp.s1, &itemstemp.s2, &itemstemp.d, &itemstemp.corpse, &itemstemp.create, &itemstemp.num, &itemstemp.x, &itemstemp.y, &itemstemp.r, &itemstemp.state, &itemstemp.time);
			}
		
	//读取当前的数据 
	fscanf(fp, "%d", &itemstemp.color);
	struct item_body *itemstemps;
	do{
		itemstemps = (struct item_body *) malloc (sizeof (struct item_body));
		fscanf(fp, "%d", &itemstemps->color);
		if (itemstemps->color == INF)
			break;
		fgetc(fp);
		fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemstemps->name, &itemstemps->symbol, &itemstemps->operation, &itemstemps->s1, &itemstemps->s2, &itemstemps->d, &itemstemps->corpse, &itemstemps->create, &itemstemps->num, &itemstemps->x, &itemstemps->y, &itemstemps->r, &itemstemps->state, &itemstemps->time);
		if (items == NULL){
			items = itemstemps;
			itemstemps->next = NULL; 
		}
		else{
			itemstemps->next = items->next;
			items->next = itemstemps;
		}
	}while (1);
	free(itemstemps);
	fclose(fp);
}

void save_node(char *txtname, int a[][SIZE_L]){
	int temp, size = SIZE_L * SIZE_H, size_l = SIZE_L - 1, count, l;
	FILE *fp = fopen(txtname, "r+");
	FILE *Temp;
	if (fp == NULL){
		fp = fopen(txtname, "a+");
		for (int i = 0; i < SIZE_H; i++){
			for (int j = 0; j < SIZE_L; j++)
				fprintf(fp, "%d ", a[i][j]);
			fprintf(fp, "\n");
		}
		fprintf(fp, "%d", INF);
	}
	else{
		Temp = fopen("temp.txt", "w+");
		
		//读取前面的数据 
		for (l = 1; l < lvl; l++)
			for (int i = 0; i < size; i++){
				fscanf(fp, "%d", &temp);
				fprintf(Temp, "%d ", temp);
				if (i % SIZE_L == size_l)
					fprintf(Temp, "\n");
			}
		
		//覆盖当前的数据 
		for (int i = 0; i < SIZE_H; i++){
			for (int j = 0; j < SIZE_L; j++)
				fprintf(Temp, "%d ", a[i][j]);
			fprintf(Temp, "\n");
		}
		
		//后面有没有数据 
		count = 0;
		while(~fscanf(fp, "%d", &temp) && temp != INF){
			if(count == 0)
				for (int i = 0; i < size; i++)
					fscanf(fp, "%d", &temp);
			fprintf(Temp, "%d ", temp);
			if (count % SIZE_L == size_l)
				fprintf(Temp, "\n");
			count++;
		}
		
		fprintf(Temp, "%d", INF);
		fseek(Temp, 0L, 0);
		fclose(fp);
		
		//写入数据
		fp = fopen(txtname, "w+");
		count = 0;
		while(~fscanf(Temp, "%d", &temp) && temp != INF){
			fprintf(fp, "%d ", temp);
			if ((count++) % SIZE_L == size_l)
				fprintf(fp, "\n");
		}
		
		fprintf(fp, "%d", INF);
		fclose(Temp);
	}
	fclose(fp);
}

void save(){
	int temp, size = SIZE_L * SIZE_H, size_l = SIZE_L - 1, count, l;
	char txtname[name_max_long];
	FILE *Temp;
	//地牢
	strcpy(txtname, "dungeon.txt");
	save_node(txtname, geography);
	
	//怪物
	strcpy(txtname, "map_monster.txt");
	save_node(txtname, map_monster);
	
	//物品
	strcpy(txtname, "map_item.txt");
	save_node(txtname, map_item);
	
	//地图
	strcpy(txtname, "see.txt");
	save_node(txtname, see);
	
	//地图
	strcpy(txtname, "history.txt");
	save_node(txtname, history);
	
	//房间
	FILE *fp = fopen("house.txt", "r+");
	if (fp == NULL){
		fp = fopen("house.txt", "a+");
		for (int i = 0; i < SIZE_L; i++)
			for (int j = 0; j < 4; j++)
				fprintf(fp, "%d ", houses[i][j]);
		fprintf(fp, "\n%d", INF);
	}
	else{
		Temp = fopen("temp.txt", "w+");
		
		//读取前面的数据 
		int house_size = SIZE_L * 4;
		for (l = 1; l < lvl; l++){
			for (int i = 0; i < house_size; i++){
				fscanf(fp, "%d", &temp);
				fprintf(Temp, "%d ", temp);
			}
			fprintf(Temp, "\n");
		}
		
		//覆盖当前的数据 
		for (int i = 0; i < SIZE_L; i++)
			for (int j = 0; j < 4; j++)
				fprintf(Temp, "%d ", houses[i][j]);
		fprintf(Temp, "\n");
		
		//后面有没有数据 
		count = 0;
		while(~fscanf(fp, "%d", &temp) && temp != INF){
			if(count == 0)
				for (int i = 0; i < house_size; i++)
					fscanf(fp, "%d", &temp);
			fprintf(Temp, "%d ", temp);
			if (count % house_size == house_size - 1)
				fprintf(Temp, "\n");
			count++;
		}
		
		fprintf(Temp, "%d", INF);
		fseek(Temp, 0L, 0);
		fclose(fp);
		
		//写入数据
		fp = fopen("house.txt", "w+");
		count = 0;
		while(~fscanf(Temp, "%d", &temp) && temp != INF){
			fprintf(fp, "%d ", temp);
			if ((count++) % house_size == house_size - 1)
				fprintf(fp, "\n");
		} 
		
		fprintf(fp, "%d", INF);
		fclose(Temp);
	}
	fclose(fp);
	
	//怪物 
	fp = fopen("monsters.txt", "r+");
	if (fp == NULL){
		fp = fopen("monsters.txt", "a+");
		fprintf(fp, "%d\n", 2 * INF);
		for (struct monster_body *monsterstemp = monsters->next; monsterstemp; monsterstemp = monsterstemp->next)
			fprintf(fp, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d\n", monsterstemp->num, monsterstemp->name, monsterstemp->symbol, monsterstemp->color, monsterstemp->frequency, monsterstemp->corpse, monsterstemp->power, monsterstemp->magic, monsterstemp->attack, monsterstemp->fance, monsterstemp->speed, monsterstemp->party, monsterstemp->x, monsterstemp->y);
		fprintf(fp, "%d\n", INF);
	}
	else{
		Temp = fopen("temp.txt", "w+");
		
		//读取前面的数据 
		struct monster_body monsterstemp;
		for (l = 1; l < lvl; l++){
			while(~fscanf(fp, "%d", &monsterstemp.num) && monsterstemp.num != INF){
				if (monsterstemp.num == INF * 2){
					fscanf(fp, "%d", &monsterstemp.num);
					fprintf(Temp, "%d\n", 2 * INF);
				}
				fgetc(fp);
				fscanf(fp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemp.name, &monsterstemp.symbol, &monsterstemp.color, &monsterstemp.frequency, &monsterstemp.corpse, &monsterstemp.power, &monsterstemp.magic, &monsterstemp.attack, &monsterstemp.fance, &monsterstemp.speed, &monsterstemp.party, &monsterstemp.x, &monsterstemp.y);
				fprintf(Temp, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d\n", monsterstemp.num, monsterstemp.name, monsterstemp.symbol, monsterstemp.color, monsterstemp.frequency, monsterstemp.corpse, monsterstemp.power, monsterstemp.magic, monsterstemp.attack, monsterstemp.fance, monsterstemp.speed, monsterstemp.party, monsterstemp.x, monsterstemp.y);
			}
			fprintf(Temp, "%d\n", INF);
		}
		
		//覆盖当前的数据 
		fprintf(Temp, "%d\n", 2 * INF);
		for (struct monster_body *monsterstemps = monsters->next; monsterstemps; monsterstemps = monsterstemps->next)
			fprintf(Temp, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d\n", monsterstemps->num, monsterstemps->name, monsterstemps->symbol, monsterstemps->color, monsterstemps->frequency, monsterstemps->corpse, monsterstemps->power, monsterstemps->magic, monsterstemps->attack, monsterstemps->fance, monsterstemps->speed, monsterstemps->party, monsterstemps->x, monsterstemps->y);
		fprintf(Temp, "%d\n", INF);
		
		//后面有没有数据 
		count = 0;
		while(~fscanf(fp, "%d", &monsterstemp.num) && monsterstemp.num == INF * 2){
			if(count == 0){
				while(~fscanf(fp, "%d", &monsterstemp.num) && monsterstemp.num != INF){
					fgetc(fp);
					fscanf(fp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemp.name, &monsterstemp.symbol, &monsterstemp.color, &monsterstemp.frequency, &monsterstemp.corpse, &monsterstemp.power, &monsterstemp.magic, &monsterstemp.attack, &monsterstemp.fance, &monsterstemp.speed, &monsterstemp.party, &monsterstemp.x, &monsterstemp.y);
				}
			}
			else{
				fprintf(Temp, "%d\n", 2 * INF);
				while(~fscanf(fp, "%d", &monsterstemp.num) && monsterstemp.num != INF){
					fgetc(fp);
					fscanf(fp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemp.name, &monsterstemp.symbol, &monsterstemp.color, &monsterstemp.frequency, &monsterstemp.corpse, &monsterstemp.power, &monsterstemp.magic, &monsterstemp.attack, &monsterstemp.fance, &monsterstemp.speed, &monsterstemp.party, &monsterstemp.x, &monsterstemp.y);
					fprintf(Temp, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d\n", monsterstemp.num, monsterstemp.name, monsterstemp.symbol, monsterstemp.color, monsterstemp.frequency, monsterstemp.corpse, monsterstemp.power, monsterstemp.magic, monsterstemp.attack, monsterstemp.fance, monsterstemp.speed, monsterstemp.party, monsterstemp.x, monsterstemp.y);
				}
				fprintf(Temp, "%d\n", INF);
			}
			count++;
		}
		
		fseek(Temp, 0L, 0);
		fclose(fp);
		
		//写入数据
		fp = fopen("monsters.txt", "w+");
		while(~fscanf(Temp, "%d", &monsterstemp.num) && monsterstemp.num == INF * 2){
			fprintf(fp, "%d\n", 2 * INF);
			while(~fscanf(Temp, "%d", &monsterstemp.num) && monsterstemp.num != INF){
				fgetc(Temp);
				fscanf(Temp, "%s %c %d %d %d %d %d %d %d %d %d %d %d", monsterstemp.name, &monsterstemp.symbol, &monsterstemp.color, &monsterstemp.frequency, &monsterstemp.corpse, &monsterstemp.power, &monsterstemp.magic, &monsterstemp.attack, &monsterstemp.fance, &monsterstemp.speed, &monsterstemp.party, &monsterstemp.x, &monsterstemp.y);
				fprintf(fp, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d\n", monsterstemp.num, monsterstemp.name, monsterstemp.symbol, monsterstemp.color, monsterstemp.frequency, monsterstemp.corpse, monsterstemp.power, monsterstemp.magic, monsterstemp.attack, monsterstemp.fance, monsterstemp.speed, monsterstemp.party, monsterstemp.x, monsterstemp.y);
			}
			fprintf(fp, "%d\n", INF);
		}
		
		fclose(Temp);
	}
	fclose(fp);
	
	//物品 
	fp = fopen("items.txt", "r+");
	if (fp == NULL){
		fp = fopen("items.txt", "a+");
		fprintf(fp, "%d\n", 2 * INF);
		for (struct item_body *itemtemp = items; itemtemp; itemtemp = itemtemp->next)
			fprintf(fp, "%d %s %c %c %d %d %d %d %d %d %d %d %d %d %d\n", itemtemp->color, itemtemp->name, itemtemp->symbol, itemtemp->operation, itemtemp->s1, itemtemp->s2, itemtemp->d, itemtemp->corpse, itemtemp->create, itemtemp->num, itemtemp->x, itemtemp->y, itemtemp->r, itemtemp->state, itemtemp->time);
		fprintf(fp, "%d\n", INF);
	}
	else{
		Temp = fopen("temp.txt", "w+");
		
		//读取前面的数据 
		struct item_body itemtemp;
		for (l = 1; l < lvl; l++){
			while(~fscanf(fp, "%d", &itemtemp.color) && itemtemp.color != INF){
				if (itemtemp.color == INF * 2){
					fscanf(fp, "%d", &itemtemp.color);
					fprintf(Temp, "%d\n", 2 * INF);
				}
				fgetc(fp);
				fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemtemp.name, &itemtemp.symbol, &itemtemp.operation, &itemtemp.s1, &itemtemp.s2, &itemtemp.d, &itemtemp.corpse, &itemtemp.create, &itemtemp.num, &itemtemp.x, &itemtemp.y, &itemtemp.r, &itemtemp.state, &itemtemp.time);
				fprintf(Temp, "%d %s %c %c %d %d %d %d %d %d %d %d %d %d %d\n", itemtemp.color, itemtemp.name, itemtemp.symbol, itemtemp.operation, itemtemp.s1, itemtemp.s2, itemtemp.d, itemtemp.corpse, itemtemp.create, itemtemp.num, itemtemp.x, itemtemp.y, itemtemp.r, itemtemp.state, itemtemp.time);
			}
			fprintf(Temp, "%d\n", INF);
		}
		
		//覆盖当前的数据 
		fprintf(Temp, "%d\n", 2 * INF);
		for (struct item_body *itemtemps = items; itemtemps; itemtemps = itemtemps->next)
			fprintf(Temp, "%d %s %c %c %d %d %d %d %d %d %d %d %d %d %d\n", itemtemps->color, itemtemps->name, itemtemps->symbol, itemtemps->operation, itemtemps->s1, itemtemps->s2, itemtemps->d, itemtemps->corpse, itemtemps->create, itemtemps->num, itemtemps->x, itemtemps->y, itemtemps->r, itemtemps->state, itemtemps->time);
		fprintf(Temp, "%d\n", INF);
		
		//后面有没有数据 
		count = 0;
		while(~fscanf(fp, "%d", &itemtemp.color) && itemtemp.color == INF * 2){
			if(count == 0){
				while(~fscanf(fp, "%d", &itemtemp.color) && itemtemp.color != INF){
					fgetc(fp);
					fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemtemp.name, &itemtemp.symbol, &itemtemp.operation, &itemtemp.s1, &itemtemp.s2, &itemtemp.d, &itemtemp.corpse, &itemtemp.create, &itemtemp.num, &itemtemp.x, &itemtemp.y, &itemtemp.r, &itemtemp.state, &itemtemp.time);
				}
			}
			else{
				fprintf(Temp, "%d\n", 2 * INF);
				while(~fscanf(fp, "%d", &itemtemp.color) && itemtemp.color != INF){
					fgetc(fp);
					fscanf(fp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemtemp.name, &itemtemp.symbol, &itemtemp.operation, &itemtemp.s1, &itemtemp.s2, &itemtemp.d, &itemtemp.corpse, &itemtemp.create, &itemtemp.num, &itemtemp.x, &itemtemp.y, &itemtemp.r, &itemtemp.state, &itemtemp.time);
					fprintf(Temp, "%d %s %c %c %d %d %d %d %d %d %d %d %d %d %d\n", itemtemp.color, itemtemp.name, itemtemp.symbol, itemtemp.operation, itemtemp.s1, itemtemp.s2, itemtemp.d, itemtemp.corpse, itemtemp.create, itemtemp.num, itemtemp.x, itemtemp.y, itemtemp.r, itemtemp.state, itemtemp.time);
				}
				fprintf(Temp, "%d\n", INF);
			}
			count++;
		}
		
		fseek(Temp, 0L, 0);
		fclose(fp);
		
		//写入数据
		fp = fopen("items.txt", "w+");
		while(~fscanf(Temp, "%d", &itemtemp.color) && itemtemp.color == INF * 2){
			fprintf(fp, "%d\n", 2 * INF);
			while(~fscanf(Temp, "%d", &itemtemp.color) && itemtemp.color != INF){
				fgetc(Temp);
					fscanf(Temp, "%s %c %c %d %d %d %d %d %d %d %d %d %d %d", itemtemp.name, &itemtemp.symbol, &itemtemp.operation, &itemtemp.s1, &itemtemp.s2, &itemtemp.d, &itemtemp.corpse, &itemtemp.create, &itemtemp.num, &itemtemp.x, &itemtemp.y, &itemtemp.r, &itemtemp.state, &itemtemp.time);
					fprintf(fp, "%d %s %c %c %d %d %d %d %d %d %d %d %d %d %d\n", itemtemp.color, itemtemp.name, itemtemp.symbol, itemtemp.operation, itemtemp.s1, itemtemp.s2, itemtemp.d, itemtemp.corpse, itemtemp.create, itemtemp.num, itemtemp.x, itemtemp.y, itemtemp.r, itemtemp.state, itemtemp.time);
			}
			fprintf(fp, "%d\n", INF);
		}
		
		fclose(Temp);
	}
	fclose(fp);
}
