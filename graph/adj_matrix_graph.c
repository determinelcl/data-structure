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

void dfs_AMG(MatrixGraph matrixGraph, bool *markFlag, int index, bool isPrintFlag);

void sortEdges_AMG(MatrixGraph matrixGraph, Edges edges);

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
                if (matrixGraph->matrix[edge[i].vi][edge[i].vj] == 0 ||
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] == UNFLAG_WEIGHT_GRAPH) {
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
                    matrixGraph->edgeNum++;
                }
                break;

            case DN:
                if (matrixGraph->matrix[edge[i].vi][edge[i].vj] == 0 ||
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] == UNFLAG_WEIGHT_GRAPH) {
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
                    matrixGraph->edgeNum++;
                }
                break;

            case UDG:
                if (matrixGraph->matrix[edge[i].vi][edge[i].vj] == 0 ||
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] == UNFLAG_WEIGHT_GRAPH) {
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] = 1;
                    matrixGraph->matrix[edge[i].vj][edge[i].vi] = 1;
                    matrixGraph->edgeNum++;
                }
                break;

            case UDN:
                if (matrixGraph->matrix[edge[i].vi][edge[i].vj] == 0 ||
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] == UNFLAG_WEIGHT_GRAPH) {
                    matrixGraph->matrix[edge[i].vi][edge[i].vj] = edge[i].weight;
                    matrixGraph->matrix[edge[i].vj][edge[i].vi] = edge[i].weight;
                    matrixGraph->edgeNum++;
                }
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
        dfs_AMG(matrixGraph, markFlag, i, true);
    }

    fprintf(stdout, "\n\n");
}

void dfs_AMG(MatrixGraph matrixGraph, bool *markFlag, int index, bool isPrintFlag) {
    markFlag[index] = true;
    if (isPrintFlag)
        printf("%c\t", matrixGraph->vertex[index]);

    for (int i = 0; i < matrixGraph->vexNum; i++) {
        if (matrixGraph->matrix[index][i] != UNFLAG_WEIGHT_GRAPH && !markFlag[i])
            dfs_AMG(matrixGraph, markFlag, i, isPrintFlag);
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

int numOfConnectedComponents_AMG(MatrixGraph matrixGraph) {
    assert(matrixGraph);

    // 用于标记被访问的节点
    bool markFlag[matrixGraph->vexNum];
    for (int i = 0; i < matrixGraph->vexNum; i++)
        markFlag[i] = false;


    int num = 0;
    // 设置节点被访问标志的顺序
    for (int i = 0; i < matrixGraph->vexNum; i++) {
        if (markFlag[i]) continue;
        dfs_AMG(matrixGraph, markFlag, i, false);
        num++;
    }
    return num;
}

/**
 * Prim算法求最小生成树：
 *
 * 1、初始化两个集合：一个顶点集和一个对应的相对最小的权重值的集合
 * 2、遍历权重值集合，找出权重最小的值，并记录下权重值最小对应的顶点的索引
 * 3、输出边的信息
 * 4、置权值集合的最小权值的的位置的值为0，表示已访问过
 * 5、根据输出的最小权值所对应的顶点，比较与最小权值顶点的边邻接的顶点的权值，
 *      如果比权值数组中小，那么更新权值数组中的值，否则不更新，到循环最后，
 *      集合到对应各个边的权值边就是两个访问过的顶点邻接的顶点的边的权值为最小的
 *
 * @param matrixGraph
 */
void miniSpanTree_Prim(MatrixGraph matrixGraph) {
    int vertexU[matrixGraph->vexNum];    // 保存相关顶点下标
    int weightsU[matrixGraph->vexNum];   // 保存相关顶点的权值

    vertexU[0] = 0;  // 初始化第一个顶点下标为0
    weightsU[0] = 0; // 初始化第一个权值为0，即v0加入生成树中

    for (int i = 1; i < matrixGraph->vexNum; i++) {
        vertexU[i] = 0;                             // 都初始化为v0的下标
        weightsU[i] = matrixGraph->matrix[0][i];    // 将与v0顶点相关点的权值存入weightsU数组中
    }


    for (int i = 1; i < matrixGraph->vexNum; i++) {
        int indexOfMinWeight = 0;
        int min = 32767;

        // 寻找当前权值最小的边
        for (int j = 1; j < matrixGraph->vexNum; j++) {
            // 如果权值不为0且不等于没有权值的标志
            if (weightsU[j] == 0 || weightsU[j] == UNFLAG_WEIGHT_GRAPH) continue;
            if (weightsU[j] < min) {
                min = weightsU[j];
                indexOfMinWeight = j;
            }
        }

        // indexOfMinWeight用来保存权值最小的顶点的索引
        // 打印当前顶点中权值最小的边
        printf("(%c,%c)", matrixGraph->vertex[vertexU[indexOfMinWeight]], matrixGraph->vertex[indexOfMinWeight]);
        weightsU[indexOfMinWeight] = 0;    // 将当前顶点的权值置为0，表示完成任务


        // 更新weightsU和vertexU数组
        for (int j = 1; j < matrixGraph->vexNum; j++) {
            if (weightsU[j] != 0 && matrixGraph->matrix[indexOfMinWeight][j] < weightsU[j]) {
                // 在所有u ∈ U, v ∈ V-U的边中选一条代价最小的边（u0，v0）并入集合 TE，同时将v0并入U；
                weightsU[j] = matrixGraph->matrix[indexOfMinWeight][j];
                vertexU[j] = indexOfMinWeight;
            }
        }
    }
    printf("\n\n");
}

int find_AMG(const int *parent, int f) {
    while (parent[f] > 0)
        f = parent[f];

    return f;
}

// Kruskal最小生成树算法
void miniSpanTree_Kruskal(MatrixGraph matrixGraph) {
    Edges edges = malloc(sizeof(EdgeType) * matrixGraph->edgeNum);
    // 定义一数组来判断边与边是否形成环路
    int parent[matrixGraph->vexNum];
    for (int i = 0; i < matrixGraph->vexNum; i++)
        parent[i] = 0;

    sortEdges_AMG(matrixGraph, edges);
    for (int i = 0; i < matrixGraph->edgeNum; i++) {
        // 看一看在S集合中时候有此顶点
        int n = find_AMG(parent, edges[i].vi);
        int m = find_AMG(parent, edges[i].vj);

        if (n != m) {  // 如果n和m不相等，说明此边没有与现有生成树形成环路
            parent[n] = m; // 将此边的结尾顶点放在下标为n的parent，表示已经放入到生成树集合中
            printf("(%c,%c)", matrixGraph->vertex[edges[i].vi], matrixGraph->vertex[edges[i].vj]);
        }
    }

    printf("\n\n");
}

void sortEdges_AMG(MatrixGraph matrixGraph, Edges edges) {
    int count = 0;
    for (int i = 0; i < matrixGraph->vexNum; i++) {
        for (int j = matrixGraph->vexNum - 1; j > i; j--) {
            if (matrixGraph->matrix[i][j] == 0 || matrixGraph->matrix[i][j] == UNFLAG_WEIGHT_GRAPH) continue;
            EdgeType edge = {i, j, matrixGraph->matrix[i][j]};
            edges[count++] = edge;
        }
    }

    // 根据边集按照冒泡排序
    for (int i = 0; i < matrixGraph->edgeNum; i++) {
        for (int j = i; j < matrixGraph->edgeNum; ++j) {
            if (edges[i].weight > edges[j].weight) {
                EdgeType temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}