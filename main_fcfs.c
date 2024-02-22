/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/* Priorities at which the tasks are created. */
#define	mainTASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

static void task1(void *pvParameters);
static void task2(void *pvParameters);
static void task3(void *pvParameters);
static void statistics(void *pvParameters);

int wt1_fcfs, wt2_fcfs, wt3_fcfs, tt1_fcfs, tt2_fcfs, tt3_fcfs;   //waiting time and turnaround time of the different tasks

void main_fcfs( void )
{
		xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( statistics, "statistics", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY-1, NULL );

		/* Start the tasks and timer running. */
		vTaskStartScheduler();
}

static void task1(void *pvParameters){
	int i;
	TickType_t task1Start = xTaskGetTickCount();
	printf("Task1 started at time %dms\n", pdTICKS_TO_MS(task1Start));
	while (xTaskGetTickCount() - task1Start < pdMS_TO_TICKS(1200));
	TickType_t task1Stop = xTaskGetTickCount();
	printf("Task1 finished at time %dms\n", pdTICKS_TO_MS(task1Stop));
	wt1_fcfs = pdTICKS_TO_MS(task1Start);
	tt1_fcfs = pdTICKS_TO_MS(task1Stop);
	vTaskDelete(NULL);
}

static void task2(void *pvParameters){
	int i;
	TickType_t task2Start = xTaskGetTickCount();
	printf("Task2 started at time %dms\n", pdTICKS_TO_MS(task2Start));
	while (xTaskGetTickCount() - task2Start < pdMS_TO_TICKS(300));
	TickType_t task2Stop = xTaskGetTickCount();
	printf("Task2 finished at time %dms\n", pdTICKS_TO_MS(task2Stop));
	wt2_fcfs = pdTICKS_TO_MS(task2Start);
	tt2_fcfs = pdTICKS_TO_MS(task2Stop);
	//printf("Waiting time task2 = %dms, workaround time = %dms\n", pdTICKS_TO_MS(task2Start), pdTICKS_TO_MS(task2Stop));
	vTaskDelete(NULL);
}

static void task3(void *pvParameters){
	int i;
	TickType_t task3Start = xTaskGetTickCount();
	printf("Task3 started at time %dms\n", pdTICKS_TO_MS(task3Start));
	while (xTaskGetTickCount() - task3Start < pdMS_TO_TICKS(600));
	TickType_t task3Stop = xTaskGetTickCount();
	printf("Task3 finished at time %dms\n", pdTICKS_TO_MS(task3Stop));
	wt3_fcfs = pdTICKS_TO_MS(task3Start);
	tt3_fcfs = pdTICKS_TO_MS(task3Stop);
	//printf("Waiting time task3 = %dms, workaround time = %dms\n", pdTICKS_TO_MS(task3Start), pdTICKS_TO_MS(task3Stop));
	vTaskDelete(NULL);
}

static void statistics(void *pvParameters){
	printf("Waiting time task1 = %dms, workaround time = %dms\n", wt1_fcfs, tt1_fcfs);
	printf("Waiting time task2 = %dms, workaround time = %dms\n", wt2_fcfs, tt2_fcfs);
	printf("Waiting time task3 = %dms, workaround time = %dms\n", wt3_fcfs, tt3_fcfs);
	printf("Average Waiting Time = %dms, average Turnaround Time = %dms\n", (wt1_fcfs+wt2_fcfs+wt3_fcfs)/3, (tt1_fcfs+tt2_fcfs+tt3_fcfs)/3);
	vTaskDelete(NULL);
}
/*-----------------------------------------------------------*/


