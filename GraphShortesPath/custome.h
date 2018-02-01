//
//  custome.h
//  GraphShortesPath
//
//  Created by hgl on 2018/2/1.
//  Copyright © 2018年 hgl. All rights reserved.
//

#ifndef custome_h
#define custome_h
#define MAX_VERT_NUM 10
typedef int Bool;
#define False 0
#define True 1
struct Graph{
    char verts[MAX_VERT_NUM];
    int edgs[MAX_VERT_NUM][MAX_VERT_NUM];
    int vertnum;
    int edgnum;
};
struct Graph init(void);
void printEdg(struct Graph g);
void ShortestPath(struct Graph g);
#endif /* custome_h */
