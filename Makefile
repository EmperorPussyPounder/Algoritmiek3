CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = standaard.o azul.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Azul

clean:
	rm -f *.o Azul

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

azul.o: azul.cc standaard.h constantes.h azul.h
	$(CC) $(CompileParms)  azul.cc

main.o: main.cc standaard.h constantes.h azul.h
	$(CC) $(CompileParms)  main.cc

