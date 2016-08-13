/*
 * Modulo de rotinas para ajuste e controle do display LCD:
 * Modelo: HD44780U
 * Fabricante: Hitachi
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <8051.h>
#include "delay.h"

#define WDATA 	0x2010 /* Posicao de escrita de dados no display */
#define RDATA 	0x2030 /* Posicao de leitura de dados do display */
#define WCOMMAND 0x2000 /* Posicao de escrita de comandos no display */
#define RSTATUS 0x2020 /* Posicao de leitura de estado do display */

unsigned char __far __at (@WDATA) wdata;
unsigned char __far __at (@RDATA) rdata;
unsigned char __far __at (@WCOMMAND) wcommand;
unsigned char __far __at (@RSTATUS) rstatus;

void displaycommand (int cmd) {
  /* Rotina que envia comandos ao display */
  delay_asm(1);
  wcommand = cmd;
}

void displaydata (int car) {
  /* Testa Busy Flag antes de escrever */
  __asm
  BUSY:   MOV DPTR,#_rstatus
  MOVX A,@DPTR
  ANL A,#0x80
  JNZ BUSY
  __endasm;
  wdata = car;
}

/* Rotina que programa o display */
void progrdisplay (void) {
  displaycommand(0x38);  /* 2 linhas 5x7 */
  displaycommand(0x0C);  /* sem cursor */
  displaycommand(0x06);  /* escreve deslocando para a direita */
}

/* Rotina que limpa o display */
void cleardisplay (void) {
  displaycommand(0x01);
}

void retorno_carro (void) {
  /* Rotina que volta o cursor para o inicio da linha */
  displaycommand(0x80);
}

void line (int lin) {
  /* Rotina que seleciona a linha do display que será escrita */
  /* lin: seleciona a linha do display */
  if (lin == 1)
  displaycommand(0x80);  /* desloca cursor 1a.lin e 1a.col */
  else
  displaycommand(0xC0);  /* desloca cursor 2a.lin e 1a.col */
}

void print_display(char* cadeia, int len){
  int i = 0;
  cleardisplay();
  retorno_carro();
  while(len > 0){
	displaydata(cadeia[i]);
	i++;
	len--;
  }
}

#endif /* end of include guard: DISPLAY_H */
