#include "main.h"
/* Address: 0x27; Mode: Write*/
#define Slave_Address_LCD		0x4E
extern I2C_HandleTypeDef hi2c1;
void LCD_Send_Data(uint8_t data)	// rs = 0
{
	uint8_t data_upper_nibble = data & 0xf0;
	uint8_t data_lower_nibble = (data<<4) & 0xf0;
	uint8_t data_send[4];
	data_send[0] = data_upper_nibble | 0x0d;	// upper nibble: en = 1; rs = 1
	data_send[1] = data_upper_nibble | 0x09;	// upper nibble: en = 0; rs = 1
	data_send[2] = data_lower_nibble | 0x0d;	// lower nibble: en = 1; rs = 1
	data_send[3] = data_lower_nibble | 0x09;	// lower nibble: en = 0; rs = 1
	HAL_I2C_Master_Transmit(&hi2c1,Slave_Address_LCD,(uint8_t*)data_send,sizeof(data_send),HAL_MAX_DELAY);
}

void LCD_Send_Command(uint8_t cmd)
{
	uint8_t cmd_upper_nibble = cmd & 0xf0;
	uint8_t cmd_lower_nibble = (cmd<<4) & 0xf0;
	uint8_t cmd_send[4];
	cmd_send[0] = cmd_upper_nibble | 0x0c;	// upper nibble: en = 1; rs = 0
	cmd_send[1] = cmd_upper_nibble | 0x08;	// upper nibble: en = 0; rs = 0
	cmd_send[2] = cmd_lower_nibble | 0x0c;	// lower nibble: en = 1; rs = 0
	cmd_send[3] = cmd_lower_nibble | 0x08;	// lower nibble: en = 0; rs = 0
	HAL_I2C_Master_Transmit(&hi2c1,Slave_Address_LCD,(uint8_t*)cmd_send,sizeof(cmd_send),HAL_MAX_DELAY);
}

void LCD_Init()
{
	HAL_Delay(16);
	LCD_Send_Command(0x33);
	LCD_Send_Command(0x32);
	HAL_Delay(5);
	LCD_Send_Command(0x28);
	HAL_Delay(5);
	LCD_Send_Command(0x08);
	HAL_Delay(5);
	LCD_Send_Command(0x01);
	HAL_Delay(5);
	LCD_Send_Command(0x06);
	HAL_Delay(5);
	LCD_Send_Command(0x0d);
}

void LCD_Print(uint8_t* str)
{
	uint8_t i = 0;
	while(*(str+i) != '\0')
	{
		LCD_Send_Data(*(str+i));
		i++;
	}
}

void LCD_Goto_XY(int x, int y)
{
	int location = 0x80 + 0x40*y + x;
	LCD_Send_Command(location);
}

void LCD_Clear()
{
	LCD_Send_Command(0x01);
}
void LCD_Return_Home()
{
	LCD_Send_Command(0x02);
	HAL_Delay(2);
}