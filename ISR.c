/***************************************************
* @file  ISR.c
* @brief timer interupt
* @autor Yven Vogt
* @date  25.12.2018
***************************************************/

#include <LPC17xx.h>
#include "globals.h"

void SysTick_Handler (void)   //Timer
{
	iTimer++;
	iRandTimer++;
}
