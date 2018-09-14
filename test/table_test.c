//
//  table_test.c
//  data-structure
//
//  Created by determination on 2018/8/25.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "table_test.h"

static char *answer(bool rs) {
    return rs ? "yes" : "no";
}

void testArrayList(void) {
    puts("**************************************************");
    puts("*                 顺序表测试例程                   *");
    puts("**************************************************");

    ArrayListPtr listPtr = newArrayList();
    printf("顺序表指针是否为空：%s\n", listPtr ? "否" : "是");
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(listPtr), size_AL(listPtr));
    showList_AL(listPtr);

    printf("销毁顺序表指针\n");
    destroy_AL(&listPtr);
    printf("顺序表指针是否为空：%s\n", listPtr ? "否" : "是");

    ArrayList arrayList;
    DataType_AL data;

    initArrayList(&arrayList);
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    showList_AL(&arrayList);

    printf("是否为空表？%s\n", answer(isEmpty_AL(&arrayList)));
    for (int i = 0; i < 20; i++) {
        insert_AL(&arrayList, i + 1, i);
    }
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    showList_AL(&arrayList);

    get_AL(&arrayList, 6, &data);
    printf("第6个元素是: %d\n", data);

    printf("6是否存在于表中: %s\n", answer(isExist_AL(&arrayList, 6)));
    printf("21是否存在于表中: %s\n", answer(isExist_AL(&arrayList, 21)));
    printf("是否为空表: %s\n", answer(isEmpty_AL(&arrayList)));

    remove_AL(&arrayList, 11, &data);
    printf("被删除的元素是：%d\n", data);
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    printf("删除之后的元素序列为：\n");
    showList_AL(&arrayList);

    remove_AL(&arrayList, 11, &data);
    printf("被删除的元素是：%d\n", data);
    printf("删除之后的元素序列为：\n");
    showList_AL(&arrayList);

    printf("执行清空之后:\n");
    clear_AL(&arrayList);
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    insert_AL(&arrayList, 1, 1);
    showList_AL(&arrayList);

    printf("销毁顺序表：\n");
    ArrayListPtr temp = &arrayList;
    destroy_AL(&temp);
    printf("顺序表指针是否为空：%s\n", temp ? "否" : "是");
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    showList_AL(&arrayList);

    printf("插入元素\n");

    for (int i = 0; i < 1; i++) {
        insert_AL(&arrayList, i + 1, i);
    }
    insert_AL(&arrayList, 1, 6);
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    showList_AL(&arrayList);

    int num = 10;
    printf("添加元素%d\n", num);
    add_AL(&arrayList, num);
    printf("顺序表容量 = %d, 元素个数 = %d\n", capacity_AL(&arrayList), size_AL(&arrayList));
    showList_AL(&arrayList);

    puts("\n");
}

void testLinkedList(void) {
    puts("**************************************************");
    puts("*                 单链表测试例程                   *");
    puts("**************************************************");

    LinkedList list = newLinkedList();
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("向链表之中存放元素\n");

    const int SIZE = 20;
    int elements[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        elements[i] = i + 1;
        add_LL(list, &elements[i]);
    }

    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    int index = 6;
    int no1 = 102;
    printf("向链表中第%d个位置插入数据%d\n", index, no1);
    insertByIndex_LL(list, &no1, index);
    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    int no2 = 103;
    int element = 10;
    Position_LL elementOfNode = find_LL(list, &element);
    printf("向链表中的元素为%d的节点后插入数据%d\n", *(int *) dataOfPosNode_LL(elementOfNode), no2);
    insert_LL(list, &no2, elementOfNode);
    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    index = 20;
    Position_LL pos = get_LL(list, index);
    printf("获取索引为%d的位置的元素为：%d\n", index, *(int *) dataOfPosNode_LL(pos));
    printf("获取第一个的位置的元素为：%d\n", *(int *) dataOfPosNode_LL(first_LL(list)));
    printf("获取索引为%d的位置的元素为：%d 的下一个元素：%d 和下一个元素：%d\n", index,
           *(int *) dataOfPosNode_LL(pos), *(int *) dataOfPosNode_LL(advance_LL(pos)),
           *(int *) dataOfPosNode_LL(advance_LL(advance_LL(pos))));
    printf("链表的数据元素为：\n");
    showList_LL(list);

    printf("链表的第一个节点是否是头节点：%s，是否是最后一个节点：%s\n",
           isHead_LL(list, header_LL(list)) ? "是" : "否", isLast_LL(list, header_LL(list)) ? "是" : "否");

    index = 12;
    pos = get_LL(list, index);
    printf("删除索引为%d的元素：%d\n", index, *(int *) dataOfPosNode_LL(pos));
    delete_LL(list, pos->data);
    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    index = 6;
    pos = get_LL(list, index);
    printf("删除索引为%d的元素：%d\n", index, *(int *) dataOfPosNode_LL(pos));
    delete_LL(list, pos->data);
    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    printf("清空链表\n");
    clear_LL(list);
    printf("链表中的数据的个数为：%d\n", size_LL(list));
    printf("链表是否为空：%s\n", isEmpty_LL(list) ? "是" : "否");
    printf("链表的数据元素为：\n");
    showList_LL(list);

    puts("\n");
}


