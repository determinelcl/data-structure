cmake_minimum_required(VERSION 3.10)
project(hello C)

set(CMAKE_C_STANDARD 11)

include_directories(table test tree)
set(TABLE_ADT   table/array_list.h      table/array_list.c
                table/linked_list.h     table/linked_list.c
                table/linked_list2.h    table/linked_list2.c
                table/linked_list_o.h   table/linked_list_o.c
                table/linked_list2_o.h  table/linked_list2_o.c
                table/array_stack.h     table/array_stack.c
                table/linked_stack.h    table/linked_stack.c
                table/array_queue_o.h   table/array_queue_o.c
                table/linked_queue.h    table/linked_queue.c)


set(TREE_ADT    tree/binary_tree.h      tree/binary_tree.c
                tree/search_tree.h      tree/search_tree.c
                tree/avl_tree.h         tree/avl_tree.c
                tree/tree_generic.h                         )

set(TEST_ADT    test/table_test.h       test/table_test.c
                test/tree_test.h        test/tree_test.c)


add_executable(hello main.c ${TABLE_ADT} ${TREE_ADT} ${TEST_ADT} )