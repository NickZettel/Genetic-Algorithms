#include <iostream>
#include <ctime>
#include <cstdlib>

// An Introduction to Genetic Algorithms
//By Melanie Mitchel
//Page 31.
//1. implement a simple GA with fitness-proportionate selection, roulette-wheel sampling, population size 100
// single point crossover rate = .7, and bitwise mutation rate .001. Try it on the following fitness function:
// f(x) = number of ones in x, where x is a chromosome of length 20.

//Observations: high crossover rate with low mutation finds the perfect solution 10 times faster than just mutation
//without crossover. In crossover, good chunks can spread to the population. Without crossover there is no spread.


void evaluateFitness(bool population[100][20], int fitness[100]) {
    for (int i = 0; i < 100; i++) {
        int countOnes = 0;
        for (int j = 0; j < 20; j++) {
            if (population[i][j]) {
                countOnes++;
            }
        }
        fitness[i] = countOnes;
    }
}

void evaluateProportionalFitness(int fitness[100], double proportionalArray[100]) {
    double totalFit = 0;
    for (int i = 0; i < 100; i++) {
        totalFit += fitness[i];
    }
    for (int i = 0; i < 100; i++) {
        proportionalArray[i] = fitness[i] / totalFit;
    }
    totalFit = 0;
    for (int i = 0; i < 100; i++) {
        totalFit += proportionalArray[i];
        proportionalArray[i] = totalFit;
    }
}

int makeSelection(double proportionalArray[100]) {
    double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
    for (int i = 0; i < 100; i++) {
        if (proportionalArray[i] >= randomValue) {
            return i;
        }
    }
    return 0; // Default return if something goes wrong
}

void crossover(bool partner1[20], bool partner2[20]) {
    //crossover of .7if (static_cast<double>(std::rand()) / RAND_MAX < 0.7) {
    if (true) {
        int crossoverPoint = std::rand() % 19 + 1; // Adjusted to 19 to avoid overflow
        bool newString1[20];
        bool newString2[20];
        for (int i = 0; i < crossoverPoint; i++) {
            newString1[i] = partner1[i];
            newString2[i] = partner2[i];
        }
        for (int i = crossoverPoint; i < 20; i++) {
            newString1[i] = partner2[i];
            newString2[i] = partner1[i];
        }
        for (int i = 0; i < 20; i++) {
            partner1[i] = newString1[i];
            partner2[i] = newString2[i];
        }
    }
}

bool perfectionFound(bool population[100][20]) {
    for (int i = 0; i < 100; i++) {
        bool found = true;
        for (int j = 0; j < 20; j++) {
            if (!population[i][j]) {
                found = false;
                break;
            }
        }
        if (found){
            return true;
        }// Return immediately when found
    }
    return false;
}

void mutate(bool population[100][20]){
    for (int i = 0; i<100; i++){
        for (int j = 0; j <20; j++){
            if (std::rand() % 1000 + 1 == 69){
                population[i][j] = !population[i][j];
            }
        }
    }
}


int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int fitness[100];
    double proportionalArray[100];
    bool population[100][20];

    int avgGenerations = 0;

    for (int run = 0; run < 200; run++) {
        // Initialize random population
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 20; j++) {
                population[i][j] = std::rand() % 2;
            }
        }

        int generations = 0;
        while (!perfectionFound(population)) {
            // Find fitness
            evaluateFitness(population, fitness);
            evaluateProportionalFitness(fitness, proportionalArray);

            // Create new generation
            bool newPopulation[100][20]; // Reset new population for each generation
            for (int i = 0; i < 100; i += 2) {
                int selection1 = makeSelection(proportionalArray);
                int selection2 = makeSelection(proportionalArray);

                bool partner1[20];
                bool partner2[20];

                for (int j = 0; j < 20; j++) {
                    partner1[j] = population[selection1][j];
                    partner2[j] = population[selection2][j];
                }

                crossover(partner1, partner2);
                for (int j = 0; j < 20; j++) {
                    newPopulation[i][j] = partner1[j];
                    newPopulation[i + 1][j] = partner2[j];
                }
            }
            std::copy(&newPopulation[0][0], &newPopulation[0][0] + 100 * 20, &population[0][0]);
            mutate(population);
            generations++;
        }
        avgGenerations += generations;
        std::cout << generations << std::endl;
    }

    std::cout << "Average generations to find perfection: " << avgGenerations / 200.0 << std::endl;
    return 0;
}
