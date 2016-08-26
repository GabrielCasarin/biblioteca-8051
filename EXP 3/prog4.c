#include "teclado.h"
#include "interrupcoes.h"
#include "terminal.h"


#define FILTRO_ADDR 0x2700
unsigned char __far __at (@FILTRO_ADDR) filtro;
unsigned int contador, sentido;
#define MIN 0
#define MAX 200

void init_timer0() {
/* Rotina de configuracao do timer 0*/
  IE |= 0x82;
  
  // modo 8 bit
  TMOD |= 0x01;
  TH0 = 0xFF;
  TL0 = 0x66;
 
  contador = MIN;
  sentido = 1;
  
  // run
  TR0 = 1;
}

unsigned char __far __at 0xFFF3 vetor[] = {0x02,0xA0,0x0B};
void timer0_int (void) __interrupt (1) __using (1) {
   
  if (sentido)
    contador++;
  else
    contador--;

  if (contador == MIN) {
    sentido = 1;
  }
  else if (contador == MAX) {
    sentido = 0;
  }
	
  filtro = contador;
  
  TH0 = 0xFF;
  TL0 = 0x66;
}


void main(void) {
  unsigned char opcao = 0;
  IE = 0;
  init_timer0();
  
  while(1) {
  }
}