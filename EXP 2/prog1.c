#include <8051.h>
#include "util.h"
#include "terminal.h"
#include "delay.h"
#include "display_HD44780U.h"
#include "ADC_0802.h"


void main(void) {
  unsigned int temp;
  unsigned char temp_str[] = "TEMP 00oC";
  int cont_timer;
  unsigned char limite_char[2];
  int limite;
  temp_str[7] = 0xDF;

  init_adc0802();
  progrdisplay();
  cleardisplay();
  CO('L');  CO('I');  CO('M');  CO('I');  CO('T');  CO('E');  CO(':');  CO(' ');
  limite_char[0] = CI();
  limite_char[1] = CI();
  limite = ASCII_TO_INT(limite_char);

  while(1) {

	for(cont_timer = 0; cont_timer < 100; ++cont_timer)
	   Delay();
	temp = ler_temperatura();
	INT_TO_ASCII(temp, temp_str + 5);

	retorno_carro();
	print_display(temp_str, 9);
	if (temp >=  limite) {
		print_terminal("EXPLODIU!",9);
	}

  }
}
