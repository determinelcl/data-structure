//
// Created by determination on 2018/11/8.
//

#include "adj_mult_graph.h"
#include "linked_queue.h"

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
bool theEdgeIsExist(EdgeNode_AMTG currEdge, EdgeNode_AMTG itTemp);

/**
 * 判断下一个节点（ilink或jlink）是否为空
 *
 * @param currEdge 需要新建边的节点的元素
 * @param itTemp 已存在图中的边
 * @return 不为空返回true，否则返回false
 */
bool isNotNullOfNext(EdgeNode_AMTG currEdge, EdgeNode_AMTG itTemp);

/**
 * 将新建的边放进正确的位置
 *
 * @param currEdge 新建边的数据
 * @param edgeTemp 新建的边的节点元素
 * @param itTemp 图中已存在的边的节点元素
 * @return 操作成功返回true，否则返回false
 */
bool putEdgeIntoCorrectPos_AMTG(EdgeNode_AMTG edgeTemp, EdgeNode_AMTG itTemp, VertexNode_AMTG firstIn);

void dfs_AMTG(AdjMultipleTableGraph tableGraph, bool *visited, int index);

/**
 * 判断需要设置ilink的值
 *
 * @param currEdge 需要设置的值的节点
 * @param itTemp 接收赋值的节点
 * @return 需要设置返回true，否则返回false
 */
bool isShouldBeSetILink(EdgeNode_AMTG currEdge, const struct EdgeNode_AMTG *itTemp);

/**
 * 判断需要设置ilink的值
 *
 * @param currEdge 需要设置的值的节点
 * @param itTemp 接收赋值的节点
 * @return 需要设置返回true，否则返回false
 */
bool isShouldBeSetJLink(EdgeNode_AMTG currEdge, const struct EdgeNode_AMTG *itTemp);

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
        if (!itTemp) {
            firstVertexTemp->firstIn = edgeTemp;
            tableGraph->edgeSize++;
        } else {
            bool rs = putEdgeIntoCorrectPos_AMTG(edgeTemp, itTemp, firstVertexTemp);
            if (rs) tableGraph->edgeSize++;
        }

        // 存放入度的边
        VertexNode_AMTG secondVertexTemp = get_AL(tableGraph->table, currEdge.vj + 1);
        if (!secondVertexTemp) {
            fprintf(stdout, "指定索引：%d的顶点不存在\n", currEdge.vj);
            exit(EXIT_FAILURE);
        }
        itTemp = secondVertexTemp->firstIn;
        if (!itTemp) {
            secondVertexTemp->firstIn = edgeTemp;
        } else
            putEdgeIntoCorrectPos_AMTG(edgeTemp, itTemp, secondVertexTemp);

    }
}

bool isShouldBeSetILink(EdgeNode_AMTG currEdge, const struct EdgeNode_AMTG *itTemp) {
    return currEdge->ivex == itTemp->ivex || currEdge->jvex == itTemp->ivex;
}

bool isShouldBeSetJLink(EdgeNode_AMTG currEdge, const struct EdgeNode_AMTG *itTemp) {
    return currEdge->ivex == itTemp->jvex || currEdge->jvex == itTemp->jvex;
}

bool isCurrGreaterThanIt(EdgeNode_AMTG currEdge, const struct EdgeNode_AMTG *itTemp) {
    return (itTemp->ivex + itTemp->jvex) > (currEdge->ivex + currEdge->jvex);
}

bool putEdgeIntoCorrectPos_AMTG(EdgeNode_AMTG edgeTemp, EdgeNode_AMTG itTemp, VertexNode_AMTG firstIn) {
    bool isConflict = false;
    EdgeNode_AMTG prev = NULL;
    while (isNotNullOfNext(edgeTemp, itTemp)) {
        if (theEdgeIsExist(edgeTemp, itTemp)) {
            isConflict = true;
            break;
        }

        // 排序邻接的边
        if (isCurrGreaterThanIt(edgeTemp, itTemp)) {
            if (itTemp == firstIn->firstIn)
                firstIn->firstIn = edgeTemp;
            else if (prev) {
                if (isShouldBeSetILink(edgeTemp, prev))
                    prev->ilink = edgeTemp;
                else if (isShouldBeSetJLink(edgeTemp, prev))
                    prev->jlink = edgeTemp;
            }

            if (isShouldBeSetILink(itTemp, edgeTemp))
                edgeTemp->ilink = itTemp;
            else if (isShouldBeSetJLink(itTemp, edgeTemp))
                edgeTemp->jlink = itTemp;

            isConflict = true;
            break;
        }

        prev = itTemp;
        if (isShouldBeSetILink(edgeTemp, itTemp))
            itTemp = itTemp->ilink;
        else if (isShouldBeSetJLink(edgeTemp, itTemp))
            itTemp = itTemp->jlink;
    }

    if (isConflict) return false;

    // 排序邻接的边
    if (isCurrGreaterThanIt(edgeTemp, itTemp)) {
        if (itTemp == firstIn->firstIn)
            firstIn->firstIn = edgeTemp;
        else if (prev) {
            if (isShouldBeSetILink(edgeTemp, prev))
                prev->ilink = edgeTemp;
            else if (isShouldBeSetJLink(edgeTemp, prev))
                prev->jlink = edgeTemp;
        }

        if (isShouldBeSetILink(itTemp, edgeTemp))
            edgeTemp->ilink = itTemp;
        else if (isShouldBeSetJLink(itTemp, edgeTemp))
            edgeTemp->jlink = itTemp;

    } else if (isShouldBeSetILink(edgeTemp, itTemp)) {
        itTemp->ilink = edgeTemp;
        return true;
    } else if (isShouldBeSetJLink(edgeTemp, itTemp)) {
        itTemp->jlink = edgeTemp;
        return true;
    }

    return false;
}

