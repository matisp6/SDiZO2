#include "Graf.h"
#include <algorithm>


using namespace std;

Graf::Graf(int w, int m) {
    krawedzie = m;
    wierzcholki = w;
    macierzIncydencji = new int *[wierzcholki];
    macierzSasiedztwa = new int *[wierzcholki];
    grafNieskierowanyM = new int *[wierzcholki];
    listySasiedztwa = new ElementListy *[wierzcholki];
    grafNieskierowanyL = new ElementListy *[wierzcholki];
    K = new Krawedz[krawedzie];
    KO = new Krawedz[krawedzie];
    krawedzieOdwrotne = 0;


}

Graf::~Graf() {
    int i;
    for (int i = 0; i < wierzcholki; i++) {
        e1 = listySasiedztwa[i];
        while (e1) {
            e2 = e1;
            e1 = e1->nastepny;
            delete e2;
        }
    }


}

void Graf::inicjalizujMacierz() {
    // Inicjalizacja macierzy macierzSasiedztwa
    for (int i = 0; i < wierzcholki; i++) {
        macierzSasiedztwa[i] = new int[wierzcholki];
        for (int j = 0; j < wierzcholki; j++) {
            macierzSasiedztwa[i][j] = 0;
        }
    }
}

void Graf::inicjalizujListySasiedztwa() {
    for (int i = 0; i < wierzcholki; i++) {
        listySasiedztwa[i] = nullptr;
    }
}

void Graf::inicjalizujGrafNieskierowany() {
    grafNieskierowanyM = new int*[wierzcholki];
    grafNieskierowanyL = new ElementListy*[wierzcholki];

    for (int i = 0; i < wierzcholki; i++) {
        grafNieskierowanyM[i] = new int[wierzcholki];
        grafNieskierowanyL[i] = nullptr;

        for (int j = 0; j < wierzcholki; j++) {
            grafNieskierowanyM[i][j] = 0;
        }
    }

    for (int i = 0; i < wierzcholki; i++) {
        for (int j = i + 1; j < wierzcholki; j++) {
            if (macierzSasiedztwa[i][j] > 0) {
                grafNieskierowanyM[i][j] = macierzSasiedztwa[i][j];
                grafNieskierowanyM[j][i] = macierzSasiedztwa[i][j];

                // aktualizacja listy grafNieskierowanyL
                ElementListy* e1 = new ElementListy;
                e1->w = j;
                e1->waga = macierzSasiedztwa[i][j];
                e1->nastepny = grafNieskierowanyL[i];
                grafNieskierowanyL[i] = e1;

                ElementListy* e2 = new ElementListy;
                e2->w = i;
                e2->waga = macierzSasiedztwa[i][j];
                e2->nastepny = grafNieskierowanyL[j];
                grafNieskierowanyL[j] = e2;
            }
        }
    }
}





void Graf::zamienGrafNaNieskierowany() {
    int i, j;
    for (i = 0; i < wierzcholki; i++)
        grafNieskierowanyM[i] = new int[wierzcholki];
    for (i = 0; i < wierzcholki; i++)
        for (j = 0; j < wierzcholki; j++) {
            grafNieskierowanyM[i][j] = 0;
        }

    for (i = 0; i < wierzcholki; i++)
        grafNieskierowanyL[i] = NULL;

    for (i = 0; i < krawedzie; i++) {
        j = 0;
        while (j < krawedzieOdwrotne) {

            // Znajd� odwr�con� kraw�d�.
            if ((KO[j].wp == K[i].wp && KO[j].wk == K[i].wk) || (KO[j].wp == K[i].wk && KO[j].wk == K[i].wp)) {
                // Je�eli istnieje kraw�d� o mniejszej wadze, to zachowaj t� kraw�d�.
                if (KO[j].waga > K[i].waga) {
                    KO[j].waga = K[i].waga;
                }
                break;
            } else j++;
        }
        if (j == krawedzieOdwrotne) {
            KO[krawedzieOdwrotne].wp = K[i].wk;
            KO[krawedzieOdwrotne].wk = K[i].wp;
            KO[krawedzieOdwrotne].waga = K[i].waga;
            krawedzieOdwrotne++;
        }
    }

    int wp, wk, waga;
    for (int i = 0; i < krawedzieOdwrotne; i++) {
        wp = KO[i].wp;
        wk = KO[i].wk;
        waga = KO[i].waga;
        e1 = new ElementListy;
        e1->w = wk;
        e1->waga = waga;
        e1->nastepny = grafNieskierowanyL[wp];
        grafNieskierowanyL[wp] = e1;
        e2 = new ElementListy;
        wp = KO[i].wk;
        wk = KO[i].wp;
        waga = KO[i].waga;
        e2->w = wk;
        e2->waga = waga;
        e2->nastepny = grafNieskierowanyL[wp];
        grafNieskierowanyL[wp] = e2;

        grafNieskierowanyM[KO[i].wp][KO[i].wk] = waga;
        grafNieskierowanyM[KO[i].wk][KO[i].wp] = waga;
    }

}

