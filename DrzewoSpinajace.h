#ifndef SDIZO_PROJEKT2_DRZEWOSPINAJACE_H
#define SDIZO_PROJEKT2_DRZEWOSPINAJACE_H


#include "Krawedz.h"
#include "ElementListy.h"
#include <iostream>
#include <cstdio>
#include <vector>

class DrzewoSpinajace {
private:

    ElementListy **T;

    Krawedz *kk;

    int rozmiarT;

    int waga, krawedzie;

    int a;

public:

    DrzewoSpinajace(int wierzcholki, int kr);

    ~DrzewoSpinajace();

    void dodajKrawedz(Krawedz k);

    void wyswietl();

    int findSet(int i, const std::vector<int> &parent);

    void unionSet(int i, int j, std::vector<int> &parent);
};


#endif //SDIZO_PROJEKT2_DRZEWOSPINAJACE_H
