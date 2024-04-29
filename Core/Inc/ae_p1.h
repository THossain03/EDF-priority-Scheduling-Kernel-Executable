#ifndef SRC_AE_P1_H_
#define SRC_AE_P1_H_

void print_ptr_addr(void* ptr, int ptr_num);
void free_blocks(int num, int expected);

void single_task(void* args);
void single_task2(void* args);
void first_task(void*args);
void second_task(void* args);
void third_task(void* args);
void task_in_task(void* args);
void simple_test(void* args);

void memory_test_task1(void* args);

#endif