void Graf::losujKrawedzie() {
	srand(time(NULL));
    int c = 0;
    int *T;
    int b, doDodania1, doDodania2, a, i, j;
    int liczStopien = 0;
    int *wDrzewie;
    int *nieWDrzewie;
    a = wierzcholki;
    nieWDrzewie = new int[a];
    for (i = 0; i < a; i++) {
        nieWDrzewie[i] = i;
    }
    wDrzewie = new int[a];
    b = rand() % a;
    doDodania1 = nieWDrzewie[b];
    nieWDrzewie[b] = nieWDrzewie[a - 1];
    a--;
    wDrzewie[c] = doDodania1;
    c++;

    for (i = 0; i < (wierzcholki - 1); i++) {
        b = rand() % c;
        doDodania1 = wDrzewie[b];

        b = rand() % a;
        doDodania2 = nieWDrzewie[b];
        nieWDrzewie[b] = nieWDrzewie[a - 1];
        a--;
        wDrzewie[c] = doDodania2;
        c++;
        K[i].wp = doDodania1;
        K[i].wk = doDodania2;
    }
    for (i = 0; i < (wierzcholki - 1); i++) {

        b = rand() % wierzcholki;
        swap(K[b].wk, K[b].wp);

    }

    for (i = wierzcholki - 1; i < krawedzie; i++) {
        a = wierzcholki;
        T = new int[a];
        for (int k = 0; k < a; k++) {
            T[k] = k;
        }

        b = rand() % a;
        doDodania1 = T[b];
        T[b] = T[a - 1];
        a--;
        while (true) {

            liczStopien = 0;
            for (j = 0; j < i; j++) {
                if (K[j].wp == doDodania1)
                    liczStopien++;
                if (liczStopien == wierzcholki - 1) break;
            }

            if (liczStopien == wierzcholki - 1) {
                b = rand() % a;
                doDodania1 = T[b];
                T[b] = T[a - 1];
                a--;
            } else break;
        }

        a = wierzcholki;
        for (int k = 0; k < a; k++) {
            T[k] = k;
        }

        T[doDodania1] = T[a - 1];
        a--;

        b = rand() % a;
        doDodania2 = T[b];
        T[b] = T[a - 1];
        a--;

        for (j = 0; j < i; j++) {
            while (doDodania1 == K[j].wp && doDodania2 == K[j].wk) {
                b = rand() % a;
                doDodania2 = T[b];
                T[b] = T[a - 1];
                a--;
                j = 0;
            }
        }
        K[i].wp = doDodania1;
        K[i].wk = doDodania2;
        delete[]T;
    }

    for (i = 0; i < krawedzie; i++)
        K[i].waga = (rand() % 9) + 1;

    delete[] nieWDrzewie;
    delete[] wDrzewie;
}

void Graf::losujGraf() {
    int i, j;
    for (i = 0; i < wierzcholki; i++)
        macierzIncydencji[i] = new int[krawedzie];
    for (i = 0; i < wierzcholki; i++)
        for (j = 0; j < krawedzie; j++) {
            macierzIncydencji[i][j] = 0;
        }

    for (i = 0; i < wierzcholki; i++)
        macierzSasiedztwa[i] = new int[wierzcholki];
    for (i = 0; i < wierzcholki; i++)
        for (j = 0; j < wierzcholki; j++) {
            macierzSasiedztwa[i][j] = 0;
        }


    for (i = 0; i < wierzcholki; i++)
        listySasiedztwa[i] = NULL;

    losujKrawedzie();
    zamienGrafNaNieskierowany();
    for (i = 0; i < krawedzie; i++) {
        int wp = K[i].wp;
        int wk = K[i].wk;
        int waga = K[i].waga;
        e1 = new ElementListy;
        e1->w = wk;
        e1->waga = waga;
        e1->nastepny = listySasiedztwa[wp];
        listySasiedztwa[wp] = e1;

        macierzIncydencji[wp][i] = 1;
        macierzIncydencji[wk][i] = -1;

        macierzSasiedztwa[wp][wk] = waga; // Zmienione na waga
    }

}

//void Graf::grafZPliku(const string& nazwaPliku) {
////    inicjalizujMacierz();
////    int i, j;
////    for (i = 0; i < wierzcholki; i++)
////        macierzIncydencji[i] = new int[krawedzie];
////    for (i = 0; i < wierzcholki; i++)
////        for (j = 0; j < krawedzie; j++) {
////            macierzIncydencji[i][j] = 0;
////        }
////
////    for (i = 0; i < wierzcholki; i++)
////        macierzSasiedztwa[i] = new int[wierzcholki];
////    for (i = 0; i < wierzcholki; i++)
////        for (j = 0; j < wierzcholki; j++) {
////            macierzSasiedztwa[i][j] = 0;
////        }
////
////
////    for (i = 0; i < wierzcholki; i++)
////        listySasiedztwa[i] = NULL;
//    ifstream plik(nazwaPliku);
//    if (!plik) {
//        cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie." << endl;
//        return;
//    }
//
//
//    plik >> krawedzie >> wierzcholki;
//    if (!plik || krawedzie < wierzcholki - 1 || wierzcholki <= 1 || krawedzie > (wierzcholki * (wierzcholki - 1))) {
//        cout << "Plik jest uszkodzony lub dane w nim zawarte sa nieprawidlowe" << endl;
//        return;
//    }
//    graf = new Graf(wierzcholki, krawedzie);
//
//
//    for (int i = 0; i < krawedzie; i++) {
//        int wp, wk, waga;
//        plik >> wp >> wk >> waga;
//        if (wp >= wierzcholki || wk >= wierzcholki || waga < 1) {
//            cout << "Krawedzie w pliku sa nieprawidlowo okreslone" << endl;
//        }
//        macierzSasiedztwa[wp][wk] = waga;
//        macierzSasiedztwa[wk][wp] = waga;
//    }
//
//    plik.close();
//}

