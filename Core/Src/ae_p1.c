#include <stdio.h>
#include <stdlib.h>
#include "ae.h"

int x = 0;
int y = 0;
int finished = 0;
void *ptr;

extern unsigned long global;

void print_ptr_addr(void *ptr, int ptr_num) {
	if (ptr == NULL) {
		printf("%d. Unable to be allocated: ptr%d\r\n", ptr_num, ptr_num);
	} else {
		printf("%d. Address of ptr%d: %p\r\n", ptr_num, ptr_num, ptr);
	}
}

void free_blocks(int num, int expected) {
	printf("Free blocks under %d should be %d: %d\r\n", num, expected, k_mem_count_extfrag(num));
}

void single_task(void* args){
	while(1){
		if(x == 0) {
			printf("Opening Task 1 for Execution : %lu ms\r\n", global);
		}
		printf("Hello world Task 1\r\n"); //produce three
		for(int i = 0; i < 10000000; i++);
		if (x == 2) {
			x = 0;
			printf("Yielding Task 1 until deadline at : %lu ms\r\n", global);
			osPeriodYield();
		} else {
			x++;
		}
	}
}

void single_task2(void* args){
	while(1){
		if(y == 0) {
			printf("Opening Task 2 for Execution : %lu ms\r\n", global);
		}
		printf("Hello, world Task 2\r\n"); //should print twice .
		for(int i = 0; i < 5000000; i++);
		if (y == 2) {
			y = 0;
			printf("Yielding Task 2 until deadline at : %lu ms\r\n", global);
			osPeriodYield();
		} else {
			y++;
		}
	}
}

void third_task(void* args){
	while(1)
	{
		for(int i = 0; i < 100000; i++){
			if(i == (100000 - 1)){
				osCreateDeadlineTask(2000, 0x400, &task4);
			}
		}
		osPeriodYield();
	}
}

void task_in_task(void* args){
	printf("reached second task/r/n");
	osTaskExit();
}

void first_task(void*args)
{
	while(1){
		printf("Hello, world!\r\n");

		if(x > 10)
			osTaskExit();
		osYield();
	}
}

void second_task(void* args)
{
	TCB myTCB;
	while(1){
		printf("There we go\r\n");
	    osTaskInfo(0,&myTCB);
	    printf("x is: %d\r\n",x);
		osYield();
	}
}

void simple_test(void* args) {
	free_blocks(48201,1);

	void* ptr1 = k_mem_alloc(9604);
	print_ptr_addr(ptr1,1);
	free_blocks(48201,1);

	void* ptr2 = k_mem_alloc(9604);
	print_ptr_addr(ptr2,2);
	free_blocks(48201,1);

	void* ptr3 = k_mem_alloc(9604);
	print_ptr_addr(ptr3,3);
	free_blocks(48201,1);

	void* ptr4 = k_mem_alloc(9604);
	print_ptr_addr(ptr4,4);
	free_blocks(48201,1);

	void* ptr5 = k_mem_alloc(9644);
	print_ptr_addr(ptr5,5);
	free_blocks(48201,0);

	int status = k_mem_dealloc(ptr2);
	if (status) {
		printf("Successful Deallocation ptr2\r\n");
	} else {
		printf("Unsuccessful Deallocation ptr2\r\n");
	}

	status = k_mem_dealloc(ptr4);
	if (status) {
		printf("Successful Deallocation ptr4\r\n");
	} else {
		printf("Unsuccessful Deallocation ptr4\r\n");
	}


	status = k_mem_dealloc(ptr3);
	if (status) {
		printf("Successful Deallocation ptr3\r\n");
	} else {
		printf("Unsuccessful Deallocation ptr3\r\n");
	}


	status = k_mem_dealloc(ptr1);
	if (status) {
		printf("Successful Deallocation ptr1\r\n");
	} else {
		printf("Unsuccessful Deallocation ptr1\r\n");
	}


	status = k_mem_dealloc(ptr5);
	if (status) {
		printf("Successful Deallocation ptr5\r\n");
	} else {
		printf("Unsuccessful Deallocation ptr5\r\n");
	}

	free_blocks(33,0);
	free_blocks(48201,1);

	osTaskExit();
}

