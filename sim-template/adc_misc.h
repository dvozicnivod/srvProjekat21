/**
 * @file adc_misc.h
 * @brief Deklaracija ADC taska
 * @author Strahinja Jankovic (jankovics@etf.bg.ac.rs), rev. Radovan Zivkovic
 * @date 2016, rev. 2020
 */

#ifndef ADC_MISC_H_
#define ADC_MISC_H_

#include "common.h"

/**
 * Struktura koja sluzi za slanje ADC poruke.
 */
typedef struct
{
	Channel_t eADCNr;	/**< Redni broj kanala sa kog je ocitana vrednost */
	uint16_t usADCData; /**< 9-bitni rezultat konverzije */
} ADCMsg_t;
/**
 * @brief Inicijalizacija ADC taska
 *
 * Funkcija koja inicijalizuje ADC tajmer i kreira odgovarajuci red sa porukama.
 */
extern void vADCInitADC(void);

/**
 * @brief Inicijalizacija AD konvertora
 *
 * Funkcija koja konfigurise hardver AD konvertora.
 * Multipleksira odgovarajuce pinove tako da se koriste za AD konvertor.
 * Konfigurise AD konvertor da radi u rezimu Repeat Sequence of channels.
 * Koristi memorijske lokacije 0 do 3 za smestanje rezultata konverzije.
 */
extern void vADCInitHardware(void);

/**
 * Red sa porukama u koji se u prekidnoj rutini smestaju rezultati konverzije
 */
extern QueueHandle_t xADCDataQueue;
/**
 * Event grupa kojom se obavestava odgovarajuci task o prispecu poruke
 */
extern EventGroupHandle_t xADCEventGroup;
/**
 * Event bits
 */
extern EventBits_t xADC_Event0;
extern EventBits_t xADC_Event1;
extern EventBits_t xADC_Event2;
extern EventBits_t xADC_Event3;

#endif /* ADC_MISC_H_ */
