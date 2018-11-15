//
// Created by determination on 2018/10/12.
//

#include "adj_matrix_graph.h"
#include "array_queue_o.h"

/**
 * 创建有向图
 */
MatrixGraph createDG(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge);

/**
 * 创建有向网
 */
MatrixGraph createDN(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge);

/**
 * 创建无向网
 */
MatrixGraph createUDG(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge);

/**
 * 创建无向网
 */
MatrixGraph createUDN(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge);

/**
 * 创建空的邻接矩阵
 */
MatrixGraph newEmptyMatrixGraph(int countOfVertex, int countOfEdge);

/**
 * 将顶点放入到邻接矩阵中
 */
void putVertexIntoMatrix(MatrixGraph matrixGraph, Vertices vertex, int countOfVertex);

void dfs_AMG(MatrixGraph matrixGraph, bool *markFlag, int index);

MatrixGraph createAdjacencyMatrix(
        Vertices vertex, Edges edge, int countOfVertex, int countOfEdge, GraphKind kind) {

    switch (kind) {
        case DG:    // 有向图
            return createDG(vertex, edge, countOfVertex, countOfEdge);
        case DN:    // 有向网
            return createDN(vertex, edge, countOfVertex, countOfEdge);
        case UDG:   // 无向图
            return createUDG(vertex, edge, countOfVertex, countOfEdge);
        case UDN:   // 无向网
            return createUDN(vertex, edge, countOfVertex, countOfEdge);
        default:
            return NULL;
    }
}

MatrixGraph newEmptyMatrixGraph(int countOfVertex, int countOfEdge) {
    MatrixGraph matrixGraph = malloc(sizeof(struct AMG));
    assert(matrixGraph);

    matrixGraph->vertex = malloc(sizeof(VertexType) * countOfVertex);
    matrixGraph->matrix = malloc(sizeof(int *) * countOfVertex);
    assert(matrixGraph->matrix);
    for (int i = 0; i < countOfVertex; ++i) {
        matrixGraph->matrix[i] = malloc(sizeof(int) * countOfVertex);
        assert(matrixGraph->matrix[i]);
    }


    matrixGraph->vexNum = countOfVertex;
    matrixGraph->edgeNum = countOfEdge;

    // 初始化矩阵
    for (int i = 0; i < countOfVertex; ++i) {
        for (int j = 0; j < countOfVertex; ++j) {
            matrixGraph->matrix[i][j] = UNFLAG_WEIGHT_GRAPH;
        }
    }

    return matrixGraph;
}


MatrixGraph createDG(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge) {
    if (countOfVertex <= 0) return NULL;
    MatrixGraph matrixGraph = newEmptyMatrixGraph(countOfVertex, countOfEdge);
    matrixGraph->kind = DG;

    putVertexIntoMatrix(matrixGraph, vertex, countOfVertex);

    // 构建矩阵
    for (int i = 0; i < countOfEdge; i++) {
        matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
    }

    return matrixGraph;
}

MatrixGraph createDN(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge) {
    if (countOfVertex <= 0) return NULL;
    MatrixGraph matrixGraph = newEmptyMatrixGraph(countOfVertex, countOfEdge);
    matrixGraph->kind = DN;
    putVertexIntoMatrix(matrixGraph, vertex, countOfVertex);

    // 构建矩阵
    for (int i = 0; i < countOfEdge; i++) {
        matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
    }

    return matrixGraph;
}

MatrixGraph createUDG(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge) {
    if (countOfVertex <= 0) return NULL;
    MatrixGraph matrixGraph = newEmptyMatrixGraph(countOfVertex, countOfEdge);
    matrixGraph->kind = UDG;
    putVertexIntoMatrix(matrixGraph, vertex, countOfVertex);

    // 构建矩阵
    for (int i = 0; i < countOfEdge; ++i) {
        matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
        matrixGraph->matrix[edge[i].vj][edge[i].vi] = 1;
    }

    return matrixGraph;
}

MatrixGraph createUDN(Vertices vertex, Edges edge, int countOfVertex, int countOfEdge) {
    if (countOfVertex <= 0) return NULL;
    MatrixGraph matrixGraph = newEmptyMatrixGraph(countOfVertex, countOfEdge);
    matrixGraph->kind = UDN;
    putVertexIntoMatrix(matrixGraph, vertex, countOfVertex);

    // 构建矩阵
    for (int i = 0; i < countOfEdge; ++i) {
        matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
        matrixGraph->matrix[edge[i].vj][edge[i].vi] = edge[i].weight;
    }

    return matrixGraph;
}

