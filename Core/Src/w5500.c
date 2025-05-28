/*
 * w5500.c
 *
 *  Created on: Feb 22, 2023
 *      Author: MrDuch
 */


#include "w5500.h"

//-----------------------------------------------

extern SPI_HandleTypeDef hspi1;
//-----------------------------------------------
extern char str1[60];
tcp_prop_ptr tcpprop;
//-----------------------------------------------

uint8_t macaddr[6]=W5500_MAC_ADDR;
extern uint8_t ipaddr[4];
extern uint8_t ipgate[4];
extern uint8_t ipmask[4];
extern uint16_t local_port;
extern uint16_t tcp_port;
extern uint8_t ipaddr_dest[4];
extern uint8_t rx_Buff_Size[8];
extern uint8_t tx_Buff_Size[8];
extern uint8_t tcp_Socket;

extern uint32_t number_Of_Lines;
extern uint32_t number_Of_Rows;
extern uint32_t OR_Clock_period;/*in mks (1, 2, 4)*/
extern uint32_t mS_To_Wait;


extern uint8_t CCD_Mode;
extern uint32_t CCD_Brust_N;
extern uint32_t CCD_Brust_Delay;
extern char CCD_Name[];

//-----------------------------------------------
//-----------------------------------------------

void w5500_ini(void)
{
  uint8_t opcode=0;
  //Hard Reset
  HAL_GPIO_WritePin(W5500_RST_GPIO_PORT, W5500_RST_PIN, GPIO_PIN_RESET);
  HAL_Delay(70);
  HAL_GPIO_WritePin(W5500_RST_GPIO_PORT, W5500_RST_PIN, GPIO_PIN_SET);
  HAL_Delay(70);
  //Soft Reset
  opcode = (BSB_COMMON<<3)|OM_FDM1;
  w5500_writeReg(opcode, MR, 0x80);
  HAL_Delay(100);
  //Configute Net
  w5500_writeReg(opcode, GAR0,ipgate[0]);
  w5500_writeReg(opcode, GAR1,ipgate[1]);
  w5500_writeReg(opcode, GAR2,ipgate[2]);
  w5500_writeReg(opcode, GAR3,ipgate[3]);
  w5500_writeReg(opcode, SUBR0,ipmask[0]);
  w5500_writeReg(opcode, SUBR1,ipmask[1]);
  w5500_writeReg(opcode, SUBR2,ipmask[2]);
  w5500_writeReg(opcode, SUBR3,ipmask[3]);
  w5500_writeReg(opcode, SHAR0,macaddr[0]);
  w5500_writeReg(opcode, SHAR1,macaddr[1]);
  w5500_writeReg(opcode, SHAR2,macaddr[2]);
  w5500_writeReg(opcode, SHAR3,macaddr[3]);
  w5500_writeReg(opcode, SHAR4,macaddr[4]);
  w5500_writeReg(opcode, SHAR5,macaddr[5]);
  w5500_writeReg(opcode, SIPR0,ipaddr[0]);
  w5500_writeReg(opcode, SIPR1,ipaddr[1]);
  w5500_writeReg(opcode, SIPR2,ipaddr[2]);
  w5500_writeReg(opcode, SIPR3,ipaddr[3]);
  //Configure Interups
  w5500_writeReg(opcode, INTLEVEL0 ,0x00);
  w5500_writeReg(opcode, INTLEVEL1 ,0x00);
  w5500_writeReg(opcode, IMR ,0x00);

  w5500_writeReg(opcode, SIMR ,0xff);

  w5500_writeReg((BSB_S0<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[0]);
  w5500_writeReg((BSB_S1<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[1]);
  w5500_writeReg((BSB_S2<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[2]);
  w5500_writeReg((BSB_S3<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[3]);
  w5500_writeReg((BSB_S4<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[4]);
  w5500_writeReg((BSB_S5<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[5]);
  w5500_writeReg((BSB_S6<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[6]);
  w5500_writeReg((BSB_S7<<3)|OM_FDM1, Sn_RXBUF_SIZE,rx_Buff_Size[7]);

  w5500_writeReg((BSB_S0<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[0]);
  w5500_writeReg((BSB_S1<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[1]);
  w5500_writeReg((BSB_S2<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[2]);
  w5500_writeReg((BSB_S3<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[3]);
  w5500_writeReg((BSB_S4<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[4]);
  w5500_writeReg((BSB_S5<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[5]);
  w5500_writeReg((BSB_S6<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[6]);
  w5500_writeReg((BSB_S7<<3)|OM_FDM1, Sn_TXBUF_SIZE,tx_Buff_Size[7]);


}
//-----------------------------------------------

void w5500_startUDP(uint8_t sock_num)
{
	  uint8_t opcode=0;
	  opcode = BSB_S0+sock_num*4;
	  opcode = (opcode<<3)|OM_FDM1;

	  w5500_writeReg(opcode, Sn_MR, Mode_UDP);

	  w5500_writeReg(opcode, Sn_DIPR0,ipaddr_dest[0]);
	  w5500_writeReg(opcode, Sn_DIPR1,ipaddr_dest[1]);
	  w5500_writeReg(opcode, Sn_DIPR2,ipaddr_dest[2]);
	  w5500_writeReg(opcode, Sn_DIPR3,ipaddr_dest[3]);

	  w5500_writeReg(opcode, Sn_PORT0,local_port>>8);
	  w5500_writeReg(opcode, Sn_PORT1,local_port);

	  w5500_writeReg(opcode, Sn_DPORT0,local_port>>8);
	  w5500_writeReg(opcode, Sn_DPORT1,local_port);

	  w5500_writeReg(opcode, Sn_IMR,0x00);

	  w5500_writeReg(opcode, Sn_CR, CR_OPEN);
}

void TCP_Recieve()
{
	uint8_t buffer_TCP[256];
	uint8_t sock_num = tcp_Socket;
	  uint8_t opcode=0;
	  opcode = BSB_S0+sock_num*4;
	  opcode = (opcode<<3)|OM_FDM1;

	uint8_t R0 = w5500_readReg(opcode,Sn_RX_RSR0);
	uint8_t R1 = w5500_readReg(opcode,Sn_RX_RSR1);
	uint16_t len = (R0<<8)|(R1);

	R0 = w5500_readReg(opcode,Sn_RX_RD0);
	R1 = w5500_readReg(opcode,Sn_RX_RD1);
	uint16_t addr = (R0<<8)|(R1);

	opcode = BSB_S0_RX+sock_num*4;
	opcode = (opcode<<3)|OM_FDM0;
	w5500_read_Buff(opcode,addr,buffer_TCP,len);

	OR_Clock_period = buffer_TCP[5];

	mS_To_Wait = buffer_TCP[8] + 256 * buffer_TCP[7] + 256*256*buffer_TCP[6];
    CCD_Mode = buffer_TCP[9];
    CCD_Brust_N = buffer_TCP[11] + 256 * buffer_TCP[10];
    CCD_Brust_Delay = buffer_TCP[14] + 256 * buffer_TCP[13] + 256 * 256 * buffer_TCP[12];

    buffer_TCP[0] = 3;
    buffer_TCP[1] = 14;
    buffer_TCP[2] = 15;
    buffer_TCP[3] = 92;
    buffer_TCP[4] = 65;
    buffer_TCP[5] = (uint8_t)(OR_Clock_period & 0xFF);
    buffer_TCP[6] = (uint8_t)((mS_To_Wait & 0xFF0000) >> 16);
    buffer_TCP[7] = (uint8_t)((mS_To_Wait & 0x00FF00) >> 8);
    buffer_TCP[8] = (uint8_t)(mS_To_Wait & 0x0000FF);
    buffer_TCP[9] = (uint8_t)(CCD_Mode & 0xFF);
    buffer_TCP[10] = (uint8_t)((CCD_Brust_N & 0x00FF00) >> 8);
    buffer_TCP[11] = (uint8_t)(CCD_Brust_N & 0x0000FF);
    buffer_TCP[12] = (uint8_t)((CCD_Brust_Delay & 0xFF0000) >> 16);
    buffer_TCP[13] = (uint8_t)((CCD_Brust_Delay & 0x00FF00) >> 8);
    buffer_TCP[14] = (uint8_t)(CCD_Brust_Delay & 0x0000FF);

    buffer_TCP[15] = (uint8_t)((number_Of_Lines & 0x00FF00) >> 8);
    buffer_TCP[16] = (uint8_t)(number_Of_Lines & 0x0000FF);
    buffer_TCP[17] = (uint8_t)((number_Of_Rows & 0x00FF00) >> 8);
    buffer_TCP[18] = (uint8_t)(number_Of_Rows & 0x0000FF);
    buffer_TCP[19] = (uint8_t)(3 & 0x0000FF);

    buffer_TCP[20] = (uint8_t)CCD_Name[0];
    buffer_TCP[21] = (uint8_t)CCD_Name[1];
    buffer_TCP[22] = (uint8_t)CCD_Name[2];
    buffer_TCP[23] = (uint8_t)CCD_Name[3];
    buffer_TCP[24] = (uint8_t)CCD_Name[4];
    buffer_TCP[25] = (uint8_t)CCD_Name[5];
    buffer_TCP[26] = (uint8_t)CCD_Name[6];
    buffer_TCP[27] = (uint8_t)CCD_Name[7];
    buffer_TCP[28] = (uint8_t)CCD_Name[8];
    buffer_TCP[29] = (uint8_t)CCD_Name[9];
    buffer_TCP[30] = (uint8_t)CCD_Name[10];
    buffer_TCP[31] = (uint8_t)CCD_Name[11];

    w5500_write_Tx_Buff(sock_num, buffer_TCP, 32);

	  opcode = BSB_S0+sock_num*4;
	  opcode = (opcode<<3)|OM_FDM1;
	  w5500_writeReg(opcode, Sn_CR, CR_SEND);

	  w5500_writeReg(opcode, Sn_IR, 0x04);
	  w5500_writeReg(opcode, Sn_CR, CR_DISCON);
	  w5500_writeReg(opcode, Sn_CR, CR_CLOSE);
	  w5500_writeReg(opcode, Sn_CR, CR_OPEN);
	  w5500_writeReg(opcode, Sn_CR, CR_LISTEN);

}
void w5500_startTCP()
{
	  uint8_t sock_num = tcp_Socket;
	  uint8_t opcode=0;
	  opcode = BSB_S0+sock_num*4;
	  opcode = (opcode<<3)|OM_FDM1;

	  w5500_writeReg(opcode, Sn_MR, Mode_TCP);

	  w5500_writeReg(opcode, Sn_DIPR0,ipaddr_dest[0]);
	  w5500_writeReg(opcode, Sn_DIPR1,ipaddr_dest[1]);
	  w5500_writeReg(opcode, Sn_DIPR2,ipaddr_dest[2]);
	  w5500_writeReg(opcode, Sn_DIPR3,ipaddr_dest[3]);

	  w5500_writeReg(opcode, Sn_PORT0,tcp_port>>8);
	  w5500_writeReg(opcode, Sn_PORT1,tcp_port);

	  w5500_writeReg(opcode, Sn_DPORT0,tcp_port>>8);
	  w5500_writeReg(opcode, Sn_DPORT1,tcp_port);

	  w5500_writeReg(opcode, Sn_IMR,0x04);

	  w5500_writeReg(opcode, Sn_CR, CR_OPEN);

	  w5500_writeReg(opcode, Sn_CR, CR_LISTEN);
}
//-----------------------------------------------
void w5500_Send_UDP (uint8_t sock_num, uint8_t *buff, uint16_t len)
{
	w5500_write_Tx_Buff (sock_num, buff, len);

	uint8_t opcode=0;
	opcode = BSB_S0+sock_num*4;
	opcode = (opcode<<3)|OM_FDM1;
	w5500_writeReg(opcode,Sn_CR, CR_SEND);
}

//-----------------------------------------------
void w5500_write_Tx_Buff (uint8_t sock_num, uint8_t *buff, uint16_t len)
{
	uint8_t opcode=0;
	opcode = BSB_S0+sock_num*4;
	opcode = (opcode<<3)|OM_FDM1;

	uint8_t txWr0 = w5500_readReg(opcode,Sn_TX_WR0);
	uint8_t txWr1 = w5500_readReg(opcode,Sn_TX_WR1);
	uint16_t addr = (txWr0<<8)|(txWr1);

	opcode = BSB_S0_TX+sock_num*4;
	opcode = (opcode<<3)|OM_FDM0;

	w5500_write_Buff(opcode,addr,buff,len);

	addr += len;

	opcode = BSB_S0+sock_num*4;
	opcode = (opcode<<3)|OM_FDM1;

	txWr0 = (addr&0xFF00)>>8;
	txWr1 = (addr&0x00FF);
	w5500_writeReg(opcode,Sn_TX_WR0,txWr0);
	w5500_writeReg(opcode,Sn_TX_WR1,txWr1);
}
//-----------------------------------------------
void w5500_write_Buff (uint8_t op, uint16_t addres, uint8_t* data, uint16_t len)
{
	  uint8_t buf[3] = {addres >> 8, addres, op|(RWB_WRITE<<2)};

	  W5500_SS_SELECT();
	  HAL_SPI_Transmit(&hspi1, buf, 3, 0xFFFFFFFF);
	  HAL_SPI_Transmit(&hspi1, data, len, 0xFFFFFFFF);
	  W5500_SS_DESELECT();
}
//-----------------------------------------------
void w5500_read_Buff (uint8_t op, uint16_t addres, uint8_t* data, uint16_t len)
{
	  uint8_t buf[] = {addres >> 8, addres, op|(RWB_READ<<2)};
	  uint8_t wbuf[4];

	  W5500_SS_SELECT();
	  HAL_SPI_Transmit(&hspi1, buf, 3, 0xFFFFFFFF);
	  HAL_SPI_TransmitReceive(&hspi1, wbuf, data, len, 0xFFFFFFFF);
	  W5500_SS_DESELECT();
}
//-----------------------------------------------

void w5500_writeReg(uint8_t op, uint16_t addres, uint8_t data)
{
  uint8_t buf[] = {addres >> 8, addres, op|(RWB_WRITE<<2), data};
  W5500_SS_SELECT();
  HAL_SPI_Transmit(&hspi1, buf, 4, 0xFFFFFFFF);
  W5500_SS_DESELECT();
}

//-----------------------------------------------
uint8_t w5500_readReg(uint8_t op, uint16_t addres)
{
  uint8_t data;
  uint8_t wbuf[] = {addres >> 8, addres, op, 0x0};
  uint8_t rbuf[4];
  W5500_SS_SELECT();
  HAL_SPI_TransmitReceive(&hspi1, wbuf, rbuf, 4, 0xFFFFFFFF);
  W5500_SS_DESELECT();
  data = rbuf[3];
  return data;
}
//-----------------------------------------------
