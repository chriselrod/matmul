#include <iostream>
#include <cmath>

void matmul1(const float *a, const float *b, float *c, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i * n + j] += a[i * n + k] * b[k * n + j];
}

void matmul2(const float *a, const float *_b, float *c, int n) {
    float *b = new float[n * n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i * n + j] = _b[j * n + i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i * n + j] += a[i * n + k] * b[j * n + k]; // <- note the indices
}

int main() {
    //int n = 1920;
    int n = 1024;
    float *a = (float*) malloc(n*n*sizeof(float));
    float *b = (float*) malloc(n*n*sizeof(float));
    float *c = (float*) malloc(n*n*sizeof(float));
    auto t1 = std::chrono::high_resolution_clock::now();
    matmul2(a, b, c, n);
    auto t2 = std::chrono::high_resolution_clock::now();
    double t = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0;
    double GHz = 1e9;
    double fma_clock = 0.0625;
    double freq = 3.2*GHz;
    double measured = t * freq / (std::pow((double)n, 3));
    double percent_peak = fma_clock / measured * 100;
    std::cout << "Size (n x n): n = " << n << std::endl;
    std::cout << "Size MB: " << 4.*n*n/(1024*1024) << std::endl;
    std::cout << "Time: " << t << "s" << std::endl;
    std::cout << "Clock cycles per element:" << std::endl;
    std::cout << "Theoretical performance peak: " << fma_clock << " cycles" << std::endl;
    std::cout << "Measured: " << measured << " cycles" << std::endl;
    std::cout << "Percent peak: " << percent_peak << " %" << std::endl;
    return 0;
}
