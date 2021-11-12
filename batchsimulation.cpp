#include "batchsimulation.hpp"

BatchSimulation::BatchSimulation() {
    itemsPerBatch = 0;
    totalBatches = 0;
    percntOfBadBatch = 0;
    percntOfBadItems = 0;
    itemsSampledPerBatch = 0;

    maxBadItemsInBatch = 0;
    minBadItemsInBatch = 0;
    actualBadBatches = 0;
    totalBadItems = 0;
    avgBadItemsPerBatch = 0;

    badSetsFound = 0;
    percntBadSetsDetected = 0;
    base = 0;
    exp = 0;

    actualBadBatches = static_cast<int>(totalBatches * (percntOfBadBatch / 100.0));
}
void BatchSimulation::GetInput(std::string fileName) {
    std::ifstream inFile;

    inFile.open(fileName);
    
    inFile >> totalBatches >> itemsPerBatch >> percntOfBadBatch >> percntOfBadItems >> itemsSampledPerBatch;

    inFile.close();

    base = (100.0 - percntOfBadItems) / 100.0;
    exp = itemsSampledPerBatch;
}

void BatchSimulation::OutputSimluation() {
    avgBadItemsPerBatch = static_cast<float>(totalBadItems) / actualBadBatches;

    std::cout << "\nNumber of batches of items: " << totalBatches;
    std::cout << "\nNumber of items in each batch: " << itemsPerBatch;
    std::cout << "\nPercentage of batches containing bad items: " << percntOfBadBatch << "%";
    std::cout << "\nPercentage of items that are bad in a bad set: " << percntOfBadItems << "%";
    std::cout << "\nItems sampled from each set: " << itemsSampledPerBatch << std::endl;

    std::cout << "\nGenerating data sets:\n\n";
    std::cout << "Total bad sets = " << actualBadBatches;
    std::cout << "\nMax number of bad items in a bad set = " << maxBadItemsInBatch;
    std::cout << "\nMin number of bad items in a bad set = " << minBadItemsInBatch;
    std::cout << "\nAverage number of bad items in a bad set = " << avgBadItemsPerBatch << std::endl;

    std::cout << "\nAnalyzing data sets:\n\n";
    std::cout << "Total bad sets found = " << badSetsFound;
    std::cout << "\nPercentage of bad batches actually detected = " << (static_cast<float>(badSetsFound) / actualBadBatches) * 100.0 << "%";
    std::cout << "\nBase = " << base;
    std::cout << " Exponent = " << exp;
    std::cout << "\nPredicted P (failure to detect bad batch) = " << pow(base,exp) << std::endl;
}

// create total batches
void BatchSimulation::CreateBatches() {
    actualBadBatches = static_cast<int>(totalBatches * (percntOfBadBatch / 100.0));
    std::string dataSet = "ds";
    std::string fileExtension = ".txt";
    std::string dataFile;

    for (int i = 0; i < actualBadBatches; i++) {
        dataFile = dataSet + std::to_string(i) + fileExtension;
        GenerateBadBatch(dataFile);
    }
    for (int i = actualBadBatches; i < totalBatches; i++) {
        dataFile = dataSet + std::to_string(i) + fileExtension;
        GenerateGoodBatch(dataFile);
    } 
}

void BatchSimulation::GenerateBadBatch(std::string outputFile) {
    std::ofstream outFile;
    int BadItemsinBatch = 0;
    int randNum = 0;

    outFile.open(outputFile);

    for (int i = 0; i < itemsPerBatch; i++) {
        randNum = rand() % 100;
        if (randNum < percntOfBadItems) {
            outFile << "b\n";
            BadItemsinBatch++;
        } else {
            outFile << "g\n";
        }
    }

    outFile.close();

    if (BadItemsinBatch > maxBadItemsInBatch) {
        maxBadItemsInBatch = BadItemsinBatch;
    }
    // initialize min
    if (minBadItemsInBatch == 0) {
        minBadItemsInBatch = BadItemsinBatch;
    }
    if (BadItemsinBatch < minBadItemsInBatch) {
        minBadItemsInBatch = BadItemsinBatch;
    }

    totalBadItems += BadItemsinBatch;
}

void BatchSimulation::GenerateGoodBatch(std::string outputFile) {
    std::ofstream outFile;

    outFile.open(outputFile);

    for (int i = 0; i < itemsPerBatch; i++) {
        outFile << "g\n";
    }

    outFile.close();
}

void BatchSimulation::MonteCarloAlgo() {
    std::string dataSet = "ds";
    std::string fileExtension = ".txt";
    std::string dataFile;

    for (int i = 0; i < totalBatches; i++) {
        dataFile = dataSet + std::to_string(i) + fileExtension;
        TestBatch(dataFile);
    }
}

void BatchSimulation::TestBatch(std::string batchFile) {
    std::ifstream inFile;
    std::ofstream outFile; // temp
    std::string testLine;
    inFile.open(batchFile);
    for (int i = 0; i < itemsSampledPerBatch; i++) {
        inFile >> testLine;
        if (testLine.at(0) == 'b') {
            badSetsFound++;
            break;
        }
    }

    inFile.close();
}
