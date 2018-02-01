//
//  GraphOpera.c
//  GraphShortesPath
//
//  Created by hgl on 2018/2/1.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custome.h"
#include <stdlib.h>
#define MAXDISTANCE 9999//假如两个顶点没有 直接 的路径，它们之间的权值就用这个来表示
/*
  初始化图，求有向图的某个顶点到其他顶点的最短路径用邻接矩阵存储存储图
 */
struct Graph init(void){
    struct Graph g;
    int i,j,k1,k2,weight;
    char data1,data2;
    int locateVert(struct Graph g,char data);
    printf("请输入图的顶点数:");
    scanf("%d",&g.vertnum);
    printf("请输入图的边数:");
    scanf("%d",&g.edgnum);
    for(i=0;i<g.vertnum;i++){
        printf("请输入第%d个顶点:",i+1);
        scanf(" %c",&g.verts[i]);
    }
    for(i=0;i<g.vertnum;i++){
        for(j=0;j<g.vertnum;j++){
            g.edgs[i][j]=MAXDISTANCE;//先给边赋上最大的权值
        }
    }
    for(j=0;j<g.edgnum;j++){
        printf("请输入第%d条边的起点:",j+1);
        scanf(" %c",&data1);
        printf("请输入第%d条边的终点:",j+1);
        scanf(" %c",&data2);
        printf("请输入第%d条边的权值:",j+1);
        scanf("%d",&weight);
        k1=locateVert(g,data1);
        k2=locateVert(g,data2);
        g.edgs[k1][k2]=weight;//对边进行赋权值
    }
    return g;
}

/*
   根据顶点信息求顶点的位置
 */
int locateVert(struct Graph g,char data){
    int i;
    for(i=0;g.verts[i]!=data;i++);
    if(i>g.vertnum-1){
        printf("输入的顶点有误");
        exit(1);
    }
    return i;
}

/*
  打印该图的边的权值
 */
void printEdg(struct Graph g){
    int i,j;
    for(i=0;i<g.vertnum;i++){
        for(j=0;j<g.vertnum;j++){
            printf("%d\t",g.edgs[i][j]);
            if(j==g.vertnum-1){
                printf("\n");
            }
        }
    }
}

/*
  求从顶点 a 到其他顶点的最短距离
 */
void ShortestPath(struct Graph g){
    Bool p[MAX_VERT_NUM][MAX_VERT_NUM];//若p[v][w]为True，则w是从a顶点到其余顶点v的最短路径上的顶点
    int D[MAX_VERT_NUM];//为顶点a到该第i个顶点最短路径的权值和
    Bool final[MAX_VERT_NUM];//final[i]为true，当且仅当第i个顶点属于s，即已经求得从a到第i个顶点的最短路径
    int v,w,i,j,distance=9999,min,k;
    for(v=0;v<g.vertnum;v++){
        final[v]=False;
        D[v]=g.edgs[0][v];
        for(w=0;w<g.vertnum;w++) p[v][w]=False;
        if(D[v]<distance){
            p[v][0]=True;
            p[v][v]=True;
        }
    }
    D[0]=0;
    final[0]=True;
    /*开始主循环，每次求得a到其他顶点距离中最短的一个，并加v到s中,比如第一次求得的是a顶点到c顶点的距离最短，为10，
      第二次求得的是a顶点到e顶点的距离最短，为30，以此类推，以后求的都是次短的路径距离*/
    for(i=0;i<g.vertnum;i++){
        min=distance;
        for(w=0;w<g.vertnum;w++){//循环完之后，求得的是其他顶点到a的最短路径，就是假如c到a是10，b到a是5，那么求得的顶点是b
            if(!final[w]){
                if(D[w]<min){
                    v=w;
                    min=D[w];
                }
            }
        }
        final[v]=True;//求得a顶点到其他顶点距离中最小的那个顶点后，把该顶点加入到final数组中，代表已经求出来了，下次循环开始求次短的
        for(w=0;w<g.vertnum;w++){
            /*更新其他顶点到a的最短距离，上一步求出到a顶点有最短路径的顶点了，求a顶点通过该顶点到其他顶点的距离，
              和他们直接到a顶点的距离相比较，是否需要重新对D[i]赋值*/
            if(!final[w] && (min+g.edgs[v][w]<D[w])){
                D[w]=min+g.edgs[v][w];
                for(k=0;k<g.vertnum;k++){
                    p[w][k]=p[v][k];
                }
                p[w][w]=True;//如果a顶点有到w顶点的路径，说明在a顶点到w顶点的路径上，一定包括w顶点
            }
        }
    }
    //打印出最后的结果
    for(i=1;i<g.vertnum;i++){
        printf("a顶点到%c顶点的权值是:%d\n",g.verts[i],D[i]);
        if(D[i]>=distance){
            printf("没有路径\n");
        }else{
            printf("{");
            for(j=0;j<g.vertnum;j++){
                if(p[i][j]){
                    printf("%c\t",g.verts[j]);
                }
            }
            printf("}\n");
        }
    }
}

