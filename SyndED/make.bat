@ECHO OFF
REM cl /Wall synded.c csvoutput.c mapwho.c asprintf.c /link /out:synded.exe
cl /W4 synded.c csvoutput.c mapwho.c asprintf.c /link /out:synded.exe
