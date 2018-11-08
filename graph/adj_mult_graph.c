//
// Created by determination on 2018/11/8.
//

#include "adj_mult_graph.h"

/**
 * 创建多重邻接表存储结构的图
 *
 * @param vertices 顶点的集合
 * @param edges 边的集合
 * @param countOfVertex 顶点的数量
 * @param countOfEdge 边的数量
 * @param weightFlag 是否设置权值的标志
 * @return 创建完成的图
 */
AdjMultipleTableGraph createGraph_AMTG(
        Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, bool weightFlag);

/**
 * 新建一个空的图
 *
 * @return 新的图
 */
AdjMultipleTableGraph newEmptyGraph_ATMG(void);

/**
 * 新建一个图的顶点节点
 *
 * @param vertexData 顶点的数据
 * @return 创建完成的图的顶点节点
 */
VertexNode_AMTG newVertexNode_AMTG(VertexType vertexData);

/**
 * 新建一个顶点之间的边
 *
 * @param currEdge 构造新的边节点结构体
 * @param weightFlag 是否设置权值的标志
 * @return 创建完成的边节点
 */
EdgeNode_AMTG newEdgeNode_ATMG(EdgeType *currEdge, bool weightFlag);

/**
 * 为图中建立新的边的节点
 *
 * @param tableGraph 多重邻接表存储结构的图
 * @param edges 新的边的集合
 * @param countOfEdge 边的数量
 * @param weightFlag 是否设置权值的标志
 */
void createNewEdgeForVertex_ATMG(AdjMultipleTableGraph tableGraph, Edges edges, int countOfEdge, bool weightFlag);

/**
 * 判断边是否存在
 *
 * @param currEdge 新的边的元素
 * @param itTemp 已存在图中的边
 * @return 存在返回true，否则返回false
 */
bool theEdgeIsExist(const EdgeType *currEdge, EdgeNode_AMTG itTemp);

/**
 * 判断下一个节点（ilink或jlink）是否为空
 *
 * @param currEdge 需要新建边的节点的元素
 * @param itTemp 已存在图中的边
 * @return 不为空返回true，否则返回false
 */
bool isNotNullOfNext(const EdgeType *currEdge, EdgeNode_AMTG itTemp);

/**
 * 将新建的边放进正确的位置
 *
 * @param currEdge 新建边的数据
 * @param edgeTemp 新建的边的节点元素
 * @param itTemp 图中已存在的边的节点元素
 */
void putEdgeIntoCorrectPos_AMTG(const EdgeType *currEdge, EdgeNode_AMTG edgeTemp, EdgeNode_AMTG itTemp);

AdjMultipleTableGraph newAdjMultipleTableGraph(
        Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, GraphKind kind) {
    assert(vertices);
    if (countOfVertex <= 0) return NULL;

    switch (kind) {
        case UDG:
            return createGraph_AMTG(vertices, edges, countOfVertex, countOfEdge, false);
        case UDN:
            return createGraph_AMTG(vertices, edges, countOfVertex, countOfEdge, true);
        default:
            return NULL;
    }
}

AdjMultipleTableGraph createGraph_AMTG(
        Vertices vertices, Edges edges, int countOfVertex, int countOfEdge, bool weightFlag) {
    AdjMultipleTableGraph tableGraph = newEmptyGraph_ATMG();
    tableGraph->kind = weightFlag ? UDN : UDG;
    tableGraph->vertexSize = countOfVertex;
    tableGraph->edgeSize = countOfEdge;

    for (int i = 0; i < countOfVertex; i++) {
        VertexNode_AMTG vertexTemp = newVertexNode_AMTG(vertices[i]);
        add_AL(tableGraph->table, vertexTemp);
    }

    createNewEdgeForVertex_ATMG(tableGraph, edges, countOfEdge, weightFlag);

    return tableGraph;
}

void createNewEdgeForVertex_ATMG(AdjMultipleTableGraph tableGraph, Edges edges, int countOfEdge, bool weightFlag) {
    for (int i = 0; i < countOfEdge; i++) {
        EdgeType currEdge = edges[i];
        // 存放出度的边
        VertexNode_AMTG firstVertexTemp = get_AL(tableGraph->table, currEdge.vi + 1);
        if (!firstVertexTemp) {
            fprintf(stdout, "指定索引：%d的顶点不存在\n", currEdge.vi);
            exit(EXIT_FAILURE);
        }
        EdgeNode_AMTG edgeTemp = newEdgeNode_ATMG(&currEdge, weightFlag);
        EdgeNode_AMTG itTemp = firstVertexTemp->firstIn;
        if (!itTemp)
            firstVertexTemp->firstIn = edgeTemp;
        else {
            putEdgeIntoCorrectPos_AMTG(&currEdge, edgeTemp, itTemp);
        }

        // 存放入度的边
        VertexNode_AMTG secondVertexTemp = get_AL(tableGraph->table, currEdge.vj + 1);
        if (!secondVertexTemp) {
            fprintf(stdout, "指定索引：%d的顶点不存在\n", currEdge.vj);
            exit(EXIT_FAILURE);
        }
        itTemp = secondVertexTemp->firstIn;
        if (!itTemp)
            secondVertexTemp->firstIn = edgeTemp;
        else {
            putEdgeIntoCorrectPos_AMTG(&currEdge, edgeTemp, itTemp);
        }
    }
}

