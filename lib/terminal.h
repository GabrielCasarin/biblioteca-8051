#ifndef TERMINAL_H
#define TERMINAL_H

#include <8051.h>

void CO (unsigned char dado)
/* Rotina para envio de caractere ao terminal */
{
  while (TI == 0) {}; /* Espera transmissor estar pronto para transmitir */
  TI = 0; /* Bloqueia transmissor */
  SBUF = dado;
  while (TI == 0) {};
}

char CI (void)
/* Rotina para recebe um caractere ASCII do terminal de video */
{
  while (RI == 0) {};
  RI = 0;
  return SBUF;
}

void print_terminal(char* cadeia, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    CO(cadeia[i]);
  }
}

#endif /* end of include guard: TERMINAL_H */
