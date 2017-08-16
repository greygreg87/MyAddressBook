#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct KsiazkaAdresowa
{
    int id;
    string imie, nazwisko, telefon, email, adres;
};

int zaladujKsiazkeAdresowa(KsiazkaAdresowa L []);
int dodajOsobe (KsiazkaAdresowa osoba [], int ilosc); // Tu sie wysyla tylko nazwe struktury??
void wyswietlanieZawartosciKsiazkiAdresowej (KsiazkaAdresowa A [], int n);
void znajdzZnajomego (KsiazkaAdresowa Z [], int n, string c);
string pierwszaLitera (string p);

int main()
{
    KsiazkaAdresowa znajomi [1000]; // Tworzenie tablicy w strukturze Ksiazka
    int iloscOsob = zaladujKsiazkeAdresowa(znajomi);
    string wybor;
    string wybor_2 = "0";
    string imieCzyNazwisko;

    do
    {
        if (wybor_2 =="0")
        {
            system("cls");
            cout << "Liczba zajomych w bazie wynosi: " << iloscOsob << " Wybierz jedna z ponizszych opcji" << endl;
            cout << "1. Zapisz nowego znajomego" << endl;
            cout << "2. Wyszukaj znajomego" << endl;
            cout << "3. Wyswietl liste znjomych" << endl;
            cout << "4. Wyjscie" << endl;
            cin >> wybor;

            if (wybor =="1")
            {
                iloscOsob = dodajOsobe(znajomi, iloscOsob); // Tu siê wysy³a tylko nazwe tablicy??
            }   // Koniec zapytania if

            else if (wybor =="2")
            {
                system("cls");
                cout << "1. Wyszukiwanie po imieniu" << endl;
                cout << "2. Wyszukiwanie po nazwisku" << endl;
                cout << "3. Powrot do menu głownego" << endl;
                cin >> wybor_2;

                if (wybor_2 =="1")
                {
                    imieCzyNazwisko = "imie" ;
                    znajdzZnajomego (znajomi, iloscOsob, imieCzyNazwisko);
                    wybor_2 = "0";
                }   // Koniec zapytania if
                else if (wybor_2 =="2")
                {
                    imieCzyNazwisko = "nazwisko" ;
                    znajdzZnajomego (znajomi, iloscOsob, imieCzyNazwisko);
                    wybor_2 = "0";
                }   // Koniec zapytania else if
                else if (wybor_2 =="3")
                {
                    wybor_2 = "0";
                }   // Koniec zapytania else if

                else
                {
                    cout << "Nie ma takiej opcji";
                    Sleep (1000) ;
                    wybor_2 = "0";
                }   // Koniec zapytania else if

            }   // Koniec zapytania else if

            else if (wybor =="3")
            {
                wyswietlanieZawartosciKsiazkiAdresowej (znajomi, iloscOsob);
            }   // Koniec zapytania else if

            else if (wybor =="4")
            {
                exit (0);
            }   // Koniec zapytania else if

            else
            {
                cout << "Nie ma takiej opcji";
                Sleep (1000) ;
            }   // Koniec zapytania else if
        }   // Koniec zapytania if
    }   // Koniec petli while
    return 0;
}   // Koniec czesci glownej main

int zaladujKsiazkeAdresowa(KsiazkaAdresowa L [])
{
    int nr_linii = 1;
    int j = 0;
    string linia;
    fstream skorowidz ;
    skorowidz.open ("Ksiazka_Adresowa.txt" , ios::in) ;

    while (getline (skorowidz , linia))
    {
       switch (nr_linii)
       {
           case 1: L[j].id = atoi (linia.c_str ());       break;
           case 2: L[j].imie = linia ;    break;
           case 3: L[j].nazwisko = linia ; break;
           case 4: L[j].telefon = linia ;  break;
           case 5: L[j].email = linia ;   break;
           case 6: L[j].adres = linia ;    break;
       };    // Koniec wyrazenia switch

       if (nr_linii == 6) {nr_linii = 0; j++;} // Cala petla wykonuje sie prawidlowoa ilosc razy

       nr_linii++ ;
    }   // Koniec petli while

    skorowidz.close () ;
    return j;
}   // Koniec funkcji zaladujKsiazkeAdresowa

