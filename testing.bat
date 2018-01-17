@echo off
set file =src\UVa11799 - Horror Dash.cpp
del src\*.exe
del src\*.o
echo Archivo: %1
echo.
echo ------------------COMPILACION------------------------
c++ -lm -O2 -std=c++11 -pipe -DONLINE_JUDGE %1
if %ErrorLevel% == 0 (
	echo Compilacion correcta
	echo -------------------SALIDA-------------------------
	a < test.in > mytest.out

) else (
	echo Error de compilacion
)
