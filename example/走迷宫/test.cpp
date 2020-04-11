/*
   0,1,0,0,0
   0,1,0,1,0
   0,0,0,0,0
   0,1,1,1,0
   0,0,0,1,0
 */

#include <stdio.h>
#include <queue>

using namespace std;

typedef struct node{
	int first;
	int second;
	int per; //用于记录上一个节点信息
}Node;
Node pnode[25] = {{0,0,0}}; //用于缓存下一个节点
int map[5][5] = {{0,1,0,0,0},
                {0,1,0,1,0},
                {0,0,0,0,0},
                {0,1,1,1,0},
                {0,0,0,1,0}}; //迷宫地图

int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}}; //迷宫里移动的方向
bool path[5][5] = {false}; //记录走过的路径

Node Vs = {0,4,0},Ve = {4,0,25},Vn,Vw; //迷宫起点和终点位置

int head = 0,tail = 0;

void print(void){
	printf("path is :\n");
    for(int i =0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(path[j][4-i]){   //坐标系转换为数组下标在打印
                printf("* ");
            }else{
                printf("x ");
            }
        }
        printf("\n");
    }
}

void print_path(int s){
	printf("s %d\n",s);
	if(pnode[s].per != 0){
		print_path(pnode[s].per);
		
		printf("%d (%d, %d)\n",pnode[s].per,pnode[s].first,pnode[s].second);
	}
}

int main(){  
	Vs.per = head;//起点进栈
	path[Vs.first][Vs.second] = true;
    pnode[tail] = Vs;
	tail++;

    //for(int i=0;i<4 /*head < tail*/;i++){
	while(head < tail){

        Vn = pnode[head];
		//printf("取出 node %d %d %d\n",Vn.first,Vn.second,Vn.per);

        for(int i=0; i<4 ; i++){

            Vw.first = Vn.first+dir[i][0]; 
			Vw.second = Vn.second+dir[i][1];
	
			//printf("node %d %d %d\n",Vw.first,Vw.second,Vw.per);
            if((Vw.first == Ve.first) && (Vw.second == Ve.second)){ //找到终点
                pnode[tail] = Vw;
				path[Vw.first][Vw.second] = true;
				print();
				printf("head = %d",head);
				print_path(head);
                return 0;
            }
			
            //判断Vn是否合法
            if(Vw.first < 0 || Vw.first > 4) continue;
            if(Vw.second < 0 || Vw.second > 4) continue;
            if(map[4-Vw.second][Vw.first] != 0) continue;
            if((path[Vw.first][Vw.second] != true)){
				printf("进栈 node[%d] (%d %d) Vw.per = %d head = %d\n",tail,Vw.first,Vw.second,Vw.per,head);
				path[Vw.first][Vw.second] = true;
				Vw.per = head;
                pnode[tail] = Vw;
				tail++;
            }
        }
		head++;
		//printf("head = %d tail = %d\n",head,tail);
		//printf("----------\n");
    }

    /*printf("path is :\n");
    for(int i =0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(path[j][4-i]){   //坐标系转换为数组下标在打印
                printf("* ");
            }else{
                printf("x ");
            }
        }
        printf("\n");
    }*/

    return 1;
}
