#ifndef TECLADO_H
#define TECLADO_H

#include <8051.h>

unsigned char KI() {
  unsigned char buf;
	unsigned int i = 0;

  buf = 0x0;

	// cria mascara com todos bits ativados
	P1 = 0xFF;
	while (buf == 0x0){
		// verifica primeira linha
		P1 = 0x7F;
		switch(P1&0x0F) {
			case 0x0E:
				buf = 0x43;
			break;
			case 0x0d:
				buf = 0x30;
			break;
			case 0x0b:
				buf = 0x38;
			break;
			case 0x07:
				buf = 0x34;
			break;
		}

		P1 = 0xBF;
		switch(P1&0x0F) {
			case 0x0E:
				buf = 0x44;
			break;
			case 0x0d:
				buf = 0x31;
			break;
			case 0x0b:
				buf = 0x39;
			break;
			case 0x07:
				buf = 0x35;
			break;
		}

		P1 = 0xDF;
		switch(P1&0x0F) {
			case 0x0E:
				buf = 0x45;
			break;
			case 0x0d:
				buf = 0x32;
			break;
			case 0x0b:
				buf = 0x41;
			break;
			case 0x07:
				buf = 0x36;
			break;
		}

		P1 = 0xEF;
		switch(P1&0x0F) {
			case 0x0E:
				buf = 0x46;
			break;
			case 0x0d:
				buf = 0x33;
			break;
			case 0x0b:
				buf = 0x42;
			break;
			case 0x07:
				buf = 0x37;
			break;
		}
	}

	for (i = -1; i > 0; i--){
	}
	while (P1 != 0xEF) {};

  return buf;

}

#endif
