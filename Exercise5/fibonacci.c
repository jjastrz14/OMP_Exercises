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

int ser_fib(int n) {
  int x, y;
  if (n < 2)
    return n;

  x = ser_fib(n - 1);
  y = ser_fib(n - 2);
  return x+y;
}


int main() {

  int n, ser_fibonacci, if_fibonacci, par_fibonacci;

  double starttime, ser_time = 0., if_time=0., par_time=0.;

  printf("Please insert n, to calculate fib(n): \n");
  scanf("%d",&n);

  starttime = omp_get_wtime();
  ser_fibonacci = ser_fib(n);
  ser_time = omp_get_wtime() - starttime;
  printf("ser_fib(%d)=%d \n", n, ser_fibonacci);
  printf("ser_fib calculation took %lf sec\n", ser_time);
  return 0;
}
