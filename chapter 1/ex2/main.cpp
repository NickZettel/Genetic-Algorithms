#include <iostream>
#include <ctime>
#include <cstdlib>

// An Introduction to Genetic Algorithms
//By Melanie Mitchel
//Page 32.
//1. implement a simple GA with fitness-proportionate selection, roulette-wheel sampling, population size 100
// single point crossover rate = .7, and bitwise mutation rate .001. Try it on the following fitness function:
// f(x) = the integer representated by the binary number x, where x is a chromosome of length 20.
//run the GA for 100 generations and plot the fitness of the best individual found at each generation as
//well as the average fitness of the population at each generation. How do these plots change as you vary the population
//size, crossover rate, and mutation rate?

//observations: a small (100) population will never find the optimal solution, because changes in later digits of a binary
//number confer a small comparative fitness than numbers at the start. Therefore there is less pressure the further you
//go along the string, and mutations push back towards randomness. A large population (10000) can overcome this and easily
//find the optimal string not because of pressure so much as by flooding possible solutions to a relatively small schema.

//A small mutation rate (.0001) performed better than larger rates (.01 or .001) at small (100) pop, but
//mutations turned off with small (100) pop is almost guaranteed never to find the optimum solution.

//high (.1) mutations with no crossover performed well

const int population_size = 100;

int boolArrayToBinaryLiteralToInt(const bool boolArray[]) {
    std::string binaryString;
    // Build the binary string from the boolean array
    for (int i = 0; i < 20; ++i) {
        binaryString += (boolArray[i] ? '1' : '0');
    }
    // Convert the binary string to an integer using std::stoi
    int result = std::stoi(binaryString, nullptr, 2);
    return result;
}

void evaluateFitness(bool population[population_size][20], int fitness[population_size]) {
    for (int i = 0; i < population_size; i++) {
        fitness[i] = boolArrayToBinaryLiteralToInt(population[i]);
    }
}

void evaluateProportionalFitness(int fitness[population_size], double proportionalArray[population_size]) {
    double totalFit = 0;
    for (int i = 0; i < population_size; i++) {
        totalFit += fitness[i];
    }
    for (int i = 0; i < population_size; i++) {
        proportionalArray[i] = fitness[i] / totalFit;
    }
    totalFit = 0;
    for (int i = 0; i < population_size; i++) {
        totalFit += proportionalArray[i];
        proportionalArray[i] = totalFit;
    }
}

int makeSelection(double proportionalArray[population_size]) {
    double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
    for (int i = 0; i < population_size; i++) {
        if (proportionalArray[i] >= randomValue) {
            return i;
        }
    }
    return 0; // Default return if something goes wrong
}

void crossover(bool partner1[20], bool partner2[20]) {
    //if (static_cast<double>(std::rand()) / RAND_MAX < 0.7) {
    if (false){
        int crossoverPoint = std::rand() % 18 + 1;
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


void mutate(bool population[population_size][20]){
    for (int i = 0; i<population_size; i++){
        for (int j = 0; j <20; j++){
            if (std::rand() % 1000 + 1 == 6){
                population[i][j] = !population[i][j];
            }
        }
    }
}


int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int fitness[population_size];
    double proportionalArray[population_size];
    bool population[population_size][20];


    // Initialize random population
    for (int i = 0; i < population_size; i++) {
        for (int j = 0; j < 20; j++) {
            population[i][j] = std::rand() % 2;
        }
    }



    for (int gens = 0; gens< 100; gens++) {
        int best = 0;
        int bestI = 0;
        int avg = 0;
        // Find fitness
        evaluateFitness(population, fitness);
        evaluateProportionalFitness(fitness, proportionalArray);

        for (int i = 0;i<population_size;i++){
            if (fitness[i]>best){
                best = fitness[i];
                bestI = i;
            }
            avg += fitness[i];
        }
        avg /= population_size;

        std::cout <<"generation: " << gens<< ". "<< "Average fitness: "<< avg<< ". Best fitness: "<< best<<". (";
        for (int i = 0; i<20; i++){
            std::cout<< population[bestI][i];
        }
         std::cout << ") "<<std::endl;

        // Create new generation
        bool newPopulation[population_size][20]; // Reset new population for each generation
        for (int i = 0; i < population_size; i += 2) {
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
        std::copy(&newPopulation[0][0], &newPopulation[0][0] + population_size * 20, &population[0][0]);
        mutate(population);

    }

    return 0;
}

