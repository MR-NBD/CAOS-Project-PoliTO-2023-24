/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

/* Priorities at which the tasks are created. */
#define	mainTASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

static void task1(void *pvParameters);
static void task2(void *pvParameters);
static void task3(void *pvParameters);
static void statistics(void *pvParameters);

TickType_t wt1_rr, wt2_rr, wt3_rr, tt1_rr, tt2_rr, tt3_rr;    //waiting time and turnaround time of the different tasks


void main_rr( void )
{
		xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( statistics, "statistics", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY-1, NULL );
		
		/* Start the tasks and timer running. */
		vTaskStartScheduler();
}

static void task1(void *pvParameters){
	TickType_t task1Start = xTaskGetTickCount();
	TickType_t task1Restart = task1Start;
	wt1_rr = task1Start;
	TickType_t task1Stop;
	printf("Task1 started at time %dms\n", pdTICKS_TO_MS(task1Start));
	while (xTaskGetTickCount() - wt1_rr < pdMS_TO_TICKS(1200)){
		if ((xTaskGetTickCount() - task1Restart) >= pdMS_TO_TICKS(100UL)){
			task1Stop = xTaskGetTickCount();
			printf("Task1 stopped at time %dms\n", pdTICKS_TO_MS(task1Stop));
			taskYIELD();
			task1Restart = xTaskGetTickCount();
			printf("Task1 restarted at time %dms\n", pdTICKS_TO_MS(task1Restart));
			wt1_rr += task1Restart - task1Stop;
		}
	}
	wt1_rr = pdTICKS_TO_MS(wt1_rr);
	tt1_rr = pdTICKS_TO_MS(xTaskGetTickCount());
	printf("Task1 finished at time %dms\n", pdTICKS_TO_MS(tt1_rr));
	vTaskDelete(NULL);
}

static void task2(void *pvParameters){
	TickType_t task2Start = xTaskGetTickCount();
	TickType_t task2Restart = task2Start;
	wt2_rr = task2Start;
	TickType_t task2Stop;
	printf("Task2 started at time %dms\n", pdTICKS_TO_MS(task2Start));
	while (xTaskGetTickCount() - wt2_rr < pdMS_TO_TICKS(300)){
		if ((xTaskGetTickCount() - task2Restart) >= pdMS_TO_TICKS(100UL)){
			task2Stop = xTaskGetTickCount();
			printf("Task2 stopped at time %dms\n", pdTICKS_TO_MS(task2Stop));
			taskYIELD();
			task2Restart = xTaskGetTickCount();
			printf("Task2 restarted at time %dms\n", pdTICKS_TO_MS(task2Restart));
			wt2_rr += task2Restart - task2Stop;
		}
	}
	wt2_rr = pdTICKS_TO_MS(wt2_rr);
	tt2_rr = pdTICKS_TO_MS(xTaskGetTickCount());
	printf("Task2 finished at time %dms\n", pdTICKS_TO_MS(tt2_rr));
	vTaskDelete(NULL);
}

static void task3(void *pvParameters){
	TickType_t task3Start = xTaskGetTickCount();
	TickType_t task3Restart = task3Start;
	wt3_rr = task3Start;
	TickType_t task3Stop;
	printf("Task3 started at time %dms\n", pdTICKS_TO_MS(task3Start));
	while (xTaskGetTickCount() - wt3_rr < pdMS_TO_TICKS(600)){
		if ((xTaskGetTickCount() - task3Restart) >= pdMS_TO_TICKS(100UL)){
			task3Stop = xTaskGetTickCount();
			printf("Task3 stopped at time %dms\n", pdTICKS_TO_MS(task3Stop));
			taskYIELD();
			task3Restart = xTaskGetTickCount();
			printf("Task3 restarted at time %dms\n", pdTICKS_TO_MS(task3Restart));
			wt3_rr += task3Restart - task3Stop;
		}
	}
	wt3_rr = pdTICKS_TO_MS(wt3_rr);
	tt3_rr = pdTICKS_TO_MS(xTaskGetTickCount());
	printf("Task3 finished at time %dms\n", pdTICKS_TO_MS(tt3_rr));
	vTaskDelete(NULL);
}

static void statistics(void *pvParameters){
	printf("Waiting time task1 = %dms, turnaround time = %dms\n", pdTICKS_TO_MS(wt1_rr), pdTICKS_TO_MS(tt1_rr));
	printf("Waiting time task2 = %dms, turnaround time = %dms\n", pdTICKS_TO_MS(wt2_rr), pdTICKS_TO_MS(tt2_rr));
	printf("Waiting time task3 = %dms, turnaround time = %dms\n", pdTICKS_TO_MS(wt3_rr), pdTICKS_TO_MS(tt3_rr));
	printf("Average Waiting Time = %dms, average Turnaround Time = %dms\n", (wt1_rr+wt2_rr+wt3_rr)/3, (tt1_rr+tt2_rr+tt3_rr)/3);
	vTaskDelete(NULL);
}
/*-----------------------------------------------------------*/


