/* Standard includes. */
#include <stdio.h>


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#define configTASK_LOW_PRIORITY ( tskIDLE_PRIORITY + 1 )
#define configUSE_PREEMPTION			0

#define A_period pdMS_TO_TICKS( 40UL ) 
#define B_period pdMS_TO_TICKS( 80UL )
#define C_period pdMS_TO_TICKS( 120UL ) 
//lcm(40,80,120) = 240
//GCD(40,80,120) = 40

#define mainTASK_Major_MS pdMS_TO_TICKS( 240UL )
#define mainTASK_Minor_MS pdMS_TO_TICKS( 40UL ) //DURATION OF THE MINOR
#define mainEXEC_TASK_A pdMS_TO_TICKS( 20UL ) 
#define mainEXEC_TASK_B pdMS_TO_TICKS( 10UL ) 
#define mainEXEC_TASK_C pdMS_TO_TICKS( 10UL )

extern char* division(int num, int den, int prec);

TickType_t A(TickType_t Start);
void B();
void C();

void Major();
TickType_t Minor1();
void Minor2();
void Minor3();
void Minor4();
void Minor5();
void Minor6();

void main_TimeLineScheduling( void ){
BaseType_t major_task;

    major_task = xTaskCreate( Major,
                "Major",
                configMINIMAL_STACK_SIZE, 		// The size of the stack to allocate to the task. 
                NULL,
                configTASK_LOW_PRIORITY,
                NULL);


    vTaskStartScheduler();
  
}



void Major(){
    TickType_t xNextWakeTime;
    uint32_t xBlockTime;
    uint32_t StartTime = 0;
    uint32_t CPU_UTILIZATION_FACTOR;
    
    while(1){
        CPU_UTILIZATION_FACTOR = 0;
        StartTime = Minor1();                                  
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1     
        CPU_UTILIZATION_FACTOR += xBlockTime;
       

        StartTime = xTaskGetTickCount();        //I start the counter  
        Minor2();                                   //Execute the processes in the minor
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1
        CPU_UTILIZATION_FACTOR += xBlockTime;

        StartTime = xTaskGetTickCount();        //I start the counter  
        Minor3();                                   //Execute the processes in the minor
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1
        CPU_UTILIZATION_FACTOR += xBlockTime;
        

        StartTime = xTaskGetTickCount();        //I start the counter  
        Minor4();                                   //Execute the processes in the minor
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1
        CPU_UTILIZATION_FACTOR += xBlockTime;
        
       
        StartTime = xTaskGetTickCount();        //I start the counter  
        Minor5();                                   //Execute the processes in the minor
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1
        CPU_UTILIZATION_FACTOR += xBlockTime;
        
       
        StartTime = xTaskGetTickCount();        //I start the counter  
        Minor6();                                   //Execute the processes in the minor
        xBlockTime = xTaskGetTickCount() - StartTime;
        if(xBlockTime <  mainTASK_Minor_MS)
            vTaskDelay(mainTASK_Minor_MS - xBlockTime); //I wait for the remaining time within a single minor inside the major  -  //REMEMBER THAT #define INCLUDE_vTaskDelay = 1
        CPU_UTILIZATION_FACTOR += xBlockTime;
        

        printf("\nCpu_Utilization_factor : %s\n", division(CPU_UTILIZATION_FACTOR, mainTASK_Major_MS, 3)); //precision = decimal numbers
        break;
    }
    vTaskDelete(NULL);
}


TickType_t Minor1(){
    TickType_t StartTime = xTaskGetTickCount();
    StartTime = A(StartTime);
    B();
    C();
    return StartTime;
}
void Minor2(){
    TickType_t xNextWakeTime = xTaskGetTickCount();
    printf("\nMinor 2: %d\n", pdTICKS_TO_MS( xNextWakeTime ));
    A(0);
    

}

void Minor3(){
    TickType_t xNextWakeTime = xTaskGetTickCount();
    printf("\nMinor 3: %d\n", pdTICKS_TO_MS( xNextWakeTime ));
    A(0);
    B();
}
void Minor4(){
    TickType_t xNextWakeTime = xTaskGetTickCount();
    printf("\nMinor 4: %d\n", pdTICKS_TO_MS( xNextWakeTime ));
    A(0);
    C();
}
void Minor5(){
    TickType_t xNextWakeTime = xTaskGetTickCount();
    printf("\nMinor 5: %d\n", pdTICKS_TO_MS( xNextWakeTime ));
    A(0);
    B();
}
void Minor6(){
    TickType_t xNextWakeTime = xTaskGetTickCount();
    printf("\nMinor 6: %d\n", pdTICKS_TO_MS( xNextWakeTime ));
    A(0);
}



TickType_t A(TickType_t Start){
    TickType_t StartTime = xTaskGetTickCount() - Start;
    printf("A started at: %d\n", StartTime );
    while(xTaskGetTickCount() - StartTime < mainEXEC_TASK_A);
    printf("  finished at: %d\n", pdTICKS_TO_MS( xTaskGetTickCount() ));

    return StartTime;
    
}

void B(){
    TickType_t StartTime = xTaskGetTickCount();
    printf("B started at: %d\n", StartTime );
    while(xTaskGetTickCount() - StartTime < mainEXEC_TASK_B);
    printf("  finished at: %d\n", pdTICKS_TO_MS( xTaskGetTickCount() ));
    
}

void C(){
    TickType_t StartTime = xTaskGetTickCount();
    printf("C started at: %d\n", StartTime );
    while(xTaskGetTickCount() - StartTime < mainEXEC_TASK_C);
    printf("  finished at: %d\n", pdTICKS_TO_MS( xTaskGetTickCount() ));
}
