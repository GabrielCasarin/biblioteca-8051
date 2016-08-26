#include "teclado.h"
#include "interrupcoes.h"
#include "terminal.h"


#define FILTRO_ADDR 0x2700
unsigned char __far __at (@FILTRO_ADDR) filtro;
unsigned int overflows;

void init_timer0() {
/* Rotina de configuracao do timer 0*/
  IE |= 0x82;
  
  // modo 8 bit
  TMOD |= 0x02;
  TH0 = 0;

  overflows = 0;  
  filtro = 0xFF;
  
  // run
  TR0 = 1;
}

unsigned char __far __at 0xFFF3 vetor[] = {0x02,0xA0,0x0B};
void timer0_int (void) __interrupt (1) __using (1) {
  overflows++;
  
  if (overflows == 18) {
    filtro = 0xFF;
  }
  else if (overflows == 36) {
    filtro = 0x00;
    overflows = 0;
  }
}


void main(void) {
  IE = 0;
  init_timer0();
  
  while(1) {
  }
}
