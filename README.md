# Biblioteca 8051
Rotinas desenvolvidas para o microcontrolador Intel 8051

Para compilar, utilize o SDCC:
```
sdcc --code-loc 0xA000 --xram-loc 0x8000 <codigo-fonte.c> (-I ../lib/)
```
