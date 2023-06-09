#include "Interfejs.h"
#include "Testy.h"

using namespace std;

void UI::wyborMetodyGenerowaniaGrafu() {

    while (naPoczatek) {
        cout << "--- Opcje tworzenia grafu ---" << endl << "1. Wygeneruj graf losowo" << endl
             << "2. Utworz graf z pliku" << endl;
        cin >> wybor;
        switch (wybor) {
            case 1: {
                grafLosowy();
                wyborFunkcji();
            }
                break;
            case 2: {
                grafZPliku();
                wyborFunkcji();
            }
                break;
        }
    }
}

void UI::wyborFunkcji() {
    while (!naPoczatek) {

        cout << endl << "--- Menu wyboru algorytmu ---" << endl
             << "1. Wyswietl macierz wag i reprezentacje listowa" << endl
             << "2. Algorytm Kruskala " << endl
             << "3. Algorytm Dijkstry" << endl
             << "4. Algorytm Prima" << endl
             << "5. Algorytm Bellmana-Forda" << endl
             << "6. Algorytm Forda-Fulkersona" << endl
             << "7. Stworz nowy graf" << endl;
        cin >> wybor;
        switch (wybor) {
            case 1: {
                graf->wyswietl();
                cout << endl;
            }
                break;
            case 2: {
                

                while (true) {
                    int wyborReprezentacji;
                    cout << "Jakiej reprezentacji uzyc w algorytmie?" << endl << "1. Macierz sasiedztwa" << endl
                         << "2. Lista sasiedztwa" << endl;
                    cin >> wyborReprezentacji;
                    if (wyborReprezentacji == 1) {
                        graf->wyswietMacierzNieskierowna();
                       graf->KruskalMacierz();
                      
                        break;
                    } else if (wyborReprezentacji == 2) {
                       graf->wyswietlListaNieskierowana();
                        graf->KruskalLista();
						break;
                    }
                }
            }
                break;

            case 3: {
                while (true) {
                    cout << "Zdefiniuj wierzcholek poczatkowy: ";
                    cin >> b;
                    if (b < graf->wierzcholki) break;
                    else cout << "Podano nieprawidlowy numer wierzcholka!" << endl;
                }
                while (true) {
                    int wyborReprezentacji;
                    cout << "Wybierz sposob przedstawienia: " << endl << "1. Macierz sasiedztwa" << endl
                         << "2. Lista sasiedztwa" << endl;
                    cin >> wyborReprezentacji;
                    if (wyborReprezentacji == 1) {
                        graf->wyswietMacierz();
                        graf->macierz_Dijkstry(b);
                        break;
                    } else if (wyborReprezentacji == 2) {
//                            graf->lista_Forda(b, c);
                        graf->wyswietlLista();
                        graf->lista_Dijkstry(b);
                        break;
                    }
                }
            }
                break;


            case 4: {
                while (true) {
                    int wyborReprezentacji;
                    cout << "Wybierz sposob przedstawienia: " << endl
                         << "1. Macierz sasiedztwa" << endl
                         << "2. Lista sasiedztwa" << endl;
                    cin >> wyborReprezentacji;
                    if (wyborReprezentacji == 1) {
                        graf->wyswietMacierzNieskierowna();
                        graf->macierz_Prim();
                        break;
                    } else if (wyborReprezentacji == 2) {
                        graf->wyswietlListaNieskierowana();
                        graf->lista_Prim();
                        break;
                    }
                }

            }
                break;

            case 5: {
                while (true) {
                    cout << "Zdefiniuj wierzcholek poczatkowy: ";
                    cin >> b;
                    if (b < graf->wierzcholki) break;
                    else cout << "Podano nieprawidlowy numer wierzcholka!" << endl;
                }
//                while (true) {
//                    cout << "Zdefiniuj wierzcholek koncowy: ";
//                    cin >> c;
//                    if (c < graf->wierzcholki) break;
//                    else cout << "Podano nieprawidlowy numer wierzcholka!" << endl;
//                }

                while (true) {
                    int wyborReprezentacji;
                    cout << "Wybierz sposob przedstawienia: " << endl << "1. Macierz sasiedztwa" << endl
                         << "2. Lista sasiedztwa" << endl;
                    cin >> wyborReprezentacji;
                    if (wyborReprezentacji == 1) {
//                        graf->macierz_Forda(b, c);
                            graf->wyswietMacierz();
                            graf->macierz_Forda(b);
                            break;
                        } else if (wyborReprezentacji == 2) {
//                            graf->lista_Forda(b, c);
                            graf->wyswietlLista();
                            graf->lista_Forda(b);
                            break;
                    }
                }
//                graf->BellmanFord(b);
            }
                break;

            case 6: {
                int zrodlo, ujscie;
                while (true) {
                    cout << "Zdefiniuj zrodlo: ";
                    cin >> zrodlo;
                    if (zrodlo < graf->wierzcholki) break;
                    else cout << "Podano nieprawidlowe zrodlo!" << endl;
                }
                while (true) {
                    cout << "Zdefiniuj ujscie: ";
                    cin >> ujscie;
                    if (ujscie < graf->wierzcholki) break;
                    else cout << "Podano nieprawidlowe ujscie!" << endl;
                }

                while (true) {
                    int wyborReprezentacji;
                    cout << "Wybierz sposob przedstawienia: " << endl << "1. Macierz sasiedztwa" << endl
                         << "2. Lista sasiedztwa" << endl;
                    cin >> wyborReprezentacji;
                    if (wyborReprezentacji == 1) {
                        graf->wyswietMacierz();
                        graf->macierz_FordFulkerson(zrodlo, ujscie);
                        break;
                    } else if (wyborReprezentacji == 2) {
                        graf->wyswietlLista();
                        graf->lista_FordFulkerson(zrodlo, ujscie);
                        break;
                    }
                }
            }
                break;


            case 7: {
                delete graf;
                naPoczatek = true;
            }
                break;

            case 8: {
                Tests tests(graf);
                tests.measureTime();
                cout << endl;
            }
                break;
        }
    }
}

