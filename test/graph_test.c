//
// Created by determination on 2018/10/12.
//

#include "graph_test.h"

void testAdjMatrixGrpah() {
    printf("*****************************************************\n");
    printf("*              邻接矩阵存储结构图测试例程              *\n");
    printf("*****************************************************\n");

    const int VERTEX_SIZE = 5;
    Vertex_AMG vertex = malloc(sizeof(VertexType) * VERTEX_SIZE);
    for (char i = 0, vex = 'a'; i < VERTEX_SIZE; i++, vex++) {
        vertex[i] = vex;
    }

    // [a, b, c, d, e]
    Edge_AMG edge = malloc(sizeof(EdgeType_AMG) * VERTEX_SIZE);
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

    MatrixGraph matrix = createAdjacencyMatrix(vertex, edge, VERTEX_SIZE, VERTEX_SIZE, DN);
    showMatrixGraph(matrix);

    edge = realloc(edge, sizeof(EdgeType_AMG) * (VERTEX_SIZE + 2));
    edge[5].vi = 1;
    edge[5].vj = 3;
    edge[5].weight = 60;

    edge[6].vi = 3;
    edge[6].vj = 2;
    edge[6].weight = 90;

    newEdgeForGraphVertex(matrix, edge, VERTEX_SIZE + 2);
    showMatrixGraph(matrix);
    puts("\n");
}
