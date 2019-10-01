make:
	gcc main.c nbody.c bodies.c image.c -o nbody -O2 --pedantic -Wall

clean:
	rm img/*.pgm

gif:
	convert -delay 4 -loop 0 img/*.pgm img/image.gif