bool Graf::sprawdzSpojnosc() {
    Stos stos;
    int w, u, i;
    int licz = 0;

    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }

    stos.push(0);
    odwiedzone[0] = true;

    while (!stos.empty()) {
        w = stos.top();
        stos.pop();
        licz++;
        for (e1 = grafNieskierowanyL[w]; e1; e1 = e1->nastepny) {
            u = e1->w;
            if (!odwiedzone[u]) {
                odwiedzone[u] = true;
                stos.push(u);
            }
        }
    }
    delete[]odwiedzone;
    if (licz == wierzcholki)
        return true;

    else return false;
}
/*
void Graf::macierz_DFS(int w) {
    int i, j;
  
    Stos stos;
    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }
    cout << "Graf nieskierowany:" << endl;

    cout << "      ";
    for (i = 0; i < krawedzieOdwrotne; i++) {
        cout << setw(3) << i;

    }
    cout << endl << "      ";
    for (i = 0; i < krawedzieOdwrotne; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < krawedzieOdwrotne; j++)
            cout << setw(3) << grafNieskierowanyM[i][j];
        cout << endl;
    }
    cout << endl;
    cout << "Wagi: ";
    for (i = 0; i < krawedzieOdwrotne; i++) {
        cout << setw(3) << KO[i].waga;
    }
    cout << endl << endl;
    cout << "Odwiedzone wierzcholki:" << endl;
   
    stos.push(w);
    while (!stos.empty()) {

        w = stos.top();
        stos.pop();

        if (!odwiedzone[w]) {
            odwiedzone[w] = true;
            for (i = krawedzie - 1; i >= 0; i--) {
                if (grafNieskierowanyM[w][i] != 0)
                    for (j = 0; j < wierzcholki; j++)
                        if (j != w && grafNieskierowanyM[j][i] != 0) {
                            if (!odwiedzone[j]) {
                                stos.push(j);
                            }
                        }

            }
            cout << w << ", ";
        }
    }
    cout << endl << endl;


    delete[]odwiedzone;
    stos.~Stos();
}

void Graf::lista_DFS(int w) {
   
    Stos stos;
    int u, i;

    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }
    cout << endl << "Graf nieskierowany: " << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << "[" << i << "] =";
        e1 = grafNieskierowanyL[i];
        while (e1) {
            cout << setw(3) << e1->w << "(" << e1->waga << ") ";
            e1 = e1->nastepny;
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "Odwiedzone wierzcholki:" << endl << endl;
   
    stos.push(w);

    while (!stos.empty()) {
        w = stos.top();
        stos.pop();

        if (!odwiedzone[w]) {
            odwiedzone[w] = true;
            for (e1 = grafNieskierowanyL[w]; e1; e1 = e1->nastepny) {
                u = e1->w;
                if (!odwiedzone[u]) {
                    stos.push(u);
                }
            }
            cout << w << ", ";
        }

    }
    
    delete[]odwiedzone;
    stos.~Stos();
}
*/
void Graf::KruskalMacierz() {
    vector<Krawedz> edges;
    for (int i = 0; i < wierzcholki; i++) {
        for (int j = i + 1; j < wierzcholki; j++) {
            if (grafNieskierowanyM[i][j] != 0) {
                Krawedz krawedz;
                krawedz.wp = i;
                krawedz.wk = j;
                krawedz.waga = grafNieskierowanyM[i][j];
                edges.push_back(krawedz);
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Krawedz &a, const Krawedz &b) {
        return a.waga < b.waga;
    });

    vector<int> parent(wierzcholki);
    for (int i = 0; i < wierzcholki; i++)
        parent[i] = i;

    DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, edges.size());

    for (auto &edge : edges) {
        int set_u = find(parent, edge.wp);
        int set_v = find(parent, edge.wk);

        if (set_u != set_v) {
            drzewo->dodajKrawedz(edge);
            unionSets(parent, set_u, set_v);
        }
    }

    cout << "Minimalne drzewo rozpinajace:\n";
    drzewo->wyswietl();
    delete drzewo;
}

int Graf::find(vector<int> &parent, int i) {
    if (i == parent[i])
        return i;
    return find(parent, parent[i]);
}

void Graf::unionSets(vector<int> &parent, int i, int j) {
    parent[i] = j;
}




