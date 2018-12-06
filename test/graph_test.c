//
// Created by determination on 2018/10/12.
//

#include "graph_test.h"

Vertices newVexTestCase(int VERTEX_SIZE);

Edges newEdgeTestCase(int VERTEX_SIZE);

Edges reAllocEdge(int VERTEX_SIZE, Edges edges);

void testAdjMatrixGraph() {
    printf("*****************************************************\n");
    printf("*              邻接矩阵存储结构图测试例程              *\n");
    printf("*****************************************************\n");

    const int VERTEX_SIZE = 5;
    Vertices vertex = newVexTestCase(VERTEX_SIZE);

    // [a, b, c, d, e]
    Edges edge = newEdgeTestCase(VERTEX_SIZE);

    MatrixGraph matrix = createAdjacencyMatrix(vertex, edge, VERTEX_SIZE, VERTEX_SIZE, DN);
    showMatrixGraph_AMG(matrix);

    edge = reAllocEdge(VERTEX_SIZE, edge);

    newEdgeForGraphVertex_AMG(matrix, edge, VERTEX_SIZE + 2);
    showMatrixGraph_AMG(matrix);

    printf("深度优先遍历的结果：\n");
    dfsTraversal_AMG(matrix);

    printf("广度优先遍历的结果：\n");
    bfsTraversal_AMG(matrix);

    printf("连通分量的个数为：%d\n", numOfConnectedComponents_AMG(matrix));

    printf("Prime的算法计算最小生成树：\n");
    miniSpanTree_Prim(matrix);

    printf("Kruskal的算法计算最小生成树：\n");
    miniSpanTree_Kruskal(matrix);

    printf("Dijkstra算法计算最短路径：\n");
    int D[matrix->vexNum], V0 = 0;
    shortPath_Dijkstra(matrix, V0, D);
    for (int i = 0; i < matrix->vexNum; ++i)
        printf("%c -> %c : %d\n", matrix->vertex[V0], matrix->vertex[i], D[i]);

    printf("Floyd算法计算最短路径：\n");
    int P[matrix->vexNum][matrix->vexNum];
    int D_f[matrix->vexNum][matrix->vexNum];
    shortestPath_Floyd(matrix, P, D_f);
    printf("矩阵D：\n");
    for (int i = 0; i < matrix->vexNum; ++i) {
        for (int j = 0; j < matrix->vexNum; ++j)
            if (D_f[i][j] == UNFLAG_WEIGHT_GRAPH)
                printf("∞\t");
            else
                printf("%d\t", D_f[i][j]);
        printf("\n");
    }

    printf("矩阵P：\n");
    for (int i = 0; i < matrix->vexNum; ++i) {
        for (int j = 0; j < matrix->vexNum; ++j)
            printf("%d\t", P[i][j]);
        printf("\n");
    }
    puts("\n");
}

Edges reAllocEdge(const int VERTEX_SIZE, Edges edges) {
    edges = realloc(edges, sizeof(EdgeType) * (VERTEX_SIZE + 2));
    edges[5].vi = 1;
    edges[5].vj = 3;
    edges[5].weight = 60;

    edges[6].vi = 3;
    edges[6].vj = 2;
    edges[6].weight = 90;
    return edges;
}

Edges newEdgeTestCase(const int VERTEX_SIZE) {
    Edges edge = malloc(sizeof(EdgeType) * VERTEX_SIZE);
    edge[0].vi = 0;
    edge[0].vj = 1;
    edge[0].weight = 10;

    edge[1].vi = 0;
    edge[1].vj = 2;
    edge[1].weight = 20;

    edge[2].vi = 0;
    edge[2].vj = 3;
    edge[2].weight = 30;

    edge[3].vi = 2;
    edge[3].vj = 4;
    edge[3].weight = 40;

    edge[4].vi = 2;
    edge[4].vj = 1;
    edge[4].weight = 50;
    return edge;
}

Vertices newVexTestCase(const int VERTEX_SIZE) {
    Vertices vertex = malloc(sizeof(VertexType) * VERTEX_SIZE);
    for (char i = 0, vex = 'a'; i < VERTEX_SIZE; i++, vex++) {
        vertex[i] = vex;
    }
    return vertex;
}

