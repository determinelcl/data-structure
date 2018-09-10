//
// Created by determination on 2018/9/10.
//

#ifndef HELLO_GENERIC_H
#define HELLO_GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#define CASE_TYPE *(int *)
#define PRINT_FMT(data) printf("%d\t", CASE_TYPE (data))

typedef enum {
    EQUAL, GT, LT
} Comparable;

/**
 * 用于比较两种数据是否相等分别用于返回枚举
 */
#define COMPARE_WITH(data, another) \
    (CASE_TYPE (data) == CASE_TYPE (another) ? EQUAL\
    :\
    (CASE_TYPE (data) > CASE_TYPE (another) ? GT : LT))



#endif //HELLO_GENERIC_H