void Graf::KruskalLista(){
	 int w, i;
    
    Krawedz k;
    priority_queue<Krawedz, vector<Krawedz>, Krawedz> kolejka;
    DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);
    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }
    
    w = 0;
    odwiedzone[w] = true;

    for (i = 1; i < wierzcholki; i++) {

        for (e1 = grafNieskierowanyL[w]; e1; e1 = e1->nastepny) {
            if (!odwiedzone[e1->w]) {
                k.wp = w;
                k.wk = e1->w;
                k.waga = e1->waga;
                kolejka.push(k);
            }
        }
        do {
            k = kolejka.top();
            kolejka.pop();

        } while (odwiedzone[k.wk]);

        drzewo->dodajKrawedz(k);
        odwiedzone[k.wk] = true;
        w = k.wk;

    }

   
    cout << endl;
    cout << "Minimalne drzewo rozpinajace:";
    drzewo->wyswietl();
    delete drzewo;
	
}
void Graf::lista_Dijkstry(int w) {
    int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin, synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;
    
    Stos stos;
    int szerokosc, i, j;
    koszta = new int[wierzcholki];
    poprzednicy = new int[wierzcholki];
    odwiedzone = new bool[wierzcholki];
    kopiec = new int[wierzcholki];
    pozycjaKopiec = new int[wierzcholki];

    for (i = 0; i < wierzcholki; i++) {
        koszta[i] = INT_MAX;
        poprzednicy[i] = -1;
        odwiedzone[i] = false;
        kopiec[i] = pozycjaKopiec[i] = i;
    }
    
    rozmiarKopca = wierzcholki;

    koszta[w] = 0;
    wezel = kopiec[0];
    kopiec[0] = kopiec[w];
    kopiec[w] = wezel;
    pozycjaKopiec[w] = 0;
    pozycjaKopiec[0] = w;

    for (i = 0; i < wierzcholki; i++) {
        korzen = kopiec[0];

        kopiec[0] = kopiec[--rozmiarKopca];
        pozycjaKopiec[kopiec[0]] = ojciec = 0;
        while (true) {
            lewySyn = ojciec + ojciec + 1;
            prawySyn = lewySyn + 1;
            if (lewySyn >= rozmiarKopca) break;
            kosztMin = koszta[kopiec[lewySyn]];
            synMin = lewySyn;
            if ((prawySyn < rozmiarKopca) && (kosztMin > koszta[kopiec[prawySyn]])) {
                kosztMin = koszta[kopiec[prawySyn]];
                synMin = prawySyn;
            }
            if (koszta[kopiec[ojciec]] <= kosztMin)
                break;
            wezel = kopiec[ojciec];
            kopiec[ojciec] = kopiec[synMin];
            kopiec[synMin] = wezel;
            pozycjaKopiec[kopiec[ojciec]] = ojciec;
            pozycjaKopiec[kopiec[synMin]] = synMin;
            ojciec = synMin;
        }

        odwiedzone[korzen] = true;

        if (listySasiedztwa[korzen] != NULL)
            for (e1 = listySasiedztwa[korzen]; e1; e1 = e1->nastepny)
                if (!odwiedzone[e1->w] && (koszta[e1->w] > koszta[korzen] + e1->waga)) {
                    koszta[e1->w] = koszta[korzen] + e1->waga;
                    poprzednicy[e1->w] = korzen;

                    for (syn = pozycjaKopiec[e1->w]; syn; syn = ojciec) {
                        ojciec = syn / 2;
                        if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
                            break;
                        wezel = kopiec[ojciec];
                        kopiec[ojciec] = kopiec[syn];
                        kopiec[syn] = wezel;
                        pozycjaKopiec[kopiec[ojciec]] = ojciec;
                        pozycjaKopiec[kopiec[syn]] = syn;
                    }
                }
    }
   
    cout << endl;

    cout << "Najkrotsza sciezka z wierzcholka " << w << ":" << endl;
    for (i = 0; i < wierzcholki; i++) {
        szerokosc = -2;

        cout << i << ": ";


        if (koszta[i] ==INT_MAX || koszta[i] < 0)
            cout << "Brak" << endl;
        else {
            for (j = i; j > -1; j = poprzednicy[j]) {
                stos.push(j);
                szerokosc = szerokosc + 2;
            }

            while (!stos.empty()) {
                cout << stos.top() << " ";
                stos.pop();
            }
            for (j = 0; j < wierzcholki - szerokosc; j++)
                cout << " ";
            cout << setw(5) << "(" << koszta[i] << ")" << endl;
        }
    }
    cout << endl << endl;
}

