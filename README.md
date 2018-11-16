# data-structure

#### 数据结构C实现的简单汇总

+ graph模块
+ table模块
+ test模块
+ tree模块
+ CMakeLists.txt文件

#### 1、graph模块

图模块：用于存放图的定义和实现

|图结构名称|释义|
|:----:|---|
|adj_matrix_graph|邻接矩阵存储结构|
|adj_mult_graph|邻接多重表存储结构|
|adj_table_graph|邻接表存储结构|
|cross_list_graph|十字链表存储结构|
|graph_generic|graph模块的通用头文件|

#### 2、table模块

线性表模块：用于存放线性表的定义和实现

| 线性表名称 | 释义 |
|:----:|---|
|array_list|顺序表|
|array_queue_o|顺序循环队列 |
|array_stack|顺序栈|
|linked_list|单链表|
|linked_list2|双链表|
|linked_list2_o|双循环链表|
|linked_list_o|单循环链表|
|linked_queue|链式队列|
|linked_stack|链式栈|

#### 3、test模块

测试驱动模块：测试单元程序的定义和实现

|测试单元名称|释义|
|:----:|---|
|graph_test|图的测试驱动|
|table_test|线性表测试驱动|
|tree_test|树的测试驱动|

#### 4、tree模块

树模块：树结构的定义和实现

|树结构名称|释义|
|:----:|---|
|avl_tree|AVL平衡树|
|binary_tree|链式存储的二叉树，功能较弱|
|huffman_tree|Huffman树|
|search_tree|链式存储二叉搜索树，建议用它<br>来研究二叉树的链式存储结构|
|seq_bi_tree|顺序存储的二叉树，功能较弱|
|tree_generic|tree模块的通用头文件|


#### 5、CMakeLists.txt文件

- CMake的语法参考Jetbrain的
[Clion -- Quick CMake Tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)
的教程即可 

表中列出了CMakeLists中的部分变量的命名规则进行说明

|  变量  | 释义 |
|:-----:|----|
|TABLE_ADT| 标识table模块下的文件名称宏 |
|TABLE_TEST_ADT | 标识test模块下的文件名称宏|
|TREE_ADT|标示tree模块下的文件名称宏|
|GRAPH_ADT|标示graph模块下的文件名称宏|

 









