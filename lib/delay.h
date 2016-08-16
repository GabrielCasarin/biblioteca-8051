#ifndef DELAY_H
#define DELAY_H

#include <8051.h>

void delay_asm(int tempo) {
/* Rotina de espera de tempo em assembly inline*/
  tempo = tempo; // para o compilador nao reclamar
__asm
  MOV   R0,DPL
  INC   R0
  DJNZ  R0,DELAY1
  AJMP  FIMDELAY
  DELAY1:    MOV   R1,#50
  DELAY2:    DJNZ  R1,DELAY2
  DJNZ  R0,DELAY1
  FIMDELAY:  NOP
__endasm;
}

void Delay(void)
{
 //TMOD = 0x01;
 TL0 = 0x47;
 TH0 = 0xFF;
 TR0 = 1;
 while(!TF0);
 TR0 = 0;
 TF0 = 0;
} 

#endif /* end of include guard: DELAY_H */
