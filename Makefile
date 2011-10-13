
GCC="gcc"
GCCOPT="-Wall"

##########################################################
COMPILE=$(GCC) $(GCCOPT)

uebung1: gennum.o sortnum.o
	$(COMPILE) -o uebung1.out sortieren.c gennum.o sortnum.o

clean:
	rm -f *.o
	rm -f *.out

gennum.o:
	$(COMPILE) -c gennum.c

sortnum.o:
	$(COMPILE) -c sortnum.c
