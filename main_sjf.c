/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/* Priorities at which the tasks are created. */
#define	TASK1_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	TASK2_PRIORITY		( tskIDLE_PRIORITY + 4 )
#define	TASK3_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define STAT_PRIORITY       ( tskIDLE_PRIORITY + 1 )

static void task1(void *pvParameters);
static void task2(void *pvParameters);
static void task3(void *pvParameters);
static void statistics(void *pvParameters);

int wt1_sjf, wt2_sjf, wt3_sjf, tt1_sjf, tt2_sjf, tt3_sjf;      //waiting time and turnaround time of the different tasks

void main_sjf( void )
{
		xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL );
		xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL );
		xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL );
		xTaskCreate( statistics, "statistics", configMINIMAL_STACK_SIZE, NULL, STAT_PRIORITY, NULL );

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
	wt1_sjf = pdTICKS_TO_MS(task1Start);
	tt1_sjf = pdTICKS_TO_MS(task1Stop);
	vTaskDelete(NULL);
}

static void task2(void *pvParameters){
	int i;
	TickType_t task2Start = xTaskGetTickCount();
	printf("Task2 started at time %dms\n", pdTICKS_TO_MS(task2Start));
	while (xTaskGetTickCount() - task2Start < pdMS_TO_TICKS(300));
	TickType_t task2Stop = xTaskGetTickCount();
	printf("Task2 finished at time %dms\n", pdTICKS_TO_MS(task2Stop));
	wt2_sjf = pdTICKS_TO_MS(task2Start);
	tt2_sjf = pdTICKS_TO_MS(task2Stop);
	vTaskDelete(NULL);
}

static void task3(void *pvParameters){
	int i;
	TickType_t task3Start = xTaskGetTickCount();
	printf("Task3 started at time %dms\n", pdTICKS_TO_MS(task3Start));
	while (xTaskGetTickCount() - task3Start < pdMS_TO_TICKS(600));
	TickType_t task3Stop = xTaskGetTickCount();
	printf("Task3 finished at time %dms\n", pdTICKS_TO_MS(task3Stop));
	wt3_sjf = pdTICKS_TO_MS(task3Start);
	tt3_sjf = pdTICKS_TO_MS(task3Stop);
	vTaskDelete(NULL);
}

static void statistics(void *pvParameters){
	printf("Waiting time task1 = %dms, workaround time = %dms\n", wt1_sjf, tt1_sjf);
	printf("Waiting time task2 = %dms, workaround time = %dms\n", wt2_sjf, tt2_sjf);
	printf("Waiting time task3 = %dms, workaround time = %dms\n", wt3_sjf, tt3_sjf);
	printf("Average Waiting Time = %dms, average Turnaround Time = %dms\n", (wt1_sjf+wt2_sjf+wt3_sjf)/3, (tt1_sjf+tt2_sjf+tt3_sjf)/3);
	vTaskDelete(NULL);
}
/*-----------------------------------------------------------*/


