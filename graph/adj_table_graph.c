//
// Created by determination on 2018/10/18.
//

#include "adj_table_graph.h"
#include "linked_queue.h"


/**
 * 创建有向图
 */
AdjTableGraph createDG_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge);

/**
 * 创建有向网
 */
AdjTableGraph createDN_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge);

/**
 * 创建无向图
 */
AdjTableGraph createUDG_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge);

/**
 * 创建无向网
 */
AdjTableGraph createUDN_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge);

/**
 * 新建一个只有顶点的图
 */
AdjTableGraph newEmptyGraph_ATG(const VertexType *vertices, int countOfVertex);

/**
 * 为有向网或者有向图建立顶点与顶点之间的边
 *
 * @param edges 边的集合
 * @param countOfEdge 边的个数
 * @param tableGraph 邻接表结构存储的图
 * @param weightFlag 是否包含有权值的标示
 */
void newEdgeRelationForD_ATG(const EdgeType *edges, int countOfEdge, AdjTableGraph tableGraph, bool weightFlag);

/**
 *
 * @return 新建的边节点
 */
EdgeNode_ATG newEdgeNode_ATG();

/**
 * 向无向图或无向网中设置边节点
 *
 * @param vertex 顶点节点
 * @param edge 边节点
 * @param tableGraph
 */
void setupEdgeForUD_ATG(VertexNode_ATG vertex, EdgeNode_ATG edge, AdjTableGraph tableGraph);

void setupEdge_ATG(VertexNode_ATG vertex, int adj, int weight, AdjTableGraph tableGraph);

/**
 * 为无向网或者无向图建立顶点与顶点之间的边
 *
 * @param edges 边的集合
 * @param countOfEdge 边的个数
 * @param tableGraph 邻接表结构存储的图
 * @param weightFlag 是否包含有权值的标示
 */
void newEdgeRelationForUD_ATG(const EdgeType *edges, int countOfEdge, AdjTableGraph tableGraph, bool weightFlag);

void dfs_ATG(AdjTableGraph tableGraph, bool *visited, int index);

AdjTableGraph newAdjTableGraph(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind) {
    switch (kind) {
        case DG:
            return createDG_ATG(vertices, edges, countOfVertex, countOfEdge);

        case DN:
            return createDN_ATG(vertices, edges, countOfVertex, countOfEdge);

        case UDG:
            return createUDG_ATG(vertices, edges, countOfVertex, countOfEdge);

        case UDN:
            return createUDN_ATG(vertices, edges, countOfVertex, countOfEdge);
    }
    return NULL;
}

AdjTableGraph createDG_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge) {

    AdjTableGraph tableGraph = newEmptyGraph_ATG(vertices, countOfVertex);
    tableGraph->kind = DG;

    newEdgeRelationForD_ATG(edges, countOfEdge, tableGraph, false);

    return tableGraph;
}

void newEdgeRelationForD_ATG(const EdgeType *edges, int countOfEdge, AdjTableGraph tableGraph, bool weightFlag) {
    for (int i = 0; i < countOfEdge; i++) {
        VertexNode_ATG vi = get_AL(tableGraph->adjTable, edges[i].vi + 1);

        EdgeNode_ATG edge = malloc(sizeof(struct EdgeNode_ATG));
        edge->adjvex = edges[i].vj;

        // 设置边的权重值
        edge->weight = UNFLAG_WEIGHT_GRAPH;
        if (weightFlag) edge->weight = edges[i].weight;

        edge->next = NULL;

        EdgeNode_ATG temp = vi->firstEdge;
        if (temp == NULL) {
            vi->firstEdge = edge;
            tableGraph->countOfEdge++;
            continue;
        }

        bool isConflict = false;
        EdgeNode_ATG prev = NULL;
        while (temp->next) {
            // 检查顶点是否已经存在
            if (temp->adjvex == edge->adjvex) {
                isConflict = true;
                break;
            }

            // 用于对节点进行排序
            if (temp->adjvex > edge->adjvex) {
                edge->next = temp;
                if (temp == vi->firstEdge)
                    vi->firstEdge = edge;
                else if (prev)
                    prev->next = edge;
                tableGraph->countOfEdge++;
                isConflict = true;
                break;
            }

            prev = temp;
            temp = temp->next;
        }

        if (!isConflict) {
            // 用户对节点进行排序
            if (temp->adjvex > edge->adjvex) {
                if (temp == vi->firstEdge)
                    vi->firstEdge = edge;
                else if (prev)
                    prev->next = edge;
                edge->next = temp;
            } else
                temp->next = edge;

            tableGraph->countOfEdge++;
        }
    }
}

