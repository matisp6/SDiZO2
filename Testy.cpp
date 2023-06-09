#include "Testy.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;


void Tests::startTimer(){
    startTime = std::chrono::high_resolution_clock::now();
}

void Tests::stopTimer(){
    endTime = std::chrono::high_resolution_clock::now();
}

long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}


long Tests::measuredTime(){
    return std::chrono::duration_cast<std::chrono::microseconds>(Tests::endTime - Tests::startTime).count();
}

// Wyniki pomiar�w dla algorytmu Prim (reprezentacja macierzowa)
long primMatrixResults[100];
int primMatrixIndex = 0;

// Wyniki pomiar�w dla algorytmu Kruskala (reprezentacja macierzowa)
long kruskalMatrixResults[100];
int kruskalMatrixIndex = 0;

// Wyniki pomiar�w dla algorytmu Prim (reprezentacja listowa)
long primListResults[100];
int primListIndex = 0;

// Wyniki pomiar�w dla algorytmu Kruskala (reprezentacja listowa)
long kruskalListResults[100];
int kruskalListIndex = 0;

// Wyniki pomiar�w dla algorytmu Dijkstry (reprezentacja listowa)
long dijkstraListResults[100];
int dijkstraListIndex = 0;

// Wyniki pomiar�w dla algorytmu Dijkstry (reprezentacja macierzowa)
long dijkstraMatrixResults[100];
int dijkstraMatrixIndex = 0;

// Wyniki pomiar�w dla algorytmu Bellmana-Forda (reprezentacja listowa)
long bellmanFordListResults[100];
int bellmanFordListIndex = 0;

// Wyniki pomiar�w dla algorytmu Bellmana-Forda (reprezentacja macierzowa)
long bellmanFordMatrixResults[100];
int bellmanFordMatrixIndex = 0;

// Wyniki pomiar�w dla algorytmu Forda-Fulkersona (reprezentacja listowa)
long fordFulkersonListResults[100];
int fordFulkersonListIndex = 0;

// Wyniki pomiar�w dla algorytmu Forda-Fulkersona (reprezentacja macierzowa)
long fordFulkersonMatrixResults[100];
int fordFulkersonMatrixIndex = 0;


void addPrimMatrix(long duration) {
    primMatrixResults[primMatrixIndex] = duration;
    primMatrixIndex++;
}

void addKruskalMatrix(long duration) {
    kruskalMatrixResults[kruskalMatrixIndex] = duration;
    kruskalMatrixIndex++;
}

void addPrimList(long duration) {
    primListResults[primListIndex] = duration;
    primListIndex++;
}

void addKruskalList(long duration) {
    kruskalListResults[kruskalListIndex] = duration;
    kruskalListIndex++;
}

void addDijkstraMatrix(long duration) {
    dijkstraMatrixResults[dijkstraMatrixIndex] = duration;
    dijkstraMatrixIndex++;
}

void addDijkstraList(long duration) {
    dijkstraListResults[dijkstraListIndex] = duration;
    dijkstraListIndex++;
}

void addBellmanFordMatrix(long duration) {
    bellmanFordMatrixResults[bellmanFordMatrixIndex] = duration;
    bellmanFordMatrixIndex++;
}

void addBellmanFordList(long duration) {
    bellmanFordListResults[bellmanFordListIndex] = duration;
    bellmanFordListIndex++;
}

void addFordFulkersonMatrix(long duration) {
    fordFulkersonMatrixResults[fordFulkersonMatrixIndex] = duration;
    fordFulkersonMatrixIndex++;
}

void addFordFulkersonList(long duration) {
    fordFulkersonListResults[fordFulkersonListIndex] = duration;
    fordFulkersonListIndex++;
}