void Graf::macierz_Dijkstry(int w) {
    int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin, synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;

    Stos stos;
    int szerokosc, i, j;
    koszta = new int[wierzcholki];
    poprzednicy = new int[wierzcholki];
    odwiedzone = new bool[wierzcholki];
    kopiec = new int[wierzcholki];
    pozycjaKopiec = new int[wierzcholki];

    for (i = 0; i < wierzcholki; i++) {
        koszta[i] = INT_MAX;
        poprzednicy[i] = -1;
        odwiedzone[i] = false;
        kopiec[i] = pozycjaKopiec[i] = i;
    }

    rozmiarKopca = wierzcholki;

    koszta[w] = 0;
    wezel = kopiec[0];
    kopiec[0] = kopiec[w];
    kopiec[w] = wezel;
    pozycjaKopiec[w] = 0;
    pozycjaKopiec[0] = w;

    for (i = 0; i < wierzcholki; i++) {
        korzen = kopiec[0];

        kopiec[0] = kopiec[--rozmiarKopca];
        pozycjaKopiec[kopiec[0]] = ojciec = 0;
        while (true) {
            lewySyn = ojciec + ojciec + 1;
            prawySyn = lewySyn + 1;
            if (lewySyn >= rozmiarKopca) break;
            kosztMin = koszta[kopiec[lewySyn]];
            synMin = lewySyn;
            if ((prawySyn < rozmiarKopca) && (kosztMin > koszta[kopiec[prawySyn]])) {
                kosztMin = koszta[kopiec[prawySyn]];
                synMin = prawySyn;
            }
            if (koszta[kopiec[ojciec]] <= kosztMin)
                break;
            wezel = kopiec[ojciec];
            kopiec[ojciec] = kopiec[synMin];
            kopiec[synMin] = wezel;
            pozycjaKopiec[kopiec[ojciec]] = ojciec;
            pozycjaKopiec[kopiec[synMin]] = synMin;
            ojciec = synMin;
        }

        odwiedzone[korzen] = true;

        for (j = 0; j < wierzcholki; j++) {
            if (macierzSasiedztwa[korzen][j] != 0 && !odwiedzone[j] && koszta[j] > koszta[korzen] + macierzSasiedztwa[korzen][j]) {
                koszta[j] = koszta[korzen] + macierzSasiedztwa[korzen][j];
                poprzednicy[j] = korzen;

                for (syn = pozycjaKopiec[j]; syn; syn = ojciec) {
                    ojciec = syn / 2;
                    if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
                        break;
                    wezel = kopiec[ojciec];
                    kopiec[ojciec] = kopiec[syn];
                    kopiec[syn] = wezel;
                    pozycjaKopiec[kopiec[ojciec]] = ojciec;
                    pozycjaKopiec[kopiec[syn]] = syn;
                }
            }
        }
    }

    cout << endl;

    cout << "Najkrotsza sciezka z wierzcholka " << w << ":" << endl;
    for (i = 0; i < wierzcholki; i++) {
        szerokosc = -2;

        cout << i << ": ";


        if (koszta[i] ==INT_MAX || koszta[i] < 0)
            cout << "Brak" << endl;
        else {
            for (j = i; j > -1; j = poprzednicy[j]) {
                stos.push(j);
                szerokosc = szerokosc + 2;
            }

            while (!stos.empty()) {
                cout << stos.top() << " ";
                stos.pop();
            }
            for (j = 0; j < wierzcholki - szerokosc; j++)
                cout << " ";
            cout << setw(5) << "(" << koszta[i] << ")" << endl;
        }
    }
    cout << endl << endl;
}


void Graf::macierz_Prim() {

    int w, i, j;

    Krawedz krawedz;
    priority_queue<Krawedz, vector<Krawedz>, Krawedz> kolejka;
    DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);
    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }

//    cout << "Graf nieskierowany:" << endl;
//
//    cout << "      ";
//    for (i = 0; i < wierzcholki; i++) {
//        cout << setw(3) << i;
//    }
//
//    cout << endl << "      ";
//    for (i = 0; i < wierzcholki; i++) {
//        cout << setw(3) << "-";
//    }
//
//    cout << endl;
//    for (i = 0; i < wierzcholki; i++) {
//        cout << setw(3) << i << " | ";
//        for (int j = 0; j < wierzcholki; j++)
//            cout << setw(3) << grafNieskierowanyM[i][j];
//        cout << endl;
//    }
//    cout << endl;

    w = 0;
    odwiedzone[w] = true;
    for (i = 1; i < wierzcholki; i++) {
        for (j = 0; j < wierzcholki; j++) {
            if (grafNieskierowanyM[w][j] != 0 && !odwiedzone[j]) {
                krawedz.wp = w;
                krawedz.wk = j;
                krawedz.waga = grafNieskierowanyM[w][j];
                kolejka.push(krawedz);
            }
        }

        do {
            krawedz = kolejka.top();
            kolejka.pop();
        } while (odwiedzone[krawedz.wk]);

        drzewo->dodajKrawedz(krawedz);
        odwiedzone[krawedz.wk] = true;
        w = krawedz.wk;
    }

    cout << "Minimalne drzewo rozpinajace:";
    drzewo->wyswietl();
    delete drzewo;
}









