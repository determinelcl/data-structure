//
// Created by determination on 2018/10/26.
//

#include "cross_list_graph.h"
#include "linked_queue.h"


/**
 * 新建一个图
 *
 * @param vertices 顶点的集合
 * @param edges 边的集合
 * @param countOfVertex 顶点的个数
 * @param countOfEdge 边的个数
 * @param weightFlag 是否设置权值的标志，用于区别创建的是有向图还是有向网
 * @return 十字链表存储结构的图
 */
ClgGraph createGraph_CLG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, bool weightFlag);

/**
 * 新建一个空的ClgGraph
 * @return 空的ClgGraph
 */
ClgGraph newEmptyCLG(void);

/**
 * 新建一个顶点的节点
 *
 * @param data 顶点存放的数据
 * @return 新的顶点的节点
 */
VertexNode_CLG newVertexNode_CLG(VertexType data);

/**
 * 新建一个边的节点
 *
 * @param edge 边的结构体
 * @param weightFlag 是否设置权值的标志
 * @return 新的边的节点
 */
EdgeNode_CLG newEdgeNode_CLG(EdgeType *edge, bool weightFlag);

/**
 * 为十字链表存储结构的图建立边
 *
 * @param clgGraph 图
 * @param edges 边的集合
 * @param countOfEdge 边的个数
 * @param weightFlag 设否设置权值的标志
 * @return 是否创建成功
 */
bool newEdges_CLG(ClgGraph clgGraph, Edges edges, int countOfEdge, bool weightFlag);

void dfs_CLG(ClgGraph clgGraph, bool *visited, int index);

ClgGraph createClgGraph(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind) {
    ClgGraph clgGraph = NULL;
    switch (kind) {
        case DG:
            clgGraph = createGraph_CLG(vertices, edges, countOfVertex, countOfEdge, false);
            if (clgGraph)
                clgGraph->kind = DG;
            return clgGraph;
        case DN:
            clgGraph = createGraph_CLG(vertices, edges, countOfVertex, countOfEdge, true);
            if (clgGraph)
                clgGraph->kind = DN;
            return clgGraph;
        default:
            return NULL;
    }

}

ClgGraph newEmptyCLG() {
    ClgGraph clgGraph = malloc(sizeof(struct CLG));

    clgGraph->edgeSize = 0;
    clgGraph->vertexSize = 0;
    clgGraph->cljTable = newArrayList();
    return clgGraph;
}

ClgGraph createGraph_CLG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, bool weightFlag) {
    if (countOfVertex <= 0) return NULL;

    ClgGraph clgGraph = newEmptyCLG();

    clgGraph->vertexSize = countOfVertex;

    // 存放顶点到集合之中
    for (int i = 0; i < countOfVertex; i++) {
        add_AL(clgGraph->cljTable, newVertexNode_CLG(vertices[i]));
    }

    // 设置边
    return newEdges_CLG(clgGraph, edges, countOfEdge, weightFlag) ? clgGraph : NULL;
}