void UI::grafLosowy() {
    naPoczatek = false;
    while (true) {
        cout << "Zdefiniuj liczbe wierzcholkow grafu: ";
        cin >> w;
        if (w > 1) break;
        else cout << "Liczba wierzcholkow nie moze byc mniejsza lub rowna 1." << endl;
    }


    int maxK = w * (w - 1);
    double minG = ceil((((double) w - 1) * 100) / (double) maxK);

    while (true) {

        cout << "Zdefiniuj gestosc grafu (minimum " << minG << "%): ";
        cin >> g;
        if (g < minG || g > 100)
            cout << "Podana gestosc jest nieprawidlowa!" << endl;
        else
            break;
    }
    double krawedzie = ceil((maxK * g) / 100);
    graf = new Graf(w, krawedzie);
    graf->losujGraf();
}

//void UI::grafZPliku() {
//    naPoczatek = false;
//    ElementListy* e1;
//    string nazwa;
//    cout << "Nazwa pliku (bez rozszerzenia): ";
//    cin >> nazwa;
//    nazwa = nazwa + ".txt";
//    ifstream plik(nazwa);
//    if (!plik) {
//        cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie." << endl;
//        naPoczatek = true;
//    } else {
//        int wierzcholki, krawedzie;
//        plik >> krawedzie >> wierzcholki;
//        if (!plik || krawedzie < wierzcholki - 1 || wierzcholki <= 1 || krawedzie > (wierzcholki * (wierzcholki - 1))) {
//            cout << "Plik jest uszkodzony lub dane w nim zawarte sa nieprawidlowe" << endl;
//            naPoczatek = true;
//        } else {
//            graf = new Graf(wierzcholki, krawedzie);
//            for (int i = 0; i < krawedzie; i++) {
//                int wp, wk, waga;
//                plik >> wp >> wk >> waga;
//                if (wp >= wierzcholki || wk >= wierzcholki || waga < 1) {
//                    cout << "Krawedzie w pliku sa nieprawidlowo okreslone" << endl;
//                    naPoczatek = true;
//                    break;
//                }
//                graf->macierzSasiedztwa[wp][wk] = waga;
//                graf->macierzSasiedztwa[wk][wp] = waga;
//            }
//            if (!naPoczatek) {
//                if (!graf->sprawdzSpojnosc()) {
//                    cout << "Zawarty w pliku graf jest niespojny" << endl;
//                    naPoczatek = true;
//                    delete graf;
//                } else {
//                    wyborFunkcji();
//                }
//            }
//        }
//        plik.close();
//    }
//}

