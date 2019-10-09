#include "nbody.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printTimestamp();

int main(int argc, char** argv) {
  int n = argc > 1 ? atoi(argv[1]) : 1000;
  int size = 400;
  int nframes = argc > 2 ? atoi(argv[2]) : 500;

  Universe uni = newCircularUniverse(n, 250, 30);
  universeToCsv(uni, "state0.csv");

  printf("\nGalaxySim n-body simulation v1.0.1\n");
  printTimestamp();

  printf("Specifications:\n");
  printf("\tn = %d\n", n);
  printf("\timage dimensions = %dx%d\n", size, size);
  printf("\tframes = %d\n", nframes);
  printf("\n");

  char filename[20];
  clock_t t0, t1, total0, total1;
  double timeRendering = 0, timeComputing = 0;
  total0 = clock();
  for (int i = 0; i < nframes; i++) {
    sprintf(filename, "img/image%04d.pbm", i+1);

    t0 = clock();
    renderUniverse(uni, filename, 0, 0, 1, size, size);
    t1 = clock();
    timeRendering += (double)(t1 - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    iterateBarnesHut(&uni, 0.02);
    t1 = clock();
    timeComputing += (double)(t1 - t0) / CLOCKS_PER_SEC;
  }
  total1 = clock();

  printf("Done.\n");
  printf("Time used: %.3fs\n\n", (double)(total1 - total0) / CLOCKS_PER_SEC );
  printf("Time used rendering images and saving them to file:\n");
  printf("\t%.3fs total for %d frames\n", timeRendering, nframes);
  printf("\t%.3fms on average\n", timeRendering / nframes * 1000 );
  printf("\n");
  printf("Time used updating the universe state:\n");
  printf("\t%.3fs total for %d frames\n", timeComputing, nframes);
  printf("\t%.3fms on average\n", timeComputing / nframes * 1000 );
  printf("\n");

  return 0;
}


/* HELPER FUNCTIONS */

void printTimestamp() {
  time_t ltime = time(NULL);
  printf("%s\n",asctime(localtime(&ltime)));
}
