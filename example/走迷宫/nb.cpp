#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
int b[6][6];
// int a[6][6];
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node
{
    int x,y;
    int pre;
}que[510];
int tx,ty;

int a[5][5] =  {{0,1,0,0,0},
                {0,1,0,1,0},
                {0,0,0,0,0},
                {0,1,1,1,0},
                {0,0,0,1,0}}; //迷宫地图

void print(int s)
{
    if(que[s].pre!=-1)
    {
        print(que[s].pre);
        printf("(%d, %d)\n",que[s].x,que[s].y);
    }
}

void bfs(int x,int y)
{
    int head=1,tail=1;
    que[tail].x=x;
    que[tail].y=y;
    que[tail].pre=-1;
    tail++;
    while(head<tail)
    {
        for(int i=0;i<4;i++)
        {
            tx=que[head].x+next[i][0];
            ty=que[head].y+next[i][1];
            if(tx<0||tx>=5||ty<0||ty>=5)continue;
            if(b[tx][ty]==0&&a[tx][ty]==0)
            {
                b[tx][ty]=1;
                que[tail].x=tx;
                que[tail].y=ty;
                que[tail].pre=head;
                tail++;
            }
            if(tx==4&&ty==4)
                print(head);
        }
        head++;
    }
}

int main()
{
    // for(int i=0;i<5;i++)
    // {
    //     for(int j=0;j<5;j++)
    //     {
    //         scanf("%d",&a[i][j]);
    //     }
    // }
    memset(b,0,sizeof(b));
    b[0][0]=1;
    printf("(0, 0)\n");
    bfs(0,0);
    printf("(4, 4)\n");
    return 0;
}