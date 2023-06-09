#ifndef TESTY_H
#define TESTY_H

#include <iostream>
#include <fstream>
#include <chrono>
#include "Graf.h"

class Tests {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    long measuredTime();

//    void addPrimMatrix(long duration);
//    void addKruskalMatrix(long duration);
//    void addPrimList(long duration);
//    void addKruskalList(long duration);
//    void addDijkstralList(long duration);
//    void addDijkstraMatrix(long duration);
//    void addBellmanFordList(long duration);
//    void addBellmanFordMatrix(long duration);
//    void addFordFulkersonList(long duration);
//    void addFordFulkersonMatrix(long duration);
//    Graf *graf;
    Graf* graf;

    double calculateAverage(double* results, int size);

public:
    Tests(Graf* graf) : graf(graf)  {
            // Konstruktor
    }
    double primMatrixResults[100];
    double kruskalMatrixResults[100];
    double primListResults[100];
    double kruskalListResults[100];
    double DijkstralListResults[100];
    double DijkstraMatrixResults[100];
    double BellmanFordListResults[100];
    double BellmanFordMatrixResults[100];
    double FordFulkersonListResults[100];
    double FordFulkersonMatrixResults[100];
//    void measureTime();


    void measureTime();

    void startTimer();
    void stopTimer();

    void saveResults(const std::string& filename, int index);
};

#endif  // TESTY_H
