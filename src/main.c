#include "nbody.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define str(x) #x
#define xstr(x) str(x)

/* PARAMETERS */
int n = 1000;
int size = 400;
int nframes = 500;
int r = 250;
typedef enum { Euler, BarnesHut, MostSignificant } Method;
Method method = Euler;

void printTimestamp();
void readParameters();
char* methodString(Method method);

int main(int argc, char** argv) {

  readParameters();

  printf("\nGalaxySim n-body simulation v1.2.1\n");
  printTimestamp();

  printf("Specifications:\n");
  printf("\tn                 = %d\n", n);
  printf("\timage dimensions  = %dx%d\n", size, size);
  printf("\tframes            = %d\n", nframes);
  printf("\titeration method  = %s\n", methodString(method));
  printf("\n");

  Universe uni = newSpiralUniverse(n, r, 30);
  universeToCsv(uni, "state0.csv");

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
    switch (method) {
      default:
      case Euler:
        iterateEuler(&uni, 0.02);
        break;

      case BarnesHut:
        iterateBarnesHut(&uni, 0.02);
        break;

      case MostSignificant:
        iterateMostSignificant(&uni, 0.02, 1000);
        break;
    }
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

void readIntegerParameter(char* question, int* val) {
  int x;
  printf("%s", question);
  printf(" (%d)? ", *val);
  scanf("%d", &x);
  *val = x == 0 ? *val : x;
}

void readParameters() {
  readIntegerParameter("Number of bodies", &n);
  readIntegerParameter("Galaxy radius", &r);
  readIntegerParameter("Image size", &size);
  readIntegerParameter("Number of frames", &nframes);

  getchar();
  char c;
  printf("Iteration method (e = Euler, b = Barnes-Hut, m = Most-Significant)? ");
  scanf("%c", &c);
  switch (c) {
    default:
    case 'e':
      method = Euler; break;
    case 'b':
      method = BarnesHut; break;
    case 'm':
      method = MostSignificant; break;
  }
}

char* methodString(Method method) {
  switch (method) {
    default:
    case Euler:
      return "Euler";
    case BarnesHut:
      return "Barnes-Hut";
    case MostSignificant:
      return "Most-Significant";
  }
}
