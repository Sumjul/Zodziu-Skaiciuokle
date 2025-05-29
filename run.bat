@echo off
setlocal
cmake -B build -S . 
cmake --build build
build\Zodziu_Skaiciuokle.exe
endlocal
