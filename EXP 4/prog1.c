#include <8051.h>
#include "notas_cromaticas_ocidentais.h"
#include "timer_8254.h"

void Delay(void) {
 TMOD = 0x01;
 TL0 = 0x47;
 TH0 = 0xFF;
 TR0 = 1;
 while(!TF0);
 TR0 = 0;
 TF0 = 0;
}

void tocar_nota(NOTA nota, int oitava, int duracao) {
  unsigned int freq;
  unsigned int duracao_fundamental = 0x47FF,
               temp;
  if (nota != PAUSA) {
    freq = 51200/N[nota][oitava];
    set_timer0_8254(freq);
  }
  else {
    set_timer0_8254(0);
  }
  for (temp = 0; temp < 1800*duracao; ++temp) {
    Delay();
  }
}

unsigned int __far __at (@0x9500) Lacrimosa_Soprano[][3] =
{
  // compasso 1
  {LA, 4, 4},
  {FA, 5, 1},
  {RE, 5, 1},
  {RE, 5, 3},
  {DO_H, 5, 1},
  {PAUSA, 0, 2},

  // compasso 2
  {LA, 4, 4},
  {FA, 5, 1},
  {RE, 5, 1},
  {RE, 5, 3},
  {DO_H, 5, 1},
  {PAUSA, 0, 2},

  // etc
  {RE, 4, 2},
  {PAUSA, 0, 1},
  {MI, 4, 2},
  {PAUSA, 0, 1},
  {FA, 4, 2},
  {PAUSA, 0, 1},
  {SOL, 4, 2},
  {PAUSA, 0, 1},

  {LA, 4, 2},
  {PAUSA, 0, 1},
  {SI, 4, 2},
  {PAUSA, 0, 1},
  {DO, 5, 2},
  {PAUSA, 0, 1},
  {RE, 5, 2},
  {PAUSA, 0, 1},


  {RE_H, 5, 3},
  {MI, 5, 3},
  {FA, 5, 3},
  {FA_H, 5, 3},
  {SOL, 5, 3},
  {SOL_H, 5, 3},
  {LA, 5, 3},
  {LA, 4, 1},
  {PAUSA, 0, 2},


  {LA, 4, 4},
  {LA_H, 4, 1},
  {LA, 4, 1},
  {LA, 4, 4},
  {FA, 5, 1},
  {RE, 5, 1},
  {DO_H, 5, 4},
  {RE, 5, 1},
  {MI, 5, 1},
  {MI, 5, 3},
  {RE, 5, 2},
  {PAUSA, 0, 1},


  {RE_H, 5, 4},
  {SOL, 5, 1},
  {MI, 5, 1},
  {MI, 5, 3},
  {RE, 5, 1},
  {PAUSA, 0, 2},
  {RE, 5, 4},
  {FA, 5, 1},
  {MI, 5, 1},
  {MI, 5, 3},
  {RE, 5, 1},
  {PAUSA, 0, 2},


  {RE, 5, 4},
  {SOL, 5, 1},
  {FA, 5, 1},
  {FA, 5, 3},
  {MI, 5, 2},
  {PAUSA, 0, 1},

  {MI, 5, 6},
  {LA, 4, 1},
  {LA, 4, 3},
  {LA, 4, 2},
  {PAUSA, 0, 1},


  {SI, 4, 3},
  {DO, 5, 3},
  {RE, 5, 3},
  {RE, 5, 3},
  {RE, 5, 3},
  {DO, 5, 3},
  {SI, 4, 3},
  {SI, 4, 3},


  {SI, 4, 3},
  {DO, 5, 3},
  {RE, 5, 3},
  {DO, 5, 2},
  {FA, 5, 1},
  {FA, 5, 4},
  {RE, 5, 1},
  {SI, 4, 1},
  {DO, 5, 4},
  {LA_H, 4, 1},
  {SOL, 4, 1},
  {FA, 4, 2},
  {PAUSA, 0, 10},

  // interludio
  {FA, 5, 1},
  {FA, 4, 1},
  {LA_H, 4, 1},
  {FA, 5, 1},
  {RE, 5, 1},
  {SI, 4, 1},
  {DO, 6, 1},
  {LA, 5, 1},
  {DO, 5, 2},
  {LA_H, 5, 1},
  {SOL, 5, 1},
  //
  {FA, 4, 1},
  {MI, 5, 1},
  {FA, 5, 1},
  {RE, 5, 1},
  {DO_H, 6, 1},
  {RE, 6, 1},
  {LA_H, 4, 1},
  {RE, 5, 1},
  {DO_H, 5, 1},
  {LA, 4, 1},
  {LA, 5, 1},
  {DO, 5, 1},

  {LA, 4, 4},
  {FA, 5, 1},
  {RE, 5, 1},
  {RE, 5, 3},
  {DO_H, 5, 1},
  {PAUSA, 0, 2},
  {LA, 4, 4},
  {FA, 5, 1},
  {RE, 5, 1},
  {RE, 5, 3},
  {DO_H, 5, 1},
  {PAUSA, 0, 2},

  {PAUSA, 0, 6},
  {RE, 5, 3},
  {DO, 5, 3},

  {LA_H, 4, 3},
  {LA, 4, 3},
  {SOL, 4, 3},
  {FA, 4, 3},


  {MI, 4, 3},
  {RE, 4, 3},
  {DO_H, 4, 3},
  {RE, 4, 3},
  {MI, 4, 3},
  {FA, 4, 3},
  {MI, 4, 3},
  {MI, 4, 3},

  {RE, 4, 2},
  {PAUSA, 0, 10},

  {RE, 5, 12},
  {RE, 5, 12},

  {FIM, 0, 0}
};

void executar() {
  unsigned int i;

  for(i = 0; i < 200; ++i) {
    tocar_nota(Lacrimosa_Soprano[i][0], Lacrimosa_Soprano[i][1], Lacrimosa_Soprano[i][2]);
  }
}


void main(void) {
  init_timer0_8254(); // timer externo
  executar();

  while (1) {}
}
