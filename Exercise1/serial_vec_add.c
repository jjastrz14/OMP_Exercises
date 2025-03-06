#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifdef _OPENMP
 #include <omp.h>
#endif

int main(int argc, char *argv[]) {
  int i;
  int n = 10000000;

  float *a;
  float *b;
  float *c;

  printf("Vector addition\n");
  printf("\tC/OpenMP version\n");
  printf("\n");
  printf("\tA program which adds two vector.\n");

  /*
   * Allocate the vector data.
   */

  a = (float *)malloc(n * sizeof(float));
  b = (float *)malloc(n * sizeof(float));
  c = (float *)malloc(n * sizeof(float));

  for (i = 0; i < n; i++) {
    a[i] = (float)(1);
    b[i] = (float)(2);
    c[i] = (float)(0);
  }

  #ifdef _OPENMP
    double tick = omp_get_wtime();
  #else
    clock_t tick = clock();
  #endif

  for (i = 0; i < n; i++){
    c[i] = a[i] + b[i];
  }

  #ifdef _OPENMP
    double tock = omp_get_wtime();
  #else
    clock_t tock = clock();
  #endif

  /*
    Print a few entries.
  */
  printf("\n");
  printf("   i        a[i]        b[i]      c[i] = a[i] + b[i]\n");
  printf("\n");
  for (i = 0; i < n && i < 10; i++) {
    printf("  %2d  %10.4f  %10.4f  %10.4f\n", i, a[i], b[i], c[i]);
  }
  /*
    Free memory.
  */
  free(a);
  free(b);
  free(c);
  /*
    Terminate.
  */
  printf("\n");
  printf("Vector addition\n");
  printf("  Normal end of execution.\n");

  printf("===================================== \n");
  #ifdef _OPENMP
    printf("Work took %f seconds\n", (tock - tick) );
  #else
    double t = tock - tick; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("Work took %f seconds\n", time_taken);
  #endif
  printf("===================================== \n");

  return 0;
}


