/***************************************************
* @file  Print.c
* @brief all setter functions
* @autor Yven Vogt
* @date  25.12.2018
***************************************************/

#include <lpc17xx.h>
#include <stdio.h>
#include "ADC_LandTiger.h"
#include "Buttons_LandTiger.h"
#include "GLCD_LandTiger.h"
#include "LED_LandTiger.h"
#include "globals.h"
#include "Board_Joystick.h"

void SetApple (struct block* spApple, int16_t iX, int16_t iY)
{
	spApple->iX=iX;
	spApple->iY=iY;
	iEatApple=1;
}

void Joystick (struct snake* spSnake)
{
	if (Joystick_GetState()!=0)
	{
		if ((Joystick_GetState()==1)&& (spSnake->eSpeed!=up)&&(spSnake->eSpeed!=down))
		{
			spSnake->eSpeed=up;
		}
		
		else if ((Joystick_GetState()==2)&& (spSnake->eSpeed!=up)&&(spSnake->eSpeed!=down))
		{
			spSnake->eSpeed=down;
		}
		
		else if ((Joystick_GetState()==8)&& (spSnake->eSpeed!=right)&&(spSnake->eSpeed!=left))
		{
			spSnake->eSpeed=right;
		}
		else if ((Joystick_GetState()==16)&& (spSnake->eSpeed!=right)&&(spSnake->eSpeed!=left))
		{
			spSnake->eSpeed=left;
		}
	}
}

void SetSnake (struct snake* spSnake)
{
	
	int16_t x;
	int16_t y;
	int16_t i;
	spSnake->iX_Old = spSnake->sBlock[spSnake->iSize-1].iX;
	spSnake->iY_Old = spSnake->sBlock[spSnake->iSize-1].iY;
	
	for (i=(spSnake->iSize-1);i>0;i--)    
	{
		spSnake->sBlock[i]=spSnake->sBlock[i-1];
	}
	
	x= spSnake->sBlock[0].iX;
	y= spSnake->sBlock[0].iY;
	
	if (spSnake->eSpeed==right)
	{
		if (x < 310)
		{
			spSnake->sBlock[0].iX=spSnake->sBlock[0].iX+10;
			
		}
		
		else if (x == 310)
		{
			spSnake->sBlock[0].iX=0;
		}
			
	}
	
	else if (spSnake->eSpeed==left)
	{
		if (x > 0)
		{
			spSnake->sBlock[0].iX=spSnake->sBlock[0].iX-10;
		}
		
		else if (x == 0)
		{
			spSnake->sBlock[0].iX=310;
		}
	}
	
	else if (spSnake->eSpeed==up)
	{
		if (y <= 20)
		{
			spSnake->sBlock[0].iY=230;
		}
		
		else if (y > 20)
		{
			spSnake->sBlock[0].iY=spSnake->sBlock[0].iY-10;
		}
	}
	
	else if (spSnake->eSpeed==down)
	{
		if (y >= 230)
		{
			spSnake->sBlock[0].iY=20;
		}
		
		else if (y >= 20)
		{
			spSnake->sBlock[0].iY=spSnake->sBlock[0].iY+10;
		}	
	}
}

void SetTime()
{
   static int32_t iStaticTimer;
   iStaticTimer++;
   if (iStaticTimer > 20)
   {
      iStaticTimer = 0;
      if (Joystick_GetState()!=0)
      {
         if ((Joystick_GetState()==8))
         {
            iTime+=10*230000;
         }
         else if ((Joystick_GetState()==16))
         {
            iTime-=10*230000;
         }
      }
      if (iTime < 10*230000)
      {
         iTime = 10*230000;
      }
      
      else if (iTime > 1000*230000)
      {
         iTime = 1000*230000;
      }
   }
   
   GLCD_SetBackColor(LightGrey);
   GLCD_SetTextColor(White);
   sprintf(cString, "Time : %4dsec",iTime/230000);
   GLCD_DisplayString(9, 3, 1,(unsigned char*) cString);
}