void UI::grafZPliku() {
    naPoczatek = false;

    string nazwa;
    cout << "Nazwa pliku (bez rozszerzenia): ";
    cin >> nazwa;
    nazwa = nazwa + ".txt";

    ifstream plik(nazwa);
    if (!plik) {
        cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie." << endl;
        naPoczatek = true;
        return;
    }

    int wierzcholki, krawedzie;
    plik >> krawedzie >> wierzcholki;
    if (!plik || krawedzie < wierzcholki - 1 || wierzcholki <= 1 || krawedzie > (wierzcholki * (wierzcholki - 1))) {
        cout << "Plik jest uszkodzony lub dane w nim zawarte sa nieprawidlowe" << endl;
        naPoczatek = true;
        return;
    }

//    delete graf;  // Zwolnij poprzedni obiekt Graf (jeœli istnieje)
    graf = nullptr;
    graf = new Graf(wierzcholki, krawedzie);  // Utwórz nowy obiekt Graf
    graf->inicjalizujMacierz();
    graf->inicjalizujListySasiedztwa();

    // Przekazanie danych z pliku do obiektu Graf
    for (int i = 0; i < krawedzie; i++) {
        int wp, wk, waga;
        plik >> wp >> wk >> waga;
        graf->macierzSasiedztwa[wp][wk] = waga;
        graf->macierzSasiedztwa[wk][wp] = waga;

        ElementListy* e1 = new ElementListy;
        e1->w = wk;
        e1->waga = waga;
        e1->nastepny = graf->listySasiedztwa[wp];
        graf->listySasiedztwa[wp] = e1;

        ElementListy* e2 = new ElementListy;
        e2->w = wp;
        e2->waga = waga;
        e2->nastepny = graf->listySasiedztwa[wk];
        graf->listySasiedztwa[wk] = e2;
    }
    graf->inicjalizujGrafNieskierowany();

    plik.close();

}



//void UI::grafZPliku() {
//    string nazwaPliku;
//    cout << "Nazwa pliku (bez rozszerzenia): ";
//    cin >> nazwaPliku;
//    nazwaPliku += ".txt";
//
//    ifstream plik(nazwaPliku);
//    if (!plik) {
//        cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie." << endl;
//        return;
//    }
//
//    int wierzcholki, krawedzie;
//    plik >> wierzcholki >> krawedzie;
//
//    // Utworzenie nowego grafu
//    graf = new Graf(wierzcholki, krawedzie);
//
//    for (int i = 0; i < krawedzie; i++) {
//        int wp, wk, waga;
//        plik >> wp >> wk >> waga;
//
//        // Dodaj krawêdŸ do grafu rêcznie uaktualniaj¹c macierz s¹siedztwa
//        graf->macierzSasiedztwa[wp][wk] = waga;
//        graf->macierzSasiedztwa[wk][wp] = waga;  // Je¿eli graf jest nieskierowany
//    }
//
//    plik.close();
//    cout << "Graf zosta³ wczytany z pliku." << endl;
//}


