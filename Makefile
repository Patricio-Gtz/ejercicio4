#HEADERS = funciones.h

default: tarea4.out

tarea4.o: tarea4.c #$(HEADERS)
	gcc -c tarea4.c -o tarea4.o

tarea4.out: tarea4.o
	gcc tarea4.o -o tarea4.out

clean:
	-rm -f tarea4.o
	-rm -f tarea4.out
