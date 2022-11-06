#include <iostream>
#include "plansza.h"
#include "SI.h"
using namespace std;

// X - gracz
// O - komputer


int main() {

    SI komputer;
    int rozmiar;
    int wiersz;
    int kolumna;


    // tworzenie planszy
    cout << "Prosze podac rozmiar planszy (min 3): " << endl;
    cin >> rozmiar;
    if (rozmiar < 3) {
        cout << "podano zbyt mala wartosc" << endl;
        return 0;
    }
    plansza plansza(rozmiar);


    //ustalenie zasad
    cout << "Ile znakow w rzedzie jest koniecznych aby wygrac? (min 3 - max rozmiar): " << endl;
    int zasada;
    cin >> zasada;
    if (zasada < 3 || zasada > rozmiar) {
        cout << "bledna zasada niespelniajaca wymagan " << endl;
        return 0;
    }

    srand(time(NULL));
    int x = rand() % rozmiar;
    int y = rand() % rozmiar;
    plansza(x, y) = 'O';


    // glowna petla programu
    while (1) {


        //system("clear");
        plansza.wyswietl();
        if (plansza.czyRemis()) {
            plansza.wyczysc();
            cout << "remis" << endl;
            return 0;
        }

        //while do wyboru ruchu
        while (1) {

            cout << "podaj numer wieszu: ";
            cin >> wiersz;
            if (wiersz < 0 || wiersz > rozmiar - 1) {
                cout << "podano nieprawidowe dane dla wiersza" << endl;
                return 0;
            } //do awaryjnego wylaczenia programu
            cout << endl;

            cout << "podaj numer kolumny: ";
            cin >> kolumna;
            if (kolumna < 0 || kolumna > rozmiar - 1) {
                cout << "podano nieprawidowe dane dla kolumny" << endl;
                return 0;
            } //do awaryjnego wylaczenia programu
            cout << endl;

            //weryfikacja mozliwosci ruchu w dane miejsce, jesli tak ruch jest wykonywany
            if (plansza.mozliwosc_ruchu(wiersz, kolumna)) {
                plansza.ruch(wiersz, kolumna, 'X');
                break;
            }
            //w przeciwnym wypadku uzytkownik wybiera jeszcze raz
            else {
                cout << endl << "to pole jest niedostepne, sproboj ponownie" << endl;
            }

        }//while od ruchu


        //sprawdzanie czy wygrana
        if (plansza.czyWygrana('X', zasada)) {
            //system("clear");
            plansza.wyswietl();
            plansza.wyczysc();
            cout << "Wygrana X" << endl;
            //sleep(3);
            return 0;
        }

        //ruch komputera, zabezpieczenie przed zajetymi polami jest w klasie SI
        komputer.najlepszy_ruch(plansza.get_wsk(), plansza.get_rozmiar(), zasada);
        wiersz = komputer.get_wiersz();
        kolumna = komputer.get_kolumna();
        plansza.ruch(wiersz, kolumna, 'O');


        //sprawdzanie czy wygrana
        if (plansza.czyWygrana('O', zasada)) {
            //system("clear");
            plansza.wyswietl();
            plansza.wyczysc();
            cout << "Wygrana O" << endl;
            //sleep(3);
            return 0;
        }

    }// while
}//main


