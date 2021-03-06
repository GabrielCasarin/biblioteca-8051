/*
 * Modulo de rotinas para ajuste e controle do ADC (conversor analogico-digital) :
 * Modelo: ADC0802
 * Fabricante: National
 *
 */

#ifndef ADC_H
#define ADC_H

#include <8051.h>
#include "interrupcoes.h"

#define ADC_ADDR 0x2200 /* posicao de acionamento do processo de conversao */
unsigned char __far __at (@ADC_ADDR) ADC;

volatile unsigned char leu;
volatile unsigned int leitura_atual;

void init_adc0802() {
/* rotina de inicializacao da interrupcao EXT1 utilizada pelo ADC0802 */
  IE |= GLOBAL | EX1;
}

unsigned char __far __at 0xFFF6 vetorEX1[] = {0x02, 0xA0, 0x13};
void ext1_int() __interrupt 2 __using 1 {
  leitura_atual = ADC;
  leu = 1;
}

unsigned int ler_temperatura() {
/* sub-rotina que retorna a temperatura atual, vinda via interrupcao */

  leu = 0;
  ADC = 0; // provoca uma comparacao no ADC

  while (!leu) {}

  return (unsigned int) leitura_atual*0.242;
}



#endif