void putVertexIntoMatrix(MatrixGraph matrixGraph, Vertices vertex, int countOfVertex) {// 存放顶点到邻接矩阵
    for (int i = 0; i < countOfVertex; ++i) {
        matrixGraph->vertex[i] = vertex[i];
    }
}

void newEdgeForGraphVertex_AMG(MatrixGraph matrixGraph, Edges edge, int countOfEdge) {
    assert(matrixGraph);
    assert(matrixGraph->vertex);

    for (int i = 0; i < countOfEdge; ++i) {
        switch (matrixGraph->kind) {
            case DG:
                matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
                break;

            case DN:
                matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
                break;

            case UDG:
                matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
                matrixGraph->matrix[edge[i].vj][edge[i].vi] = 1;
                break;

            case UDN:
                matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
                matrixGraph->matrix[edge[i].vj][edge[i].vi] = edge[i].weight;
                break;
        }
    }
}

void showMatrixGraph_AMG(MatrixGraph matrixGraph) {
    assert(matrixGraph);
    assert(matrixGraph->vertex);

    // 打印矩阵的行的头
    for (int i = 0; i < matrixGraph->vexNum; ++i) {
        fprintf(stdout, "\t%c", matrixGraph->vertex[i]);
    }
    fprintf(stdout, "\n");

    // 打印矩阵
    for (int i = 0; i < matrixGraph->vexNum; i++) {
        // 打印矩阵列的头
        fprintf(stdout, "%c[\t", matrixGraph->vertex[i]);
        for (int j = 0; j < matrixGraph->vexNum; j++) {
            int value = matrixGraph->matrix[i][j];

            // 判定如果是图，则是矩阵空则为0，如果是网，则是矩阵空为∞
            if (matrixGraph->kind == DG || matrixGraph->kind == UDG)
                fprintf(stdout, "%d\t", value != UNFLAG_WEIGHT_GRAPH ? value : 0);
            else {
                if (value == UNFLAG_WEIGHT_GRAPH)
                    fprintf(stdout, "∞\t");
                else fprintf(stdout, "%d\t", value);
            }
        }
        fprintf(stdout, "]\n");
    }

    puts("\n");
}


void dfsTraversal_AMG(MatrixGraph matrixGraph) {
    assert(matrixGraph);

    // 用于标记被访问的节点
    bool markFlag[matrixGraph->vexNum];
    for (int i = 0; i < matrixGraph->vexNum; i++)
        markFlag[i] = false;


    // 设置节点被访问标志的顺序
    for (int i = 0; i < matrixGraph->vexNum; i++) {
        if (markFlag[i]) continue;
        dfs_AMG(matrixGraph, markFlag, i);
    }

    fprintf(stdout, "\n\n");
}

void dfs_AMG(MatrixGraph matrixGraph, bool *markFlag, int index) {
    markFlag[index] = true;
    printf("%c\t", matrixGraph->vertex[index]);

    for (int i = 0; i < matrixGraph->vexNum; i++) {
        if (matrixGraph->matrix[index][i] != UNFLAG_WEIGHT_GRAPH && !markFlag[i])
            dfs_AMG(matrixGraph, markFlag, i);
    }
}

void bfsTraversal_AMG(MatrixGraph matrixGraph) {
    ArrayQueue queue = newQueue_AQ(matrixGraph->vexNum + 2);
    bool markFlag[matrixGraph->vexNum];
    for (int i = 0; i < matrixGraph->vexNum; i++)
        markFlag[i] = false;

    for (int i = 0; i < matrixGraph->vexNum; i++) {
        if (markFlag[i]) continue;

        markFlag[i] = true;
        printf("%c\t", matrixGraph->vertex[i]);
        enqueue_AQ(queue, i);


        while (!isEmpty_AQ(queue)) {
            int vexIndex = frontAndDequeue_AQ(queue);

            for (int j = 0; j < matrixGraph->vexNum; j++) {
                if (matrixGraph->matrix[vexIndex][j] == UNFLAG_WEIGHT_GRAPH || markFlag[j]) continue;

                printf("%c\t", matrixGraph->vertex[j]);
                markFlag[j] = true;
                enqueue_AQ(queue, j);
            }
        }
    }

    fprintf(stdout, "\n\n");
}