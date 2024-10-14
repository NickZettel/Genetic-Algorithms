#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

//page 9 of An Introduction to Genetic Algorithms by Malanie Mitchell

double fitnessFunction(double y){
    if (y<0 || y >= M_PI){
        return 0.0;
    }
    return y + fabs(sin(32*y));
}


//function does a lot of things. takes as argument the array holding solutions (assumed to be 10)
void nextGen(double arr[]) {
    //variables to keep track of current highest fitness
    double highest = 0;
    int highI;
    //loop through solutions saving the index and fitness of fittest solution thus far
    for (int i = 0; i < 10; ++i) {
        if (fitnessFunction(arr[i]) > highest){
            highI = i;
            highest = fitnessFunction(arr[i]);
        }
    }
    //turn non-fittest solutions into fittest solution + or - a few decimal points
    for (int i = 0; i < 10; ++i) {
        if (i != highI){
            arr[i] = arr[highI] + ((double)rand() / RAND_MAX) * 0.2 - 0.1;

        }
    }
    std::cout <<std::endl<<std::endl<< arr[highI] << "||| " <<highest<<std::endl;
}

int main() {

    srand((unsigned) time(NULL));


    double solutions[10];

    for (int i = 0; i < 10; i++) {
        double random = (double)rand() / RAND_MAX * M_PI;
        solutions[i] = random;
    }


    for(int i = 0; i< 2000; i++){
        nextGen(solutions);
    }

    return 0;
}

//the answer it turns out is a y value of 3.09348 conferring a fitness value of 4.09299

