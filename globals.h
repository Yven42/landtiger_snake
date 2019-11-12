/***************************************************
* @file  globals.h
* @brief deklaration and extern
* @autor Yven Vogt
* @date  25.12.2018
***************************************************/

#include <LPC17xx.h>

//---Enum---
enum speed
{
	right =0,
	left=1,
	up=2,
	down=3
};

enum life
{
	alive=0,
   dead=1,
};

//---Struct---
struct block
{
	int16_t iX;
	int16_t iY;
};

struct snake
{
	uint16_t iSize;
	uint16_t iX_Old;
	uint16_t iY_Old;
	struct block sBlock [200];
	enum speed eSpeed;
};

//---Extern Int---
extern uint32_t iTimer;
extern uint32_t iRandTimer;
extern int32_t iTime;
extern int32_t iValue;
extern int8_t iEatApple;
extern int8_t iScore;

//---Extern Lookup Tabel---
extern int8_t iX_Apple_Lookup [90];
extern int8_t iY_Apple_Lookup [90];

//---Extern Char---
extern char cString[50]; 

//---Extern Enum---
extern enum life eLife;

//---Extern Functions---
extern void AnimationApple(void);
extern void PrintSnake (struct snake* spSnake);
extern void PrintApple (struct block* spApple);
extern void Menu (struct snake* spSnake);
extern void SetApple (struct block* spApple,int16_t iX,int16_t iY);
extern void SetSnake (struct snake* spSnake);
extern void SetTime(void);
extern void Joystick (struct snake* spSnake);
extern void Eat (struct block* spApple,struct snake* spSnake);
extern void Death (struct snake* spSnake);