void putEdgeIntoCorrectPos_AMTG(const EdgeType *currEdge, EdgeNode_AMTG edgeTemp, EdgeNode_AMTG itTemp) {
    bool isConflict = false;
    while (isNotNullOfNext(currEdge, itTemp)) {
        if (theEdgeIsExist(currEdge, itTemp)) {
            isConflict = true;
            break;
        }

        if ((*currEdge).vi == itTemp->ivex || (*currEdge).vj == itTemp->ivex)
            itTemp = itTemp->ilink;
        else if ((*currEdge).vi == itTemp->jvex || (*currEdge).vj == itTemp->jvex)
            itTemp = itTemp->jlink;
    }

    if (isConflict) return;

    if ((*currEdge).vi == itTemp->ivex || (*currEdge).vj == itTemp->ivex)
        itTemp->ilink = edgeTemp;
    else if ((*currEdge).vi == itTemp->jvex || (*currEdge).vj == itTemp->jvex)
        itTemp->jlink = edgeTemp;
}

bool isNotNullOfNext(const EdgeType *currEdge, EdgeNode_AMTG itTemp) {
    return (itTemp->ilink && ((*currEdge).vi == itTemp->ivex || (*currEdge).vj == itTemp->ivex)) ||
           (itTemp->jlink && ((*currEdge).vi == itTemp->jvex || (*currEdge).vj == itTemp->jvex));
}

bool theEdgeIsExist(const EdgeType *currEdge, EdgeNode_AMTG itTemp) {
    return ((*currEdge).vi == itTemp->ivex && (*currEdge).vj == itTemp->jvex) ||
           ((*currEdge).vi == itTemp->jvex && (*currEdge).vj == itTemp->ivex);
}

EdgeNode_AMTG newEdgeNode_ATMG(EdgeType *currEdge, bool weightFlag) {
    EdgeNode_AMTG edgeTemp = malloc(sizeof(struct EdgeNode_AMTG));
    edgeTemp->ilink = NULL;
    edgeTemp->jlink = NULL;
    edgeTemp->weight = weightFlag ? (*currEdge).weight : UNFLAG_WEIGHT_GRAPH;
    edgeTemp->mark = false;
    edgeTemp->ivex = (*currEdge).vi;
    edgeTemp->jvex = (*currEdge).vj;
    return edgeTemp;
}

VertexNode_AMTG newVertexNode_AMTG(VertexType vertexData) {
    VertexNode_AMTG vertexNode = malloc(sizeof(struct VertexNode_AMTG));
    assert(vertexNode);

    vertexNode->data = vertexData;
    vertexNode->firstIn = NULL;
    return vertexNode;
}

AdjMultipleTableGraph newEmptyGraph_ATMG() {
    AdjMultipleTableGraph tableGraph = malloc(sizeof(struct AMTG));
    assert(tableGraph);
    tableGraph->table = newArrayList();
    tableGraph->vertexSize = 0;
    tableGraph->edgeSize = 0;
    return tableGraph;
}

void newEdgeForGraphVertex_AMTG(AdjMultipleTableGraph tableGraph, Edges edges, int countOfEdge) {
    assert(tableGraph);
    if (countOfEdge <= 0) return;
    createNewEdgeForVertex_ATMG(tableGraph, edges, countOfEdge, tableGraph->kind == UDN);
}

void showAdjMultipleTableGraph_AMTG(AdjMultipleTableGraph tableGraph) {
    if (!tableGraph) return;
    ArrayListPtr table = tableGraph->table;

    fprintf(stdout, "索引\t顶点\t\t出度(顶点, 顶点, 边的权值-->下一个边的信息)\n");
    for (int i = 0; i < tableGraph->vertexSize; i++) {
        VertexNode_AMTG vertexNode = get_AL(table, i + 1);

        fprintf(stdout, " %d\t %c\t\t", i, vertexNode->data);

        EdgeNode_AMTG temp = vertexNode->firstIn;
        while (temp) {
            fprintf(stdout, "%d", temp->ivex);
            fprintf(stdout, ", %d", temp->jvex);
            if (tableGraph->kind == UDN)
                fprintf(stdout, ", %d", temp->weight);

            temp->mark = true;
            if (temp->ivex == i)
                temp = temp->ilink;
            else if (temp->jvex == i)
                temp = temp->jlink;

            if (temp != NULL)
                fprintf(stdout, "\t-->\t\t");
        }

        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
