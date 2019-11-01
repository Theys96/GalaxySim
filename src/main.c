#include "nbody.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define str(x) #x
#define xstr(x) str(x)

#define CURRENT_MAIN defaultMain
#define VERSION "v1.2.3"

/* PARAMETERS */
int n = 1000;
int size = 400;
int nframes = 500;
int r = 250;
double dt = 0.02;
double delta_barnes_hut = 0.5;
typedef enum { Euler = 0, BarnesHut = 1, MostSignificant = 2 } Method;
Method method = Euler;

// Main functions:
int defaultMain(int argc, char** argv);
int customMain_energies(int argc, char** argv);
int customMain_collisions(int argc, char** argv);

// Helper functions:
void simulate(Universe uni, int saveImage, double *timeRendering, double *timeComputing);
void printTimestamp();
void printTitle();
void readParameters();
char* methodString(Method method);



int main(int argc, char** argv) {
  // CURRENT COMPILED MAIN FUNCTION:
  return CURRENT_MAIN(argc, argv);
}



int defaultMain(int argc, char** argv) {

  if (argc > 1) {
    delta_barnes_hut = atof(argv[1]);
  }

  readParameters();

  printTitle();

  printf("\nSpecifications:\n");
  printf("\tn                 = %d\n", n);
  printf("\timage dimensions  = %dx%d\n", size, size);
  printf("\tframes            = %d\n", nframes);
  printf("\titeration method  = %s\n", methodString(method));
  if (method == BarnesHut) {
    printf("\tdelta barnes hut  = %f\n", delta_barnes_hut);
  }
  printf("\n");

  Universe uni = newCircularUniverse(n, r, 30, newBody(0, 0, 0, 0, 0, 0, 1000*n)));
  universeToCsv(uni, "state0.csv");

  double energy0 = totalEnergy(uni);

  clock_t total0, total1;
  double timeRendering = 0, timeComputing = 0;
  total0 = clock();
  simulate(uni, 1, &timeRendering, &timeComputing);
  total1 = clock();

  double energy1 = totalEnergy(uni);
  double energyDiff = energy1-energy0;

  printf("Done.\n");
  printf("%s %.2lf%% of the universe's energy during this simulation.\n", energyDiff > 0 ? "Gained" : "Lost", fabs(energyDiff)/energy0*100);
  printf("\n");

  printf("Time used: %.3fs\n\n", (double)(total1 - total0) / CLOCKS_PER_SEC );
  printf("Time used rendering images and saving them to file:\n");
  printf("\t%.3fs total for %d frames\n", timeRendering, nframes);
  printf("\t%.3fms on average\n", timeRendering / nframes * 1000 );
  printf("\n");
  printf("Time used updating the universe state:\n");
  printf("\t%.3fs total for %d frames\n", timeComputing, nframes);
  printf("\t%.3fms on average\n", timeComputing / nframes * 1000 );
  printf("\n");

  // save
  FILE * fp = fopen ("analysis/delta_barnes_variation.csv", "a");
  fprintf (fp, "%d,%f,%.5f,%.3f\n", n, delta_barnes_hut, energyDiff/energy0, (double)(total1 - total0) / CLOCKS_PER_SEC);
  fclose (fp);

  return 0;
}


/* CUSTOM MAIN FUNCTIONS (FOR SPECIFIC EXPERIMENTS) */

// For measuring energy discrepancies
int customMain_energies(int argc, char** argv) {

  if (argc < 6) {
    printf("Error: required parameters: <method> <dt> <nframes> <repeats> <file>\n");
    return 0;
  }

  printTitle();
  printf("CUSTOM program for measuring energy discrepancies.\n\n");

  n = 200;
  method = (Method)atoi(argv[1]);
  dt = atof(argv[2]);
  nframes = atoi(argv[3]);
  int repeats = atoi(argv[4]);
  char* filename = argv[5];

  printf("dt = %.2lf\n", dt);
  printf("method = %s\n", methodString(method));
  printf("n (bodies) = %d\n", n);
  printf("nframes = %d\n", nframes);
  printf("\n");

  FILE* csv = fopen(filename, "a");
  Universe uni;
  for (int it = 0; it < repeats; it++ ) {
    uni = newCircularUniverse(n, r, 30, newBody(0, 0, 0, 0, 0, 0, 1000*n)));
    double energy0 = totalEnergy(uni);
    simulate(uni, 0, NULL, NULL);
    double energy1 = totalEnergy(uni);
    double energyDiff = energy1-energy0;
    printf("%+.3lf%%\n", energyDiff/energy0*100);
    fprintf(csv, "%d,%.5lf\n", nframes, energyDiff/energy0);
    freeUniverse(uni);
  }
  fclose(csv);

  return 0;
}

// For showing the collisions
int customMain_collisions(int argc, char** argv) {

  if (argc > 1) {
    delta_barnes_hut = atof(argv[1]);
  }

  scale = 6.0;

  Universe uni1 = newCircularUniverse(n, r, 30, newBody(0, 0, 0, 0, 0, 0, 1000*n)));
  Universe uni2 = newCircularUniverse(n, r, 30, newBody(600, 600, 0, 0, -50, 10, 1000*n), newBody(600, 600, 0, 0, -50, 10, 1000*n));
  Universe uni;
  uni.n = uni1.n + uni2.n;
  uni.bodies = calloc(uni.n, sizeof(Body));
  memcpy(uni.bodies, uni1.bodies, sizeof(Body) * uni1.n);
  memcpy(uni.bodies + uni1.n, uni2.bodies, sizeof(Body) * uni2.n);
  universeToCsv(uni, "state0.csv");
  simulate(uni, 1, NULL, NULL);

  return 0;
}


/* HELPER FUNCTIONS */

void simulate(Universe uni, int saveImage, double *timeRendering, double *timeComputing) {
  char filename[20];
  clock_t t0, t1;
  for (int i = 0; i < nframes; i++) {
    if (saveImage) {
      sprintf(filename, "img/image%04d.pbm", i+1);

      if (timeRendering != NULL) {
        t0 = clock();
      }
      // center the first galaxy in the image
      renderUniverse(uni, filename, uni.bodies[0].x, uni.bodies[0].y, scale, size, size);
      // center origin of the coordinate system in the image
      // renderUniverse(uni, filename, 0, 0, scale, size, size);
      if (timeRendering != NULL) {
        t1 = clock();
        *timeRendering += (double)(t1 - t0) / CLOCKS_PER_SEC;
      }
    }

    if (timeComputing != NULL) {
      t0 = clock();
    }
    switch (method) {
      default:
      case Euler:
        iterateEuler(&uni, dt);
        break;

      case BarnesHut:
        iterateBarnesHut(&uni, dt);
        break;

      case MostSignificant:
        iterateMostSignificant(&uni, dt, 1000);
        break;
    }
    if (timeComputing != NULL) {
      t1 = clock();
      *timeComputing += (double)(t1 - t0) / CLOCKS_PER_SEC;
    }
  }
}

void printTitle() {
  printf("\nGalaxySim n-body simulation %s\n", VERSION);
  printTimestamp();
}

void printTimestamp() {
  time_t ltime = time(NULL);
  printf("%s",asctime(localtime(&ltime)));
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
