//
//  linked_list2_o.c
//  data-structure
//
//  Created by determination on 2018/8/28.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "linked_list2_o.h"
#define TEST_AND_EXAMPLE 1

/********************************************************************
 * 函数名称： CreateListNode
 * 功能描述： 创建新的链表结点
 * 输入参数： T_LL2O_LIST *pList :链表指针
 *           VOID *pvNodeData  :待插入的链表结点数据指针
 * 输出参数： NA
 * 返 回 值： T_LL2O_LIST_NODE*
 ***********************************************************************/
static T_LL2O_LIST_NODE *CreateListNode(T_LL2O_LIST *pList, VOID *pvNodeData)
{
    T_LL2O_LIST_NODE *pInsertNode = (T_LL2O_LIST_NODE*) calloc((sizeof(T_LL2O_LIST_NODE) + pList->dwNodeDataSize), 1);
    if (NULL == pInsertNode)
    {
        printf("[%s]pList(%p) failed to alloc for pInsertNode!\n", FUNC_NAME, pList);
        return NULL;
    }
    
    // 这里是一个随便用来初始化的值
    pInsertNode->pvNodeData = (INT8U *)pInsertNode + sizeof(T_LL2O_LIST_NODE);
    
    if (NULL != pvNodeData)
    {   //创建非头结点时
        memmove(pInsertNode->pvNodeData, pvNodeData, pList->dwNodeDataSize);
    }
    
    return pInsertNode;
}

/**********************************************************************
 * 函数名称： RemoveListNode
 * 功能描述： 删除指定的链表结点(释放结点内存并置其前驱后继指针为NULL)
 * 输入参数： T_LL2O_LIST *pList :链表指针
 *           VOID *pvNode       :待删除的链表结点指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 本函数未置待删除结点指针为NULL，请避免访问已删除结点
 ***********************************************************************/
static LIST_STATUS RemoveListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE *pNode)
{
    LL2O_ISOL_NODE(pNode);
    free(pNode);  //释放链表结点
    
    return LL2O_LIST_OK;
}


/**********************************************************************
 * 函数名称： DestroyListNode
 * 功能描述： 销毁指定的链表结点(释放结点内存并置结点指针为NULL)
 * 输入参数： T_LL2O_LIST *pList :链表指针
 *           VOID **pNode       :待销毁的链表结点指针的指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 当指向待销毁结点的指针存在多份拷贝且散布程序各处时(尤其当
 *           调用链未能保证**pNode指向原始结点时)，无法彻底销毁该结点
 ***********************************************************************/
