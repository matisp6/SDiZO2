#ifndef SDIZO_PROJEKT2_GRAF_H
#define SDIZO_PROJEKT2_GRAF_H

#include <iostream>
#include <ctime>
#include <fstream>

#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <queue>
#include <stdio.h>

#include "Krawedz.h"
#include "ElementListy.h"
#include "Stos.h"
#include "DrzewoSpinajace.h"

class Graf {
public:
    Graf(int w, int m);

    ~Graf();

    Krawedz *K, *KO;
    int **macierzIncydencji, **grafNieskierowanyM;
    int **macierzSasiedztwa;
    ElementListy **listySasiedztwa, **grafNieskierowanyL;
    int wierzcholki, krawedzie, gestosc, krawedzieOdwrotne;
    ElementListy *e1, *e2;
    bool *odwiedzone;

public:

    void macierz_Prim();

    void wyswietl();

    void lista_Prim();

    void KruskalLista();
    
	void KruskalMacierz();

    void Dijkstra(int w);

   	bool sprawdzSpojnosc();

    void losujGraf();

    void losujKrawedzie();

    void zamienGrafNaNieskierowany();

    void macierz_Forda(int start, int end);

    void lista_Forda(int start, int end);

    void macierz_Forda(int start);

    void lista_Forda(int start);

    void BellmanFord(int start);

    void wyswietMacierz();

    void wyswietlLista();

    void lista_Dijkstry(int w);

    void macierz_Dijkstry(int w);

    void wyswietMacierzNieskierowna();

    void inicjalizujMacierz();

    void wyswietlListaNieskierowana();

    void unionSets(std::vector<int> &parent, int i, int j);

    int find(std::vector<int> &parent, int i);

    void lista_FordFulkerson(int zrodlo, int ujscie);

    int lista_FordFulkersonDFS(int u, int t, int minPojemnosc, int *odwiedzone, int *przeplyw);

    int lista_FordFulkersonDFS(int u, int t, int minPojemnosc, int *odwiedzone, int **przeplyw);

    int macierz_FordFulkersonDFS(int u, int t, int minPojemnosc, int *odwiedzone, int **przeplyw);

    void macierz_FordFulkerson(int zrodlo, int ujscie);

    void grafZPliku(const std::string &nazwaPliku);

    void inicjalizujListySasiedztwa();

    void inicjalizujGrafNieskierowany();
};

#endif //SDIZO_PROJEKT2_GRAF_H
