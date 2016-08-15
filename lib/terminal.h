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

void CHEX (unsigned char dado)  {
  unsigned char aux;
  aux = dado/0x10; /* desloca 4 bits para a direita - dado AB: pega 0x0A */
  if (aux<=0x09) { /* se A for número */
    aux = aux + 0x30; /* converte número em ASCII */
  }
  else { /* se A for letra */
    aux = aux + 0x37; /* converte letra em ASCII */
  }
  CO(aux); /* envia A em ASCII para o terminal de vídeo */
  aux = dado&0x0F; /* dado AB: pega 0x0B */
  if (aux<=0x09) /* se B for número */
    aux = aux + 0x30; /* converte número em ASCII */
  else /* se B for letra */
    aux = aux + 0x37; /* converte letra em ASCII */
  CO(aux); /* envia B em ASCII para o terminal de vídeo */

}

void print_terminal(char* cadeia, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    CO(cadeia[i]);
  }
}

#endif /* end of include guard: TERMINAL_H */