void Graf::lista_Prim() {
    int w, i;
    
    Krawedz k;
    priority_queue<Krawedz, vector<Krawedz>, Krawedz> kolejka;
    DrzewoSpinajace *drzewo = new DrzewoSpinajace(wierzcholki, krawedzie);
    odwiedzone = new bool[wierzcholki];
    for (i = 0; i < wierzcholki; i++) {
        odwiedzone[i] = false;
    }
//    cout << endl << "Graf nieskierowany: " << endl << endl;
//    for (i = 0; i < wierzcholki; i++) {
//        cout << "[" << i << "] =";
//        e1 = grafNieskierowanyL[i];
//        while (e1) {
//            cout << setw(3) << e1->w << "(" << e1->waga << ") ";
//            e1 = e1->nastepny;
//        }
//        cout << endl;
//    }
//    cout << endl;
    
    w = 0;
    odwiedzone[w] = true;

    for (i = 1; i < wierzcholki; i++) {

        for (e1 = grafNieskierowanyL[w]; e1; e1 = e1->nastepny) {
            if (!odwiedzone[e1->w]) {
                k.wp = w;
                k.wk = e1->w;
                k.waga = e1->waga;
                kolejka.push(k);
            }
        }
        do {
            k = kolejka.top();
            kolejka.pop();

        } while (odwiedzone[k.wk]);

        drzewo->dodajKrawedz(k);
        odwiedzone[k.wk] = true;
        w = k.wk;

    }

   
    cout << endl;
    cout << "Minimalne drzewo rozpinajace:";
    drzewo->wyswietl();
    delete drzewo;
}

void Graf::BellmanFord(int start)
{
    int szerokosc;
    Stos stos;
    int* drogaWagi = new int[wierzcholki];
    int* poprzednicy = new int[wierzcholki];

    for (int i = 0; i < wierzcholki; i++)
    {
        drogaWagi[i] = INT_MAX;
        poprzednicy[i] = -1;
    }

    drogaWagi[start] = 0;

    for (int i = 0; i < wierzcholki - 1; i++)
    {
        for (int j = 0; j < krawedzie; j++)
        {
            int u = K[j].wp;
            int v = K[j].wk;
            int waga = K[j].waga;

            if (drogaWagi[u] != INT_MAX && drogaWagi[u] + waga < drogaWagi[v])
            {
                drogaWagi[v] = drogaWagi[u] + waga;
                poprzednicy[v] = u;
            }
        }
    }

    cout << "Najkrotsza sciezka z wierzcholka " << start << ":" << endl;

    for (int i = 0; i < wierzcholki; i++)
    {
        szerokosc = -2;
        cout << i << ": ";

        if (drogaWagi[i] == INT_MAX)
        {
            cout << "Brak" << endl;
            continue;
        }

        for (int j = i; j != -1; j = poprzednicy[j])
        {
            stos.push(j);
            szerokosc = szerokosc + 2;
        }

        while (!stos.empty())
        {
            cout << stos.top() << " ";
            stos.pop();
        }
        for (int j = 0; j < wierzcholki - szerokosc; j++)
            cout << " ";

        cout << setw(5) << "(" << drogaWagi[i] << ")" << endl;
    }

    delete[] drogaWagi;
    delete[] poprzednicy;
}


void Graf::lista_Forda(int start)
{
    Stos stos;
    bool zmiana = true;
    int* drogaWagi = new int[wierzcholki];
    int* poprzednicy = new int[wierzcholki];

    for (int i = 0; i < wierzcholki; i++)
    {
        drogaWagi[i] = INT_MAX;
        poprzednicy[i] = -1;
    }
    drogaWagi[start] = 0;

    ElementListy* el;
    while (zmiana)
    {
        zmiana = false;
        for (int i = 0; i < wierzcholki; i++)
        {
            el = listySasiedztwa[i];
            while(el)
            {
                if (drogaWagi[i] < INT_MAX && drogaWagi[el->w] > drogaWagi[i] + el->waga)
                {
                    drogaWagi[el->w] = drogaWagi[i] + el->waga;
                    poprzednicy[el->w] = i; //aktualizowanie poprzednika
                    zmiana = true;
                }
                el = el->nastepny;
            }
        }
    }

    cout << "Najkrotsza sciezka z wierzcholka " << start << "  korzystajac z listy:" << endl;
    for (int i = 0; i < wierzcholki; i++)
    {
        int szerokosc = -2;
        cout << i << ": ";
        if (drogaWagi[i] == INT_MAX)
        {
            cout << "Brak" << endl;
            continue;
        }

        for (int j = i; j != -1; j = poprzednicy[j])
        {
            stos.push(j);
            szerokosc = szerokosc + 2;
        }

        while (!stos.empty())
        {
            cout << stos.top() << " ";
            stos.pop();
        }
        for (int j = 0; j < wierzcholki - szerokosc; j++)
            cout << " ";

        cout << setw(5) << "(" << drogaWagi[i] << ")" << endl;
    }

    delete[] drogaWagi;
    delete[] poprzednicy;
}


