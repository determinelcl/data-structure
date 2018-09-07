//
//  linked_list2_o.h
//  data-structure
//
//  Created by determination on 2018/8/28.
//  Copyright © 2018年 determination. All rights reserved.
//

#ifndef linked_list2_o_h
#define linked_list2_o_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef u_int8_t  INT8U;
typedef u_int16_t INT16U;
typedef u_int32_t INT32U;
typedef void VOID;
typedef bool BOOL;
typedef struct T_LL2O_LIST_NODE {
    struct T_LL2O_LIST_NODE  *pPrev;      /* 指向链表直接前驱结点的指针 */
    struct T_LL2O_LIST_NODE  *pNext;      /* 指向链表直接后继结点的指针 */
    void                     *pvNodeData; /* 指向链表数据的指针。获取具体数据时需显式转换该指针类型为目标类型 */
} T_LL2O_LIST_NODE;


typedef struct{
    T_LL2O_LIST_NODE   *pHead;          /* 指向链表头结点的指针 */
    T_LL2O_LIST_NODE   *pTail;          /* 指向链表尾结点的指针 */
    INT32U             dwNodeNum;       /* 链表结点数目 */
    INT32U             dwNodeDataSize;  /* 链表结点保存的数据字节数 */
}T_LL2O_LIST;

//链表函数返回状态枚举值
typedef enum{
    LL2O_LIST_OK    = (INT8U)0,
    LL2O_LIST_ERROR = (INT8U)1
} LIST_STATUS;

//链表结点空闲情况枚举值
typedef enum{
    LL2O_LIST_OCCUPIED = (INT8U)0,
    LL2O_LIST_EMPTY    = (INT8U)1,
    LL2O_LIST_NULL     = (INT8U)2
}LIST_OCCUPATION;

//BOOL型常量，适用于'Is'前缀函数
#define  LL2O_LIST_TRUE   (BOOL)1
#define  LL2O_LIST_FALSE  (BOOL)0

#define   FUNC_NAME    __FUNCTION__ //(__func__)



/* 指针校验宏 */
//若无返回值则retVal置RETURN_VOID
#define RETURN_VOID
/* 单个指针较验宏 */
#define CHECK_SINGLE_POINTER(ptr1, retVal) do{\
    if(NULL == (ptr1))\
    { \
        printf("[%s(%d)]Null Pointer: "#ptr1"!\n\r", FUNC_NAME, __LINE__); \
        return retVal; \
    } \
}while(0)

/* 双指针较验宏 */
#define CHECK_DOUBLE_POINTER(ptr1, ptr2, retVal) do{\
    if((NULL == (ptr1)) || (NULL == (ptr2))) \
    { \
        printf("[%s(%d)]Null Pointer: "#ptr1"(%p), "#ptr2"(%p)!\n\r", FUNC_NAME, __LINE__, ptr1, ptr2); \
        return retVal; \
    } \
}while(0)

/* 三指针是否较验宏 */
#define CHECK_TRIPLE_POINTER(ptr1, ptr2, ptr3, retVal) do{\
    if((NULL == (ptr1)) || (NULL == (ptr2)) || (NULL == (ptr3))) \
    { \
        printf("[%s(%d)]Null Pointer: "#ptr1"(%p), "#ptr2"(%p), "#ptr3"(%p)!\n\r", FUNC_NAME, __LINE__, ptr1, ptr2, ptr3); \
        return retVal; \
    } \
}while(0)

/* 常用指针操作节点宏 */
//创建结点为作为链表头以生成双向循环空链表
#define LL2O_INIT_NODE(pNode) do{ \
    (pNode)->pNext = (pNode)->pPrev = (pNode); \
 }while(0)

//"孤立"链表结点，避免通过该结点访问其前驱和后继结点(进而遍历链表)
#define LL2O_ISOL_NODE(pNode) do{ \
    (pNode)->pNext = (pNode)->pPrev = NULL; \
}while(0)

//判断链表是否仅含头结点
#define LL2O_LIST_WITH_HEAD(pHeadNode) do{ \
    (((pHeadNode)->pPrev == (pHeadNode)) && ((pHeadNode->pNext == pHeadNode))); \
}while(0)

//插入链表结点
#define LL2O_INSERT_NODE(prevNode, insertNode) do{ \
    (insertNode)->pNext      = (prevNode)->pNext;  \
    (insertNode)->pPrev      = (prevNode);         \
    (prevNode)->pNext->pPrev = (insertNode);       \
    (prevNode)->pNext        = (insertNode);       \
}while(0)

//删除链表结点
#define LL2O_REMOVE_NODE(removeNode) do{ \
    (removeNode)->pPrev->pNext = (removeNode)->pNext;  \
    (removeNode)->pNext->pPrev = (removeNode)->pPrev;  \
}while(0)

