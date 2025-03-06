#include <iostream>
#include <cmath>
#include <chrono>

#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    // Number of elements
    std::size_t n{10000000};

    std::cout << std::endl;
    std::cout << "Vector addition" << std::endl;
    std::cout << "  C++/OpenMP version" << std::endl;
    std::cout << std::endl;
    std::cout << "  A program which adds two vector." << std::endl;

    // Allocate the vector data.
    float *a{new float[n]};
    float *b{new float[n]};
    float *c{new float[n]};

    for (std::size_t i = 0; i < n; i++) {
        a[i] = 1.f;
        b[i] = 2.f;
        c[i] = 0.f;
    }

    #ifdef _OPENMP
      double tick = omp_get_wtime();
    #else
      auto tick{std::chrono::high_resolution_clock::now()};
    #endif
    
    for (std::size_t i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    #ifdef _OPENMP
      double tock = omp_get_wtime();
    #else
      auto tock{std::chrono::high_resolution_clock::now()};
    #endif

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
    for (std::size_t i = 0; i < 10; i++) {
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
    #ifdef _OPENMP
      double time = (tock - tick);
      std::cout << "Work took " << time << " seconds." << std::endl;
    #else
      auto int_ms{std::chrono::duration_cast<std::chrono::microseconds>(tock - tick)};
      std::cout << "Work took " << int_ms.count() << " microseconds." << std::endl;
   #endif 
   std::cout << "=====================================" << std::endl;

    return 0;
}

