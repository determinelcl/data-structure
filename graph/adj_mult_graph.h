//
// Created by determination on 2018/11/8.
//

#ifndef HELLO_ADJ_MULT_GRAPH_H
#define HELLO_ADJ_MULT_GRAPH_H

/**
 * 多重邻接表的实现
 */
#include "graph_generic.h"
#include "array_list.h"

/**
 * 多重邻接表的边节点结构
 */
typedef struct EdgeNode_AMTG {
    bool mark;
    int ivex;
    struct EdgeNode_AMTG *ilink;
    int jvex;
    struct EdgeNode_AMTG *jlink;
    int weight;
} *EdgeNode_AMTG;

/**
 * 多重邻接表的顶点的结构
 */
typedef struct VertexNode_AMTG {
    VertexType data;
    EdgeNode_AMTG firstIn;
} *VertexNode_AMTG;

/**
 * 多重邻接表的结构
 */
typedef struct AMTG {
    ArrayListPtr table;
    int vertexSize;
    int edgeSize;
    GraphKind kind;
} *AdjMultipleTableGraph;


/**
 * 构造一个新的多重邻接表
 *
 * @param vertices 顶点的集合
 * @param edges 边的集合
 * @param countOfVertex 顶点的数量
 * @param countOfEdge 边的数量
 * @param kind 图的类型：无向图或无向网
 * @return 一个新的多重的链表
 */
AdjMultipleTableGraph newAdjMultipleTableGraph(
        Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind);

/**
 * 为多重邻接表存储结构的图新建顶点之间的边
 *
 * @param tableGraph 多重邻接表存储结构的图
 * @param edges 新的边的集合
 * @param countOfEdge 新的边的个数
 */
void newEdgeForGraphVertex_AMTG(AdjMultipleTableGraph tableGraph, Edges edges, int countOfEdge);

/**
 * 显示多重邻接存储结构的图中的顶点和边的信息
 *
 * @param tableGraph 多重邻接存储结构的图
 */
void showAdjMultipleTableGraph_AMTG(AdjMultipleTableGraph tableGraph);

#endif //HELLO_ADJ_MULT_GRAPH_H
