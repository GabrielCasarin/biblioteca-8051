@ECHO off
set x8051=J:\
set US=S:\

%x8051%\x8051 NL %US%\PROG.TXT PROG.OBJ
REM chama o assembler, NL -> Nao gera listagem

%x8051%\link2 PROG.DAT
REM chama o Linker, usa o arquivo .dat como instrucoes de arquivos para linkar