/*
 * e2v_Clicks.c
 *
 *  Created on: Feb 13, 2023
 *      Author: MrDuch
 */

#include "e2v_Clicks.h"

uint32_t E2V_CLICKS_OR_Clock_period_Ticks;//hundred of ticks;
uint32_t E2V_CLICKS_OR_Clock_Freq;//hundred of ticks;

uint32_t delay;

uint32_t r0u_to_r0d;
uint32_t r0d_to_r3u;
uint32_t r3u_to_r2d;
uint32_t r2d_to_r1u;
uint32_t r1u_to_r3d;
uint32_t r3d_to_r2u;
uint32_t r2u_to_r1d;
uint32_t r1d_to_r0u;


uint32_t number_Of_Lines;
uint32_t number_Of_Rows;
uint32_t OR_Clock_period;/*in mks (1, 2, 4)*/
uint32_t mS_To_Wait;

uint8_t CCD_Mode;
uint32_t CCD_Brust_N;
uint32_t CCD_Brust_Delay;



extern uint8_t tcp_recieve;


uint16_t buff_size = 2;
uint8_t buff_to_send[256];
volatile uint32_t adc = 0;

uint32_t* spi1_cr2 = &(SPI1->CR2);
uint32_t* dma2_lifcr = DMA2_BASE+0x8UL;
uint32_t* dma2_stream3_ndtr = DMA2_BASE+0x5CUL;
uint32_t* dma2_stream3_cr = DMA2_BASE+0x58UL;

void E2V_CLICKS_Ini()
{

	/*
	E2V_CLICKS_OR_Clock_period_Ticks = OR_Clock_period*E2V_CLICKS_BASE_FREQ;
	r0u_to_r0d = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.1);
	r0d_to_r3u = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.07);
	r3u_to_r2d = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.1);
	r2d_to_r1u = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.23);
	r1u_to_r3d = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.1);
	r3d_to_r2u = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.23);
	r2u_to_r1d = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.1);
	r1d_to_r0u = (uint32_t)(E2V_CLICKS_OR_Clock_period_Ticks * 0.07);
*/
	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I1 + 16U))|
							(0x1UL << (E2V_CLICKS_I2 + 16U))|
							(0x1UL << (E2V_CLICKS_I3 + 16U))|
							(0x1UL << (E2V_CLICKS_R  + 16U))|
							(0x1UL << (E2V_CLICKS_R1 + 16U))|
							(0x1UL << (E2V_CLICKS_R2 + 16U))|
							(0x1UL << (E2V_CLICKS_R3 + 16U));


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_DG + 16U));

	number_Of_Lines = 515;
	number_Of_Lines = 516;
	number_Of_Rows = 2148;
//	number_Of_Rows = 700;

	OR_Clock_period = 4;/*in mks (1, 2, 4)*/
	mS_To_Wait = 1;

	CCD_Mode = 0;
	CCD_Brust_N = 1;
	CCD_Brust_Delay = 1000;

	switch (OR_Clock_period)
		{
		case 1:
			E2V_CLICKS_OR_Clock_Freq = 1000;
			break;
		case 2:
			E2V_CLICKS_OR_Clock_Freq = 500;
			break;
		case 4:
			E2V_CLICKS_OR_Clock_Freq = 250;
			break;
		default:
			E2V_CLICKS_OR_Clock_Freq = 1000;
			break;
		}
}

void E2V_CLICKS_Base_R_Output_1000 ()
{
	/*
	 * R   /-\_______________|/
	 * R1  _________/------\_|_
	 * R2  ----\__________/--|-
	 * R3  ___/------\_______|_
	 * OS  /----------\______|/
	 */

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R));
	delay = 0U;
//	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R+16U));
//	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3));
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2+16U));
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1));
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3+16UL));
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2));
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1+16UL));

}

