#ifndef TIMER_8254_H
#define TIMER_8254_H

#define SC1 (1 << 7)
#define SC0 (1 << 6)
#define RW1 (1 << 5)
#define RW0 (1 << 4)
#define M2 (1 << 3)
#define M1 (1 << 2)
#define M0 (1 << 1)
#define BCD (1 << 0)

unsigned char __far __at (@0x2300) TIMER0_8254;
unsigned char __far __at (@0x2303) PALAVRA_CONTROLE;


void init_timer0_8254() {
  PALAVRA_CONTROLE = 0;
  PALAVRA_CONTROLE = RW1 | RW0 | M1 | M0;
}

void set_timer0_8254(unsigned int periodo) {
  TIMER0_8254 = periodo; // LSB
  TIMER0_8254 = periodo >> 8; // MSB
}

#endif
