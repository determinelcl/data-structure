//
//  table_test.c
//  data-structure
//
//  Created by determination on 2018/8/25.
//  Copyright © 2018年 determination. All rights reserved.
//

#include "table_test.h"

static char* answer(bool rs)
{
    return rs ? "yes" : "no";
}

void testArrayList(void)
{
    ArrayList arrayList;
    DataType_AL data;
    //    ElemType* temp;
    //1.初始化
    newArrayList(&arrayList);
    printf("初始化顺序表：size = %d, length = %d\n", arrayList.capacity, arrayList.length);
    showList_AL(&arrayList);
    printf("\n是否为空表？%s\n", answer(isEmpty_AL(&arrayList)));
    int i = 0;
    //2.插入元素
    while(i < 20)
    {
        insert_AL(&arrayList, i+1, i);
        i++;
    }
    showList_AL(&arrayList);
    //3.根据位置返回元素

    get_AL(&arrayList, 6, &data);
    printf("\n第6个元素是: %d\n", data);

    //4.查找某个元素是否存在
    printf("\n6是否存在于表中？ %s\n", answer(isExist_AL(&arrayList, 6)));
    printf("\n21是否存在于表中？ %s\n", answer(isExist_AL(&arrayList, 21)));
    printf("\n是否为空表？ %s\n", answer(isEmpty_AL(&arrayList)));

    //5.删除元素
    remove_AL(&arrayList, 11, &data);
    printf("\n被删除的元素是：%d\n", data);
    printf("删除之后的元素序列为：");
    showList_AL(&arrayList);

    remove_AL(&arrayList, 11, &data);
    printf("\n被删除的元素是：%d\n", data);
    printf("删除之后的元素序列为：");
    showList_AL(&arrayList);
    
    //6.清空顺序表
    printf("执行清空之后:");
    clear_AL(&arrayList);
    insert_AL(&arrayList, 1, 1); //执行清空之后仍可插入
    showList_AL(&arrayList);

    //7.销毁顺序表
    printf("执行销毁之后：");
    
    destory_AL(&arrayList); //销毁只是回收了分配给线性表的空间，而arrayList变量依然存在，仍然可以访问arrayList.size等成员变量
    showList_AL(&arrayList);
    
    i = 0;
    while(i < 1)
    {
        insert_AL(&arrayList, i+1, i);
        i++;
    }
    insert_AL(&arrayList, 1, 6); //销毁之后再插入可能出现异常，因为地址已经被标记为可以被其他程序使用，当使用已经被占用的内存地址就会发生错误
    showList_AL(&arrayList);
    
}

void testLinkedList2(void)
{
    int i;
    LinkedList2 list = newLinkedList2();
    
    int array1[10];
    int array2[10];
    
    for(i=0; i<10; i++)
    {
        array1[i] = i+1;
        array2[i] = i+100+1;
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
    
    printf("从末尾移除的元素是: %d\n", *(int *)removeBack_LL2(list));
    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);
    
    printf("从开头移除的元素是: %d\n", *(int *)removeFront_LL2(list));
    printf("链表大小(SIZE): %d\n", size_LL2(list));
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);
    
    printf("清空链表，Clear(list)后\n");
    clear_LL2(list);
    printf("链表大小(SIZE): %d\n", size_LL2(list));
    
    for(i=0; i<10; i++)
    {
        addFront_LL2(list, &array2[i]);
    }
    printf("正向打印链表:\n");
    traverse_LL2(list);
    printf("反向打印链表:\n");
    rTraverse_LL2(list);
    
    destroy_LL2(list);
    printf("销毁链表Destroy(list)\n");

}

void testLinkedListO(void)
{
    Criculist list = newLinkedListO();
    int initData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        add_LLO(list, &initData[i]);
    }
    
    printf("链表的长度为：%d\n", size_LLO(list));
    showList_LLO(list);
    
    int pos = 1, data = 10;
    printf( "在位置为%d的后面插入%d\n", pos, data);
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
}

void testLinkedList2O(void)
{
    ListTestExample();
}


void testArrayStack(void)
{
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
}

void testLinkedStack(void)
{
    printf("===========================链式栈==============================\n");
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
}

void testArrayQueueO(void)
{
    printf("=================循环队列（数组实现）测试===============\n");
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
}

void testLinkedQueue(void)
{
    printf("============================链队测试例程=======================\n");
    
    LinkedQueue queue = (LinkedQueue) malloc(sizeof(Queue_LQ));
    printf("链队初始化%s\n", initLinkedQueue(queue) ? "成功" : "失败");
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    
    printf("入队20个元素\n");
    for (int i = 0; i < 20; i++) {
        enqueue_LQ(queue, &i);
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
    
    printf("出队并打印元素，出队的元素是：%d\n", *(int *)frontAndDequeue_LQ(queue));
    printf("队列是否为空：%s\n", isEmpty_LQ(queue) ? "是" : "否");
    printf("队列的元素个数：%d\n", size_LQ(queue));
    printf("队列中的元素是：\n");
    showLinkedQueue_LQ(queue);
    
    printf("打印当前队列的最前面的一个元素：%d\n", *(int *)front_LQ(queue));
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
}





















