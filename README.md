#data-structure

####数据结构C实现的简单汇总

+ table文件夹说明
+ test文件夹说明
+ CMakeLists.txt文件说明

#### 1、table文件夹说明

此文件夹用于存放表的定义和实现，此文件夹中的文件名命名规则全英文单词夹几个简单缩写符号

| 符号 | 释义 |
|:----:|:---:|
|array | 表示为数组实现|
|linked | 表示为指针实现 |
| _o | 表示为循环的表 |
| 2 | 表示双链表思实现 |

#### 2、test文件夹说明

此文件夹为测试单元所存饭的位置，此文件夹的文件命名规则为`模块名+_test`即可


#### 3、CMakeLists.txt文件说明

-- CMake的语法参考Jetbrain的
[Clion -- Quick CMake Tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html)
的教程即可 --

这里仅仅对CMakeLists中的部分变量的命名规则进行说明

|  变量  | 释义 |
|:-----:|:----:|
|TABLE_ADT| 标识table模块下的文件名称宏 |
|TABLE_TEST_ADT | 标识test模块下的文件名称宏|

 









