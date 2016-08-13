#ifndef SERIAL_H
#define SERIAL_H

#include <8051.h>

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

#endif /* end of include guard: SERIAL_H */
