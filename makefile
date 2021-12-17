all: stringProg

stringProg: hw33.c
	gcc -g hw33.c -o stringProg

clean:
	rm stringProg