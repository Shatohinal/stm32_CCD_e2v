/*
 * w5500.h
 *
 *  Created on: Feb 22, 2023
 *      Author: MrDuch
 */

#ifndef INC_W5500_H_
#define INC_W5500_H_

#include "main.h"
//==================================================
void w5500_writeReg(uint8_t op, uint16_t addres, uint8_t data);
uint8_t w5500_readReg(uint8_t op, uint16_t addres);
void w5500_ini(void);

void w5500_startUDP(uint8_t sock_num);
void w5500_startTCP();

void w5500_write_Buff (uint8_t op, uint16_t addres, uint8_t* data, uint16_t len);
void w5500_read_Buff (uint8_t op, uint16_t addres, uint8_t* data, uint16_t len);

void w5500_write_Tx_Buff (uint8_t sock_num, uint8_t *buff, uint16_t len);
void w5500_Send_UDP (uint8_t sock_num, uint8_t *buff, uint16_t len);

//=========================================

//======================================================
typedef struct tcp_prop {
volatile uint8_t cur_sock;//активный сокет
} tcp_prop_ptr;

//--------------------------------------------------
#define W5500_CS_GPIO_PORT GPIOA
#define W5500_CS_PIN GPIO_PIN_4

#define W5500_RST_GPIO_PORT GPIOA
#define W5500_RST_PIN GPIO_PIN_2

#define W5500_INT_GPIO_PORT GPIOA
#define W5500_INT_PIN GPIO_PIN_3

#define W5500_SS_SELECT() HAL_GPIO_WritePin(W5500_CS_GPIO_PORT, W5500_CS_PIN, GPIO_PIN_RESET)
#define W5500_SS_DESELECT() HAL_GPIO_WritePin(W5500_CS_GPIO_PORT, W5500_CS_PIN, GPIO_PIN_SET)
//--------------------------------------------------
#define W5500_MAC_ADDR {0x02,0x03,0x14,0x15,0x92,0x65}
//--------------------------------------------------
#define BSB_COMMON 0x00
#define BSB_S0 0x01
#define BSB_S0_TX 0x02
#define BSB_S0_RX 0x03
#define BSB_S1 0x05
#define BSB_S1_TX 0x06
#define BSB_S1_RX 0x07
#define BSB_S2 0x09
#define BSB_S2_TX 0x0A
#define BSB_S2_RX 0x0B
#define BSB_S3 0x0D
#define BSB_S3_TX 0x0E
#define BSB_S3_RX 0x0F
#define BSB_S4 0x11
#define BSB_S4_TX 0x12
#define BSB_S4_RX 0x13
#define BSB_S5 0x15
#define BSB_S5_TX 0x16
#define BSB_S5_RX 0x17
#define BSB_S6 0x19
#define BSB_S6_TX 0x1A
#define BSB_S6_RX 0x1B
#define BSB_S7 0x1D
#define BSB_S7_TX 0x1E
#define BSB_S7_RX 0x1F
//--------------------------------------------------
#define RWB_WRITE 1
#define RWB_READ 0
//--------------------------------------------------
#define OM_FDM0 0x00//режим передачи данных переменной длины
#define OM_FDM1 0x01//режим передачи данных по одному байту
#define OM_FDM2 0x02//режим передачи данных по два байта
#define OM_FDM3 0x03//режим передачи данных по четыре байта
//--------------------------------------------------

/** Common Rigister BLOCK**/
#define MR 0x0000//Mode Register
//---------
#define GAR0 0x0001//Gateway IP Address Register MSB
#define GAR1 0x0002
#define GAR2 0x0003
#define GAR3 0x0004// LSB
#define SUBR0 0x0005//Subnet Mask Register MSB
#define SUBR1 0x0006
#define SUBR2 0x0007
#define SUBR3 0x0008// LSB
#define SHAR0 0x0009//Source Hardware Address Register MSB
#define SHAR1 0x000A
#define SHAR2 0x000B
#define SHAR3 0x000C
#define SHAR4 0x000D
#define SHAR5 0x000E// LSB
#define SIPR0 0x000F//Source IP Address Register MSB
#define SIPR1 0x0010
#define SIPR2 0x0011
#define SIPR3 0x0012// LSB
//----------  Interrups
#define INTLEVEL0 0x0013
#define INTLEVEL1 0x0014
#define IR 0x0015
#define IMR 0x0016
#define SIR 0x0017
#define SIMR 0x0018
/** Common Rigister BLOCK END**/




//--------------------------------------------------
#define Sn_MR 0x0000 // Socket  Mode Register
#define Sn_CR 0x0001 // Socket  Command Register
#define Sn_IR 0x0002 // Socket  Interrupt Register
#define Sn_SR 0x0003 // Socket  Status Register
//--------------------------------------------------
//Socket mode
#define Mode_CLOSED 0x00
#define Mode_TCP 0x01
#define Mode_UDP 0x02
#define Mode_MACRAV 0x04
//--------------------------------------------------
//Socket commands
#define CR_OPEN 	0x01
#define CR_LISTEN 	0x02
#define CR_CONNECT  0x04
#define CR_DISCON 	0x08
#define CR_CLOSE 	0x10
#define CR_SEND 	0x20
#define CR_SEND_MAC 0x21
#define CR_SEND_KEEP 0x22
#define CR_RECV 	0x40
//--------------------------------------------------
//Socket states
#define SOCK_CLOSED 0x00
#define SOCK_INIT 0x13
#define SOCK_LISTEN 0x14
#define SOCK_ESTABLISHED 0x17
#define SOCK_UDP 0x22
//-------------------------------------------
#define Sn_PORT0 0x0004 // Socket 0 Source Port Register MSB
#define Sn_PORT1 0x0005 // Socket 0 Source Port Register LSB
#define Sn_DHAR0 0x0006
#define Sn_DHAR1 0x0007
#define Sn_DHAR2 0x0008
#define Sn_DHAR3 0x0009
#define Sn_DHAR4 0x000A
#define Sn_DHAR5 0x000B
#define Sn_DIPR0 0x000C
#define Sn_DIPR1 0x000D
#define Sn_DIPR2 0x000E
#define Sn_DIPR3 0x000F
#define Sn_DPORT0 0x0010
#define Sn_DPORT1 0x0011
#define Sn_MSSR0 0x0012
#define Sn_MSSR1 0x0013
#define Sn_TOS 0x0015
#define Sn_TTL 0x0016
#define Sn_RXBUF_SIZE 0x001E
#define Sn_TXBUF_SIZE 0x001F
#define Sn_TX_FSR0 0x0020
#define Sn_TX_FSR1 0x0021
#define Sn_TX_RD0 0x0022
#define Sn_TX_RD1 0x0023
#define Sn_TX_WR0 0x0024
#define Sn_TX_WR1 0x0025
#define Sn_RX_RSR0 0x0026
#define Sn_RX_RSR1 0x0027
#define Sn_RX_RD0 0x0028
#define Sn_RX_RD1 0x0029
#define Sn_RX_WR0 0x002A
#define Sn_RX_WR1 0x002B

#define Sn_IMR 0x002C
#define Sn_FRAG0 0x002D
#define Sn_FRAG1 0x002E
#define Sn_KALVTR 0x002F

//--------------------------------------------------

#endif /* INC_W5500_H_ */