AdjTableGraph newEmptyGraph_ATG(const VertexType *vertices, int countOfVertex) {
    AdjTableGraph tableGraph = malloc(sizeof(struct ATG));
    assert(tableGraph);
    tableGraph->countOfVertex = countOfVertex;
    tableGraph->countOfEdge = 0;
    tableGraph->adjTable = newArrayList();

    for (int i = 0; i < countOfVertex; i++) {
        VertexNode_ATG vertexNode = malloc(sizeof(struct VertexNode_ATG));
        vertexNode->vertex = vertices[i];
        vertexNode->firstEdge = NULL;
        add_AL(tableGraph->adjTable, vertexNode);
    }

    return tableGraph;
}

AdjTableGraph createDN_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge) {
    AdjTableGraph tableGraph = newEmptyGraph_ATG(vertices, countOfVertex);
    tableGraph->kind = DN;

    newEdgeRelationForD_ATG(edges, countOfEdge, tableGraph, true);

    return tableGraph;
}

AdjTableGraph createUDG_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge) {
    AdjTableGraph tableGraph = newEmptyGraph_ATG(vertices, countOfVertex);
    tableGraph->kind = UDG;

    newEdgeRelationForUD_ATG(edges, countOfEdge, tableGraph, false);
    return tableGraph;
}

void newEdgeRelationForUD_ATG(const EdgeType *edges, int countOfEdge, AdjTableGraph tableGraph, bool weightFlag) {
    for (int i = 0; i < countOfEdge; i++) {
        VertexNode_ATG vi = get_AL(tableGraph->adjTable, edges[i].vi + 1);
        VertexNode_ATG vj = get_AL(tableGraph->adjTable, edges[i].vj + 1);

        // 判定是否是无向图或者无向网的权值
        int weight = UNFLAG_WEIGHT_GRAPH;
        if (weightFlag) weight = edges[i].weight;

        setupEdge_ATG(vi, edges[i].vj, weight, tableGraph);
        setupEdge_ATG(vj, edges[i].vi, weight, tableGraph);
    }
}

void setupEdge_ATG(VertexNode_ATG vertex, int adj, int weight, AdjTableGraph tableGraph) {
    EdgeNode_ATG edge = newEdgeNode_ATG();
    edge->adjvex = adj;
    if (weight != UNFLAG_WEIGHT_GRAPH) edge->weight = weight;
    setupEdgeForUD_ATG(vertex, edge, tableGraph);
}

void setupEdgeForUD_ATG(VertexNode_ATG vertex, EdgeNode_ATG edge, AdjTableGraph tableGraph) {
    EdgeNode_ATG temp = vertex->firstEdge;
    if (temp == NULL) {
        vertex->firstEdge = edge;
        tableGraph->countOfEdge++;
    } else {
        bool isConflict = false;
        EdgeNode_ATG prev = NULL;
        while (temp->next) {
            // 检查顶点是否已经存在
            if (temp->adjvex == edge->adjvex) {
                isConflict = true;
                break;
            }

            // 用于对节点进行排序
            if (temp->adjvex > edge->adjvex) {
                edge->next = temp;
                if (temp == vertex->firstEdge)
                    vertex->firstEdge = edge;
                else if (prev)
                    prev->next = edge;
                tableGraph->countOfEdge++;
                isConflict = true;
                break;
            }

            prev = temp;
            temp = temp->next;
        }

        // 顶点不存在才进行赋值
        if (!isConflict) {
            // 用户对节点进行排序
            if (temp->adjvex > edge->adjvex) {
                if (temp == vertex->firstEdge)
                    vertex->firstEdge = edge;
                else if (prev)
                    prev->next = edge;
                edge->next = temp;
            } else
                temp->next = edge;
            tableGraph->countOfEdge++;
        }
    }
}

EdgeNode_ATG newEdgeNode_ATG() {
    EdgeNode_ATG edgeForVi = malloc(sizeof(struct EdgeNode_ATG));
    assert(edgeForVi);
    edgeForVi->adjvex = UNFLAG_WEIGHT_GRAPH;
    edgeForVi->weight = UNFLAG_WEIGHT_GRAPH;
    edgeForVi->next = NULL;
    return edgeForVi;
}


