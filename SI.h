#pragma once
#include <iostream>
#include <math.h>
#include "plansza.h"
using namespace std;

class SI {
private:
    //friend class plansza;   
    //char *wsk;  
    int wiersz = 0;
    int kolumna = 0;

public:
    bool mozliwosc_wykonania_ruchu(char** wsk, int rozmiar);
    int szacowanie(char** wsk, int rozmiar, int zasada);
    int minimax(char** wsk, int rozmiar, int deph, bool isMax, int alpha, int beta, int zasada);
    void najlepszy_ruch(char** tablica, int rozmiar, int zasada);
    int get_wiersz();
    int get_kolumna();
};


//sprawdzamy czy jest gdzie wykonac ruch
bool SI::mozliwosc_wykonania_ruchu(char** tablica, int rozmiar) {
    //cout << "jestm w mozliwosc wykonania ruchu" << endl;
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

int SI::szacowanie(char** tablica, int r, int zasada) {    //warunkiem wygrania sa 3 te same znaki / | __
//cout << "jestm w szacowanie" << endl;


//DLA opcji ukos w prawo
    for (int i = 0; i < (r - (zasada - 1)); i++) {
        for (int j = 0; j < r - (zasada - 1); j++) {
            int w, k;
            w = i;
            k = j;
            int licznik_pion_O = 0;
            int licznik_pion_X = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania


                if (tablica[w][k] == 'O') {
                    licznik_pion_O++;
                    if (licznik_pion_O == zasada) {
                        ;
                        return 10;
                    }
                }
                else {
                    licznik_pion_O = 0;
                }


                if (tablica[w][k] == 'X') {
                    licznik_pion_X++;
                    if (licznik_pion_X == zasada) {
                        ;
                        return -10;
                    }
                }
                else {
                    licznik_pion_X = 0;
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
            int licznik_pion_O = 0;
            int licznik_pion_X = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania


                if (tablica[w][k] == 'O') {
                    licznik_pion_O++;
                    if (licznik_pion_O == zasada) {
                        ;
                        return 10;
                    }
                }
                else {
                    licznik_pion_O = 0;
                }


                if (tablica[w][k] == 'X') {
                    licznik_pion_X++;
                    if (licznik_pion_X == zasada) {
                        ;
                        return -10;
                    }
                }
                else {
                    licznik_pion_X = 0;
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
            int licznik_pion_O = 0;
            int licznik_pion_X = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania


                if (tablica[w][k] == 'O') {
                    licznik_pion_O++;
                    if (licznik_pion_O == zasada) {
                        ;
                        return 10;
                    }
                }
                else {
                    licznik_pion_O = 0;
                }


                if (tablica[w][k] == 'X') {
                    licznik_pion_X++;
                    if (licznik_pion_X == zasada) {
                        ;
                        return -10;
                    }
                }
                else {
                    licznik_pion_X = 0;
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
            int licznik_pion_O = 0;
            int licznik_pion_X = 0;
            for (int s = 0; s < zasada; s++) {   //petla od sprawdzania


                if (tablica[w][k] == 'O') {
                    licznik_pion_O++;
                    if (licznik_pion_O == zasada) {
                        ;
                        return 10;
                    }
                }
                else {
                    licznik_pion_O = 0;
                }


                if (tablica[w][k] == 'X') {
                    licznik_pion_X++;
                    if (licznik_pion_X == zasada) {
                        ;
                        return -10;
                    }
                }
                else {
                    licznik_pion_X = 0;
                }


                k++;
            }
        }
    }

    return 0;
}//szacowanie

int SI::minimax(char** tablica, int rozmiar, int depth, bool isMax, int alpha, int beta, int zasada) {


    int score = szacowanie(tablica, rozmiar, zasada);
    //cout << score << endl;


    if (score == 10) {
        return score;
    }

    if (score == -10) {
        return score;
    }

    if (mozliwosc_wykonania_ruchu(tablica, rozmiar) == false) {
        return 0;
    }

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (tablica[i][j] == ' ') {
                    tablica[i][j] = 'O';
                    best = max(best, minimax(tablica, rozmiar, depth + 1, !isMax, alpha, beta, zasada));
                    alpha = max(alpha, best);
                    //cout << "alpha " << alpha << endl;
                    tablica[i][j] = ' ';
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }//
        return best;
    }

    else {
        int best = 1000;

        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (tablica[i][j] == ' ') {
                    tablica[i][j] = 'X';
                    best = min(best, minimax(tablica, rozmiar, depth + 1, !isMax, alpha, beta, zasada));
                    beta = min(beta, best);
                    //cout << "beta " << beta << endl;
                    tablica[i][j] = ' ';
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }//
        return best;
    }


}

void SI::najlepszy_ruch(char** tablica, int rozmiar, int zasada) {
    //cout << "jestm w najlepszy ruch" << endl;
    int bestVal = -1000;
    SI najlepszy_ruch;
    najlepszy_ruch.wiersz = -1;
    najlepszy_ruch.kolumna = -1;

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[i][j] == ' ') {
                tablica[i][j] = 'O';
                int moveVal = minimax(tablica, rozmiar, 0, false, -1000, 1000, zasada);
                tablica[i][j] = ' ';
                //cout << moveVal << " dla " << i <<  " " << j << endl;
                //cout << " ... " << endl;
                if (moveVal > bestVal) {
                    najlepszy_ruch.wiersz = i;
                    najlepszy_ruch.kolumna = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    wiersz = najlepszy_ruch.wiersz;
    kolumna = najlepszy_ruch.kolumna;
}

int SI::get_wiersz() {
    return wiersz;
}

int SI::get_kolumna() {
    return kolumna;
}

