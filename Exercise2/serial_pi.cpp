/* Exercise: Pi
 *  *
 *   * In this exercise you will determine the value
 *    * of PI using the integral  of
 *     *    4/(1+x*x) between 0 and 1.
 *      *
 *       * The integral is approximated by a sum of n intervals.
 *        *
 *         * The approximation to the integral in each interval is:
 *          *    (1/n)*4/(1+x*x).
 * * * * * * */

#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <omp.h>
#include <cstdlib>

inline constexpr std::size_t INTERVALS{10000000000};
inline constexpr long double TRUE_PI{3.1415926535897932384626433832795L};

//TO COMPILE WITH -std = c++20 OR 23

int main()
{
    double x(0.0), dx(1.0 / static_cast<double>(INTERVALS)), f(0.0), sum(0.0), pi(0.0);

    double time2{0.0};
    double time3{0.0};
    double time1a{omp_get_wtime()};

    std::cout << "Number of intervals: " << INTERVALS << std::endl;

    // option 1 with critical and atomic 
    #pragma omp parallel for default(none) private(x, f) shared(dx, INTERVALS, sum)
    for (std::size_t i = 1; i <= INTERVALS; i++)
    {
        x = dx * (static_cast<double>(i) - 0.5);
        f = 4.0 / (1.0 + x * x);
    #pragma omp atomic
        sum += f;
    }

    pi = dx * sum;

    time2 = omp_get_wtime() - time1a;

    long double error1((TRUE_PI - static_cast<long double>(pi))/TRUE_PI);

    std::cout << "Computed PI: " << std::setprecision(25) << pi << std::endl
            << "True PI: " << std::setprecision(25) << TRUE_PI << std::endl
            << "Estimate error: " <<  std::abs(error1) << std::endl
            << "Elapsed time (s) = " << time2 << std::endl;

    double time1b{omp_get_wtime()};

    // option 2 reduction
    #pragma omp parallel for default(none) private(x, f) shared(dx, INTERVALS) reduction(+:sum)
    // Using OpenMP to parallelize the loop for better performance
    for (std::size_t i = 1; i <= INTERVALS; i++)
    {
        x = dx * (static_cast<double>(i) - 0.5);
        f = 4.0 / (1.0 + x * x);
        sum += f;
    }

    pi = dx * sum;
    
    time3 = omp_get_wtime() - time1b;

    long double error2((TRUE_PI - static_cast<long double>(pi))/TRUE_PI);

    std::cout << "Computed PI: " << std::setprecision(25) << pi << std::endl
            << "True PI: " << std::setprecision(25) << TRUE_PI << std::endl
            << "Estimate error: " <<  std::abs(error2) << std::endl
            << "Elapsed time (s) = " << time3 << std::endl;

    return 0;
}

