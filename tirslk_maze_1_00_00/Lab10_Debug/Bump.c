// Bump.c
// Runs on MSP432
// Provide low-level functions that interface bump switches the robot.
// Daniel Valvano and Jonathan Valvano
// July 11, 2019

/* This example accompanies the book
   "Embedded Systems: Introduction to Robotics,
   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/
#include <stdint.h>
#include "msp.h"
#define BUMPPORT8 0
#if BUMPPORT8
// Negative logic bump sensors
// P8.7 Bump5
// P8.6 Bump4
// P8.5 Bump3
// P8.4 Bump2
// P8.3 Bump1
// P8.0 Bump0


// Initialize Bump sensors
// Make P8.7-P8.3, P8.0 as inputs
// Activate interface pullup
void Bump_Init(void){
    // write this as part of Lab 10
  P8->SEL0 &= ~0xF9;
  P8->SEL1 &= ~0xF9;    // 1) configure P8.7-P8.3, P8.0 as GPIO
  P8->DIR &= ~0xF9;     // 2) make P8.7-P8.3, P8.0 in
  P8->REN |= 0xF9;      // 3) enable pull resistors on P8.7-P8.3, P8.0
  P8->OUT |= 0xF9;      //    P8.7-P8.3, P8.0 are pull-up
}
// Read current state of 6 switches
// Returns a 6-bit positive logic result (0 to 63)
// bit 5 Bump5
// bit 4 Bump4
// bit 3 Bump3
// bit 2 Bump2
// bit 1 Bump1
// bit 0 Bump0
uint8_t Bump_Read(void){uint32_t in;
    // write this as part of Lab 10
  in = ~P8->IN;
  return(((in&0xF8)>>2)|(in&0x01));
}
#else
// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

// Initialize Bump sensors
// Make six Port 4 pins inputs
// Activate interface pullup
// pins 7,6,5,3,2,0
void Bump_Init(void){
   // write this as part of Lab 10
  P4->SEL0 &= ~0xED;
  P4->SEL1 &= ~0xED;    // 1) configure P4.7-P4.5, P4.3, P4.2, and P4.0 as GPIO
  P4->DIR &= ~0xED;     // 2) make P4.7-P4.5, P4.3, P4.2, and P4.0 in
  P4->REN |= 0xED;      // 3) enable pull resistors on P4.7-P4.5, P4.3, P4.2, and P4.0
  P4->OUT |= 0xED;      //    P4.7-P4.5, P4.3, P4.2, and P4.0 are pull-up
}
// Read current state of 6 switches
// Returns a 6-bit positive logic result (0 to 63)
// bit 5 Bump5
// bit 4 Bump4
// bit 3 Bump3
// bit 2 Bump2
// bit 1 Bump1
// bit 0 Bump0
uint8_t Bump_Read(void){ uint32_t in;
// write this as part of Lab 10
  in = ~P4->IN;
  return(((in&0xE0)>>2)|((in&0x0C)>>1)|(in&0x01));
}
#endif