void E2V_CLICKS_Base_R_Output_500 ()
{
	/*
	 * R   /-\_______________|/
	 * R1  _________/------\_|_
	 * R2  ----\__________/--|-
	 * R3  ___/------\_______|_
	 * OS  /----------\______|/
	 */

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R));
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R+16U));
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3));
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2+16U));
	delay = 0U;
	while (delay<5U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1));
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3+16UL));


	delay = 0U;
	while (delay<5U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2));
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1+16UL));
	delay = 0U;
	while (delay<1U)
		{
		delay++;
		}
}

void E2V_CLICKS_Base_R_Output_250 ()
{
	/*
	 * R   /-\_______________|/
	 * R1  _________/------\_|_
	 * R2  ----\__________/--|-
	 * R3  ___/------\_______|_
	 * OS  /----------\______|/
	 */

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R));
	delay = 0U;
	while (delay<3U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R+16U));
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3));
	delay = 0U;
	delay = 0U;
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2+16U));
	delay = 0U;
	delay = 0U;
	while (delay<11U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1));
	delay = 0U;
	delay = 0U;
	delay = 0U;


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R3+16UL));

	ADC1->CR2 = 0x40000001;							///////////////////////////////

	delay = 0U;
	delay = 0U;
	delay = 0U;
	delay = 0U;
	while (delay<10U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R2));
//	delay = 0U;
//	delay = 0U;
//	delay = 0U;

    adc = ADC1->DR; // читаем полученное значение в переменную adc///////////////////////////////



    E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1+16UL));

	  buff_to_send[0]=(uint8_t)((adc&0xFF00)>>8);		///////////////////////////////
	  buff_to_send[1]=(uint8_t)((adc&0x00FF));			///////////////////////////////

	*spi1_cr2=0x0UL;									///////////////////////////////
	*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////
	*dma2_stream3_ndtr = buff_size; //DMA2_Stream2->NDTR///////////////////////////////
	*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
	*spi1_cr2=0x2UL;									///////////////////////////////
//	HAL_SPI_Transmit_DMA(&hspi1, buff_to_send, buff_size);
//	delay = 0U;
//	delay = 0U;
//	delay = 0U;
//	while (delay<3U)
//		{
//		delay++;
//		}
}

/*
void E2V_CLICKS_Base_I_Output ()
{
	//
	//  I1  _____/------\___________
	 // I2  __________/------\______
	 // I3  _______________/-----\__

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R));
	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1));


	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I3 + 16U));
	delay = 0U;
	while (delay<20U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I1));
	delay = 0U;
	while (delay<94U*5U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I2));
	delay = 0U;
	while (delay<52U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I1 + 16U));
	delay = 0U;
	while (delay<84U*5U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I3));
	delay = 0U;
	while (delay<52U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I2 + 16U));
	delay = 0U;
	while (delay<94U*5U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I3 + 16U));
	delay = 0U;
	while (delay<18U)
		{
		delay++;
		}

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_R1 + 16U));

	switch (E2V_CLICKS_OR_Clock_Freq)
		{
		case 500:
			for (int i= 0;i<1070;i++) E2V_CLICKS_Base_R_Output_500();
			break;
		case 250:
			for (int i= 0;i<1070;i++) E2V_CLICKS_Base_R_Output_250();
			break;
		default:
			for (int i= 0;i<1070;i++) E2V_CLICKS_Base_R_Output_1000();
			break;
		}
}

*/


