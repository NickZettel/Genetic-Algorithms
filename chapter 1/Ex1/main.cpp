#include <iostream>
#include <ctime>
#include <cstdlib>

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
    if (static_cast<double>(std::rand()) / RAND_MAX < 0.7) {
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
        if (found) return true; // Return immediately when found
    }
    return false;
}


int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int fitness[100];
    double proportionalArray[100];
    bool population[100][20];

    int avgGenerations = 0;

    for (int run = 0; run < 20; run++) {
        // Initialize random population
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 20; j++) {
                population[i][j] = std::rand() % 2;
            }
        }

        int generations = 0;
        int maxGenerations = 1000; // Set a limit to generations
        while (!perfectionFound(population) && generations < maxGenerations) {
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
            generations++;
        }
        avgGenerations += generations;
    }

    std::cout << "Average generations to find perfection: " << avgGenerations / 20.0 << std::endl;
    return 0;
}
