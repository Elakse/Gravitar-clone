all: Gravitar

Gravitar: main.o polilinea.o color.o nave.o
	gcc main.o polilinea.o color.o nave.o -o Gravitar -lm -lSDL2

main.o: main.c config.h polilinea.h nave.h
	gcc -c main.c -Wall -std=c99 -pedantic -Werror -o main.o

polilinea.o: polilinea.c color.h polilinea.h
	gcc -c polilinea.c -Wall -std=c99 -pedantic -Werror -o polilinea.o

color.o: color.c color.h
	gcc -c color.c -Wall -std=c99 -pedantic -Werror -o color.o

nave.o: nave.c nave.h
	gcc -c nave.c -Wall -std=c99 -pedantic -Werror -o nave.o