void testAdjTableGraph() {
    printf("*****************************************************\n");
    printf("*                邻接表存储结构图测试例程              *\n");
    printf("*****************************************************\n");

    const int VERTEX_SIZE = 5;
    Vertices vertices = newVexTestCase(VERTEX_SIZE);

    // [a, b, c, d, e]
    Edges edges = newEdgeTestCase(VERTEX_SIZE);

    AdjTableGraph tableGraph = newAdjTableGraph(vertices, edges, VERTEX_SIZE, VERTEX_SIZE, DN);
    showAdjTableGraph_ATG(tableGraph);

    edges = malloc(sizeof(EdgeType) * 2);
    edges[0].vi = 1;
    edges[0].vj = 3;
    edges[0].weight = 60;

    edges[1].vi = 3;
    edges[1].vj = 4;
    edges[1].weight = 90;
    newEdgeForGraphVertex_ATG(tableGraph, reAllocEdge(VERTEX_SIZE, edges), 2);
    showAdjTableGraph_ATG(tableGraph);

    printf("深度优先遍历的结果：\n");
    dfsTraversal_ATG(tableGraph);

    printf("广度优先遍历的结果：\n");
    bfsTraversal_ATG(tableGraph);

    printf("拓扑排序：");
    bool rs = topologicalSort_ATG(tableGraph);
    printf("是否存在回路：%s\n", rs ? "否" : "是");

    printf("计算图的关键路径：\n");
    criticalPath_ATG(tableGraph);

    puts("\n");
}

void testCrossListGraph(void) {
    printf("*****************************************************\n");
    printf("*               十字链表存储结构图测试例程             *\n");
    printf("*****************************************************\n");
    const int VERTEX_SIZE = 5;
    Vertices vertices = newVexTestCase(VERTEX_SIZE);

    // [a, b, c, d, e]
    Edges edges = newEdgeTestCase(VERTEX_SIZE);

    ClgGraph clgGraph = createClgGraph(vertices, edges, VERTEX_SIZE, VERTEX_SIZE, DG);
    showClgGraph_CLG(clgGraph);

    edges = malloc(sizeof(EdgeType) * 2);
    edges[0].vi = 1;
    edges[0].vj = 3;
    edges[0].weight = 60;

    edges[1].vi = 3;
    edges[1].vj = 2;
    edges[1].weight = 90;
    newEdgeForGraphVertex_CLG(clgGraph, reAllocEdge(VERTEX_SIZE, edges), 2);
    showClgGraph_CLG(clgGraph);

    printf("深度优先遍历的结果：\n");
    dfsTraversal_CLG(clgGraph);

    printf("广度优先遍历的结果：\n");
    bfsTraversal_CLG(clgGraph);

    puts("\n");
}

void testAdjMultipleTableGraph(void) {
    printf("*****************************************************\n");
    printf("*              多重邻接表存储结构图测试例程             *\n");
    printf("*****************************************************\n");
    const int VERTEX_SIZE = 5;
    Vertices vertices = newVexTestCase(VERTEX_SIZE);

    // [a, b, c, d, e]
    Edges edges = newEdgeTestCase(VERTEX_SIZE);
    AdjMultipleTableGraph tableGraph = newAdjMultipleTableGraph(vertices, edges, VERTEX_SIZE, VERTEX_SIZE, UDG);
    showAdjMultipleTableGraph_AMTG(tableGraph);

    edges = malloc(sizeof(EdgeType) * 2);
    edges[0].vi = 1;
    edges[0].vj = 3;
    edges[0].weight = 60;

    edges[1].vi = 3;
    edges[1].vj = 2;
    edges[1].weight = 90;
    newEdgeForGraphVertex_AMTG(tableGraph, reAllocEdge(VERTEX_SIZE, edges), 2);
    showAdjMultipleTableGraph_AMTG(tableGraph);

    printf("深度优先遍历的结果：\n");
    dfsTraversal_AMTG(tableGraph);

    printf("广度优先遍历的结果：\n");
    bfsTraversal_AMTG(tableGraph);

    puts("\n");
}