void Graf::macierz_Forda(int start) {
    bool zmiana = true;
    int *drogaWagi = new int[wierzcholki];
    int *poprzednicy = new int[wierzcholki];

    for (int i = 0; i < wierzcholki; i++) {
        drogaWagi[i] = INT_MAX;
        poprzednicy[i] = -1;
    }
    drogaWagi[start] = 0;

    while (zmiana) {
        zmiana = false;
        for (int i = 0; i < wierzcholki; i++) {
            for (int j = 0; j < wierzcholki; j++) {
                if (macierzSasiedztwa[i][j] != 0) { // Sprawdzenie czy kraw�d� istnieje
                    if (drogaWagi[i] < INT_MAX && drogaWagi[j] > drogaWagi[i] + macierzSasiedztwa[i][j]) {
                        drogaWagi[j] = drogaWagi[i] + macierzSasiedztwa[i][j];
                        poprzednicy[j] = i; //aktualizowanie poprzednika
                        zmiana = true;
                    }
                }
            }
        }
    }

    cout << "Najkrotsza sciezka z wierzcholka " << start << "  korzystajac z macierzy:" << endl;
    Stos stos;
    for (int i = 0; i < wierzcholki; i++)
    {
        int szerokosc = -2;
        cout << i << ": ";
        if (drogaWagi[i] == INT_MAX)
        {
            cout << "Brak" << endl;
            continue;
        }

        for (int j = i; j != -1; j = poprzednicy[j])
        {
            stos.push(j);
            szerokosc = szerokosc + 2;
        }

        while (!stos.empty())
        {
            cout << stos.top() << " ";
            stos.pop();
        }
        for (int j = 0; j < wierzcholki - szerokosc; j++)
            cout << " ";

        cout << setw(5) << "(" << drogaWagi[i] << ")" << endl;
    }

    delete[] drogaWagi;
    delete[] poprzednicy;
}







    void Graf::wyswietl() {
//    cout << "Macierz incydencji:" << endl;
//    int i;
//    cout << "      ";
//    for (i = 0; i < krawedzie; i++) {
//        cout << setw(3) << i;
//
//    }
//
//    cout << endl << "      ";
//    for (i = 0; i < krawedzie; i++) {
//        cout << setw(3) << "-";
//
//    }
//
//    cout << endl;
//    for (i = 0; i < wierzcholki; i++) {
//        cout << setw(3) << i << " | ";
//        for (int j = 0; j < krawedzie; j++)
//            cout << setw(3) << macierzIncydencji[i][j];
//        cout << endl;
//    }
//    cout << endl;
//    cout << "Wagi: ";
//    for (i = 0; i < krawedzie; i++) {
//        cout << setw(3) << K[i].waga;
//    }

        cout << "Macierz sasiedztwa:" << endl;
        int i;
        cout << "      ";
        for (i = 0; i < wierzcholki; i++) {
            cout << setw(3) << i;

        }

        cout << endl << "      ";
        for (i = 0; i < wierzcholki; i++) {
            cout << setw(3) << "-";

        }

        cout << endl;
        for (i = 0; i < wierzcholki; i++) {
            cout << setw(3) << i << " | ";
            for (int j = 0; j < wierzcholki; j++)
                cout << setw(3) << macierzSasiedztwa[i][j];
            cout << endl;
        }
        cout << endl;
//        cout << "Wagi: ";
//        for (i = 0; i < wierzcholki; i++) {
//            cout << setw(3) << K[i].waga;
//        }

    cout << endl << endl << "Lista sasiedztwa wraz z wagami:" << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << "[" << i << "] ";
        e1 = listySasiedztwa[i];
        while (e1) {
            cout << setw(3) << " -> " << e1->w << "(" << e1->waga << ")";
            e1 = e1->nastepny;
        }
        cout << endl;
    }
}

void Graf::wyswietlLista() {
    cout << endl << endl << "Lista sasiedztwa wraz z wagami:" << endl;
    for (int i = 0; i < wierzcholki; i++) {
        cout << "[" << i << "] ";
        e1 = listySasiedztwa[i];
        while (e1) {
            cout << setw(3) << " -> " << e1->w << "(" << e1->waga << ")";
            e1 = e1->nastepny;
        }
        cout << endl;
    }
}

void Graf::wyswietMacierz() {
    cout << "Macierz sasiedztwa:" << endl;
    int i;
    cout << "      ";
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << i;

    }

    cout << endl << "      ";
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < wierzcholki; j++)
            cout << setw(3) << macierzSasiedztwa[i][j];
        cout << endl;
    }
    cout << endl;
}

void Graf::wyswietMacierzNieskierowna() {
    cout << endl << "Graf nieskierowany:" << endl;
    int i;
    cout << "      ";
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << i;

    }

    cout << endl << "      ";
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << "-";

    }

    cout << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << setw(3) << i << " | ";
        for (int j = 0; j < wierzcholki; j++)
            cout << setw(3) << grafNieskierowanyM[i][j];
        cout << endl;
    }
    cout << endl;
}
////////////

int Graf::lista_FordFulkersonDFS(int u, int t, int minPojemnosc, int* odwiedzone, int** przeplyw) {
    odwiedzone[u] = 1;
    if (u == t)
        return minPojemnosc;
    for (ElementListy* e = listySasiedztwa[u]; e != NULL; e = e->nastepny) {
        int v = e->w;
        if (!odwiedzone[v] && e->waga > 0 && przeplyw[u][v] < e->waga) {
            int przeplywDoV = min(minPojemnosc, e->waga - przeplyw[u][v]);
            int przeplywSciezki = lista_FordFulkersonDFS(v, t, przeplywDoV, odwiedzone, przeplyw);
            if (przeplywSciezki > 0) {
                przeplyw[u][v] += przeplywSciezki;
                przeplyw[v][u] -= przeplywSciezki;
                return przeplywSciezki;
            }
        }
    }
    return 0;
}