void testLinkedList2(void) {
    puts("**************************************************");
    puts("*                 双链表测试例程                   *");
    puts("**************************************************");
    int i;
    LinkedList2 list = newLinkedList2();

    int array1[10];
    int array2[10];

    for (i = 0; i < 10; i++) {
        array1[i] = i + 1;
        array2[i] = i + 100 + 1;
        addBack_LL2(list, &array1[i]);
    }

    printf("链表大小(SIZE): %d\n", size_LL2(list));

    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    printf("添加array2[0]数\n");
    addBack_LL2(list, &array2[0]);

    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    printf("调用AddFront函数，添加array2[0]数\n");
    addFront_LL2(list, &array2[1]);

    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    printf("从末尾移除的元素是: %d\n", *(int *) removeBack_LL2(list));
    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    printf("从开头移除的元素是: %d\n", *(int *) removeFront_LL2(list));
    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    printf("清空链表，Clear(list)后\n");
    clear_LL2(list);
    printf("链表大小(SIZE): %d\n", size_LL2(list));

    for (i = 0; i < 10; i++) {
        addFront_LL2(list, &array2[i]);
    }
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);

    destroy_LL2(list);
    printf("销毁链表Destroy(list)\n");

    puts("\n");
}

void testLinkedListO(void) {
    puts("**************************************************");
    puts("*               单循环链表测试例程                 *");
    puts("**************************************************");

    Criculist list = newLinkedListO();
    int initData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        add_LLO(list, &initData[i]);
    }

    printf("链表的长度为：%d\n", size_LLO(list));
    showList_LLO(list);

    int pos = 1, data = 10;
    printf("在位置为%d的后面插入%d\n", pos, data);
    insert_LLO(list, pos, &data);

    printf("链表的长度为：%d，", size_LLO(list));
    showList_LLO(list);

    int dataOfFind = 6;
    printf("元素%d在链表中的位置是：%d\n", dataOfFind, indexOf_LLO(list, &dataOfFind));

    DataType_LLO dataOfDelete = (DataType_LLO) malloc(sizeof(int));
    int posOfDelete = 2;
    printf("删除第%d个位置上的元素\n", posOfDelete);
    delete_LLO(list, posOfDelete, dataOfDelete);
    printf("删除的元素是：%d\n", *dataOfDelete);

    printf("该链表的长度为：%d，", size_LLO(list));
    showList_LLO(list);

    printf("元素%d在链表中的位置是：%d\n", dataOfFind, indexOf_LLO(list, &dataOfFind));

    puts("\n");
}

void testLinkedList2O(void) {
    puts("**************************************************");
    puts("*               双循环链表测试例程                 *");
    puts("**************************************************");

    ListTestExample();

    puts("\n");
}


void testArrayStack(void) {
    puts("**************************************************");
    puts("*                 顺序栈测试例程                   *");
    puts("**************************************************");

    ArrayStackPtr stack = (ArrayStackPtr) malloc(sizeof(ArrayStack));
    printf("初始化栈%s\n", initStack_AS(stack) ? "成功" : "失败");
    printf("存放元素\n");

    printf("栈的目前容量为：%d\n", capcity_AS(stack));

    for (int i = 0; i < 15; i++) {
        push_AS(stack, i + 1);
    }

    printf("栈的目前容量为：%d\n", capcity_AS(stack));
    printf("栈的元素个数是：%d\n", size_AS(stack));
    printf("栈中的元素是：\n");
    showStack_AS(stack);

    printf("弹出栈顶元素：%d\n", topAndPop_AS(stack));
    printf("栈的元素个数是：%d\n", size_AS(stack));
    printf("栈中的元素是：\n");
    showStack_AS(stack);

    printf("弹出栈顶元素，并不返回栈顶元素\n");
    pop_AS(stack);
    printf("栈的元素个数是：%d\n", size_AS(stack));
    printf("栈中的元素是：\n");
    showStack_AS(stack);

    printf("栈%s\n", isEmpty_AS(stack) ? "为空" : "不为空");
    printf("清空栈中所有的元素\n");
    clear_AS(stack);
    printf("栈中的元素是：\n");
    showStack_AS(stack);
    printf("栈%s\n", isEmpty_AS(stack) ? "为空" : "不为空");
    printf("栈的目前容量为：%d\n", capcity_AS(stack));

    printf("向栈中存放元素\n");
    for (int i = 0; i < 15; i++) {
        push_AS(stack, i + 1);
    }
    printf("栈中的元素是：\n");
    showStack_AS(stack);
    printf("栈%s\n", isEmpty_AS(stack) ? "为空" : "不为空");
    printf("栈的目前容量为：%d\n", capcity_AS(stack));

    printf("销毁栈\n");
    destory_AS(stack);

    puts("\n");
}

