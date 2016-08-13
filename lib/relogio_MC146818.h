/*
 * Modulo de rotinas para ajuste e controle do RTC (relogio de tempo real):
 * Modelo: MC146818
 * Fabricante: Motorola
 *
 */

#ifndef MC146818
#define MC146818

#include <8051.h>
#include "terminal.h"
#include "util.h"

#define REG_A 0x210A
#define REG_B 0x210B
#define REG_C 0x210C

__far unsigned char __at (@REG_A) reg_a;
__far unsigned char __at (@REG_B) reg_b;
__far unsigned char __at (@REG_C) reg_c;

__far unsigned char __at (@0x2100) segundos;
__far unsigned char __at (@0x2101) segundos_alarme;
__far unsigned char __at (@0x2102) minutos;
__far unsigned char __at (@0x2103) minutos_alarme;
__far unsigned char __at (@0x2104) horas;
__far unsigned char __at (@0x2105) horas_alarme;
__far unsigned char __at (@0x2106) dia_da_semana;
__far unsigned char __at (@0x2107) dia;
__far unsigned char __at (@0x2108) mes;
__far unsigned char __at (@0x2109) ano;

#define DV0 4
#define DV1 5
#define DV2 6

#define FORMATO24_12 1
#define DM 2
#define AIE 5
#define UIE 4
#define SET 7

void init_mc146818() {
/* Rotina de programacao do relogio */
  IE |= 0x81;

  reg_a = 0;
  reg_a |= (1 << DV1) | 0x06;
  reg_b  = 0;
  reg_b |= (1 << FORMATO24_12) | (1 << UIE);
}

void set_mc146818(
/* Rotina de atualizacao de horario */
  unsigned char _segundos,
  unsigned char _minutos,
  unsigned char _horas,
  unsigned char _dia,
  unsigned char _mes,
  unsigned char _ano)
{
    reg_b |= 0x80;

    segundos = _segundos;
    //segundos_alarme = 0x00;
    minutos = _minutos;
    //minutos_alarme = 0x00;
    horas = _horas;
    //horas_alarme = 0x00;
    dia_da_semana = 0x02;
    dia = _dia;
    mes = _mes;
    ano = _ano;

    reg_b &= 0x7F;
}


void atualizarDataHorario(char *datahora) {
  char _segundos,
       _minutos,
       _horas,
       _dia,
       _mes,
       _ano;
  char temp[2];

  temp[0] = datahora[0];
  temp[1] = datahora[1];
  _horas = ASCII_TO_BCD(temp);

  temp[0] = datahora[2];
  temp[1] = datahora[3];
  _minutos = ASCII_TO_BCD(temp);

  temp[0] = datahora[4];
  temp[1] = datahora[5];
  _segundos = ASCII_TO_BCD(temp);

  temp[0] = datahora[6];
  temp[1] = datahora[7];
  _dia = ASCII_TO_BCD(temp);

  temp[0] = datahora[8];
  temp[1] = datahora[9];
  _mes = ASCII_TO_BCD(temp);

  temp[0] = datahora[10];
  temp[1] = datahora[11];
  _ano = ASCII_TO_BCD(temp);

  set_mc146818(_segundos,_minutos,_horas,_dia,_mes,_ano);
}

void displayHorarioTerminal() {
    unsigned char segundos_str[2],
                  minutos_str[2],
                  horas_str[2],
				  dia_str[2],
                  mes_str[2],
                  ano_str[2];

    BCD_TO_ASCII(segundos, segundos_str);
    BCD_TO_ASCII(minutos, minutos_str);
    BCD_TO_ASCII(horas, horas_str);
    BCD_TO_ASCII(dia, dia_str);
    BCD_TO_ASCII(mes, mes_str);
    BCD_TO_ASCII(ano, ano_str);

	CO(' ');
	CO(horas_str[0]);
	CO(horas_str[1]);
	CO(':');
	CO(minutos_str[0]);
	CO(minutos_str[1]);
	CO(':');
	CO(segundos_str[0]);
	CO(segundos_str[1]);

	CO(' ');
	CO(dia_str[0]);
	CO(dia_str[1]);
	CO('/');
	CO(mes_str[0]);
	CO(mes_str[1]);
	CO('/');
	CO(ano_str[0]);
	CO(ano_str[1]);
}

#endif /* end of include guard: MC146818 */
