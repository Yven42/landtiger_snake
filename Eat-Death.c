/***************************************************
* @file  Eat-Death.c
* @brief functions for eating and dying
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

void Eat (struct block* spApple,struct snake* spSnake)
{
	if ((spSnake->sBlock[0].iX == spApple->iX) && (spSnake->sBlock[0].iY == spApple->iY))
	{
		iEatApple = 0;
		GLCD_SetBackColor(White);
	   GLCD_SetTextColor(White);
      GLCD_Bargraph(spApple->iX,spApple->iY-4,15,15,1023);
		PrintSnake(spSnake);
		spSnake->iSize++;
	}
}

void Death (struct snake* spSnake)
{
	int8_t iLive=0;
	int16_t i;
  
	for (i=1;i<(spSnake->iSize);i++)
	{
		if((spSnake->sBlock[0].iX == spSnake->sBlock[i].iX) && (spSnake->sBlock[0].iY == spSnake->sBlock[i].iY))
		{	
			iLive++;
		}
	}
	
	if (iLive>0)
	{
		eLife=dead;
	}
}

