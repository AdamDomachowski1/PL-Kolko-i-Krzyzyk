#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class plansza {
private:
    char** tablica;
    char* plansza_wsk; //wskaznik na tablice
    int rozmiar_planszy;

public:
    plansza(int rozmiar);                   //konstruktor parametryczny
    void wyczysc();
    bool mozliwosc_ruchu(int w, int k);     //sprawdza czy mozna wykonach ruch
    void ruch(int w, int k, char gracz);    //umozliwia wykonanie ruchu 
    void wyswietl();                        //wyswietla plansze
    bool czyWygrana(char znak, int zasada);             //sprawdza czy gra nie zostala juz wygrana
    bool czyRemis();
    char& operator () (int row, int column);
    char** get_wsk();
    int get_rozmiar();

};



plansza::plansza(int rozmiar) {              //konstruktor parametryczny, tablica przechowuje wskazniki na elementy
    plansza_wsk = new char[rozmiar * rozmiar];    //przechowujemy rozmiar^2 danych 
    for (int i = 0; i < rozmiar * rozmiar; i++) {
        plansza_wsk[i] = ' ';                   //wypelniamy pole spacjami
    }

    //przepsiuje to do tablicy 2 wymiarowej
    tablica = new char* [rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        tablica[i] = new char[rozmiar];
    }

    //wypelniam tablice spacjami
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            tablica[i][j] = plansza_wsk[j + (i * rozmiar)];
        }
    }

    //usuwam pierwsza tablice
    delete[] plansza_wsk;

    rozmiar_planszy = rozmiar;

}

void plansza::wyczysc() {
    for (int i = 0; i < rozmiar_planszy; i++) {
        delete[] tablica[i];
    }
    delete[] tablica;
}

void plansza::wyswietl() {                   //wyswietla plansze  
    cout << endl << endl; // nowy wiersz
    for (int i = 0; i < rozmiar_planszy; i++) {
        for (int j = 0; j < rozmiar_planszy; j++) {
            cout << " [ " << tablica[i][j] << " ] ";
        }
        cout << endl << endl; // nowy wiersz
    }//for   
}

void plansza::ruch(int w, int k, char gracz) {
    tablica[w][k] = gracz;
}

bool plansza::mozliwosc_ruchu(int w, int k) {
    if (tablica[w][k] == ' ') {
        return true;
    }
    else {
        return false;
    }
}

bool plansza::czyWygrana(char znak, int zasada) {    //warunkiem wygrania sa 3 te same znaki / | __
//dla ulatwien zapisu
//char *p = plansza_wsk;
    int r = rozmiar_planszy;
    int licznik = 0;

    //Algorytm ilosci przeszukiwan po przekatnych dla tablicy zalezy do rozmiaru i zasady. Wzor na ilosc koniecznych 
    //pzreszukan to (R-(Z-1)^2) gdzie R to rozmiar i Z to zasada.

    //DLA opcji ukos w prawo
    for (int i = 0; i < (r - (zasada - 1)); i++) {
        for (int j = 0; j < r - (zasada - 1); j++) {
            int w, k;
            w = i;
            k = j;
            licznik = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania
                if (tablica[w][k] == znak) {
                    licznik++;
                    if (licznik == zasada) {
                        cout << "1" << endl;
                        return true;
                    }
                }
                else {
                    licznik = 0;
                }
                w++;
                k++;
            }
        }
    }

    //DLA opcji ukos w lewo
    for (int i = r - (zasada - 1) + 1; i > zasada - 2; i--) {
        for (int j = 0; j < r - (zasada - 1); j++) {
            int w, k;
            w = i;
            k = j;
            licznik = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania
                if (tablica[w][k] == znak) {
                    licznik++;
                    if (licznik == zasada) {
                        cout << "2" << endl;
                        return true;
                    }
                }
                else {
                    licznik = 0;
                }
                w--;
                k++;
            }
        }
    }



    //DLA opcji pionowej
    for (int i = 0; i < (r - (zasada - 1)); i++) {
        for (int j = 0; j < r; j++) {
            int w, k;
            w = i;
            k = j;
            licznik = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania
                if (tablica[w][k] == znak) {
                    licznik++;
                    if (licznik == zasada) {
                        cout << "3" << endl;
                        return true;
                    }
                }
                else {
                    licznik = 0;
                }
                w++;
            }
        }
    }

    //DLA opcji poziomej

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < (r - (zasada - 1)); j++) {
            int w, k;
            w = i;
            k = j;
            licznik = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania
                if (tablica[w][k] == znak) {
                    licznik++;
                    if (licznik == zasada) {
                        cout << "4" << endl;
                        return true;
                    }
                }
                else {
                    licznik = 0;
                }
                k++;
            }
        }
    }



    return false;
}

bool plansza::czyRemis() {
    int licznik = 0;
    for (int i = 0; i < rozmiar_planszy; i++) {
        for (int j = 0; j < rozmiar_planszy; j++) {
            if (tablica[i][j] != ' ') {
                licznik++;
            }
            if (licznik == rozmiar_planszy * rozmiar_planszy) {
                return true;
            }
        }
    }
    return false;
}

char& plansza::operator()(int w, int k) {
    if (w >= rozmiar_planszy) {
        throw "wystapil blad plansza.cpp operator ()";
        exit(0);
    }

    if (k >= rozmiar_planszy) {
        throw "wystapil blad plansza.cpp operator ()";
        exit(0);
    }

    return tablica[w][k];
}

char** plansza::get_wsk() {
    return tablica;
}

int plansza::get_rozmiar() {
    return rozmiar_planszy;
}