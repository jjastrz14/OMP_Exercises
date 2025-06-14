#include <memory>
#include <random>
#include <iostream>
#include <omp.h>

inline void initMat(double *A, size_t MM, size_t NN)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1, 1);

    for (std::size_t i = 0; i < MM * NN; ++i)
        A[i] = dis(gen);
}

int main()
{
    const std::size_t m(4096), n(4096);
    double tol(1.0e-6), error(1.0), start_time(0.0), end_time(0.0);
    int iter(0), iter_max(100);

    // matrices initialization
    auto A{std::make_unique<double[]>(m * n)};
    auto Anew{std::make_unique<double[]>(m * n)};

    start_time = omp_get_wtime();
    initMat(A.get(), m, n);
    end_time = omp_get_wtime();
    std::cout << "Elapsed time for initialization (s) = " << end_time - start_time << std::endl;

    std::cout << "Jacobi relaxation Calculation: << " << m << " x " << n << " mesh." << std::endl;

    start_time = omp_get_wtime();

    while (error > tol && iter < iter_max)
    {
        error = 0.0;
#pragma omp parallel default(none) shared(Anew, A, n, m, error)
        {
#pragma omp for collapse(2) reduction(max : error) schedule(dynamic, 256)
            for (std::size_t i = 1; i < m - 1; i++)
            {
                for (std::size_t j = 1; j < n - 1; j++)
                {
                    Anew[i * n + j] = 0.25 * (A[i * n + (j + 1)] + A[i * n + (j - 1)] + A[(i - 1) * n + j] + A[(i + 1) * n + j]);
                    error = fmax(error, fabs(Anew[i * n + j] - A[i * n + j]));
                }
            }
#pragma omp for schedule(dynamic, 256)
            for (std::size_t i = 1; i < m * n; i++)
            {
                A[i] = Anew[i];
            }
        }

        iter++;

        if (iter % 10 == 0)
            std::cout << "Iteration: " << iter << " \t Error: " << error << std::endl;
    }

    end_time = omp_get_wtime();

    std::cout << "Elapsed time (s) = " << end_time - start_time << std::endl
              << "Stopped at iteration: " << iter << std::endl;

    return 0;
}
