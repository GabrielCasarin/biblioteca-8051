#ifndef UTIL_H
#define UTIL_H

unsigned char ASCII_TO_BCD(unsigned char ascii_text[2]) {
  /* rotina que converte dois caracteres ASCII para código BCD (em byte)*/
  unsigned char bcd_value;

  ascii_text[1] -= 0x30;
  ascii_text[0] -= 0x30;
  ascii_text[0] = (unsigned char) ascii_text[0] << 4;
  bcd_value = (unsigned char) ascii_text[0] | ascii_text[1];

  return bcd_value;
}

void BCD_TO_ASCII(unsigned char bcd_value, unsigned char* ascii_text) {
  ascii_text[1] = ((unsigned char) bcd_value&0x0F) + 0x30;
  ascii_text[0] = ((unsigned char) bcd_value>>4) + 0x30;
}

void INT_TO_ASCII(unsigned char int_value, unsigned char* ascii_text) {
  unsigned char resto = int_value%10;
  ascii_text[1] = resto + 0x30;
  ascii_text[0] = int_value/10 + 0x30;
}

int ASCII_TO_INT(unsigned char ascii_text[2]) {
  ascii_text[1] -= 0x30;
  ascii_text[0] -= 0x30;
  
  return (int) ascii_text[0]*10 + ascii_text[1];
}

#endif /* end of include guard: UTIL_H */