bool newEdges_CLG(ClgGraph clgGraph, Edges edges, int countOfEdge, bool weightFlag) {
    for (int i = 0; i < countOfEdge; i++) {
        EdgeNode_CLG edgeNodeTmp = newEdgeNode_CLG(&edges[i], weightFlag);

        // 存放出度的边
        VertexNode_CLG tailVertexNodeTmp = get_AL(clgGraph->cljTable, edgeNodeTmp->tailVex + 1);
        if (!tailVertexNodeTmp) {
            printf("创建边失败，索引为：%d的节点未找到！", edgeNodeTmp->tailVex);
            return false;
        }
        EdgeNode_CLG edgeTmp = tailVertexNodeTmp->firstOut;
        if (!edgeTmp) {
            tailVertexNodeTmp->firstOut = edgeNodeTmp;
            clgGraph->edgeSize++;
        } else {
            bool isConflict = false;
            EdgeNode_CLG prev = NULL;
            while (edgeTmp->tLink) {
                if (edgeTmp->tailVex == edgeNodeTmp->tailVex && edgeTmp->headVex == edgeNodeTmp->headVex) {
                    isConflict = true;
                    break;
                }

                // 排序邻接的边
                if (edgeTmp->headVex > edgeNodeTmp->headVex) {
                    if (edgeTmp == tailVertexNodeTmp->firstOut)
                        tailVertexNodeTmp->firstOut = edgeNodeTmp;
                    else if (prev)
                        prev->tLink = edgeNodeTmp;

                    edgeNodeTmp->tLink = edgeTmp;
                    isConflict = true;
                    clgGraph->edgeSize++;
                    break;
                }

                prev = edgeTmp;
                edgeTmp = edgeTmp->tLink;
            }

            if (isConflict) continue;

            // 排序邻接的边
            if (edgeTmp->headVex > edgeNodeTmp->headVex) {

                if (edgeTmp == tailVertexNodeTmp->firstOut)
                    tailVertexNodeTmp->firstOut = edgeNodeTmp;
                else if (prev)
                    prev->tLink = edgeNodeTmp;

                edgeNodeTmp->tLink = edgeTmp;
            } else
                edgeTmp->tLink = edgeNodeTmp;
            clgGraph->edgeSize++;
        }


        // 存放入度的边
        VertexNode_CLG headVertexNodeTmp = get_AL(clgGraph->cljTable, edgeNodeTmp->headVex + 1);
        if (!headVertexNodeTmp) {
            printf("创建边失败，索引为：%d的节点未找到！", edgeNodeTmp->tailVex);
            return false;
        }
        edgeTmp = headVertexNodeTmp->firstIn;
        if (!edgeTmp) headVertexNodeTmp->firstIn = edgeNodeTmp;
        else {
            bool isConflict = false;
            EdgeNode_CLG prev = NULL;
            while (edgeTmp->hLink) {
                if (edgeTmp->tailVex == edgeNodeTmp->tailVex && edgeTmp->headVex == edgeNodeTmp->headVex) {
                    isConflict = true;
                    break;
                }

                // 排序邻接的边
                if (edgeTmp->tailVex > edgeNodeTmp->tailVex) {
                    if (edgeTmp == tailVertexNodeTmp->firstIn)
                        tailVertexNodeTmp->firstIn = edgeNodeTmp;
                    else if (prev)
                        prev->hLink = edgeNodeTmp;

                    edgeNodeTmp->hLink = edgeTmp;
                    isConflict = true;
                    break;
                }

                prev = edgeTmp;
                edgeTmp = edgeTmp->hLink;
            }

            if (isConflict) continue;
            // 排序邻接的边
            if (edgeTmp->tailVex > edgeNodeTmp->tailVex) {

                if (edgeTmp == tailVertexNodeTmp->firstIn)
                    tailVertexNodeTmp->firstIn = edgeNodeTmp;
                else if (prev)
                    prev->hLink = edgeNodeTmp;

                edgeNodeTmp->hLink = edgeTmp;
            } else
                edgeTmp->hLink = edgeNodeTmp;
        }

    }
    return true;
}

EdgeNode_CLG newEdgeNode_CLG(EdgeType *edge, bool weightFlag) {
    EdgeNode_CLG edgeNodeTmp = malloc(sizeof(struct EdgeNode_CLG));
    edgeNodeTmp->tailVex = edge->vi;
    edgeNodeTmp->headVex = edge->vj;

    edgeNodeTmp->weight = weightFlag ? edge->weight : UNFLAG_WEIGHT_GRAPH;
    edgeNodeTmp->hLink = NULL;
    edgeNodeTmp->tLink = NULL;
    return edgeNodeTmp;
}

VertexNode_CLG newVertexNode_CLG(VertexType data) {
    VertexNode_CLG vertexNodeTmp = malloc(sizeof(struct VertexNode_CLG));
    vertexNodeTmp->data = data;
    vertexNodeTmp->firstIn = NULL;
    vertexNodeTmp->firstOut = NULL;
    return vertexNodeTmp;
}


void newEdgeForGraphVertex_CLG(ClgGraph clgGraph, Edges edges, int countOfEdge) {
    if (countOfEdge <= 0) return;
    assert(clgGraph);

    bool weightFlag = true;
    if (clgGraph->kind == DG)
        weightFlag = false;

    newEdges_CLG(clgGraph, edges, countOfEdge, weightFlag);
}


