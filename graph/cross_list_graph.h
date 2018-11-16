//
// Created by determination on 2018/10/26.
//

#ifndef HELLO_CROSS_LIST_GRAPH_H
#define HELLO_CROSS_LIST_GRAPH_H

/**
 * 有向图的十字链表存储结构
 */
#include "graph_generic.h"
#include "array_list.h"


/**
 * 边的节点
 */
typedef struct EdgeNode_CLG {
    int headVex;                // 弧头的下标
    int tailVex;                // 弧尾的下标
    struct EdgeNode_CLG *hLink; // 指向下一个具有相同头节点的边
    int weight;                 // 表示权重值
    struct EdgeNode_CLG *tLink; // 指向下一个具有相同尾节点的边
} *EdgeNode_CLG;


/**
 * 存放顶点的节点
 */
typedef struct VertexNode_CLG {
    VertexType data;            // 顶点数据
    EdgeNode_CLG firstIn;       // 此顶点的入度的边
    EdgeNode_CLG firstOut;      // 此顶点的出度的边
} *VertexNode_CLG;


/**
 * 图的十字链表结构的存储表示
 */
typedef struct CLG {
    ArrayListPtr cljTable;      // 十字链表的顶点的集合
    int vertexSize;             // 顶点的大小
    int edgeSize;               // 边的大小
    GraphKind kind;             // 图的类型：有向图或有向网
} *ClgGraph;

/**
 * 创建十字链表存储结构的图
 *
 * @param vertices 构造十字链表的顶点
 * @param edges 构造十字链表的边
 * @param countOfVertex 顶点的数量
 * @param countOfEdge 边的数量
 * @param kind 图的类型
 * @return 十字链表存储结构的图
 */
ClgGraph createClgGraph(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind);

/**
 * 新建一条边
 *
 * @param clgGraph 需要新建边的图
 * @param edges 新的边
 * @param countOfEdge 新建边的数量
 */
void newEdgeForGraphVertex_CLG(ClgGraph clgGraph, Edges edges, int countOfEdge);

/**
 * 打印十字链表存储结构的图
 *
 * @param clgGraph 需要打印的图
 */
void showClgGraph_CLG(ClgGraph clgGraph);

/**
 * 深度优先遍历图
 *
 * @param clgGraph 需要遍历的图
 */
void dfsTraversal_CLG(ClgGraph clgGraph);

/**
 * 广度优先遍历图
 *
 * @param clgGraph 需要遍历的图
 */
void bfsTraversal_CLG(ClgGraph clgGraph);

#endif //HELLO_CROSS_LIST_GRAPH_H
