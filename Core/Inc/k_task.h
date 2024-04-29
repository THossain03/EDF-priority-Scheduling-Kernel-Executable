/*
 * k_task.h
 *
 *  Created on: Jan 5, 2024
 *      Author: nexususer
 *
 *      NOTE: any C functions you write must go into a corresponding c file that you create in the Core->Src folder
 */

#ifndef INC_K_TASK_H_
#define INC_K_TASK_H_


// TCB BLOCK

typedef struct task_control_block{
	void (*ptask)(void* args); //entry address
	long unsigned int* stack_high; //starting address (high address)
	long unsigned int* stack_location; //Current location of thread stack
	int tid; //task ID
	char state; //task's state
	short stack_size; //stack size. Must be a multiple of 8
}TCB;



//KERNEL API FUNCTIONS
void osKernelInit(void);
int osCreateTask (TCB* task);
int osKernelStart(void);
void osYield(void);
int osTaskInfo(int TID, TCB* task_copy);
int osTaskExit(void);
int osScheduler(void);
int osSchedulerExit(void);

void setStack(void);
void setStackExit(void);
void setStackFirst(void);



#endif /* INC_K_TASK_H_ */
