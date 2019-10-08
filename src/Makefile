make:
	gcc main.c nbody.c bodies.c image.c tree.c -o nbody -O2 --pedantic -Wall -lm

clean:
	rm img/*.pbm

gif:
	convert -delay 4 -loop 0 img/*.pbm img/image.gif