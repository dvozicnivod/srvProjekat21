/**
 * @file main.c
 * @author Radovan Zivkovic
 * @date Jan 2020
 * @brief SRV projekat No.21, skolska 2018/2019
 *
 * @version [1.0 @ 01/2020] Initial version
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "uart.h"
#include "event_groups.h"
#include "queue.h"
#include "semphr.h"

/* Hardware includes. */
#include "msp430.h"
#include "hal_ETF5438A.h"

/* Project specific includes. */
#include "adc_misc.h"

/** uart task priority */
#define mainUART_TEST_TASK_PRIO ( 3 )
/** hp task priority */
#define mainHP_TASK_PRIO        ( 2 )
/** lp task priority */
#define mainLP_TASK_PRIO        ( 1 )

/** Taster event group handle */
static EventGroupHandle_t xTasterEventGroup = NULL;
/** S1_Event bit */
static EventBits_t xS1_Event = BIT4;
/** S2_Event bit */
static EventBits_t xS2_Event = BIT5;
/** S3_Event bit */
static EventBits_t xS3_Event = BIT6;
/** S4_Event bit */
static EventBits_t xS4_Event = BIT7;
/** channel selector */
static uint8_t ucChannelSelector = 1;

static void prvSetupHardware( void );
static void prvTask1( void *pvParameters );
static void prvTask2( void *pvParameters );
static void prvTask3( void *pvParameters );
/** queue */
static QueueHandle_t xOutputQueue = NULL;
/** task handles */
static TaskHandle_t xTask1 = NULL;
static TaskHandle_t xTask2 = NULL;
static TaskHandle_t xTask3 = NULL;
/**
 * @brief xTask1
 * Task1 ceka na podatke iz prekidne rutine ADC i na tastere S1 - S4
 * pomocu Event group, te cuva zadnje primljene vrednosti za svaki kanal.
 * Na pritisak odgovarajuceg tastera salje podatak sa odgovarajuceg
 * kanala tasku xTask3.
 */
static void prvTask1( void *pvParameters )
{
    /*Taster event bits*/
    EventBits_t xTasterBits;
    /*ADC event bits*/
    EventBits_t xADCBits;
    /*poruka buffer*/
    ADCMsg_t xMsg;
    uint16_t usADClastMsg[4] = { 0 };
    for( ;; )
    {
        xADCBits = xEventGroupWaitBits( xADCEventGroup,                                    /* event group handle */
                                        xADC_Event0 | xADC_Event1 | xADC_Event2 | xADC_Event3,                                        /* event bits to wait */
                                        pdFALSE,                                           /* don't clear on exit */
                                        pdFALSE,                                           /* we wait for either event to happen */
                                        portMAX_DELAY                                      /* block until available */
                                         );
        if( ( xADCBits & xADC_Event0 ) != 0 )
        {
            xQueueReceive( xADCDataQueue, &xMsg, portMAX_DELAY );
            usADClastMsg[xMsg.eADCNr] = xMsg.usADCData;
            //xEventGroupClearBits( xADCEventGroup, xADC_Event0 );
        }
        if( ( xADCBits & xADC_Event1 ) != 0 )
        {
            xQueueReceive( xADCDataQueue, &xMsg, portMAX_DELAY );
            usADClastMsg[xMsg.eADCNr] = xMsg.usADCData;
            //xEventGroupClearBits( xADCEventGroup, xADC_Event1 );
        }
        if( ( xADCBits & xADC_Event2 ) != 0 )
        {
            xQueueReceive( xADCDataQueue, &xMsg, portMAX_DELAY );
            usADClastMsg[xMsg.eADCNr] = xMsg.usADCData;
            //xEventGroupClearBits( xADCEventGroup, xADC_Event2 );
        }
        if( ( xADCBits & xADC_Event3 ) != 0 )
        {
            xQueueReceive( xADCDataQueue, &xMsg, portMAX_DELAY );
            usADClastMsg[xMsg.eADCNr] = xMsg.usADCData;
            xEventGroupClearBits( xADCEventGroup, xADC_Event3 | xADC_Event2 | xADC_Event1 | xADC_Event0);
        }

        xTasterBits = xEventGroupWaitBits ( xTasterEventGroup,                            /* event group handle */
                                       ( xS1_Event | xS2_Event | xS3_Event | xS4_Event),  /* event bits to wait */
                                       pdFALSE,                                           /* don't clear on exit */
                                       pdFALSE,                                           /* we wait for either event to happen */
                                       pdMS_TO_TICKS(10)                                  /* block until available */
                                      );
        if ( ( xTasterBits & xS1_Event ) != 0 )
        {
            /*pritisnut S1 taster*/
            ucChannelSelector = 1;
            xEventGroupClearBits( xTasterEventGroup, xS1_Event );
        }
        else if ( ( xTasterBits & xS2_Event ) != 0 )
        {
            /*pritisnut S2 taster*/
            ucChannelSelector = 2;
            xEventGroupClearBits( xTasterEventGroup, xS2_Event );
        }
        else if ( ( xTasterBits & xS3_Event ) != 0 )
        {
            /*pritisnut S3 taster*/
            ucChannelSelector = 3;
            xEventGroupClearBits( xTasterEventGroup, xS3_Event );
        }
        else if ( ( xTasterBits & xS4_Event ) != 0 )
        {
            /*pritisnut S4 taster*/
            ucChannelSelector = 4;
            xEventGroupClearBits( xTasterEventGroup, xS4_Event );
        }

        /**
         * send data to xTask3
         */
        xQueueSend( xOutputQueue, &usADClastMsg[ucChannelSelector-1], portMAX_DELAY);
    }
}

