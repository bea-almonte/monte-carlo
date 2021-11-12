// implements brute force algorithm for traveling salesman problem
#include <iostream>
#include <fstream>  // file streams
#include <random> // rand.h
#include <math.h> // pow()

#ifndef BATCHSIMULATION_HPP
#define BATCHSIMULATION_HPP

class BatchSimulation {
private:
    int itemsPerBatch;
    int totalBatches;
    int percntOfBadBatch;
    int percntOfBadItems;
    int itemsSampledPerBatch;
// data set info
    int maxBadItemsInBatch;
    int minBadItemsInBatch;
    int actualBadBatches;
    int totalBadItems;
    float avgBadItemsPerBatch;
// monte carlo calculations
    int badSetsFound;
    float percntBadSetsDetected;
    float base;
    float exp;
public:
    BatchSimulation();
    void GetInput(std::string fileName);
    void OutputSimluation();
    void CreateBatches(); // create total batches
    void GenerateBadBatch(std::string outputFile);
    void GenerateGoodBatch(std::string outputFile);
    void MonteCarloAlgo();
    void TestBatch(std::string batchFile);
};

#endif