// Memory Manager Test
void memory_test_task1(void* args) {

	void* ptr1 = k_mem_alloc(16040);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr1,1);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr2 = k_mem_alloc(16040);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr2,2);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr3 = k_mem_alloc(16036);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr3,3);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	void* ptr4 = k_mem_alloc(15992);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr4,4);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	void* ptr5 = k_mem_alloc(1);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr5,5);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	k_mem_dealloc(ptr3);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr3.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	k_mem_dealloc(ptr2);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr2.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr6 = k_mem_alloc(32105);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr6,6);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr8 = k_mem_alloc(32072);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr8,8);
	free_blocks(33,1);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr9 = k_mem_alloc(8);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr9,9);
	free_blocks(33,1);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	void* ptr10 = k_mem_alloc(1);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr10,10);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	k_mem_dealloc(ptr1);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr1.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	k_mem_dealloc(ptr10);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr10.\r\n");
	free_blocks(33,1);
	free_blocks(5357,1);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,2);

	void* ptr11 = k_mem_alloc(5328);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr11,11);
	free_blocks(33,1);
	free_blocks(5357,1);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,2);

	void* ptr12 = k_mem_alloc(5328);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr12,12);
	free_blocks(33,1);
	free_blocks(5357,2);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,2);

	k_mem_dealloc(ptr11);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr11.\r\n");
	free_blocks(33,1);
	free_blocks(5357,3);
	free_blocks(16069,3);
	free_blocks(32137,3);
	free_blocks(48201,3);

	void* ptr13 = k_mem_alloc(4);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr13,13);
	free_blocks(33,1);
	free_blocks(5357,3);
	free_blocks(16069,3);
	free_blocks(32137,3);
	free_blocks(48201,3);

	k_mem_dealloc(ptr8);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr8.\r\n");
	free_blocks(33,0);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,2);

	void* ptr14 = k_mem_alloc(37461);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr14,14);
	free_blocks(33,0);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,2);

	void* ptr15 = k_mem_alloc(37427);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr15,15);
	free_blocks(33,1);
	free_blocks(5357,2);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,2);

	void* ptr16 = k_mem_alloc(4);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr16,16);
	free_blocks(33,1);
	free_blocks(5357,2);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,2);

	k_mem_dealloc(ptr13);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr13.\r\n");
	free_blocks(33,2);
	free_blocks(5357,3);
	free_blocks(16069,3);
	free_blocks(32137,3);
	free_blocks(48201,3);

	k_mem_dealloc(ptr15);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr15.\r\n");
	free_blocks(33,1);
	free_blocks(5357,2);
	free_blocks(16069,2);
	free_blocks(32137,2);
	free_blocks(48201,3);

	k_mem_dealloc(ptr16);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr16.\r\n");
	free_blocks(33,0);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,2);

	void* ptr17 = k_mem_alloc(37460);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr17,17);
	free_blocks(33,0);
	free_blocks(5357,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	k_mem_dealloc(ptr12);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr12.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	/* ext_frag testing next two lines */
	free_blocks(10712,0);
	free_blocks(10713,1);
	free_blocks(16069,1);
	free_blocks(32137,1);
	free_blocks(48201,1);

	k_mem_dealloc(ptr17);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr17.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,1);

	void* ptr18 = k_mem_alloc(48173);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr18,18);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,1);

	void* ptr19 = k_mem_alloc(48145);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr19,19);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	void* ptr20 = k_mem_alloc(4);
	//for(int i = 0; i < 2500000; i++);
	print_ptr_addr(ptr20,20);
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,0);

	k_mem_dealloc(ptr19);
	//for(int i = 0; i < 2500000; i++);
	printf("Deallocated ptr19.\r\n");
	free_blocks(33,0);
	free_blocks(5357,0);
	free_blocks(16069,0);
	free_blocks(32137,0);
	free_blocks(48201,1);

	osTaskExit();
}