/**
 * @brief xTask2
 * Task2 polira tastere S1-S4 i obavestava xTask1 ukoliko su pritisnuti
 * preko Event group.
 */
static void prvTask2( void *pvParameters )
{
    uint8_t ucLastState = 0, ucState = 0;
    /*
     *
     */
    for( ;; )
    {
        ucState = ~P2IN;
        if((ucState & BIT4)&&(!(ucLastState & BIT4)))
        {
            xEventGroupSetBits( xTasterEventGroup, xS1_Event );
        }
        if((ucState & BIT5)&&(!(ucLastState & BIT5)))
        {
            xEventGroupSetBits( xTasterEventGroup, xS2_Event );
        }
        if((ucState & BIT6)&&(!(ucLastState & BIT6)))
        {
            xEventGroupSetBits( xTasterEventGroup, xS3_Event );
        }
        if((ucState & BIT7)&&(!(ucLastState & BIT7)))
        {
            xEventGroupSetBits( xTasterEventGroup, xS4_Event );
        }
        ucLastState = ucState;
    }
}

/**
 * @brief xTask3
 *  Task3 ceka na redu za poruke i po prijemu podatka racuna razliku izmedju
 *  uzastopnih vrednosti i salje na UART periferiju.
 */
static void prvTask3( void *pvParameters )
{
    uint16_t usOldData = 0;
    uint16_t usResult = 0;
    uint16_t usData = 0;
    char cOutput[10];
    xUartSendString( "Razlika je: \n\r", 0 );
    for( ;; )
    {
        usOldData = usData;
        /*cekanje na red*/
        xQueueReceive( xOutputQueue, &usData, portMAX_DELAY );
        /*racunanje razlike i slanje na UART*/
        usResult = usData - usOldData;
        sprintf(cOutput, "%d", usResult);
        xUartSendString( cOutput, 0 );
        xUartSendString( "\n\r", 0 );
    }
}


/**
 * @brief UART receive callback
 * @param ucData received character
 *
 * Function that is called every time a byte is received over UART.
 */
static void prvReceiveByteCallback( uint8_t ucData )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/**
 * @brief main function
 */
void main( void )
{
    /* configure peripherals */
    prvSetupHardware();

    /* cofigure uart */
    vUartInit();
    vUartSetRxCallback( prvReceiveByteCallback );

    /* init adc objects*/
    vADCInitADC();

    /* Create tasks */
    xTaskCreate( prvTask1,"xMainTask", configMINIMAL_STACK_SIZE, NULL, mainHP_TASK_PRIO, &xTask1);
    xTaskCreate( prvTask2, "xButtonTask", configMINIMAL_STACK_SIZE, NULL, mainLP_TASK_PRIO, &xTask2 );
    xTaskCreate( prvTask3, "xUARTTask", configMINIMAL_STACK_SIZE, NULL, mainUART_TEST_TASK_PRIO, &xTask3 );

    /* create queue */
    xOutputQueue = xQueueCreate( 10, sizeof( uint16_t ) );

    /* create event group */
    xTasterEventGroup = xEventGroupCreate();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well then this line will never be reached.  If it is reached
    then it is likely that there was insufficient (FreeRTOS) heap memory space
    to create the idle task.  This may have been trapped by the malloc() failed
    hook function, if one is configured. */
    for( ;; );
}

/**
 * @brief Configure hardware upon boot
 */
static void prvSetupHardware( void )
{
    taskDISABLE_INTERRUPTS();

    /* Disable the watchdog. */
    WDTCTL = WDTPW + WDTHOLD;
	
    /* Configure Clock. Since we aren't using XT1 on the board,
     * configure REFOCLK to source FLL adn ACLK.
     */
    SELECT_FLLREF(SELREF__REFOCLK);
    SELECT_ACLK(SELA__REFOCLK);
    hal430SetSystemClock( configCPU_CLOCK_HZ, configLFXT_CLOCK_HZ );

    /* Enable buttons */
    P2DIR &= ~(0xF0);

    /* Initialize necessary hardware */
    vADCInitHardware();
}
