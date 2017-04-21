CC = gcc
outfile = intal
CFlags = -c
intal: compile
	$(CC) intal_demo.o intal.o -o $(outfile)
compile: intal.c intal_demo.c
	$(CC) $(CFlags) intal_demo.c intal.c
clean: intal.o intal_demo.o
	rm *.o