//获取链表结点及其数据(不做安全性检查)
#define GET_NODE_NUM(pList)      ((pList)->dwNodeNum)
#define GET_HEAD_NODE(pList)     ((pList)->pHead)
#define GET_TAIL_NODE(pList)     ((pList)->pTail)
#define GET_PREV_NODE(pNode)     ((pNode)->pPrev)
#define GET_NEXT_NODE(pNode)     ((pNode)->pNext)
#define GET_NODE_DATA(pNode)     ((pNode)->pvNodeData)

//双向循环链表遍历校验宏
#define LIST_ITER_CHECK(pList, retVal) do{\
    CHECK_SINGLE_POINTER((pList), retVal); \
    CHECK_SINGLE_POINTER((pList)->pHead, retVal); \
    CHECK_SINGLE_POINTER((pList)->pHead->pNext, retVal); \
}while(0)
//双向循环链表遍历宏
//pList: 链表指针；pLoopNode: 链表结点，用作循环计数器；
//pTmpNode: 链表结点，用作删除pLoopNode时临时保存pLoopNode->pNext
//某些情况下采用遍历宏代替LL2OLocateListNode或LL2OTraverseListNode函数可提高执行效率。
//如外部数据和结点数据需按共同的规则转换时，采用遍历宏可使外部数据不必重复转换。
#define LIST_ITER_LOOP(pList, pLoopNode) \
    for(pLoopNode = (pList)->pHead->pNext; \
        pLoopNode != (pList)->pHead; \
        pLoopNode = pLoopNode->pNext)
#define LIST_ITER_LOOP_SAFE(pList, pLoopNode, pTmpNode) \
    for(pLoopNode = (pList)->pHead->pNext, pTmpNode = pLoopNode->pNext; \
        pLoopNode != (pList)->pHead; \
        pLoopNode = pTmpNode, pTmpNode = pLoopNode->pNext)

#define SAFE_FREE(pointer) do{ \
    if(pointer != NULL){ \
        free(pointer); \
        pointer = NULL; \
    }\
}while(0);


/**********************************************************************
 * 函数名称： LL2OInitList
 * 功能描述： 链表初始化，产生空的双向循环链表
 * 输入参数： T_LL2O_LIST *pList    :链表指针
 *           INT32U dwNodeDataSize :链表结点保存的数据字节数
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2OInitList(T_LL2O_LIST *pList, INT32U dwNodeDataSize);


/**********************************************************************
 * 函数名称： LL2OClearList
 * 功能描述： 清空双向循环链表除头结点外的结点
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 清空链表结点后，再次插入结点时不需要初始化链表。
 ***********************************************************************/
LIST_STATUS LL2OClearList(T_LL2O_LIST *pList);


/**********************************************************************
 * 函数名称： LL2ODestroyList
 * 功能描述： 销毁双向循环链表，包括头结点
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 销毁链表后，再次插入结点时需要初始化链表。
 ***********************************************************************/
LIST_STATUS LL2ODestroyList(T_LL2O_LIST *pList);


/**********************************************************************
 * 函数名称： LL2OIsListEmpty
 * 功能描述： 判断链表是否为空(仅含头结点或不含任何结点)
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： BOOL
 ***********************************************************************/
BOOL LL2OIsListEmpty(T_LL2O_LIST *pList);


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
LIST_STATUS LL2OPrependListNode(T_LL2O_LIST *pList, VOID *pvNodeData);

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
LIST_STATUS LL2OAppendListNode(T_LL2O_LIST *pList, VOID *pvNodeData);


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
LIST_STATUS LL2OInsertListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE *pPrevNode, VOID *pvNodeData);


/**********************************************************************
 * 函数名称： LL2ORemoveListNode
 * 功能描述： 删除双向循环链表中除头结点外的某一结点
 * 输入参数： T_LL2O_LIST *pList      :链表指针
 *           T_LL2O_LIST_NODE *pNode :待删除的链表结点指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2ORemoveListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE *pNode);


/**********************************************************************
 * 函数名称： LL2ODestroyListNode
 * 功能描述： 销毁双向循环链表中除头结点外的某一结点
 * 输入参数： T_LL2O_LIST *pList       :链表指针
 *           T_LL2O_LIST_NODE **pNode :待销毁的链表结点二级指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
LIST_STATUS LL2ODestroyListNode(T_LL2O_LIST *pList, T_LL2O_LIST_NODE **pNode);


/**********************************************************************
 * 函数名称： LL2OGetListNodeByIndex
 * 功能描述： 获取链表中指定序号的结点(按头结点后继方向排序)
 * 输入参数： T_LL2O_LIST* pList :链表指针
 *           INT32U dwNodeIndex :结点序号(从1开始)
 * 输出参数： NA
 * 返 回 值： T_LL2O_LIST_NODE* 链表结点指针(空表返回NULL)
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetListNodeByIndex(T_LL2O_LIST *pList, INT32U dwNodeIndex);


/**********************************************************************
 * 函数名称： LL2OLocateListNode
 * 功能描述： 查找链表中首个与pData满足函数fpCompareNode判定关系的结点
 * 输入参数： T_LL2O_LIST* pList            :链表指针
 *           VOID* pvData                  :待比较数据指针
 *           CompareNodeFunc fpCompareNode :比较回调函数指针
 * 输出参数： NA
 * 返 回 值： T_LL2O_LIST_NODE* 链表结点指针(未找到时返回NULL)
 ***********************************************************************/