int dodajOsobe (KsiazkaAdresowa osoba [], int ilosc)
{
    string imie, nazwisko, telefon, email, adres;
    int numer;
    system("cls");

    numer = ilosc + 1; // Usalanie numeru porzadkowego osoby

    // Pobranie kolejnych danych znajomego
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << "Podaj nazwisko znajomego";
    cin >> nazwisko;
    cout << "Podaj telefon znajomego";
    cin.sync (); // Oproznianie buforu - chyba chodzi o szufladke bierzaca
    getline(cin, telefon); // Wczytuje razem ze spacjami
    cout << "Podaj email znajomego";
    cin >> email;
    cout << "Podaj adres znajomego";
    cin.sync ();
    getline(cin, adres);

    // Dodanie osoby do tablicy
    osoba[ilosc].id = numer;
    osoba[ilosc].imie = imie;
    osoba[ilosc].nazwisko = nazwisko;
    osoba[ilosc].telefon = telefon;
    osoba[ilosc].email = email;
    osoba[ilosc].adres = adres;

    // Dodanie osoby do pliku
    fstream notatnik; // Deklaracja pliku
    notatnik.open("Ksiazka_Adresowa.txt", ios::out | ios::app);
    if (notatnik.good())
    {
        notatnik << numer << endl ;
        notatnik << imie << endl;
        notatnik << nazwisko << endl;
        notatnik << telefon << endl;
        notatnik << email << endl;
        notatnik << adres << endl;

        notatnik.close ();
        cout << "Osoba zostala dodana" << endl;
        Sleep (1000);
    }   // Koniec zapytania if

    else cout << "Nie mozna odnalezc pliku, osoba niezapisana" << endl;

    ilosc ++;
    return ilosc;
}   // Koniec funkcji dodajOsobe

void znajdzZnajomego (KsiazkaAdresowa Z [], int n, string c)
{
    string f;
    cout << "Wpisz szukana fraze: " << endl;
    cin >> f;
    f = pierwszaLitera (f);
    int l = 0 ; //Bedzie pokazywalo ile osob jest o tym imieniu

    if(c == "imie")
    {
    for (int i=0; i<n; i++)
    {
        if (Z[i].imie == f)
        {
            cout <<  l+1 << " Znaleziona osoba o tym imieniu:" << endl;
            cout << "Imie znajomego: " << Z[i].imie << endl;
            cout << "Nazwisko znajomego: " << Z[i].nazwisko << endl;
            cout << "Telefon znajomego: " << Z[i].telefon << endl;
            cout << "Email znajomego: " << Z[i].email << endl;
            cout << "Adres znajomego: " << Z[i].adres << endl;
            cout << endl;
            l++;
        }   // Koniec zapytania if
    }   // Koniec petli for
    }   // Koniec duzego if
    else
    {
    for (int i=0; i<n; i++)
    {
        if (Z[i].nazwisko == f)
        {
            cout <<  l+1 << " Znaleziona osoba o tym nazwisku:" << endl;
            cout << "Imie znajomego: " << Z[i].imie << endl;
            cout << "Nazwisko znajomego: " << Z[i].nazwisko << endl;
            cout << "Telefon znajomego: " << Z[i].telefon << endl;
            cout << "Email znajomego: " << Z[i].email << endl;
            cout << "Adres znajomego: " << Z[i].adres << endl;
            cout << endl;
            l++;
        }   // Koniec zapytania if
    }   // Koniec petli for
    }   // Koniec duzego else

    if (l==0)
    {
        cout << "Brak znajomych dla wyszukania: " << c <<" - " << f << endl;
        Sleep (1000);
    }   // Koniec zapytania if

    cout << "Wcisnij enter" ;
    cin.sync ();
    getchar();
}   // Koniec funkcji znajdzImieZnajomego

string pierwszaLitera (string p)
{
    string tymczas = p;
    int dlugosc = tymczas.length () ;
    transform(tymczas.begin() , tymczas.end() , tymczas.begin() , ::toupper) ;
    char litera = tymczas[0];
    string bez = p.erase (0,1);
    string duze = litera + bez;
    return duze;
}   // Koniec funkcji pierwszaLitera

void wyswietlanieZawartosciKsiazkiAdresowej (KsiazkaAdresowa A [], int n)
{
    if (n != 0)
    {
        for (int i=0; i<n; i++)
        {
            cout << "Imie " << i+1 << " znajomego: " << A[i].imie << endl;
            cout << "Nazwisko " << i+1 << " znajomego: " << A[i].nazwisko << endl;
            cout << "Telefon " << i+1 << " znajomego: " << A[i].telefon << endl;
            cout << "Email " << i+1 << " znajomego: " << A[i].email << endl;
            cout << "Adres " << i+1 << " znajomego: " << A[i].adres << endl;
            cout << endl;
        }   // Koniec petli for

        cout << "Wcisnij enter" ;
        cin.sync ();
        getchar();
    }   // Koniec zapytania if

    else cout << "Brak znajomych w bazie" << endl;
    Sleep (1000);
}   // Koniec funkcji wyswietlaniwZawartosci KsiazkiAdresowej