void testLinkedStack(void) {
    puts("**************************************************");
    puts("*                  链栈测试例程                   *");
    puts("**************************************************");

    LinkedStackPtr stack = (LinkedStackPtr) malloc(sizeof(LinkedStack));
    printf("初始化栈%s\n", initLinedStack(stack) ? "成功" : "失败");
    printf("存放元素\n");
    printf("栈%s\n", isEmpty_LS(stack) ? "为空" : "不为空");

    printf("栈的元素个数是：%d\n", size_LS(stack));
    for (int i = 0; i < 15; i++) {
        push_LS(stack, i + 1);
    }
    printf("栈的元素个数是：%d\n", size_LS(stack));
    printf("栈中的元素是：\n");
    showStack_LS(stack);

    printf("弹出栈顶元素\n");
    pop_LS(stack);
    printf("栈的元素个数是：%d\n", size_LS(stack));
    printf("栈中的元素是：\n");
    showStack_LS(stack);

    printf("再次弹出栈顶元素，元素是：%d\n", topAndPop_LS(stack));
    printf("栈的元素个数是：%d\n", size_LS(stack));
    printf("栈中的元素是：\n");
    showStack_LS(stack);

    printf("清空栈%s\n", clear_LS(stack) ? "成功" : "失败");
    printf("栈的元素个数是：%d\n", size_LS(stack));
    printf("栈中的元素是：\n");
    showStack_LS(stack);

    for (int i = 0; i < 15; i++) {
        push_LS(stack, i + 1);
    }
    printf("栈的元素个数是：%d\n", size_LS(stack));
    printf("栈中的元素是：\n");
    showStack_LS(stack);

    puts("\n");
}

void testArrayQueueO(void) {
    puts("**************************************************");
    puts("*                循环队列测试例程                  *");
    puts("**************************************************");

    ArrayQueue queue = newQueue_AQ(20);
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");

    printf("初始化队列\n");
    for (int i = 0; i < 20; i++) {
        enqueue_AQ(queue, i + 1);
    }
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("出队并不打印元素！%s\n", dequeue_AQ(queue) ? "出队完成" : "出队失败");
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("出队并打印元素，出队的元素是：%d\n", frontAndDequeue_AQ(queue));
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("打印当前队列的最前面的一个元素：%d\n", front_AQ(queue));
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("入队一个元素：102，%s\n", enqueue_AQ(queue, 102) ? "入队成功" : "入队失败");
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("清空队列\n");
    clear_AQ(queue);
    printf("元素的个数：%d\n", size_AQ(queue));
    printf("队列的总容量%d\n", capacty_AQ(queue));
    printf("队列是否满：%s\n", isFull_AQ(queue) ? "是" : "否");
    printf("队列的元素有：\n");
    showQueue_AQ(queue);

    printf("销毁队列\n");
    disposeQueue_AQ(queue);

    puts("\n");
}

void testLinkedQueue(void) {
    puts("**************************************************");
    puts("*                  链队测试例程                   *");
    puts("**************************************************");

    LinkedQueue queue = newLinkedQueue();
//    printf("链队初始化%s\n", initLinkedQueue(queue) ? "成功" : "失败");
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));

    printf("入队20个元素\n");
    int tempData[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int i = 0; i < 20; i++) {
        enqueue_LQ(queue, &tempData[i]);
    }
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    printf("出队并不打印元素！%s\n", dequeue_LQ(queue) ? "出队完成" : "出队失败");
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    printf("出队并打印元素，出队的元素是：%d\n", *(int *) frontAndDequeue_LQ(queue));
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    printf("打印当前队列的最前面的一个元素：%d\n", *(int *) front_LQ(queue));
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    int num = 102;
    printf("入队一个元素：102，%s\n", enqueue_LQ(queue, &num) ? "入队成功" : "入队失败");
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    printf("清空队列\n");
    clear_LQ(queue);
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    int datas[6] = {100, 101, 102, 103, 104, 105};
    printf("入队一个元素：100，%s\n", enqueue_LQ(queue, &datas[0]) ? "入队成功" : "入队失败");
    printf("入队一个元素：101，%s\n", enqueue_LQ(queue, &datas[1]) ? "入队成功" : "入队失败");
    printf("入队一个元素：102，%s\n", enqueue_LQ(queue, &datas[2]) ? "入队成功" : "入队失败");
    printf("入队一个元素：103，%s\n", enqueue_LQ(queue, &datas[3]) ? "入队成功" : "入队失败");
    printf("入队一个元素：104，%s\n", enqueue_LQ(queue, &datas[4]) ? "入队成功" : "入队失败");
    printf("入队一个元素：105，%s\n", enqueue_LQ(queue, &datas[5]) ? "入队成功" : "入队失败");
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);

    printf("销毁队列\n");
    dispose_LQ(queue);
    printf("销毁队列完成\n");

    puts("\n");
}





















