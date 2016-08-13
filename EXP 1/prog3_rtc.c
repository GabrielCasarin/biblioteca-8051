/* Timer 1 é utilizado para gerar a taxa de comunicação, sem uso de interrupção */

/* Canal serial: mode = 1 (8-bit UART Serial Port) com uso de interrupção */

#include <8051.h>
#include "terminal.h"
#include "mc146818.h"

#define BUFIN_MAX 13
char bufin[BUFIN_MAX];
int bufin_cont = 0;
int chegou_ao_fim_bufin = 0;

void atualiza_bufin(char char_novo) {
 /* acrescenta o recém-chegado caractere ao buffer de entrada
  * caso tal caractere seja CR, ecoa a string formada
  */

  if (char_novo == 13) {
    bufin[bufin_cont++] = '\0';
    chegou_ao_fim_bufin = 1;
  }
  else {
    bufin[bufin_cont++] = char_novo;
    if (bufin_cont == BUFIN_MAX-1) {
      bufin[bufin_cont] = '\0';
      chegou_ao_fim_bufin = 1;
    }
  }
  /* verifica se eh para ecoar */
  if (chegou_ao_fim_bufin) {
    int i;
    /* ATUALIZA */
    //print_terminal(bufin, bufin_cont);
	atualizarDataHorario(bufin);
    /* limpa o buffer */
    for(i = 0; i < bufin_cont; ++i) {
      bufin[i] = '\0';
    }
    bufin_cont = 0;
    chegou_ao_fim_bufin = 0;
  }
}

void init_serial(void)
{
  /* Timer 1 é utilizado para gerar a taxa de comunicação */
  PCON = 0x00; /* SMOD=0, no modo 1, divide o clock por 32 */
  SCON = 0x52;  /* Seleciona modo 1: UART, 8 bits, clock do Timer 1 */
                /* SCON.4 - REN=1(habilita a recepção) */
                /* SCON.1 - TI=1 (transmissor pronto) */
                /* SCON.0 - RI=0 (receptor vazio) */
  TMOD = 0x20; /* Configura timer 1: modo 2, 8 bits, auto reload */
  TH1 = 0xFD; /* divisão para 9.600 baud */
  TR1 = 1; /* TCON.6 - dispara timer 1 */
  IE = 0x90; /* IE.4– habilita interrupção do canal serial e IE.7- global */
}

unsigned char __far __at 0xFFF0 vetorRel[] = {0x02, 0xA0, 0x03};
void ext0_int (void) __interrupt 0 __using 1 {
  char ctemp;
       ctemp = reg_c;

  displayHorarioTerminal();  
}

unsigned char __far __at 0xFFFC vetorSer[] = {0x02,0xA0,0x23};
void interrupt_serial (void) __interrupt 4 __using 1
{
  unsigned char AUX;
  if (RI == 1)
  {
    /* Se for interrupção de recepção: */
    RI = 0; /* limpa pedido de interrupção de recepção */
    AUX = SBUF; /* Retira caractere recebido do buffer */
	if (AUX == 'a') {
      IE &= 0xFE;
    }
	else if (AUX == 13) {
	  IE |= 0x01;
	}
	else {
      atualiza_bufin(AUX); /* Envia caractere recebido para rotina de tratamento de evento de novo caractere */
	}
  }
}

void main(void)
{
  char _dia = 0x08,
       _mes = 0x08,
       _ano = 0x16;

  init_serial();
  init_mc146818();
  set_mc146818(0, 0, 0, _dia, _mes, _ano);

  while(1);

}
