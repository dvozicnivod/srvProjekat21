/**
 * @file adc_misc.c
 * @brief Implementacija ADC tajmera i prekidne rutine
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs), rev. Radovan Zivkovic
 * @date 2016, rev. 2020
 *
 * ADC task startuje konverziju svaki put kada tajmer odbroji 100ms.
 * U prekidnoj rutini se rezultat konverzije smesta u red sa porukama
 * i obavestava se odgovarajuci task o prispecu poruke.
 */

/* Standard includes. */
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "timers.h"

/* Hardware includes. */
#include "msp430.h"

/* ADC includes. */
#include "adc_misc.h"

/**
 * Duzina reda sa porukama.
 */
#define adcADC_DATA_QUEUE_LEN	( 16 )
/**
 * Makro za startovanje konverzije
 */
#define adcSTART_CONV			do { ADC12CTL0 |= ADC12SC; } while( 0 )
/**
 * Period tajmera
 */
#define adcTIMER100_PERIOD  (pdMS_TO_TICKS(100))
/**
 * ADC tajmer
 */
TimerHandle_t xADCTimer100;
/**
 * Red sa porukama u koji se u prekidnoj rutini smestaju rezultati konverzije
 */
QueueHandle_t xADCDataQueue;
/**
 * Event grupa kojom se obavestava odgovarajuci task o prispecu poruke
 */
EventGroupHandle_t xADCEventGroup = NULL;
/**
 * Event bits
 */
EventBits_t xADC_Event0 = BIT0;
EventBits_t xADC_Event1 = BIT1;
EventBits_t xADC_Event2 = BIT2;
EventBits_t xADC_Event3 = BIT3;
/**
 *  Definicija callback funkcije tajmera.
 */
static void vADCTimer100Callback( TimerHandle_t xTimer );
/**
 * @brief Implementacija callback funkcije tajmera
 * Timer vrsi ponovno pokretanje akvizicije signala svakih 100ms.
 */
 static void vADCTimer100Callback( TimerHandle_t xADCTimer100 )
{
    adcSTART_CONV;
}

/**
 * @brief Inicijalizacija ADC tajmera, reda sa porukama i event grupe
 *
 * Funkcija koja inicijalizuje ADC task.
 */
void vADCInitADC(void)
{
    /*kreiranje svih potrebnih objekata*/
    xADCTimer100 = xTimerCreate( "ADCTimer100", adcTIMER100_PERIOD, pdTRUE, NULL, vADCTimer100Callback);
	xADCDataQueue = xQueueCreate( adcADC_DATA_QUEUE_LEN, sizeof( ADCMsg_t ) );
	xADCEventGroup = xEventGroupCreate();

	xTimerStart(xADCTimer100, 0);       /*startovanje tajmera*/
}
/**
 * @brief Inicijalizacija AD konvertora
 *
 * Funkcija koja konfigurise hardver AD konvertora.
 * Multipleksira odgovarajuce pinove tako da se koriste za AD konvertor.
 * Konfigurise AD konvertor da radi u rezimu Repeat Sequence of channels.
 * Koristi memorijske lokacije 0 do 3 za smestanje rezultata konverzije.
 */
void vADCInitHardware(void)
{
	/* multipleksiranje pinova */
	P7SEL |= BIT6 + BIT7;
	P5SEL |= BIT0 + BIT1;

	/* podesavanje AD konvertora */
	ADC12CTL0 = ADC12ON | ADC12MSC;		/* koristi MSC */
	ADC12CTL1 = ADC12SHS_0 | ADC12CONSEQ_1 | ADC12SHP;	/* repeat-sequence, SC startuje */
	ADC12MCTL0 = ADC12INCH_14;   /* selektovanje kanala */
	ADC12MCTL1 = ADC12INCH_15;
	ADC12MCTL2 = ADC12INCH_8;
	ADC12MCTL3 = ADC12INCH_9 | ADC12EOS;	/* MEM3 je kraj sekvence */
	ADC12IE |= ADC12IE0 | ADC12IE1 | ADC12IE2 | ADC12IE3;	/* dozvoli sve prekide */
	ADC12CTL0 |= ADC12ENC;		/* dozvoli konverziju */
}

/**
 * @brief Prekidna rutina ADC
 *
 * Unutar prekidne rutine se godnjih 9 bita rezultata konverzije upisuje u red sa porukama,
 * a zatim se o tome obavestava odgovarajuci task preko event grupe.
 */
void __attribute__ ( ( interrupt( ADC12_VECTOR ) ) ) vADCISR( void )
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	switch( ADC12IV )
	{
	case  6:					/* Vector  6: ADC12IFG0 */
	{
		ADCMsg_t xMsg = { CH0, ADC12MEM0 >> 3};
		xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );
		xEventGroupSetBits( xADCEventGroup, xADC_Event0 );
	}
	break;
	case  8:					/* Vector  8: ADC12IFG1 */
	{
		ADCMsg_t xMsg = { CH1, ADC12MEM1 >> 3};
		xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );
		xEventGroupSetBits( xADCEventGroup, xADC_Event1 );
	}
	break;
	case 10:					/* Vector 10: ADC12IFG2 */
	{
		ADCMsg_t xMsg = { CH2, ADC12MEM2 >> 3};
		xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );
		xEventGroupSetBits( xADCEventGroup, xADC_Event2 );
	}
	break;
	case 12:					/* Vector 12: ADC12IFG3 */
	{
		ADCMsg_t xMsg = { CH3, ADC12MEM3 >> 3};
		xQueueSendToBackFromISR( xADCDataQueue, &xMsg, &xHigherPriorityTaskWoken );
		xEventGroupSetBits( xADCEventGroup, xADC_Event3 );
	}
	break;
	default: break;
	}
}
