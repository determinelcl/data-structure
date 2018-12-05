//
// Created by determination on 2018/10/18.
//

#ifndef HELLO_GRAPH_GENERIC_H
#define HELLO_GRAPH_GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define UNFLAG_WEIGHT_GRAPH 32767

typedef enum {
    DG,     // 有向图
    DN,     // 有向网
    UDG,    // 无向图
    UDN     // 无向网
} GraphKind;

typedef char VertexType;    // 图的顶点的类型
typedef VertexType *Vertices;

/**
 * 表示为描述边的结构
 */
typedef struct {
    int vi;
    int vj;
    int weight;
} EdgeType;

typedef EdgeType *Edges;

#endif //HELLO_GRAPH_GENERIC_H