static LIST_STATUS DestroyListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE **pNode)
{
    free(*pNode);  //释放链表结点
    *pNode = NULL;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： GetListOccupation
 * 功能描述： 获取链表占用情况
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： LIST_OCCUPATION
 * 注意事项： 本函数仅用于内部测试。
 ***********************************************************************/
static LIST_OCCUPATION GetListOccupation(T_LL2O_LIST *pList)
{
    CHECK_SINGLE_POINTER(pList, LL2O_LIST_NULL);
    CHECK_SINGLE_POINTER(pList->pHead, LL2O_LIST_NULL);
    
    return (0 == pList->dwNodeNum) ? LL2O_LIST_EMPTY : LL2O_LIST_OCCUPIED;
}


/**********************************************************************
 * 函数名称： LL2OInitList
 * 功能描述： 链表初始化，产生空的双向循环链表
 * 输入参数： T_LL2O_LIST *pList    :链表指针
 *           INT32U dwNodeDataSize :链表结点保存的数据字节数
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2OInitList(T_LL2O_LIST *pList, INT32U dwNodeDataSize)
{
    CHECK_SINGLE_POINTER(pList, LL2O_LIST_ERROR);
    
    if(0 == dwNodeDataSize)
    {
        printf("[%s]pList=%p, dwNodeDataSize=%uBytes, undesired initialization!\n",
               FUNC_NAME, pList, dwNodeDataSize);
        return LL2O_LIST_ERROR;
    }
    pList->dwNodeDataSize = dwNodeDataSize;  //给予重新修改结点数据大小的机会
    
    if(NULL != pList->pHead)
    {
        printf("[%s]pList(%p) has been initialized!\n", FUNC_NAME, pList);
        return LL2O_LIST_OK;
    }
    
    T_LL2O_LIST_NODE *pHeadNode = CreateListNode(pList, NULL);
    if(NULL == pHeadNode)
    {
        printf("[%s]pList(%p) failed to create pHeadNode!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_INIT_NODE(pHeadNode);
    pList->pHead = pList->pTail = pHeadNode;
    pList->dwNodeNum = 0;
    
    return LL2O_LIST_OK;
}


/**********************************************************************
 * 函数名称： LL2OClearList
 * 功能描述： 清空双向循环链表除头结点外的结点
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 清空链表结点后，再次插入结点时不需要初始化链表。
 ***********************************************************************/
LIST_STATUS LL2OClearList(T_LL2O_LIST *pList)
{
    LIST_ITER_CHECK(pList, LL2O_LIST_ERROR);
    
    T_LL2O_LIST_NODE *pNextNode, *pListNode = pList->pHead->pNext;
    while(pListNode != pList->pHead)
    {
        pNextNode = pListNode->pNext;
        RemoveListNode(pList, pListNode);
        pListNode = pNextNode;
    }
    
    LL2O_INIT_NODE(pList->pHead);
    pList->pTail = pList->pHead;
    pList->dwNodeNum = 0;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2ODestroyList
 * 功能描述： 销毁双向循环链表，包括头结点
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 销毁链表后，再次插入结点时需要初始化链表。
 ***********************************************************************/
LIST_STATUS LL2ODestroyList(T_LL2O_LIST *pList)
{
    LIST_ITER_CHECK(pList, LL2O_LIST_ERROR);
    
    T_LL2O_LIST_NODE *pNextNode, *pListNode = pList->pHead->pNext;
    while(pListNode != pList->pHead)
    {
        pNextNode = pListNode->pNext;
        DestroyListNode(pList, &pListNode);
        pListNode = pNextNode;
    }
    
    DestroyListNode(pList, &(pList->pHead)); //销毁头结点
    pList->pTail = NULL;                     //尾结点指针置空
    pList->dwNodeNum = 0;
    pList->dwNodeDataSize = 0;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2OIsListEmpty
 * 功能描述： 判断链表是否为空(仅含头结点或不含任何结点)
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： BOOL
 ***********************************************************************/
BOOL LL2OIsListEmpty(T_LL2O_LIST *pList)
{
    CHECK_SINGLE_POINTER(pList, LL2O_LIST_TRUE);
    CHECK_SINGLE_POINTER(pList->pHead, LL2O_LIST_TRUE);
    
    T_LL2O_LIST_NODE *pHeadNode = pList->pHead;
    if((0 == pList->dwNodeNum) &&
       (pHeadNode->pPrev == pHeadNode) && //冗余校验以加强安全性
       (pHeadNode->pNext == pHeadNode))
    {
        return LL2O_LIST_TRUE;
    }
    else
    {
        return LL2O_LIST_FALSE;
    }
}

/**********************************************************************
 * 函数名称： LL2OPrependListNode
 * 功能描述： 在链表头结点后逆序增加结点，尾结点恒为头结点
 *           在头结点指针pHead所指向结点和pHead->pNext所指向结点
 *           之间插入新结点，先插入的结点向右移动。遍历链表时
 *           从pHead开始向右依次访问至最先插入的结点，类似于栈。
 * 输入参数： T_LL2O_LIST *pList :链表指针
 *           VOID *pvNodeData   :待插入的链表结点数据指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2OPrependListNode(T_LL2O_LIST *pList, VOID *pvNodeData)
{
    CHECK_DOUBLE_POINTER(pList, pvNodeData, LL2O_LIST_ERROR);
    
    if(0 == pList->dwNodeDataSize)
    {
        printf("[%s]pList=%p, dwNodeDataSize=0Bytes, probably uninitialized or initialized improperly. See 'LL2OInitList'!\n",
               FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    T_LL2O_LIST_NODE *pInsertNode = CreateListNode(pList, pvNodeData);
    if(NULL == pInsertNode)
    {
        printf("[%s]pList(%p) failed to create pInsertNode!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_INSERT_NODE(pList->pHead, pInsertNode); //在链表头结点后增加一个结点
    
    pList->dwNodeNum++;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2OAppendListNode
 * 功能描述： 在链表头结点后顺序增加结点，新结点作为尾结点
 *           在头结点指针pHead所指向结点前(即尾结点后)插入新结点，
 *           先插入的结点向左移动。遍历链表时从pHead开始向右依次
 *           访问至最后插入的结点，类似于队列。
 *           双向循环链表已保证pList->pTail(即pHead->pPrev)非空。
 * 输入参数： T_LL2O_LIST *pList :链表指针
 *           VOID *pvNodeData   :待插入的链表结点数据指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2OAppendListNode(T_LL2O_LIST *pList, VOID *pvNodeData)
{
    CHECK_DOUBLE_POINTER(pList, pvNodeData, LL2O_LIST_ERROR);
    
    if(0 == pList->dwNodeDataSize)
    {
        printf("[%s]pList=%p, dwNodeDataSize=0Bytes, probably uninitialized or initialized improperly. See 'LL2OInitList'!\n",
               FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    T_LL2O_LIST_NODE *pInsertNode = CreateListNode(pList, pvNodeData);
    if(NULL == pInsertNode)
    {
        printf("[%s]pList(%p) failed to create pInsertNode!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_INSERT_NODE(pList->pTail, pInsertNode); //在链表尾结点后增加一个结点
    pList->pTail = pInsertNode;                  //新的尾结点指向当前添加的结点
    
    pList->dwNodeNum++;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2OInsertListNode
 * 功能描述： 在链表中任意位置插入结点
 * 输入参数： T_LL2O_LIST *pList          :链表指针
 *           T_LL2O_LIST_NODE *pPrevNode :待插入结点的前驱结点指针
 *           VOID *pvNodeData            :待插入结点的数据域指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 若pPrevNode恒为头结点或尾结点，请使用LL2OPrependListNode
 *           或LL2OAppendListNode函数
 ***********************************************************************/
LIST_STATUS LL2OInsertListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE *pPrevNode, VOID *pvNodeData)
{
    CHECK_TRIPLE_POINTER(pList, pPrevNode, pvNodeData, LL2O_LIST_ERROR);
    
    if(0 == pList->dwNodeDataSize)
    {
        printf("[%s]pList=%p, dwNodeDataSize=0Bytes, probably uninitialized or initialized improperly. See 'LL2OInitList'!\n",
               FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    T_LL2O_LIST_NODE *pInsertNode = CreateListNode(pList, pvNodeData);
    if(NULL == pInsertNode)
    {
        printf("[%s]pList(%p) failed to create pInsertNode!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_INSERT_NODE(pPrevNode, pInsertNode);
    if(pPrevNode == pList->pTail)
        pList->pTail = pInsertNode;
    
    pList->dwNodeNum++;
    
    return LL2O_LIST_OK;
}


/**********************************************************************
 * 函数名称： LL2ORemoveListNode
 * 功能描述： 删除双向循环链表中除头结点外的某一结点
 * 输入参数： T_LL2O_LIST *pList      :链表指针
 *           T_LL2O_LIST_NODE *pNode :待删除的链表结点指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2ORemoveListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE *pNode)
{
    CHECK_DOUBLE_POINTER(pList, pNode, LL2O_LIST_ERROR);
    CHECK_DOUBLE_POINTER(pNode->pPrev, pNode->pNext, LL2O_LIST_ERROR);
    
    if(0 == pList->dwNodeNum)
    {
        printf("[%s]pList(%p) has no node to be Removed!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_REMOVE_NODE(pNode);
    if(pNode->pNext == pList->pHead)
    {
        pList->pTail = pNode->pPrev; //删除尾结点
    }
    
    RemoveListNode(pList, pNode);
    pList->dwNodeNum--;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2ODestroyListNode
 * 功能描述： 销毁双向循环链表中除头结点外的某一结点
 * 输入参数： T_LL2O_LIST *pList       :链表指针
 *           T_LL2O_LIST_NODE **pNode :待销毁的链表结点二级指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2ODestroyListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE **pNode)
{
    CHECK_DOUBLE_POINTER(pList, pNode, LL2O_LIST_ERROR);
    CHECK_SINGLE_POINTER(*pNode, LL2O_LIST_ERROR);
    
    if(0 == pList->dwNodeNum)
    {
        printf("[%s]pList(%p) has no node to be Removed!\n", FUNC_NAME, pList);
        return LL2O_LIST_ERROR;
    }
    
    LL2O_REMOVE_NODE(*pNode);
    if((*pNode)->pNext == pList->pHead)
    {
        pList->pTail = (*pNode)->pPrev; //删除尾结点
    }
    
    DestroyListNode(pList, pNode);
    pList->dwNodeNum--;
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2OGetListNodeByIndex
 * 功能描述： 获取链表中指定序号的结点(按头结点后继方向排序)
 * 输入参数： T_LL2O_LIST* pList :链表指针
 *           INT32U dwNodeIndex :结点序号(从1开始)
 * 输出参数： NA
 * 返 回 值： T_LL2O_LIST_NODE* 链表结点指针(空表返回NULL)
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetListNodeByIndex(T_LL2O_LIST *pList, INT32U dwNodeIndex)
{
    CHECK_SINGLE_POINTER(pList, NULL);
    
    if(0 == dwNodeIndex)
        return pList->pHead;  //也可返回NULL
    if(dwNodeIndex >= pList->dwNodeNum)
        return pList->pTail;
    
    T_LL2O_LIST_NODE *pListNode = pList->pHead;
    for(INT32U dwNodeIdx = 1; dwNodeIdx <= dwNodeIndex; dwNodeIdx++)
        pListNode = pListNode->pNext;
    
    return pListNode;
}

/**********************************************************************
 * 函数名称： LL2OLocateListNode
 * 功能描述： 查找链表中首个与pData满足函数fpCompareNode判定关系的结点
 * 输入参数： T_LL2O_LIST* pList             :链表指针
 *           VOID* pvData                  :待比较数据指针
 *           CompareNodeFunc fpCompareNode :比较回调函数指针
 * 输出参数： NA
 * 返 回 值： T_LL2O_LIST_NODE* 链表结点指针(未找到时返回NULL)
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OLocateListNode(T_LL2O_LIST *pList, VOID *pvData, CompareNodeFunc fpCompareNode)
{
    CHECK_TRIPLE_POINTER(pList, pvData, fpCompareNode, NULL);
    CHECK_SINGLE_POINTER(pList->pHead, NULL);
    CHECK_SINGLE_POINTER(pList->pHead->pNext, NULL);
    
    T_LL2O_LIST_NODE *pListNode = pList->pHead->pNext;
    while(pListNode != pList->pHead)
    {
        if(0 == fpCompareNode(pListNode->pvNodeData, pvData, pList->dwNodeDataSize))
            return pListNode;
        
        pListNode = pListNode->pNext;
    }
    
    return NULL;
}

/**********************************************************************
 * 函数名称： LL2OTraverseListNode
 * 功能描述： 链表结点遍历函数，遍历操作由fpTravNode指定
 * 输入参数： T_LL2O_LIST* pList      :链表指针
 *           VOID* pvTravInfo        :遍历操作回调函数所需信息
 *                                    也可为空，取决于回调函数具体实现
 *           TravNodeFunc fpTravNode :遍历操作回调函数指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 本函数可间接实现Print等操作，但不建议代替后者。
 *           fpTravNode返回非0(LL2O_LIST_OK)值时中止遍历
 ***********************************************************************/
LIST_STATUS LL2OTraverseListNode(T_LL2O_LIST *pList, VOID *pvTravInfo, TravNodeFunc fpTravNode)
{
    CHECK_DOUBLE_POINTER(pList, fpTravNode, LL2O_LIST_ERROR);
    CHECK_SINGLE_POINTER(pList->pHead, LL2O_LIST_ERROR);
    CHECK_SINGLE_POINTER(pList->pHead->pNext, LL2O_LIST_ERROR);
    
    T_LL2O_LIST_NODE *pListNode = pList->pHead->pNext;
    while(pListNode != pList->pHead)
    {
        T_LL2O_LIST_NODE *pTmpNode = pListNode->pNext; //fpTravNode内可能会销毁结点pListNode
        if(LL2O_LIST_OK != fpTravNode(pListNode, pvTravInfo, pList->dwNodeDataSize))
            break;
        
        pListNode = pTmpNode;
    }
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： LL2OPrintListNode
 * 功能描述： 打印输出链表结点的数据域内容
 * 输入参数： T_LL2O_LIST* pList        :链表指针
 *           PrintListFunc fpPrintList :打印回调函数指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2OPrintListNode(T_LL2O_LIST *pList, PrintListFunc fpPrintList)
{
    CHECK_DOUBLE_POINTER(pList, fpPrintList, LL2O_LIST_ERROR);
    CHECK_SINGLE_POINTER(pList->pHead, LL2O_LIST_ERROR);
    CHECK_SINGLE_POINTER(pList->pHead->pNext, LL2O_LIST_ERROR);
    
    T_LL2O_LIST_NODE *pListNode = pList->pHead->pNext;
    while(pListNode != pList->pHead)
    {
        //具体打印格式交给回调函数灵活处理(可直接打印也可拷贝至本地处理后打印)
        fpPrintList(pListNode->pvNodeData, pList->dwNodeNum);
        pListNode = pListNode->pNext;
    }
    printf("\n");
    
    return LL2O_LIST_OK;
}

/**********************************************************************
 * 函数名称： CompareNodeGeneric
 * 功能描述： 通用链表结点内存比较
 * 输入参数： VOID *pvNodeData      :链表结点数据指针
 *           VOID *pvData          :待比较外部数据指针
 *           INT32U dwNodeDataSize :链表结点数据大小
 * 输出参数： NA
 * 返 回 值： 0：Equal; !0:Unequal
 * 注意事项： 比较长度为结点数据字节数，即默认与外部数据大小一致
 ***********************************************************************/
INT8U CompareNodeGeneric(VOID *pvNodeData, VOID *pvData, INT32U dwNodeDataSize)
{
    CHECK_DOUBLE_POINTER(pvNodeData, pvData, 1);
    return memcmp(pvNodeData, pvData, dwNodeDataSize);
}

/**********************************************************************
 * 函数名称： PrintListWord
 * 功能描述： 打印链表结点，结点数据域为两字节整数
 * 输入参数： VOID *pvNodeData   :链表节点数据指针
 *           INT32U dwNodeNum  :链表节点数目
 * 输出参数： NA
 * 返 回 值： VOID
 * 注意事项： 仅作示例，未考虑字节序等问题。
 ***********************************************************************/
VOID PrintListWord(VOID *pvNodeData, INT32U dwNodeNum)
{
    CHECK_SINGLE_POINTER(pvNodeData, RETURN_VOID);
    printf("%d ", *((INT16U *)pvNodeData));
}

/**********************************************************************
 * 函数名称： LL2OGetListNodeNum
 * 功能描述： 获取链表结点数目
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： INT32U 链表结点数目
 ***********************************************************************/
INT32U LL2OGetListNodeNum(T_LL2O_LIST *pList)
{
    CHECK_SINGLE_POINTER(pList, 0);
    return (pList->dwNodeNum);
}

/**********************************************************************
 * 函数名称： LL2OGetListHead/LL2OGetListTail
 * 功能描述： 获取链表头结点/尾结点指针
 * 输入参数： T_LL2O_LIST *pList :链表指针
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetListHead(T_LL2O_LIST *pList)
{
    CHECK_SINGLE_POINTER(pList, NULL);
    return (pList->pHead);
}

T_LL2O_LIST_NODE* LL2OGetListTail(T_LL2O_LIST *pList)
{
    CHECK_SINGLE_POINTER(pList, NULL);
    return (pList->pTail);
}

/**********************************************************************
 * 函数名称： LL2OGetPrevNode/LL2OGetNextNode
 * 功能描述： 获取链表指定结点的前驱结点/后继结点指针
 * 输入参数： T_LL2O_LIST_NODE *pNode :指定结点的指针
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetPrevNode(T_LL2O_LIST_NODE *pNode)
{
    CHECK_SINGLE_POINTER(pNode, NULL);
    return (pNode->pPrev);
}

T_LL2O_LIST_NODE* LL2OGetNextNode(T_LL2O_LIST_NODE *pNode)
{
    CHECK_SINGLE_POINTER(pNode, NULL);
    return (pNode->pNext);
}

/**********************************************************************
 * 函数名称： LL2OGetNodeData
 * 功能描述： 获取链表指定结点的数据域
 * 输入参数： T_LL2O_LIST_NODE *pNode :指定结点的指针
 ***********************************************************************/
VOID* LL2OGetNodeData(T_LL2O_LIST_NODE *pNode)
{
    CHECK_DOUBLE_POINTER(pNode, pNode->pvNodeData, NULL);
    return (pNode->pvNodeData);
}

void SafeFree(void **pointer)
{
    if(pointer != NULL)
    {
        free(*pointer);
        *pointer = NULL;
    }
}

#ifdef TEST_AND_EXAMPLE

static LIST_STATUS TravPrintWord(VOID *pvNode, VOID *pvTravInfo, INT32U dwNodeDataSize)
{
    CHECK_SINGLE_POINTER(pvNode, LL2O_LIST_ERROR);
    T_LL2O_LIST_NODE *pNode = (T_LL2O_LIST_NODE *)pvNode;
    printf("%d ", *((INT16U *)GET_NODE_DATA(pNode)));
    return LL2O_LIST_OK;
}

T_LL2O_LIST gExampleList = {0};
void ListTestExample()
{   //本函数并非严格意义上的测试函数，主要用作示例，且示例并非最佳用法。
    INT8U ucTestIndex = 1;
    INT16U aTestListData[] = {11, 22, 33, 44, 55, 66};
    
    printf("\n<Test Case %u>: Initialization!\n", ucTestIndex++);
    LL2OInitList(&gExampleList, sizeof(INT16U));
    printf("gExampleList=%p, pHead=%p, pTail=%p\n", &gExampleList, LL2OGetListHead(&gExampleList), LL2OGetListTail(&gExampleList));
    
    printf("\n<Test Case %u>: Append Node to List!\n", ucTestIndex++);
    LL2OAppendListNode(&gExampleList, &aTestListData[0]);
    LL2OAppendListNode(&gExampleList, &aTestListData[1]);
    LL2OAppendListNode(&gExampleList, &aTestListData[2]);
    printf("LL2OIsListEmpty=%u(0-Occupied; 1-Empty)\n", LL2OIsListEmpty(&gExampleList));
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    LL2OPrintListNode(&gExampleList, PrintListWord);
    
    printf("\n<Test Case %u>: Insert Node to List!\n", ucTestIndex++);
    T_LL2O_LIST_NODE *pPrevNode = LL2OGetListNodeByIndex(&gExampleList, 2);
    printf("NodeData2=%d\n", *((INT16U *)LL2OGetNodeData(pPrevNode)));
    LL2OInsertListNode(&gExampleList, pPrevNode, &aTestListData[4]);
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    LL2OPrintListNode(&gExampleList, PrintListWord);
    
    printf("\n<Test Case %u>: Remove Node from List!\n", ucTestIndex++);
    T_LL2O_LIST_NODE *pDeleteNode = LL2OLocateListNode(&gExampleList, &aTestListData[1], CompareNodeGeneric);
    LL2ORemoveListNode(&gExampleList, pDeleteNode);
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    LL2OPrintListNode(&gExampleList, PrintListWord);
    
    printf("\n<Test Case %u>: Clear List!\n", ucTestIndex++);
    LL2OClearList(&gExampleList);
    printf("gExampleList=%p, pHead=%p, pTail=%p\n", &gExampleList, GET_HEAD_NODE(&gExampleList), GET_TAIL_NODE(&gExampleList));
    printf("LL2OIsListEmpty=%u(0-Occupied; 1-Empty)\n", LL2OIsListEmpty(&gExampleList));
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    
    printf("\n<Test Case %u>: Prepend Node to List!\n", ucTestIndex++);
    LL2OPrependListNode(&gExampleList, &aTestListData[3]);
    LL2OPrependListNode(&gExampleList, &aTestListData[4]);
    LL2OPrependListNode(&gExampleList, &aTestListData[5]);
    printf("LL2OIsListEmpty=%u(0-Occupied; 1-Empty)\n", LL2OIsListEmpty(&gExampleList));
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    LL2OPrintListNode(&gExampleList, PrintListWord);
    
    T_LL2O_LIST_NODE *pListNode = NULL;
    LIST_ITER_LOOP(&gExampleList, pListNode)
    {
        printf("%d ", *((INT16U *)GET_NODE_DATA(pListNode)));
    }
    printf("\n");
    
    LL2OTraverseListNode(&gExampleList, NULL, TravPrintWord);
    printf("\n");
    
    printf("\n<Test Case %u>: Destory List!\n", ucTestIndex++);
    LL2ODestroyList(&gExampleList);
    printf("gExampleList=%p, pHead=%p, pTail=%p\n", &gExampleList, GET_HEAD_NODE(&gExampleList), GET_TAIL_NODE(&gExampleList));
    printf("gExampleList NodeNum=%u\n", LL2OGetListNodeNum(&gExampleList));
    printf("GetListOccupation=%u(0-Occupied; 1-Empty; 2-Null)\n", GetListOccupation(&gExampleList));
}

#endif