AdjTableGraph createUDN_ATG(Vertices vertices, Edges edges, int countOfVertex, int countOfEdge) {
    AdjTableGraph tableGraph = newEmptyGraph_ATG(vertices, countOfVertex);
    tableGraph->kind = UDN;

    newEdgeRelationForUD_ATG(edges, countOfEdge, tableGraph, true);
    return tableGraph;
}

void newEdgeForGraphVertex_ATG(AdjTableGraph tableGraph, Edges edges, int countOfEdge) {
    if (countOfEdge <= 0) return;

    switch (tableGraph->kind) {
        case DG:
            newEdgeRelationForD_ATG(edges, countOfEdge, tableGraph, false);
            break;
        case DN:
            newEdgeRelationForD_ATG(edges, countOfEdge, tableGraph, true);
            break;
        case UDG:
            newEdgeRelationForUD_ATG(edges, countOfEdge, tableGraph, false);
            break;
        case UDN:
            newEdgeRelationForUD_ATG(edges, countOfEdge, tableGraph, true);
            break;
    }
}


void showAdjTableGraph_ATG(AdjTableGraph tableGraph) {
    if (!tableGraph || tableGraph->countOfVertex <= 0 || !tableGraph->adjTable) return;

    ArrayListPtr list = tableGraph->adjTable;

    fprintf(stdout, "索引\t顶点\t\t邻接的边(顶点索引, 边的权值-->下一个邻接的边)\n");

    for (int i = 0; i < tableGraph->countOfVertex; i++) {
        VertexNode_ATG vertexNode = get_AL(list, i + 1);

        fprintf(stdout, " %d\t %c\t\t", i, vertexNode->vertex);

        EdgeNode_ATG temp = vertexNode->firstEdge;
        while (temp) {
            fprintf(stdout, "%d", temp->adjvex);
            if (temp->weight != UNFLAG_WEIGHT_GRAPH)
                fprintf(stdout, ", %d", temp->weight);

            temp = temp->next;
            if (temp != NULL)
                fprintf(stdout, "\t-->\t\t");
        }

        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n\n");
}

void dfsTraversal_ATG(AdjTableGraph tableGraph) {
    assert(tableGraph);
    bool visited[tableGraph->countOfVertex];
    for (int i = 0; i < tableGraph->countOfVertex; i++)
        visited[i] = false;

    for (int i = 0; i < tableGraph->countOfVertex; i++) {
        if (visited[i]) continue;
        dfs_ATG(tableGraph, visited, i);
    }

    fprintf(stdout, "\n\n");
}

void dfs_ATG(AdjTableGraph tableGraph, bool *visited, int index) {
    visited[index] = true;
    VertexNode_ATG vertexNode = get_AL(tableGraph->adjTable, index + 1);
    printf("%c\t", vertexNode->vertex);

    EdgeNode_ATG temp = vertexNode->firstEdge;
    while (temp) {
        if (!visited[temp->adjvex])
            dfs_ATG(tableGraph, visited, temp->adjvex);
        temp = temp->next;
    }
}

void bfsTraversal_ATG(AdjTableGraph tableGraph) {
    LinkedQueue queue = newLinkedQueue();
    bool visited[tableGraph->countOfVertex];
    for (int i = 0; i < tableGraph->countOfVertex; i++)
        visited[i] = false;

    ArrayListPtr adjTable = tableGraph->adjTable;
    for (int i = 0; i < tableGraph->countOfVertex; i++) {
        if (visited[i]) continue;

        visited[i] = true;
        VertexNode_ATG vertexNode = get_AL(adjTable, i + 1);
        printf("%c\t", vertexNode->vertex);
        enqueue_LQ(queue, vertexNode);

        while (!isEmpty_LQ(queue)) {
            VertexNode_ATG vertexNodeTemp = frontAndDequeue_LQ(queue);

            EdgeNode_ATG temp = vertexNodeTemp->firstEdge;
            while (temp) {
                if (visited[temp->adjvex]) {
                    temp = temp->next;
                    continue;
                }

                VertexNode_ATG nextVertex = get_AL(adjTable, temp->adjvex + 1);
                if (!nextVertex) continue;
                printf("%c\t", nextVertex->vertex);
                visited[temp->adjvex] = true;

                enqueue_LQ(queue, nextVertex);
                temp = temp->next;
            }

        }
    }

    fprintf(stdout, "\n\n");
}