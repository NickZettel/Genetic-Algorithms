#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

void modifyArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] += 10; // Modify each element by adding 10
    }
}

double fitnessFunction(double y){
    if (y<0 || y >= M_PI){
        return 0.0;
    }
    return y + fabs(sin(32*y));
}


int main() {
    srand((unsigned) time(NULL));

    double lower = 0.0;

    double solutions[10];

    for (int i = 0; i < 10; i++) {
        double random = lower + (double)rand() / RAND_MAX * (M_PI - lower);
        solutions[i] = random;
    }

    for (int i = 0; i < 10; i++) {
        std::cout<< solutions[i]<< " ||| "<< fitnessFunction(solutions[i]) << std::endl;
    }

    return 0;
}


