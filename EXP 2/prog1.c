#include <8051.h>
#include "terminal.h"
#include "display_HD44780U.h"
#include "ADC_0802.h"

void main(void) {
  unsigned int temp;

  progrdisplay();
  cleardisplay();  

  init_adc0802();
    
  while(1) {
    temp = ler_temperatura();
    	
    CO(' ');
    CHEX((char)temp);
	
	//cleardisplay();
	//retorno_carro();
	//displaydata(temp);
  }
}