void showClgGraph_CLG(ClgGraph clgGraph) {
    if (!clgGraph || clgGraph->vertexSize <= 0) return;
    ArrayListPtr cljTable = clgGraph->cljTable;

    // 输出出度信息
    fprintf(stdout, "出度信息：\n");
    fprintf(stdout, "索引\t顶点\t\t出度(弧尾索引, 弧头索引, 边的权值-->下一个出度信息)\n");
    for (int i = 0; i < clgGraph->vertexSize; i++) {
        VertexNode_CLG vertexNode = get_AL(cljTable, i + 1);

        fprintf(stdout, " %d\t %c\t\t", i, vertexNode->data);

        EdgeNode_CLG temp = vertexNode->firstOut;
        while (temp) {
            fprintf(stdout, "%d", temp->tailVex);
            fprintf(stdout, ", %d", temp->headVex);
            if (temp->weight != UNFLAG_WEIGHT_GRAPH)
                fprintf(stdout, ", %d", temp->weight);

            temp = temp->tLink;
            if (temp != NULL)
                fprintf(stdout, "\t-->\t\t");
        }

        fprintf(stdout, "\n");
    }

    // 输出入度信息
    fprintf(stdout, "\n入度信息：\n");
    fprintf(stdout, "索引\t顶点\t\t入度(弧尾索引, 弧头索引, 边的权值-->下一个入度信息)\n");
    for (int i = 0; i < clgGraph->vertexSize; i++) {
        VertexNode_CLG vertexNode = get_AL(cljTable, i + 1);

        fprintf(stdout, " %d\t %c\t\t", i, vertexNode->data);

        EdgeNode_CLG temp = vertexNode->firstIn;
        while (temp) {
            fprintf(stdout, "%d", temp->tailVex);
            fprintf(stdout, ", %d", temp->headVex);
            if (temp->weight != UNFLAG_WEIGHT_GRAPH)
                fprintf(stdout, ", %d", temp->weight);

            temp = temp->hLink;
            if (temp != NULL)
                fprintf(stdout, "\t-->\t\t");
        }

        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void dfsTraversal_CLG(ClgGraph clgGraph) {
    assert(clgGraph);
    bool visited[clgGraph->vertexSize];

    for (int i = 0; i < clgGraph->vertexSize; ++i)
        visited[i] = false;

    for (int i = 0; i < clgGraph->vertexSize; ++i) {
        if (visited[i]) continue;
        dfs_CLG(clgGraph, visited, i);
    }
    fprintf(stdout, "\n\n");
}

void dfs_CLG(ClgGraph clgGraph, bool *visited, int index) {
    visited[index] = true;
    VertexNode_CLG vertexNode = get_AL(clgGraph->cljTable, index + 1);
    printf("%c\t", vertexNode->data);

    EdgeNode_CLG temp = vertexNode->firstOut;
    while (temp) {
        if (!visited[temp->headVex])
            dfs_CLG(clgGraph, visited, temp->headVex);
        temp = temp->tLink;
    }
}

void bfsTraversal_CLG(ClgGraph clgGraph) {
    assert(clgGraph);
    bool visited[clgGraph->vertexSize];

    for (int i = 0; i < clgGraph->vertexSize; i++)
        visited[i] = false;

    ArrayListPtr cljTable = clgGraph->cljTable;
    LinkedQueue queue = newLinkedQueue();

    for (int i = 0; i < clgGraph->vertexSize; i++) {
        if (visited[i]) continue;
        VertexNode_CLG vertexNode = get_AL(cljTable, i + 1);
        printf("%c\t", vertexNode->data);
        visited[i] = true;

        enqueue_LQ(queue, vertexNode);
        while (!isEmpty_LQ(queue)) {
            VertexNode_CLG temp = frontAndDequeue_LQ(queue);

            EdgeNode_CLG edgeNode = temp->firstOut;
            while (edgeNode) {
                if (visited[edgeNode->headVex]) {
                    edgeNode = edgeNode->tLink;
                    continue;
                }

                VertexNode_CLG nextVertexNode = get_AL(cljTable, edgeNode->headVex + 1);
                if (!nextVertexNode) continue;

                printf("%c\t", nextVertexNode->data);
                visited[edgeNode->headVex] = true;

                enqueue_LQ(queue, nextVertexNode);
                edgeNode = edgeNode->tLink;
            }
        }
    }

    fprintf(stdout, "\n\n");
}