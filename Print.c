/***************************************************
* @file  Print.c
* @brief all print functions
* @autor Yven Vogt
* @date  25.12.2018
***************************************************/

#include <lpc17xx.h>
#include <stdio.h>
#include "GLCD_LandTiger.h"
#include "ADC_LandTiger.h"
#include "Buttons_LandTiger.h"
#include "LED_LandTiger.h"
#include "globals.h"
#include "Board_Joystick.h"

void AnimationApple(void)
{
   static struct block sApple[2];
   static int16_t iSpeed_Anamtion_Apple;
   
   if (sApple[0].iX != 60)
   {
      sApple[0].iX = 60;
      sApple[0].iY = 60;
      sApple[1].iX = 245;
      sApple[1].iY = 60;
      iSpeed_Anamtion_Apple = 0;
   }
   
   if (iTimer > 100)
   {
      iTimer = 0;
      iSpeed_Anamtion_Apple += 1;
      sApple[0].iY += iSpeed_Anamtion_Apple;
      sApple[1].iY += iSpeed_Anamtion_Apple;
      
      GLCD_SetBackColor(White);
      GLCD_SetTextColor(White);
      GLCD_Bargraph(55,50,20,105,1023); 
      GLCD_Bargraph(245,50,20,105,1023);      
   }
   
   if (sApple[0].iY > 145)
   {
      sApple[0].iY = 145;
      sApple[1].iY = 145;
      iSpeed_Anamtion_Apple*=-1;
   }

   PrintApple (&sApple[0]);
   PrintApple (&sApple[1]);
}
void PrintSnake (struct snake* spSnake)
{
   //Print [Size] [Speed] [Time]
	int16_t i;
	GLCD_SetBackColor(LightGrey);
	GLCD_SetTextColor(Black);
	sprintf(cString, "Size: %u", spSnake->iSize);
	GLCD_DisplayString(1, 2, 0,(unsigned char*) cString);
	sprintf(cString, "Time : %4dsec", iTime/230000);
	GLCD_DisplayString(1, 39, 0,(unsigned char*) cString);
	sprintf(cString, "Speed : %4d", 50000/(ADC_GetValue()+500));
	GLCD_DisplayString(1, 20, 0,(unsigned char*) cString);
	ADC_StartConversion();
	//---
   
	//Kopf
	GLCD_SetBackColor(White);
   GLCD_SetTextColor(Red);
   GLCD_Bargraph(spSnake->sBlock[0].iX+1,spSnake->sBlock[0].iY+1,8,8,1023);
	
	for (i=1;i<spSnake->iSize;i++)
	{
		if (i%3==0)
		{
		  GLCD_SetBackColor(White);
	     GLCD_SetTextColor(Green);
		  GLCD_Bargraph(spSnake->sBlock[i].iX+1,spSnake->sBlock[i].iY+1,8,8,1023);
		}
		else
		{
		  GLCD_SetBackColor(White);
	     GLCD_SetTextColor(Black);
		  GLCD_Bargraph(spSnake->sBlock[i].iX+1,spSnake->sBlock[i].iY+1,8,8,1023);
		}
	}
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(White);
   GLCD_Bargraph(spSnake->iX_Old+1,spSnake->iY_Old+1,8,8,1023);
	
	GLCD_SetBackColor(LightGrey);
   GLCD_SetTextColor(LightGrey);
   GLCD_Bargraph(0,0,10,10,1023);
}

void PrintApple (struct block* spApple)
{
	uint16_t x = spApple->iX;
	uint16_t y = spApple->iY;
   uint8_t i;
   int8_t* ipX = &iX_Apple_Lookup[0];
   int8_t* ipY = &iY_Apple_Lookup[0];
    
   //Print Black
   GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
   for (i=0;i<38;i++)
   {
      GLCD_PutPixel(x+*ipX,y+*ipY);
      ipX++;
      ipY++;
   }
   //Print Green
	GLCD_SetTextColor(Green);
   for (i=0;i<7;i++)
   {
      GLCD_PutPixel(x+*ipX,y+*ipY);
      ipX++;
      ipY++;
   }
   //Print Red
	GLCD_SetTextColor(Red);
   for (i=0;i<42;i++)
   {
      GLCD_PutPixel(x+*ipX,y+*ipY);
      ipX++;
      ipY++;
   }
}
void Menu (struct snake* spSnake)
{
	GLCD_Clear(LightGrey);
	GLCD_SetBackColor(Blue);
   GLCD_SetTextColor(Blue);
   GLCD_Bargraph(50,45,220,115,1023);
	GLCD_SetBackColor(White);
   GLCD_SetTextColor(White);
   GLCD_Bargraph(55,50,210,105,1023);
	
	GLCD_SetBackColor(White);
   GLCD_SetTextColor(Black);
   sprintf(cString, "New Game");
	GLCD_DisplayString(3, 6, 1,(unsigned char*) cString);
	sprintf(cString, "Press KEY2");
	GLCD_DisplayString(5, 5, 1,(unsigned char*) cString);
   
   GLCD_SetBackColor(LightGrey);
   GLCD_SetTextColor(Black);
   sprintf(cString, "Set with joystick");
	GLCD_DisplayString(26, 17, 0,(unsigned char*) cString);
	
	if (iScore == 1)  //Print Score
	{
		GLCD_SetBackColor(Blue);
      GLCD_SetTextColor(Blue);
      GLCD_Bargraph(50,155,220,50,1023);
      GLCD_SetBackColor(White);
      GLCD_SetTextColor(White);
      GLCD_Bargraph(55,160,210,40,1023);
		GLCD_SetBackColor(White);
      GLCD_SetTextColor(Black);
		sprintf(cString, "Score: %u",spSnake->iSize);
	   GLCD_DisplayString(7, 6, 1,(unsigned char*) cString);
	}
   GLCD_SetBackColor(Blue);
   GLCD_SetTextColor(White);
   sprintf(cString, "*");
	GLCD_DisplayString(1, 1, 1,(unsigned char*) cString);
   sprintf(cString, "S");
	GLCD_DisplayString(2, 1, 1,(unsigned char*) cString);
   sprintf(cString, "N");
	GLCD_DisplayString(3, 1, 1,(unsigned char*) cString);
   sprintf(cString, "A");
	GLCD_DisplayString(4, 1, 1,(unsigned char*) cString);
   sprintf(cString, "K");
	GLCD_DisplayString(5, 1, 1,(unsigned char*) cString);
   sprintf(cString, "E");
	GLCD_DisplayString(6, 1, 1,(unsigned char*) cString);
   sprintf(cString, "*");
	GLCD_DisplayString(7, 1, 1,(unsigned char*) cString);
   sprintf(cString, "*");
	GLCD_DisplayString(1, 18, 1,(unsigned char*) cString);
   sprintf(cString, "S");
	GLCD_DisplayString(2, 18, 1,(unsigned char*) cString);
   sprintf(cString, "N");
	GLCD_DisplayString(3, 18, 1,(unsigned char*) cString);
   sprintf(cString, "A");
	GLCD_DisplayString(4, 18, 1,(unsigned char*) cString);
   sprintf(cString, "K");
	GLCD_DisplayString(5, 18, 1,(unsigned char*) cString);
   sprintf(cString, "E");
	GLCD_DisplayString(6, 18, 1,(unsigned char*) cString);
   sprintf(cString, "*");
	GLCD_DisplayString(7, 18, 1,(unsigned char*) cString);
}