/* 比较回调函数原型，用来自定义链表节点比较 */
typedef INT8U (*CompareNodeFunc)(VOID *pvNodeData, VOID *pvData, INT32U dwNodeDataSize);
T_LL2O_LIST_NODE* LL2OLocateListNode(T_LL2O_LIST *pList, VOID *pvData, CompareNodeFunc fpCompareNode);

/**********************************************************************
 * 函数名称： LL2OTraverseListNode
 * 功能描述： 链表结点遍历函数，遍历操作由fpTravNode指定
 * 输入参数： T_LL2O_LIST* pList       :链表指针
 *           VOID* pvTravInfo        :遍历操作回调函数所需信息
 *                                    也可为空，取决于回调函数具体实现
 *           TravNodeFunc fpTravNode :遍历操作回调函数指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 * 注意事项： 本函数可间接实现Print等操作，但不建议代替后者。
 *           fpTravNode返回非0(LL2O_LIST_OK)值时中止遍历
 ***********************************************************************/
typedef LIST_STATUS (*TravNodeFunc)(VOID *pvNode, VOID *pvTravInfo, INT32U dwNodeDataSize);
LIST_STATUS LL2OTraverseListNode(T_LL2O_LIST *pList, VOID *pvTravInfo, TravNodeFunc fpTravNode);

/**********************************************************************
 * 函数名称： LL2OPrintListNode
 * 功能描述： 打印输出链表结点的数据域内容
 * 输入参数： T_LL2O_LIST* pList        :链表指针
 *           PrintListFunc fpPrintList :打印回调函数指针
 * 输出参数： NA
 * 返 回 值： LIST_STATUS
 ***********************************************************************/
/* 打印回调函数原型，用来自定义链表内容打印 */
typedef VOID (*PrintListFunc)(VOID *pNodeData, INT32U dwNodeNum);
LIST_STATUS LL2OPrintListNode(T_LL2O_LIST *pList, PrintListFunc fpPrintList);


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
INT8U CompareNodeGeneric(VOID *pvNodeData, VOID *pvData, INT32U dwNodeDataSize);


/**********************************************************************
 * 函数名称： PrintListWord
 * 功能描述： 打印链表结点，结点数据域为两字节整数
 * 输入参数： VOID *pvNodeData   :链表节点数据指针
 *           INT32U dwNodeNum  :链表节点数目
 * 输出参数： NA
 * 返 回 值： VOID
 * 注意事项： 仅作示例，未考虑字节序等问题。
 ***********************************************************************/
VOID PrintListWord(VOID *pvNodeData, INT32U dwNodeNum);


/**********************************************************************
 * 函数名称： LL2OGetListNodeNum
 * 功能描述： 获取链表结点数目
 * 输入参数： T_LL2O_LIST *pList :链表指针
 * 输出参数： NA
 * 返 回 值： INT32U 链表结点数目
 ***********************************************************************/
INT32U LL2OGetListNodeNum(T_LL2O_LIST *pList);


/**********************************************************************
 * 函数名称： LL2OGetListHead/LL2OGetListTail
 * 功能描述： 获取链表头结点/尾结点指针
 * 输入参数： T_LL2O_LIST *pList :链表指针
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetListHead(T_LL2O_LIST *pList);


T_LL2O_LIST_NODE* LL2OGetListTail(T_LL2O_LIST *pList);


/**********************************************************************
 * 函数名称： LL2OGetPrevNode/LL2OGetNextNode
 * 功能描述： 获取链表指定结点的前驱结点/后继结点指针
 * 输入参数： T_LL2O_LIST_NODE *pNode :指定结点的指针
 ***********************************************************************/
T_LL2O_LIST_NODE* LL2OGetPrevNode(T_LL2O_LIST_NODE *pNode);


T_LL2O_LIST_NODE* LL2OGetNextNode(T_LL2O_LIST_NODE *pNode);


/**********************************************************************
 * 函数名称： LL2OGetNodeData
 * 功能描述： 获取链表指定结点的数据域
 * 输入参数： T_LL2O_LIST_NODE *pNode :指定结点的指针
 ***********************************************************************/
VOID* LL2OGetNodeData(T_LL2O_LIST_NODE *pNode);


void SafeFree(void **pointer);


void ListTestExample();



#endif /* linked_list2_o_h */
