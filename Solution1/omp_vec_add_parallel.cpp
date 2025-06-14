#include <iostream>
#include <cmath>
#include <cstdio>

#include <omp.h>

int main()
{
    // Number of elements
    std::size_t n{10000000};

    std::cout << std::endl;
    std::cout << "Vector addition" << std::endl;
    std::cout << "  C++/OpenMP version" << std::endl;
    std::cout << std::endl;
    std::cout << "  A program which adds two vector." << std::endl;

    std::cout << std::endl;
    std::cout << "  Number of processors available = " << omp_get_num_procs() << std::endl;
    std::cout << "  Number of threads =              " << omp_get_max_threads() << std::endl;
    std::cout << std::endl;

    // Allocate the vector data.
    float *a{new float[n]};
    float *b{new float[n]};
    float *c{new float[n]};

    for (std::size_t i = 0; i < n; i++)
    {
        a[i] = 1.f;
        b[i] = 2.f;
        c[i] = 0.f;
    }

    auto tick{omp_get_wtime()};

#pragma omp parallel // NOLINT   <-- necessary to avoid clang-tidy warning on default(none) clause
    {
        int tid = omp_get_thread_num();
        int nthreads{omp_get_num_threads()};

        for (std::size_t i = 0; i < n; i++)
        {
            c[i] += a[i] + b[i];
        }

        std::cout << "   -> Executed on thread " << tid << " of " << nthreads << std::endl;
    }

    auto tock{omp_get_wtime()};

    // Print a few entries
    std::cout << std::endl;
    std::cout << "\t"
              << "i"
              << "\t"
              << "a[i]"
              << "\t"
              << "b[i]"
              << "\t"
              << "c[i] = a[i] + b[i]" << std::endl;
    std::cout << std::endl;
    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "\t" << i << "\t" << a[i] << "\t" << b[i] << "\t\t" << c[i] << std::endl;
    }

    // Free memory
    delete[] a;
    delete[] b;
    delete[] c;

    // Terminate
    std::cout << std::endl;
    std::cout << "Vector addition" << std::endl;
    std::cout << "  Normal end of execution." << std::endl;

    std::cout << "=====================================" << std::endl;
    std::cout << "Work took " << (tock - tick) * 1.e6 << " microseconds" << std::endl;
    std::cout << "=====================================" << std::endl;

    return 0;
}

