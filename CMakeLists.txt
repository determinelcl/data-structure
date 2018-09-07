cmake_minimum_required(VERSION 3.10)
project(hello C)

set(CMAKE_C_STANDARD 11)

include_directories(table test)
set(TABLE_ADT table/array_list.h      table/array_list.c
                table/linked_list.h     table/linked_list.c
                table/linked_list2.h    table/linked_list2.c
                table/linked_list_o.h   table/linked_list_o.c
                table/linked_list2_o.h  table/linked_list2_o.c
                table/array_stack.h     table/array_stack.c
                table/linked_stack.h    table/linked_stack.c
                table/array_queue_o.h   table/array_queue_o.c
                table/linked_queue.h    table/linked_queue.c)

set(TABLE_TEST_ADT test/table_test.h test/table_test.c)
add_executable(hello main.c ${TABLE_ADT} ${TABLE_TEST_ADT})