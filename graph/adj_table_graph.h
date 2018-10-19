//
// Created by determination on 2018/10/18.
//

#ifndef HELLO_ADJ_TABLE_GRAPH_H
#define HELLO_ADJ_TABLE_GRAPH_H

#include "graph_generic.h"
#include "array_list.h"

typedef struct EdgeNode_ATG {
    int adjvex;                 // 邻接顶点的索引
    int weight;                 // 如果是网，则表示边上的权值
    struct EdgeNode_ATG *next;  // 与下一个顶点所对应的边
} *EdgeNode_ATG;

typedef struct VertexNode_ATG {
    VertexType vertex;          // 顶点的数据域
    EdgeNode_ATG firstEdge;     // 与当前顶点邻接的下一个顶点所对应的边
} *VertexNode_ATG;

typedef struct ATG {
    ArrayListPtr adjTable;      // 邻接表
    int countOfVertex;          // 顶点的数量
    int countOfEdge;            // 边的数量
    GraphKind kind;             // 图的类型
} *AdjTableGraph;


/**
 * 创建邻接表存储结构的图结构
 *
 * @param vertices 创建的图的顶点
 * @param edges 创建的图的顶点的边
 * @param countOfVertex 图顶点的个数
 * @param countOfEdge 边的个数
 * @param kind  图的类型
 * @return 构建好的邻接表存储结构的图
 */
AdjTableGraph newAdjTableGraph(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind);

/**
 * 新建一条边
 *
 * @param tableGraph 邻接表构建的图
 * @param edges 顶点与顶点的边
 * @param countOfEdge 边的个数
 */
void newEdgeForGraphVertex_ATG(AdjTableGraph tableGraph, Edges edges, int countOfEdge);

/**
 * 打印邻接表结构存储的图的元素
 *
 * @param tableGraph 邻接表存储结构的图的元素
 */
void showAdjTableGraph_ATG(AdjTableGraph tableGraph);


#endif //HELLO_ADJ_TABLE_GRAPH_H
