#include "teclado.h"
#include "interrupcoes.h"
#include "terminal.h"


#define DA_REG_ADDR 0x2700
unsigned char __far __at (@DA_REG_ADDR) DA_REG;


void main(void) {
  unsigned char nivel_in[5] = "000 ";
  unsigned int nivel = 0;
  DA_REG = 0;
  
  while(1) {
    nivel_in[0] = KI();
    nivel_in[1] = KI();
    nivel_in[2] = KI();
	
	print_terminal(nivel_in, 4);
	
	nivel = (nivel_in[0] - 0x30)*100 + (nivel_in[1] - 0x30)*10 + (nivel_in[2] - 0x30);
	
	DA_REG = nivel;

  }
}
