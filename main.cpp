#include <time.h>
#include <stdlib.h>
#include "batchsimulation.hpp"

static const int TOTAL_SIMULATIONS = 4;

int main(int argc, char** argv) {
    BatchSimulation simulations[TOTAL_SIMULATIONS];
    std::string fileName;
    std::string extension = ".txt";
    std::string argument;
    
    srand(time(NULL)); // initialize rand seed


    for (int i = 0; i < TOTAL_SIMULATIONS; i++) {
        fileName = "t" + std::to_string(i+1) + extension;
        simulations[i].GetInput(fileName);
        //std::cout << fileName << std::endl;
        simulations[i].CreateBatches();
        simulations[i].MonteCarloAlgo();
        
        std::cout << "\nSimulation " << i+1 << "\n";
        simulations[i].OutputSimluation();
        std::cout << "\n==============================================";
    }
    std::cout << std::endl;
    

    
    if (argc > 1) {
        argument = argv[1];
        if (argument == "-c") {
            std::cout << "Removing data files...\n";
            system("rm ds*"); // delete all data set files
        }
    }

    return 0;
}