bool isNotNullOfNext(EdgeNode_AMTG currEdge, EdgeNode_AMTG itTemp) {
    return (itTemp->ilink && isShouldBeSetILink(currEdge, itTemp)) ||
           (itTemp->jlink && isShouldBeSetJLink(currEdge, itTemp));
}

bool theEdgeIsExist(EdgeNode_AMTG currEdge, EdgeNode_AMTG itTemp) {
    return (currEdge->ivex == itTemp->ivex && currEdge->jvex == itTemp->jvex) ||
           (currEdge->ivex == itTemp->jvex && currEdge->jvex == itTemp->ivex);
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

void dfsTraversal_AMTG(AdjMultipleTableGraph tableGraph) {
    assert(tableGraph);

    bool visited[tableGraph->vertexSize];
    for (int i = 0; i < tableGraph->vertexSize; i++)
        visited[i] = false;

    for (int i = 0; i < tableGraph->vertexSize; i++) {
        if (visited[i]) continue;
        dfs_AMTG(tableGraph, visited, i);
    }

    fprintf(stdout, "\n\n");
}

void dfs_AMTG(AdjMultipleTableGraph tableGraph, bool *visited, int index) {
    visited[index] = true;
    VertexNode_AMTG vertexNode = get_AL(tableGraph->table, index + 1);
    printf("%c\t", vertexNode->data);

    EdgeNode_AMTG temp = vertexNode->firstIn;
    while (temp) {
        if (!visited[temp->ivex])
            dfs_AMTG(tableGraph, visited, temp->ivex);
        else if (!visited[temp->jvex])
            dfs_AMTG(tableGraph, visited, temp->jvex);

        if (temp->ivex == index)
            temp = temp->ilink;
        else if (temp->jvex == index)
            temp = temp->jlink;
    }
}

void bfsTraversal_AMTG(AdjMultipleTableGraph tableGraph) {
    assert(tableGraph);

    bool visited[tableGraph->vertexSize];
    for (int i = 0; i < tableGraph->vertexSize; i++)
        visited[i] = false;

    ArrayListPtr table = tableGraph->table;
    LinkedQueue queue = newLinkedQueue();
    for (int i = 0; i < tableGraph->vertexSize; i++) {
        if (visited[i]) continue;
        VertexNode_AMTG vertexNode = get_AL(table, i + 1);
        printf("%c\t", vertexNode->data);
        visited[i] = true;

        enqueue_LQ(queue, vertexNode);
        while (!isEmpty_LQ(queue)) {
            VertexNode_AMTG vertexNodeTemp = frontAndDequeue_LQ(queue);

            EdgeNode_AMTG temp = vertexNodeTemp->firstIn;
            while (temp) {
                VertexNode_AMTG outputVertexNode = NULL;
                if (!visited[temp->ivex]) {
                    outputVertexNode = get_AL(table, temp->ivex + 1);
                    visited[temp->ivex] = true;
                    enqueue_LQ(queue, outputVertexNode);
                } else if (!visited[temp->jvex]) {
                    outputVertexNode = get_AL(table, temp->jvex + 1);
                    visited[temp->jvex] = true;
                    enqueue_LQ(queue, outputVertexNode);
                }

                if (outputVertexNode)
                    printf("%c\t", outputVertexNode->data);

                if (temp->ivex == i)
                    temp = temp->ilink;
                else if (temp->jvex == i)
                    temp = temp->jlink;
            }
        }
    }
}
