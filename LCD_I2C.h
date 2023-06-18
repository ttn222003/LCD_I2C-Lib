#include "main.h"
#define Slave_Address_LCD		0x4E
extern I2C_HandleTypeDef hi2c1;
void LCD_Send_Data(uint8_t data);
void LCD_Send_Command(uint8_t cmd);
void LCD_Init();
void LCD_Print(uint8_t* str);
void LCD_Goto_XY(int x, int y);
void LCD_Clear();
void LCD_Return_Home();