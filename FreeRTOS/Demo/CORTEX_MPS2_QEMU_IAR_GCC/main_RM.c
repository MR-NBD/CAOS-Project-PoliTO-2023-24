/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "stdarg.h"

/* Priorities at which the tasks are created. */
#define	TASK1_PRIORITY		( tskIDLE_PRIORITY + 3 )
#define	TASK2_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	TASK3_PRIORITY		( tskIDLE_PRIORITY + 1 )

static void task1(void *pvParameters);
static void task2(void *pvParameters);
static void task3(void *pvParameters);
static void taskIdle(void *pvParameters);
static void timer1func(void *parameters);
static void timer2func(void *parameters);
static void timer3func(void *parameters);
static void timer4func(void* parameters);
extern char* division(int num, int den, int prec);
int CPUIdle = 0;
int CPUnotIdle = 0;
TaskHandle_t handle;
TaskStatus_t status;

void main_RM( void )
{
		xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL );  //T=40ms WCET=20ms 
		xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL );  //T=80ms WCET=10ms 
		xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL );  //T=120ms WCET=10ms
		handle = xTaskCreate( taskIdle, "TIdle", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );  

        TimerHandle_t timer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(40), pdTRUE, NULL, timer1func);
		xTimerStart(timer1, 0);
        TimerHandle_t timer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(80), pdTRUE, NULL, timer2func);
		xTimerStart(timer2, 0);
        TimerHandle_t timer3 = xTimerCreate("Timer3", pdMS_TO_TICKS(120), pdTRUE, NULL, timer3func);
		xTimerStart(timer3, 0);
		TimerHandle_t timer4 = xTimerCreate("Timer4", pdMS_TO_TICKS(5000), pdTRUE, NULL, timer4func);
		xTimerStart(timer4, 0);
		/* Start the tasks and timer running. */
		vTaskStartScheduler();
}

static void task1(void *pvParameters){
	TickType_t task1Start = xTaskGetTickCount();
	printf("Task1 started at %d ms\n", pdTICKS_TO_MS(task1Start));
	for (int i=0; i<700000; i++){
			CPUnotIdle+=1;
	}
	printf("Task1 finished at %d ms\n", pdTICKS_TO_MS(xTaskGetTickCount()));
	vTaskDelete(NULL);
}

static void timer1func(void* parameters){
    xTaskCreate( task1, "T1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL );
}

static void task2(void *pvParameters){
	TickType_t task2Start = xTaskGetTickCount();
	printf("Task2 started at %d ms\n", pdTICKS_TO_MS(task2Start));
	for (int i=0; i<500000; i++){
		CPUnotIdle+=1;
	}
	printf("Task2 finished at %d ms\n", pdTICKS_TO_MS(xTaskGetTickCount()));
	vTaskDelete(NULL);
}

static void timer2func(void* parameters){
    xTaskCreate( task2, "T2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL );
}

static void task3(void *pvParameters){
	TickType_t task3Start = xTaskGetTickCount();
	printf("Task3 started at %d ms\n", pdTICKS_TO_MS(task3Start));
	for (int i=0; i<500000; i++){
			CPUnotIdle+=1;
	}
	printf("Task3 finished at %d ms\n", pdTICKS_TO_MS(xTaskGetTickCount()));
	vTaskDelete(NULL);
}

static void timer3func(void* parameters){
    xTaskCreate( task3, "T3", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, NULL );
}

static void taskIdle(void *pvParameters){
	while(1){
		CPUIdle+=1;
	}
}

static void timer4func(void* parameters){
	int temp = CPUIdle+CPUnotIdle;
	printf("CPU Idle count %d\n",CPUIdle);
	printf("CPU inTask count %d\n",CPUnotIdle);
	printf("CPU Utilization Rate around %s", division(CPUnotIdle, temp, 3));
	while(1);
}

/*-----------------------------------------------------------*/

