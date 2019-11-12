/*-----------------------------------------------------------------------------
 * Name:    Buttons_MCB1700.c
 * Purpose: Buttons interface for MCB1700 evaluation board
 * Rev.:    1.00
 *----------------------------------------------------------------------------*/

/* Copyright (c) 2013 - 2014 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "GPIO_LPC17xx.h"
#include "Buttons_LandTiger.h"

#define BUTTONS_COUNT                  (2)
#define BUTTON_INT0                    (1 << 0)

/* Button pins:
   - BUTTON0: P2_10 = GPIO2[10]
*/


/* Button pin definitions */
/* modified for LandTiger by Philip Bourdon */
const PIN BUTTON_PIN[] = {
  { 2, 11},
	{ 2, 12}
};


/**
  \fn          int32_t Buttons_Initialize (void)
  \brief       Initialize buttons
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t Buttons_Initialize (void) {

  /* Enable GPIO clock */
  GPIO_PortClock   (1);

	/* modified for LandTiger by Philip Bourdon */
  /* Configure Pins */
  PIN_Configure (BUTTON_PIN[0].Portnum, BUTTON_PIN[0].Pinnum, PIN_FUNC_0, PIN_PINMODE_PULLDOWN, PIN_PINMODE_NORMAL);
  GPIO_SetDir   (BUTTON_PIN[0].Portnum, BUTTON_PIN[0].Pinnum, GPIO_DIR_INPUT);
	PIN_Configure (BUTTON_PIN[1].Portnum, BUTTON_PIN[1].Pinnum, PIN_FUNC_0, PIN_PINMODE_PULLDOWN, PIN_PINMODE_NORMAL);
  GPIO_SetDir   (BUTTON_PIN[1].Portnum, BUTTON_PIN[1].Pinnum, GPIO_DIR_INPUT);
  
  return 0;
}

/**
  \fn          int32_t Buttons_Uninitialize (void)
  \brief       De-initialize buttons
  \returns
   - \b  0: function succeeded
   - \b -1: function failed
*/
int32_t Buttons_Uninitialize (void) {

	/* modified for LandTiger by Philip Bourdon */
  /* Unconfigure Pins */
  PIN_Configure (BUTTON_PIN[0].Portnum, BUTTON_PIN[0].Pinnum, 0, 0, 0);
	PIN_Configure (BUTTON_PIN[1].Portnum, BUTTON_PIN[1].Pinnum, 0, 0, 0);

  return 0;
}

/**
  \fn          uint32_t Buttons_GetState (void)
  \brief       Get buttons state
	\param			 number of Button (0 or 1)
  \returns     Buttons state
*/

/* modified for LandTiger by Philip Bourdon */
uint32_t Buttons_GetState (uint32_t number) {
  uint32_t val;

  val = 0;
  if (!(GPIO_PinRead (BUTTON_PIN[number].Portnum, BUTTON_PIN[number].Pinnum))) val |= BUTTON_INT0;

  return val;
}

/**
  \fn          uint32_t Buttons_GetCount (void)
  \brief       Get number of available buttons
  \return      Number of available buttons
*/
uint32_t Buttons_GetCount (void) {
  return BUTTONS_COUNT;
}
