#ifndef INTERRUPTS
#define INTERRUPTS

/* habilita/desabilita global */
#define GLOBAL  (1 << 7)

/* não definido */
#define IE_6  (1 << 6)

/* não definido */
#define IE_5  (1 << 5)

/* ES porta serial */
#define ES  (1 << 4)

/* ET1 timer 1 */
#define ET1  (1 << 3)

/* EX1 externo 1 */
#define EX1  (1 << 2)

/* ET0 timer 0 */
#define ET0  (1 << 1)

/* EX0 externo 0 */
#define EX0  (1 << 0)

#endif
