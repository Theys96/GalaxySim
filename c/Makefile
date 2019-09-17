make:
	gcc nbody.c bodies.c image.c -o nbody -O2 --pedantic -Wall -lm

omp:
	gcc-9 nbody.c bodies.c image.c -o nbody -O2 --pedantic -Wall -lm -fopenmp

clean:
	rm *.pgm
