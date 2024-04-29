#include "ae.h"
#include "ae_p1.h"
#include "k_task.h"
#include "k_mem.h"
void ae_init()
{
	osKernelInit();
	k_mem_init();
	#if TEST == 1
		TCB task1;
		TCB task2;
		TCB task3;
		TCB task4;
		task1.ptask=&single_task;
		task1.stack_size = 0x400;
		task2.ptask=&single_task2;
		task2.stack_size = 0x400;
		task3.ptask=&third_task;
		task3.stack_size = 0x400;
		task4.ptask = &task_in_task;
		task4.stack_size = 0x400;
		if (!osCreateDeadlineTask(12000, 0x400, &task1)) {
			printf("Create Task Error!\r\n");
			return;
		}
		if (!osCreateDeadlineTask(8000, 0x400, &task2)) {
			printf("Create Task Error!\r\n");
			return;
		}
		if (!osCreateDeadlineTask(5000, 0x400, &third_task)) {
			printf("Create Task Error!\r\n");
			return;
		}
	#elif TEST == 2
		TCB task2;
		task2.ptask=&first_task;
		task2.stack_size = 0x400;
		osCreateTask(&task2);
		TCB task3;
		task3.ptask = &second_task;
		task3.stack_size = 0x400;
		osCreateTask(&task3);
		TCB task4;
		task4.ptask = &third_task;
		task4.stack_size = 0x400;
		osCreateTask(&task4);
	#elif TEST == 3
		TCB task5;
		task5.ptask = &simple_test;
		task5.stack_size = 0x400;
		osCreateTask(&task5);
		//TCB task6;
		//task6.ptask = &memory_test_task2;
		//task6.stack_size = 0x400;
		//osCreateTask(&task6);
	#endif
	osKernelStart();

}

