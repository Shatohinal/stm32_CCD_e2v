/*
 * e2v_Clicks.h
 *
 *  Created on: Feb 13, 2023
 *      Author: MrDuch
 */

#ifndef INC_E2V_CLICKS_H_
#define INC_E2V_CLICKS_H_

#include "main.h"
#include "stm32f4xx.h"
#include "w5500.h"
#include "stm32f407xx.h"

extern ADC_HandleTypeDef hadc1;

extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_tx;


#define E2V_CLICKS_BASE_FREQ 168 //частота stm32 100 МГц
#define E2V_CLICKS_Ticks_To_Swich 3 //тики на переключение ножки
#define E2V_CLICKS_For_Ticks 15//тики для For
#define E2V_CLICKS_Function_In 4
#define E2V_CLICKS_Function_Out 8


#define E2V_CLICKS_PORT GPIOD
#define E2V_CLICKS_R 6UL     //PIN Numbers
#define E2V_CLICKS_R1 4UL
#define E2V_CLICKS_R2 5UL
#define E2V_CLICKS_R3 7UL
#define E2V_CLICKS_I1 1UL
#define E2V_CLICKS_I2 0UL
#define E2V_CLICKS_I3 2UL
#define E2V_CLICKS_DG 3UL


extern uint32_t E2V_CLICKS_OR_Clock_period;
extern uint32_t delay;
/*
uint32_t number_Of_Lines;
uint32_t number_Of_Rows;
uint32_t OR_Clock_period;//in mks (1, 2, 4)
uint32_t mS_To_Wait;
*/
void E2V_CLICKS_Base_R_Output_1000 (void);
void E2V_CLICKS_Base_R_Output_500 (void);
void E2V_CLICKS_Base_R_Output_250 (void);
void E2V_CLICKS_Base_I_Output (void);
void E2V_CLICKS_Base_Aqu_Output ();
void E2V_CLICKS_Ini ();
//void E2V_CLICKS_Wait (uint32_t Ticks_To_Wait);

#endif /* INC_E2V_CLICKS_H_ */