void E2V_CLICKS_Base_Aqu_Output ()
{
	switch (OR_Clock_period)
		{
		case 1:
			E2V_CLICKS_OR_Clock_Freq = 1000;
			break;
		case 2:
			E2V_CLICKS_OR_Clock_Freq = 500;
			break;
		case 4:
			E2V_CLICKS_OR_Clock_Freq = 250;
			break;
		default:
			E2V_CLICKS_OR_Clock_Freq = 1000;
			break;
		}
	if (mS_To_Wait <= 0) mS_To_Wait = 1;

//	HAL_ADC_Start(&hadc1); // запускаем преобразование сигнала АЦП

	uint16_t lines_counter = 0;
	uint8_t opcode;
	uint8_t txWr0 = 0;
	uint8_t txWr1 = 0;
	uint32_t addr = 0;
	int8_t buf[3] = {0,0,0};
	int8_t sn = 0;

	  uint32_t* GPIO_BSRR_Adress = &(E2V_CLICKS_PORT->BSRR);

	  uint32_t High_R = (0x1UL << (E2V_CLICKS_R));
	  uint32_t Low_R = (0x1UL << (E2V_CLICKS_R+16U));
	  uint32_t High_R1 = (0x1UL << (E2V_CLICKS_R1));
	  uint32_t Low_R1 = (0x1UL << (E2V_CLICKS_R1+16U));
	  uint32_t High_R2 = (0x1UL << (E2V_CLICKS_R2));
	  uint32_t Low_R2 = (0x1UL << (E2V_CLICKS_R2+16U));
	  uint32_t High_R3 = (0x1UL << (E2V_CLICKS_R3));
	  uint32_t Low_R3 = (0x1UL << (E2V_CLICKS_R3+16U));

	  uint32_t High_DG = (0x1UL << (E2V_CLICKS_DG));
	  uint32_t Low_DG = (0x1UL << (E2V_CLICKS_DG+16U));
	  uint32_t High_I1 = (0x1UL << (E2V_CLICKS_I1));
	  uint32_t Low_I1 = (0x1UL << (E2V_CLICKS_I1+16U));
	  uint32_t High_I2 = (0x1UL << (E2V_CLICKS_I2));
	  uint32_t Low_I2 = (0x1UL << (E2V_CLICKS_I2+16U));
	  uint32_t High_I3 = (0x1UL << (E2V_CLICKS_I3));
	  uint32_t Low_I3 = (0x1UL << (E2V_CLICKS_I3+16U));
	  uint32_t High_d15 = (0x1UL << (15U));
	  uint32_t Low_d15 = (0x1UL << (15U+16U));

	  High_I3 = High_I3|High_d15;
	  Low_I3 = Low_I3|Low_d15;

	*GPIO_BSRR_Adress = Low_I1|Low_I2|Low_I3|Low_DG|High_R1|High_R2|Low_R3|High_R;

	*GPIO_BSRR_Adress = High_DG;

	for (lines_counter = 0;lines_counter<number_Of_Lines;lines_counter++)
	{
//				*GPIO_BSRR_Adress = High_I3;
//			  	delay = 0U;
//			  	while (delay<35U)
//			  		{
//			  		delay++;
//			  		}

			  	*GPIO_BSRR_Adress = High_I1;
			  	delay = 0U;
			  	while (delay<35U)
			  		{
			  		delay++;
			  		}

//			  	*GPIO_BSRR_Adress = Low_I3;
//			  	delay = 0U;
//			  	while (delay<35U)
//			  		{
//			  		delay++;
//			  		}

			  	*GPIO_BSRR_Adress = High_I2;
			  	delay = 0U;
			  	while (delay<35U)
			  		{
			  		delay++;
			  		}

			  	*GPIO_BSRR_Adress = Low_I1;
			  	delay = 0U;
				while (delay<35U)
			  		{
			  		delay++;
			  		}

				*GPIO_BSRR_Adress = High_I3;
				delay = 0U;
				while (delay<35U)
				  	{
				  	delay++;
				  	}

				*GPIO_BSRR_Adress = Low_I2;
				delay = 0U;
				while (delay<35U)
				  	{
				  	delay++;
				  	}

			  	*GPIO_BSRR_Adress = Low_I3;
			  	delay = 0U;
			  	while (delay<70U)
			  		{
			  		delay++;
			  		}
	}


	*GPIO_BSRR_Adress = Low_R1;
	delay = 0U;
	while (delay<2U)
		{
		delay++;
		}

	*GPIO_BSRR_Adress = Low_R2;
		delay = 0U;
		while (delay<2U)
			{
			delay++;
			}

	*GPIO_BSRR_Adress = Low_DG;
	delay = 0U;
	while (delay<35U)
		{
		delay++;
		}

		*GPIO_BSRR_Adress = High_R1;
		*GPIO_BSRR_Adress = High_R2;
		*GPIO_BSRR_Adress = Low_R3;
		*GPIO_BSRR_Adress = High_R;

				delay = 0U;
				while (delay<2U)
					{
					delay++;
					}



	uint32_t Ticks_To_Wait = mS_To_Wait*6718-848;
//	Ticks_To_Wait = 5870+6718;

	delay = 0U;
	while (delay<Ticks_To_Wait)
		{
		delay++;
		if (tcp_recieve) break;
		}

// 	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I1));

	for (lines_counter = 0;lines_counter<number_Of_Lines;lines_counter++)
	{

		sn = 0;
//		if (lines_counter&0x0001)sn = 1;

		opcode = BSB_S0+sn*4;
		opcode = (opcode<<3)|OM_FDM1;

		txWr0 = w5500_readReg(opcode,Sn_TX_WR0);
		txWr1 = w5500_readReg(opcode,Sn_TX_WR1);
		addr = (txWr0<<8)|(txWr1);

		opcode = BSB_S0_TX+sn*4;
		opcode = (opcode<<3)|OM_FDM0;

		W5500_SS_SELECT();

		DMA2_Stream3->CR &= (uint32_t)(~DMA_SxCR_DBM);
		DMA2_Stream3->NDTR = buff_size;
		DMA2_Stream3->PAR = &SPI1->DR;
		DMA2_Stream3->M0AR = buff_to_send;
		SET_BIT(hspi1.Instance->CR1, SPI_CR1_SPE);

	    buff_to_send[0]=(addr & 0xFF00)>> 8;
	    buff_to_send[1]=(addr & 0x00FF);
        buff_to_send[2]=opcode|(RWB_WRITE<<2);

        buff_to_send[3]=3;
        buff_to_send[4]=14;
	    buff_to_send[5]=15;
	    buff_to_send[6]=92;
        buff_to_send[7]=65;
        buff_to_send[8]=35;
	    buff_to_send[9]=0;
	    buff_to_send[10]=0;

	    buff_to_send[11]=(uint8_t)((lines_counter&0xFF00)>>8);
	    buff_to_send[12]=(uint8_t)((lines_counter&0x00FF));
        buff_to_send[13]=0x00;
        buff_to_send[14]=0x00;

			  	  *spi1_cr2=0x0UL;
			  	  *dma2_lifcr = 0xfc00000U; //DMA2_LIFCR
			  	  *dma2_stream3_ndtr = 14; //DMA2_Stream3->NDTR
			  	  *dma2_stream3_cr=0x600045fUL;//DMA2_Stream3->CR
			  	  *spi1_cr2=0x2UL;


			  	//////////////////////////////////////////////////////////////////////////////////////////////////////////

					*GPIO_BSRR_Adress = High_I3;
				  	delay = 0U;
				  	while (delay<35U)
				  		{
				  		delay++;
				  		}

				  	*GPIO_BSRR_Adress = High_I1;
				  	delay = 0U;
				  	while (delay<35U)
				  		{
				  		delay++;
				  		}

				  	*GPIO_BSRR_Adress = Low_I3;
				  	delay = 0U;
				  	while (delay<35U)
				  		{
				  		delay++;
				  		}

				  	*GPIO_BSRR_Adress = High_I2;
				  	delay = 0U;
				  	while (delay<35U)
				  		{
				  		delay++;
				  		}

				  	*GPIO_BSRR_Adress = Low_I1;
				  	delay = 0U;
					while (delay<35U)
				  		{
				  		delay++;
				  		}

					*GPIO_BSRR_Adress = High_I3;
					delay = 0U;
					while (delay<35U)
					  	{
					  	delay++;
					  	}

					*GPIO_BSRR_Adress = Low_I2;
					delay = 0U;
					while (delay<35U)
					  	{
					  	delay++;
					  	}

				  	*GPIO_BSRR_Adress = Low_I3;
				  	delay = 0U;
				  	while (delay<35U)
				  		{
				  		delay++;
				  		}


				  	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
				  	  __disable_irq();

//		  				*GPIO_BSRR_Adress = Low_R;
					  	delay = 0U;


			  	switch (E2V_CLICKS_OR_Clock_Freq)
			  		{
			  		case 500:
/*			  			for (int i= 0;i<number_Of_Rows;i++)
			  				{
			  				*GPIO_BSRR_Adress = High_R;
			  				delay = 0U;
			  				delay = 0U;
			  				delay = 0U;
			  				delay = 0U;
			  				delay = 0U;

			  				*GPIO_BSRR_Adress = Low_R;
			  				delay = 0U;

			  				*GPIO_BSRR_Adress = High_R3;
			  				delay = 0U;


			  				*GPIO_BSRR_Adress = Low_R2;

			  				  buff_to_send[0]=(uint8_t)((adc&0xFF00)>>8);		///////////////////////////////
			  				  buff_to_send[1]=(uint8_t)((adc&0x00FF));			///////////////////////////////

			  				*spi1_cr2=0x0UL;									///////////////////////////////
			  				*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////
			  				*dma2_stream3_ndtr = buff_size; //DMA2_Stream2->NDTR///////////////////////////////
			  				*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
			  				*spi1_cr2=0x2UL;									///////////////////////////////

			  				delay = 0U;
			  				while (delay<1U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = High_R1;
			  				delay = 0U;


			  				*GPIO_BSRR_Adress = Low_R3;

			  				ADC1->CR2 = 0x40000001;							///////////////////////////////

			  				delay = 0U;
			  				while (delay<5U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = High_R2;

			  				delay = 0U;

			  				*GPIO_BSRR_Adress = Low_R1;
			  			    adc = ADC1->DR; // читаем полученное значение в переменную adc///////////////////////////////

			  				delay = 0U;
			  				delay = 0U;
			  				delay = 0U;
			  				while (delay<0U)
			  					{
			  					delay++;
			  					}
			  				}
*/			  			break;
			  		default:
/*			  			for (int i= 0;i<number_Of_Rows;i++)
			  				{
			  				*GPIO_BSRR_Adress = High_R3;
			  				delay = 0U;

			  				*GPIO_BSRR_Adress = High_R;
			  				delay = 0U;

			  				*GPIO_BSRR_Adress = Low_R1;
			  				delay = 0U;
			  				while (delay<2U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = Low_R;
			  				delay = 0U;
			  				while (delay<2U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = High_R2;

			  				  buff_to_send[0]=(uint8_t)((adc&0xFF00)>>8);		///////////////////////////////
			  				  buff_to_send[1]=(uint8_t)((adc&0x00FF));			///////////////////////////////

			  				*spi1_cr2=0x0UL;									///////////////////////////////
			  				*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////
			  				*dma2_stream3_ndtr = buff_size; //DMA2_Stream2->NDTR///////////////////////////////
			  				*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
			  				*spi1_cr2=0x2UL;									///////////////////////////////


			  				delay = 0U;
			  				while (delay<10U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = Low_R3;

			  				ADC1->CR2 = 0x40000001;							///////////////////////////////

			  				delay = 0U;
			  				while (delay<10U)
			  					{
			  					delay++;
			  					}

			  			    adc = ADC1->DR; // читаем полученное значение в переменную adc///////////////////////////////

			  				*GPIO_BSRR_Adress = High_R1;
			  				delay = 0U;
			  				while (delay<2U)
			  					{
			  					delay++;
			  					}

			  				*GPIO_BSRR_Adress = Low_R2;
			  				delay = 0U;
			  				while (delay<3U)
			  					{
			  					delay++;
			  					}

			  				}
*/
for (int i= 0;i<number_Of_Rows;i++)
	{
	if ((i == 487))
			{
        buff_to_send[0]=3;
        buff_to_send[1]=14;
	    buff_to_send[2]=15;
	    buff_to_send[3]=92;
        buff_to_send[4]=65;
        buff_to_send[5]=35;
	    buff_to_send[6]=(uint8_t)((i&0xFF00)>>8);
	    buff_to_send[7]=(uint8_t)((i&0x00FF));

	    buff_to_send[8]=(uint8_t)((lines_counter&0xFF00)>>8);
	    buff_to_send[9]=(uint8_t)((lines_counter&0x00FF));
        buff_to_send[10]=0x01;
        buff_to_send[11]=0x00;

			  	  *spi1_cr2=0x0UL;
			  	  *dma2_lifcr = 0xfc00000U; //DMA2_LIFCR
			  	  *dma2_stream3_ndtr = 11; //DMA2_Stream3->NDTR
			  	  *dma2_stream3_cr=0x600045fUL;//DMA2_Stream3->CR
			  	  *spi1_cr2=0x2UL;

				  	delay = 0U;
				  	while (delay<20U)
				  		{
				  		delay++;
				  		}

			}
	if ((i == 974))
			{
        buff_to_send[0]=3;
        buff_to_send[1]=14;
	    buff_to_send[2]=15;
	    buff_to_send[3]=92;
        buff_to_send[4]=65;
        buff_to_send[5]=35;
	    buff_to_send[6]=(uint8_t)((i&0xFF00)>>8);
	    buff_to_send[7]=(uint8_t)((i&0x00FF));
	    buff_to_send[8]=(uint8_t)((lines_counter&0xFF00)>>8);
	    buff_to_send[9]=(uint8_t)((lines_counter&0x00FF));
        buff_to_send[10]=0x02;
        buff_to_send[11]=0x00;

			  	  *spi1_cr2=0x0UL;
			  	  *dma2_lifcr = 0xfc00000U; //DMA2_LIFCR
			  	  *dma2_stream3_ndtr = 11; //DMA2_Stream3->NDTR
			  	  *dma2_stream3_cr=0x600045fUL;//DMA2_Stream3->CR
			  	  *spi1_cr2=0x2UL;

			  	delay = 0U;
			  	while (delay<20U)
			  		{
			  		delay++;
			  		}

			}
	if ((i == 1461))
			{
        buff_to_send[0]=3;
        buff_to_send[1]=14;
	    buff_to_send[2]=15;
	    buff_to_send[3]=92;
        buff_to_send[4]=65;
        buff_to_send[5]=35;
	    buff_to_send[6]=(uint8_t)((i&0xFF00)>>8);
	    buff_to_send[7]=(uint8_t)((i&0x00FF));
	    buff_to_send[8]=(uint8_t)((lines_counter&0xFF00)>>8);
	    buff_to_send[9]=(uint8_t)((lines_counter&0x00FF));
        buff_to_send[10]=0x03;
        buff_to_send[11]=0x00;

			  	  *spi1_cr2=0x0UL;
			  	  *dma2_lifcr = 0xfc00000U; //DMA2_LIFCR
			  	  *dma2_stream3_ndtr = 11; //DMA2_Stream3->NDTR
			  	  *dma2_stream3_cr=0x600045fUL;//DMA2_Stream3->CR
			  	  *spi1_cr2=0x2UL;

				  	delay = 0U;
				  	while (delay<20U)
				  		{
				  		delay++;
				  		}

			}
	if ((i == 1948))
			{
        buff_to_send[0]=3;
        buff_to_send[1]=14;
	    buff_to_send[2]=15;
	    buff_to_send[3]=92;
        buff_to_send[4]=65;
        buff_to_send[5]=35;
	    buff_to_send[6]=(uint8_t)((i&0xFF00)>>8);
	    buff_to_send[7]=(uint8_t)((i&0x00FF));
	    buff_to_send[8]=(uint8_t)((lines_counter&0xFF00)>>8);
	    buff_to_send[9]=(uint8_t)((lines_counter&0x00FF));
        buff_to_send[10]=0x04;
        buff_to_send[11]=0x00;

			  	  *spi1_cr2=0x0UL;
			  	  *dma2_lifcr = 0xfc00000U; //DMA2_LIFCR
			  	  *dma2_stream3_ndtr = 11; //DMA2_Stream3->NDTR
			  	  *dma2_stream3_cr=0x600045fUL;//DMA2_Stream3->CR
			  	  *spi1_cr2=0x2UL;

				  	delay = 0U;
				  	while (delay<20U)
				  		{
				  		delay++;
				  		}

			}
	adc = (((GPIOE->IDR)&0x0000ffff)<<2) + (((GPIOB->IDR)&0x00000300)>>8);// считать значение ADC
//	adc = adc >> 2;

	*GPIO_BSRR_Adress = High_R2;
	delay = 0U;
	delay = 0U;

  	GPIOB->BSRR = 0x1UL << 12U + 16U; 		//КОНЕЦ acquire, начало convert

	*GPIO_BSRR_Adress = Low_R1;
	delay = 0U;

	*GPIO_BSRR_Adress = High_R;
	delay = 0U;
	while (delay<2U)
		{
		delay++;
		}

	*GPIO_BSRR_Adress = Low_R;
	delay = 0U;
	while (delay<2U)
		{
		delay++;
		}

  	GPIOB->BSRR = 0x1UL << 12U; 		//сброс флага NCNVST

	*GPIO_BSRR_Adress = High_R3;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	*GPIO_BSRR_Adress = Low_R2;

//	adc = 0;
//			HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)

	  buff_to_send[0]=(uint8_t)((adc&0x00FF0000)>>16);		///////////////////////////////
	  buff_to_send[1]=(uint8_t)((adc&0x0000FF00)>>8);			///////////////////////////////
	  buff_to_send[2]=(uint8_t)((adc&0x000000FF)>>0);			///////////////////////////////

	*spi1_cr2=0x0UL;									///////////////////////////////
	*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////
	*dma2_stream3_ndtr = 3; //DMA2_Stream2->NDTR///////////////////////////////
	*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
	*spi1_cr2=0x2UL;									///////////////////////////////


	delay = 0U;
	while (delay<10U)
		{
		delay++;
		}

	*GPIO_BSRR_Adress = High_R1;
	delay = 0U;
	delay = 0U;
	delay = 0U;

	*GPIO_BSRR_Adress = Low_R3;
	delay = 0U;
	delay = 0U;

//	ADC1->CR2 = 0x40000001;							///////////////////////////////

	delay = 0U;
	while (delay<5U)
		{
		delay++;
		}

//  adc = ADC1->DR; // читаем полученное значение в переменную adc///////////////////////////////


	}
break;
			  		case 1000:
/*			  			for (int i= 0;i<number_Of_Rows;i++)
			  				{

			  				*GPIO_BSRR_Adress = High_R;
			  				delay = 0U;
			  			//	delay = 0U;


			  				*GPIO_BSRR_Adress = Low_R;
			  			//	delay = 0U;

			  				*GPIO_BSRR_Adress = High_R3;
			  				delay = 0U;


			  				*GPIO_BSRR_Adress = Low_R2;
			  				  buff_to_send[0]=(uint8_t)((adc&0xFF00)>>8);		///////////////////////////////
			  				  buff_to_send[1]=(uint8_t)((adc&0x00FF));			///////////////////////////////

			  				*spi1_cr2=0x0UL;									///////////////////////////////
			  				*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////


			  				*GPIO_BSRR_Adress = High_R1;
			  				delay = 0U;


			  				*GPIO_BSRR_Adress = Low_R3;
			  				ADC1->CR2 = 0x40000001;							///////////////////////////////

//			  				delay = 0U;
//			  				delay = 0U;
			  				delay = 0U;
//			  				delay = 0U;
//			  				delay = 0U;
//			  				delay = 0U;
//			  				delay = 0U;
//			  				delay = 0U;
			  				*dma2_stream3_ndtr = buff_size; //DMA2_Stream2->NDTR///////////////////////////////
			  				*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
			  				*spi1_cr2=0x2UL;									///////////////////////////////

			  				*GPIO_BSRR_Adress = High_R2;
			  				delay = 0U;

			  				*GPIO_BSRR_Adress = Low_R1;
			  			    adc = ADC1->DR; // читаем полученное значение в переменную adc///////////////////////////////

//			  				delay = 0U;
//			  				delay = 0U;
			  				}
*/			  			break;
			  		}

  				*GPIO_BSRR_Adress = High_R;
  				delay = 0U;
  				delay = 0U;
  				delay = 0U;

  				*GPIO_BSRR_Adress = High_R1;

  			  buff_to_send[0]=(uint8_t)((adc&0x00FF0000)>>8);		///////////////////////////////
  			  buff_to_send[1]=(uint8_t)((adc&0x0000FF00));			///////////////////////////////
  			  buff_to_send[2]=(uint8_t)((adc&0x000000FF));			///////////////////////////////

  			*spi1_cr2=0x0UL;									///////////////////////////////
  			*dma2_lifcr = 0xfc00000U; //DMA2_LIFCR				///////////////////////////////
  			*dma2_stream3_ndtr = 3; //DMA2_Stream2->NDTR///////////////////////////////
  			*dma2_stream3_cr=0x600045fUL;//DMA2_Stream2->CR		///////////////////////////////
  			*spi1_cr2=0x2UL;
  			///////////////////////////////
  			delay = 0U;
  			while (delay<20U)
  				{
  				delay++;
  				}

				__enable_irq();

			  	//////////////////////////////////////////////////////////////////////////////////////////////////////////

		W5500_SS_DESELECT();
		addr = addr+number_Of_Rows*3+11*5;
//		if (addr > 0xffff)addr=addr-0xffff;

		if (lines_counter == 70)
		{
			delay = 0;
		}

		opcode = BSB_S0+sn*4;
		opcode = (opcode<<3)|OM_FDM1;

		txWr0 = (addr&0xFF00)>>8;
		txWr1 = (addr&0x00FF);
		w5500_writeReg(opcode,Sn_TX_WR0,txWr0);
		w5500_writeReg(opcode,Sn_TX_WR1,txWr1);

		opcode=0;
		opcode = BSB_S0+sn*4;
		opcode = (opcode<<3)|OM_FDM1;
		w5500_writeReg(opcode,Sn_CR, CR_SEND);


		if (tcp_recieve) break;

	}

//	HAL_ADC_Stop(&hadc1);

	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_I1 + 16U))|
							(0x1UL << (E2V_CLICKS_I2 + 16U))|
							(0x1UL << (E2V_CLICKS_I3 + 16U))|
							(0x1UL << (E2V_CLICKS_R + 16U))|
							(0x1UL << (E2V_CLICKS_R1 + 16U))|
							(0x1UL << (E2V_CLICKS_R2 + 16U))|
							(0x1UL << (E2V_CLICKS_R3 + 16U));


	delay = 0U;
	while (delay<100)
		{
		delay++;
		}

	delay = 0U;
	while (delay<100)
		{
		delay++;
		}
	E2V_CLICKS_PORT->BSRR = (0x1UL << (E2V_CLICKS_DG + 16U));



