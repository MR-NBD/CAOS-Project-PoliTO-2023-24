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

//waiting time, turnaround time and response time of the different tasks
TickType_t wt1_rr, wt2_rr, wt3_rr, tt1_rr, tt2_rr, tt3_rr, rt1_rr, rt2_rr, rt3_rr;    


void main_rr( void )
{
		xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY, NULL );
		xTaskCreate( statistics, "statistics", configMINIMAL_STACK_SIZE, NULL, mainTASK_PRIORITY-1, NULL );   //it must run after the three tasks so it has a lower priority
		
		/* Start the tasks and timer running. */
		vTaskStartScheduler();
}

static void task1(void *pvParameters){
	TickType_t task1Start = xTaskGetTickCount();    //saving the starting time of the task
	TickType_t task1Restart = task1Start;           //saving the last time the task started
	wt1_rr = task1Start;							//the waiting time at this moment is equal to the start time
	TickType_t task1Stop;
	printf("Task1 started at time %dms\n", pdTICKS_TO_MS(task1Start));
	while (xTaskGetTickCount() - wt1_rr < pdMS_TO_TICKS(1200)){          		//the task must last 1200 ms
	//if the difference between the current time and the last time the task started is >= 100ms a context switch must occur
		if ((xTaskGetTickCount() - task1Restart) >= pdMS_TO_TICKS(100UL) && xTaskGetTickCount() - wt1_rr < pdMS_TO_TICKS(1200)){
			task1Stop = xTaskGetTickCount();									//saving the stopping time
			printf("Task1 stopped at time %dms\n", pdTICKS_TO_MS(task1Stop));
			taskYIELD();														//force a context switch
			task1Restart = xTaskGetTickCount();									//update the restarting time
			printf("Task1 restarted at time %dms\n", pdTICKS_TO_MS(task1Restart));
			wt1_rr += task1Restart - task1Stop;  								//increment the waiting time
		}
	}
	tt1_rr = xTaskGetTickCount();
	rt1_rr = task1Start;
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
		if ((xTaskGetTickCount() - task2Restart) >= pdMS_TO_TICKS(100UL) && xTaskGetTickCount() - wt2_rr < pdMS_TO_TICKS(300)){
			task2Stop = xTaskGetTickCount();
			printf("Task2 stopped at time %dms\n", pdTICKS_TO_MS(task2Stop));
			taskYIELD();
			task2Restart = xTaskGetTickCount();
			printf("Task2 restarted at time %dms\n", pdTICKS_TO_MS(task2Restart));
			wt2_rr += task2Restart - task2Stop;
		}
	}
	tt2_rr = xTaskGetTickCount();
	rt2_rr = task2Start;
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
		if ((xTaskGetTickCount() - task3Restart) >= pdMS_TO_TICKS(100UL) && xTaskGetTickCount() - wt3_rr < pdMS_TO_TICKS(600)){
			task3Stop = xTaskGetTickCount();
			printf("Task3 stopped at time %dms\n", pdTICKS_TO_MS(task3Stop));
			taskYIELD();
			task3Restart = xTaskGetTickCount();
			printf("Task3 restarted at time %dms\n", pdTICKS_TO_MS(task3Restart));
			wt3_rr += task3Restart - task3Stop;
		}
	}
	tt3_rr = xTaskGetTickCount();
	rt3_rr = task3Start;
	printf("Task3 finished at time %dms\n", pdTICKS_TO_MS(tt3_rr));
	vTaskDelete(NULL);
}

static void statistics(void *pvParameters){		//this task print the statistics of the tasks 
	printf("Waiting time task1 = %dms, turnaround time = %dms, response time = %dms\n", pdTICKS_TO_MS(wt1_rr), pdTICKS_TO_MS(tt1_rr), pdTICKS_TO_MS(rt1_rr));
	printf("Waiting time task2 = %dms, turnaround time = %dms, response time = %dms\n", pdTICKS_TO_MS(wt2_rr), pdTICKS_TO_MS(tt2_rr), pdTICKS_TO_MS(rt2_rr));
	printf("Waiting time task3 = %dms, turnaround time = %dms, response time = %dms\n", pdTICKS_TO_MS(wt3_rr), pdTICKS_TO_MS(tt3_rr), pdTICKS_TO_MS(rt3_rr));
	printf("Average Waiting Time = %dms, average Turnaround Time = %dms, average Response Time = %dms\n", (wt1_rr+wt2_rr+wt3_rr)/3, (tt1_rr+tt2_rr+tt3_rr)/3, (rt1_rr+rt2_rr+rt3_rr)/3);
	vTaskDelete(NULL);
}
/*-----------------------------------------------------------*/


