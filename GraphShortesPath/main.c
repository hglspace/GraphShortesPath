//
//  main.c
//  GraphShortesPath
//
//  Created by hgl on 2018/2/1.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custome.h"
int main(int argc, const char * argv[]) {
   
    struct Graph g=init();
    printEdg(g);
    ShortestPath(g);
    return 0;
}
