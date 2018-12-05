//
// Created by determination on 2018/10/12.
//

#ifndef HELLO_ADJ_MATRIX_GRAPH_H
#define HELLO_ADJ_MATRIX_GRAPH_H

#include "graph_generic.h"



typedef struct AMG {
    VertexType *vertex; // 顶点集合
    int **matrix;           // 图的邻接矩阵
    int vexNum;             // 图的顶点的个数
    int edgeNum;            // 图的边的个数
    GraphKind kind;         // 图的种类标志
} *MatrixGraph;

/**
 * 新建一个邻接矩阵
 *
 * @param vertex 用户给定顶点
 * @param edge 用于给定顶点之间的关系，为两顶点之间的边
 * @param countOfVertex 给定顶点的个数
 * @param kind 创建的图的类型
 * @return 创建完成的邻接矩阵标示的图
 */
MatrixGraph createAdjacencyMatrix(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge, GraphKind kind);

/**
 * 新增边
 *
 * @param matrixGraph 邻接矩阵结构存储的图
 * @param edge 新建的图中顶点与顶点的边
 */
void newEdgeForGraphVertex_AMG(MatrixGraph matrixGraph, Edges edge, int countOfEdge);

/**
 * 打印构建完成的邻接矩阵
 *
 * @param matrixGraph 构建完成的使用邻接矩阵结构存储的图
 */
void showMatrixGraph_AMG(MatrixGraph matrixGraph);

/**
 * 深度优先遍历图
 *
 * @param matrixGraph 需要遍历的图
 */
void dfsTraversal_AMG(MatrixGraph matrixGraph);

/**
 * 广度优先遍历图
 *
 * @param matrixGraph 需要遍历的图
 */
void bfsTraversal_AMG(MatrixGraph matrixGraph);

/**
 * 统计邻接矩阵存储图的连通分量的个数
 *
 * @param matrixGraph 邻接矩阵存储的结构的存储
 * @return 连通分量的个数
 */
int numOfConnectedComponents_AMG(MatrixGraph matrixGraph);

/**
 * 使用Prime算法生成最小二叉生成树
 *
 * @param matrixGraph 邻接矩阵存储结构的图
 */
void miniSpanTree_Prim(MatrixGraph matrixGraph);

/**
 * 使用Kruskal算法生成最小二叉生成树
 *
 * @param matrixGraph 邻接矩阵存储结构的图
 */
void miniSpanTree_Kruskal(MatrixGraph matrixGraph);

#endif //HELLO_ADJ_MATRIX_GRAPH_H