void Tests::measureTime() {
    for (int i = 0; i < 100; ++i) {
        // Wykonaj pomiary dla ka�dej metody i reprezentacji grafu
        startTimer();
        // Pomiar dla metody Prim z reprezentacj� macierzow�
        graf->macierz_Prim();
        stopTimer();
        addPrimMatrix(measuredTime());

        startTimer();
        // Pomiar dla metody Kruskal z reprezentacj� macierzow�
        graf->KruskalMacierz();
        stopTimer();
        addKruskalMatrix(measuredTime());

        startTimer();
        // Pomiar dla metody Prim z reprezentacj� listow�
        graf->lista_Prim();
        stopTimer();
        addPrimList(measuredTime());

        startTimer();
        // Pomiar dla metody Kruskal z reprezentacj� listow�
        graf->KruskalLista();
        stopTimer();
        addKruskalList(measuredTime());

/////////////
        startTimer();
        // Pomiar dla metody Dijkstry z reprezentacj� listow�
        graf->lista_Dijkstry(0);
        stopTimer();
        addDijkstraList(measuredTime());

        startTimer();
        // Pomiar dla metody Dijkstry z reprezentacj� macierzow�
        graf->macierz_Dijkstry(0);
        stopTimer();
        addDijkstraMatrix(measuredTime());

        startTimer();
        // Pomiar dla metody Bellmana-Forda z reprezentacj� listow�
        graf->lista_Forda(0);
        stopTimer();
        addBellmanFordList(measuredTime());

        startTimer();
        // Pomiar dla metody Bellmana-Forda z reprezentacj� macierzow�
        graf->macierz_Forda(0);
        stopTimer();
        addBellmanFordMatrix(measuredTime());

        startTimer();
        // Pomiar dla metody Forda-Felkursona z reprezentacj� listow�
        graf->lista_FordFulkerson(0, 4);
        stopTimer();
        addFordFulkersonList(measuredTime());

        startTimer();
        // Pomiar dla metody Forda-Felkursona z reprezentacj� macierzow�
        graf->macierz_FordFulkerson(0, 4);
        stopTimer();
        addFordFulkersonMatrix(measuredTime());

    }

    // Oblicz �redni czas wykonania dla ka�dej metody i reprezentacji grafu
    double averagePrimMatrix = calculateAverage(primMatrixResults, 100);
    double averageKruskalMatrix = calculateAverage(kruskalMatrixResults, 100);
    double averageKruskalList = calculateAverage(kruskalListResults, 100);
    double averagePrimList = calculateAverage(primListResults, 100);
    double averageDijkstralList = calculateAverage(DijkstralListResults, 100);
    double averageDijkstraMatrix = calculateAverage(DijkstraMatrixResults , 100);
    double averageBellmanFordList = calculateAverage(BellmanFordListResults, 100);
    double averageBellmanFordMatrix = calculateAverage(BellmanFordMatrixResults, 100);
    double averageFordFulkersonList = calculateAverage(FordFulkersonListResults, 100);
    double averageFordFulkersonMatrix = calculateAverage(FordFulkersonMatrixResults, 100);

    // Wypisz wyniki
    cout << endl << endl << "�redni czas wykonania dla metody Prim z reprezentacj� macierzow�: " << averagePrimMatrix << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Prim z reprezentacj� listow�: " << averagePrimList << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Kruskal z reprezentacj� macierzow�: " << averageKruskalMatrix << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Kruskal z reprezentacj� listow�: " << averageKruskalList << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Dijkstra z reprezentacj� macierzow�: " << averageDijkstralList << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Dijkstra z reprezentacj� listow�: " << averageDijkstraMatrix << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Bellman-Ford z reprezentacj� macierzow�: " << averageBellmanFordMatrix << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Bellman-Ford  z reprezentacj� listow�: " << averageBellmanFordList << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Ford-Fulkerson z reprezentacj� macierzow�: " << averageFordFulkersonMatrix << " nanosekund" << endl;
    cout << "�redni czas wykonania dla metody Ford-Fulkerson z reprezentacj� listow�: " << averageFordFulkersonList << " nanosekund" << endl;

    // Kontynuuj dla pozosta�ych metod i reprezentacji grafu
}

double Tests::calculateAverage(double* results, int size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += results[i];
    }
    return sum / size;
}