for (int i = 0; i < 10; i++ )
{
	while (delay<2000)
		{
		delay++;
		}
	sn = 0;
	opcode = BSB_S0+sn*4;
	opcode = (opcode<<3)|OM_FDM1;

	txWr0 = w5500_readReg(opcode,Sn_TX_WR0);
	txWr1 = w5500_readReg(opcode,Sn_TX_WR1);
	addr = (txWr0<<8)|(txWr1);


	addr = addr+14;
	if (addr > 0xffff)addr=addr-0xffffU;

	opcode = BSB_S0+sn*4;
	opcode = (opcode<<3)|OM_FDM1;

	txWr0 = (addr&0xFF00)>>8;
	txWr1 = (addr&0x00FF);
	w5500_writeReg(opcode,Sn_TX_WR0,txWr0);
	w5500_writeReg(opcode,Sn_TX_WR1,txWr1);

	opcode=0;
	opcode = BSB_S0+sn*4;
	opcode = (opcode<<3)|OM_FDM1;
	w5500_writeReg(opcode,Sn_CR, CR_SEND);
	delay = 0U;

}

if (tcp_recieve) TCP_Recieve();
tcp_recieve = 0;


//*GPIO_BSRR_Adress = High_I1|High_I2|High_I3|Low_DG|Low_R1|Low_R2|High_R3|Low_R;

}
