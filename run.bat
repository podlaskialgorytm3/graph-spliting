@echo off
rem Create directories build/executable and build/object_files if they do not exist
if not exist build\object-files mkdir build\object-files

rem Compile the .c source files to .o object files
gcc -c src\main.c -o build\object-files\main.o
gcc -c src\graph.c -o build\object-files\graph.o


rem Link object files into an executable
gcc build\object-files\main.o build\object-files\graph.o -o program.exe

rem End of script