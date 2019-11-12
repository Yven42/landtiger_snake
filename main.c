/***************************************************
* @prog  Snake
* @file  main.c
* @brief main and initialize
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

void InitializeBoard (void);

int main(void)
{
   struct snake sSnake;
	struct block sApple;
	int16_t iX=10;
	int16_t iY=10;
	int8_t iButton=0;
   iTime=60*230000;
   
   InitializeBoard ();
	
   //---Apple startvalue
	sApple.iX=220;
   sApple.iY=220;
   //---
	  
	while(1)  //MainLoop
	{
		Menu(&sSnake);
      
		while (iButton == 0)
		{      
         AnimationApple();
         SetTime();
         
			if (Buttons_GetState(1) == 1)   //Key2 start the game
			{
				iButton=1;
				eLife=alive;
            //---Snake startvale
         	sSnake.eSpeed=right;
            sSnake.sBlock[0].iX=100;
            sSnake.sBlock[0].iY=50;
 	         sSnake.sBlock[1].iX=90;
            sSnake.sBlock[1].iY=50;
            sSnake.iSize=2;
            //---
			}
         
			if (iRandTimer > 10)   //Apple ticker for random position 
			{
				iX+=20;
				iY+=10;
				if(iY>200)
				{
					iY=20;
				}
            
				else if(iY<20)
				{
					iY=200;
				}
							
				if(iX>300)
				{
					iX=20;
				}
            
				else if(iX<20)
				{
					iX=200;
				}			
		   }
		}
      
		iButton=0;
		GLCD_Clear(White);
      //---Print 
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(LightGrey);
		GLCD_Bargraph(0,0,320,20,1023);
		
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Black);
		GLCD_Bargraph(0,19,320,2,1023);
		//---------------------------------------------Live
		while (eLife == alive)  //Start game
		{	
			Joystick(&sSnake);
				
			if (ADC_ConversionDone()==0) //Reading ADC
			{
				iValue=ADC_GetValue();
				ADC_StartConversion();
			}
			
			if (iRandTimer > 10) //Apple ticker for random position 
			{
				iTime--;
				iX+=20;
				iY+=10;
				if (iY>200)      //Y max
				{
					iY=30;
				}
				else if (iY<30)  //Y min
				{
					iY=200;
				}
				if (iX>300)      //X max
				{
					iX=20;
				}
				else if (iX<20)  //X min
				{
					iX=200;
				}
			}
         
         //---Time up---
			if (iTime < 0)
			{
				eLife = dead;
			}
         //---
			
         //---------------------MAIN EXECUTION------------------------
			if (iTimer > (iValue*1000/4095.5)+50)  //FPS 
			{
				if (iEatApple == 0)  //Set a new apple
				{
					 SetApple(&sApple,iX,iY);
				}
				SetSnake(&sSnake);
				PrintApple(&sApple);
				PrintSnake(&sSnake);
				Eat(&sApple,&sSnake);
				Death(&sSnake);
				iTimer = 0;		
		   }
         //---------------------MAIN EXECUTION------------------------
	  }
     iScore = 1; //New score
     if (iTime <= 0) //TIME OUT
     {
        	GLCD_SetBackColor(Black);
         GLCD_SetTextColor(Red);
         sprintf(cString, "TIME OUT");
         GLCD_DisplayString(4, 6, 1,(unsigned char*) cString);
     }
     else //ATE YOURSELF
     {
         GLCD_SetBackColor(Black);
         GLCD_SetTextColor(Red);
         sprintf(cString, "ATE YOURSELF");
         GLCD_DisplayString(4, 4, 1,(unsigned char*) cString);
     }
     iTimer = 0;
     while (iTimer < 5000); //Delay
     iTimer = 0;
     iTime=60*230000;
	  GLCD_Clear(White);  //Clear screen
	}
}

/***************************************************
* @fn    void InitializeBoard (void)
* @brief functions to initalize the board
* @autor Yven Vogt
* @date  25.12.2018
***************************************************/

void InitializeBoard (void)
{
	Buttons_Initialize();
	GLCD_Init();
	LED_Initialize();
	ADC_Initialize();
   Joystick_Initialize();

	SysTick_Config(SystemCoreClock/1000); 

	GLCD_Clear(White);
	ADC_StartConversion();
}
