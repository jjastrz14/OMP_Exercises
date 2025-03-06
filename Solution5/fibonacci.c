/*  Adapted from:
 *  OpenMP lecture exercises
 *  Copyright (C) 2011 by Christian Terboven <terboven@rz.rwth-aachen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You shoud have received a copy of the GNU General Public License
 *  a with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include <stdio.h>
#include <omp.h>

#define MAX 10

int ser_fib(int n) {
  int x, y;
  if (n < 2)
    return n;

  x = ser_fib(n - 1);
  y = ser_fib(n - 2);
  return x+y;
}

int par_fib(int n) {
  int x, y;
  if (n < 2) 
    return n;
  else if (n < 30)
    return ser_fib(n);

  #pragma omp task shared(x)
  {
    x = par_fib(n - 1);
  }

  #pragma omp task shared(y)
  {
    y = par_fib(n - 2);
  }

  #pragma omp taskwait
  return x+y;
}

int if_fib(int n) {
  int x, y;
  if (n < 2)
    return n;
  
  #pragma omp task shared(x) if(n>30)
  {
    x = if_fib(n - 1);
  }

  #pragma omp task shared(y) if(n>30)
  {
    y = if_fib(n - 2);
  }

  #pragma omp taskwait
  return x+y;
}

int main() {

  int j, n, ser_fibonacci, if_fibonacci, par_fibonacci;

  double init_time, ser_time = 0., if_time=0., par_time=0.;

  printf("Please insert n, to calculate fib(n): \n");
  scanf("%d",&n);

   init_time = omp_get_wtime();
   ser_fibonacci = ser_fib(n);
   ser_time = omp_get_wtime() - init_time;
   printf("Serial:         \tser_fib(%d)\t = %d in %f secs\n",n,ser_fibonacci,ser_time);

   for (j=2; j<=MAX; j+=2){
      omp_set_num_threads(j);
      init_time = omp_get_wtime();
      #pragma omp parallel
      {
           #pragma omp single
           {
               printf("num threads = %d:\t",omp_get_num_threads());
               if_fibonacci = if_fib(n);
           }
       }
       if_time = omp_get_wtime() - init_time;
       printf("if_fib(%d)\t = %d in %f secs\n",n,if_fibonacci,if_time);

     
      omp_set_num_threads(j);
      init_time = omp_get_wtime();
      #pragma omp parallel
      {
           #pragma omp single
           {
               printf("num threads = %d:\t",omp_get_num_threads());
               par_fibonacci = par_fib(n);
           }
       }
       par_time = omp_get_wtime() - init_time;
       printf("par_fib(%d)\t = %d in %f secs\n",n,par_fibonacci,par_time);
   }

  return 0;
}
