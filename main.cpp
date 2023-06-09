#include <iostream>
#include <ctime>
#include "Interfejs.h"

using namespace std;

int main() {
    // Ustawienie polskiej lokalizacji w celu poprawnego wyœwietlania znaków
    setlocale(LC_CTYPE, "Polish");

    // Wyœwietlenie informacji o autorze i projekcie
    cout << endl << "SDiZO, Projekt 2, Mateusz Staszkow, 263949" << endl << endl;

    srand(time(NULL));

    UI ui;
    ui.wyborMetodyGenerowaniaGrafu();
}