void Graf::lista_FordFulkerson(int zrodlo, int ujscie) {
    // Inicjalizacja przep�ywu.
    int **przeplyw = new int*[wierzcholki];
    for(int i = 0; i < wierzcholki; ++i) {
        przeplyw[i] = new int[wierzcholki];
        for(int j = 0; j < wierzcholki; ++j)
            przeplyw[i][j] = 0;
    }
    int maxFlow = 0;

    // G��wna p�tla, wykonywana dop�ki istnieje �cie�ka od �r�d�a do uj�cia.
    while (true) {
        int *odwiedzone = new int[wierzcholki]();
        int przeplywSciezki = lista_FordFulkersonDFS(zrodlo, ujscie, INT_MAX, odwiedzone, przeplyw);
        delete [] odwiedzone;
        if (przeplywSciezki == 0)
            break;

        maxFlow += przeplywSciezki;
    }

// Wypisanie wyniku.
    cout << endl << endl;
    for (int i = 0; i < wierzcholki; ++i) {
        for (ElementListy* e = listySasiedztwa[i]; e != NULL; e = e->nastepny) {
            int flow = przeplyw[i][e->w];
            if (flow < 0)
                flow = 0;
            cout << "Krawedz (" << i << ", " << e->w << ") | Przeplyw(used/max): " << flow << "/" << e->waga << "\n";
        }
    }
    cout << endl << "MAX FLOW = " << maxFlow << "\n";


    // Czyszczenie pami�ci.
    for (int i = 0; i < wierzcholki; ++i) {
        delete[] przeplyw[i];
    }
    delete[] przeplyw;
}


////////////

/////2/////
int Graf::macierz_FordFulkersonDFS(int u, int t, int minPojemnosc, int* odwiedzone, int** przeplyw) {
    odwiedzone[u] = 1;
    if (u == t)
        return minPojemnosc;
    for (int v = 0; v < wierzcholki; ++v) {
        if (macierzSasiedztwa[u][v] != 0 && !odwiedzone[v] && przeplyw[u][v] < macierzSasiedztwa[u][v]) {
            int przeplywDoV = min(minPojemnosc, macierzSasiedztwa[u][v] - przeplyw[u][v]);
            int przeplywSciezki = macierz_FordFulkersonDFS(v, t, przeplywDoV, odwiedzone, przeplyw);
            if (przeplywSciezki > 0) {
                przeplyw[u][v] += przeplywSciezki;
                przeplyw[v][u] -= przeplywSciezki;
                return przeplywSciezki;
            }
        }
    }
    return 0;
}
void Graf::macierz_FordFulkerson(int zrodlo, int ujscie) {
    // Inicjalizacja przep�ywu.
    int **przeplyw = new int*[wierzcholki];
    for(int i = 0; i < wierzcholki; ++i) {
        przeplyw[i] = new int[wierzcholki];
        for(int j = 0; j < wierzcholki; ++j)
            przeplyw[i][j] = 0;
    }
    int maxFlow = 0;

    // G��wna p�tla, wykonywana dop�ki istnieje �cie�ka od �r�d�a do uj�cia.
    while (true) {
        int *odwiedzone = new int[wierzcholki]();
        int przeplywSciezki = macierz_FordFulkersonDFS(zrodlo, ujscie, INT_MAX, odwiedzone, przeplyw);
        delete [] odwiedzone;
        if (przeplywSciezki == 0)
            break;

        maxFlow += przeplywSciezki;
    }

    // Wypisanie wyniku.
    for (int i = 0; i < wierzcholki; ++i) {
        for (int j = 0; j < wierzcholki; ++j) {
            if (macierzSasiedztwa[i][j] > 0) {
                int flow = przeplyw[i][j];
                if (flow < 0)
                    flow = 0;
                cout << "Krawedz (" << i << ", " << j << ") | Przeplyw(used/max): " << flow << "/" << macierzSasiedztwa[i][j] << "\n";
            }
        }
    }

    cout << endl << "MAX_FLOW = " << maxFlow << "\n";

    // Czyszczenie pami�ci.
    for (int i = 0; i < wierzcholki; ++i) {
        delete[] przeplyw[i];
    }
    delete[] przeplyw;
}

/////2/////


void Graf::wyswietlListaNieskierowana() {
    int i;
    cout << endl << "Graf nieskierowany: " << endl << endl;
    for (i = 0; i < wierzcholki; i++) {
        cout << "[" << i << "] ";
        e1 = grafNieskierowanyL[i];
        while (e1) {
            cout << setw(3) << " -> " << e1->w << "(" << e1->waga << ")";
            e1 = e1->nastepny;
        }
        cout << endl;
    }
    cout << endl;
}

