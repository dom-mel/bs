
uebung1: gennum.o sortnum.o
	gcc -Wall -O2 -lpthread -o uebung2.out sortieren.c gennum.o sortnum.o

clean:
	rm -f *.o
	rm -f *.out

gennum.o:
	gcc -Wall -O2 -c gennum.c

sortnum.o:
	gcc -Wall -O2 -c sortnum.c
