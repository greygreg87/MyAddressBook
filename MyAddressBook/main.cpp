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
int dodajOsobe (KsiazkaAdresowa osoba [], int ilosc);
void wyswietlanieZawartosciKsiazkiAdresowej (KsiazkaAdresowa A [], int n);
void znajdzImieZnajomego (KsiazkaAdresowa Z [], int n);
void znajdzNazwiskoZnajomego (KsiazkaAdresowa Z [], int n);
string pierwszaLitera (string p);

int main()
{
    KsiazkaAdresowa znajomi [1000];
    int iloscOsob = zaladujKsiazkeAdresowa(znajomi);
    string wybor;
    string wybor_2 = "0";

    while (true)
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
                iloscOsob = dodajOsobe(znajomi, iloscOsob);
            }   // if

            else if (wybor =="2")
            {
                system("cls");
                cout << "1. Wyszukiwanie po imieniu" << endl;
                cout << "2. Wyszukiwanie po nazwisku" << endl;
                cout << "3. Powrot do menu glownego" << endl;
                cin >> wybor_2;

                if (wybor_2 =="1")
                {
                    znajdzImieZnajomego (znajomi, iloscOsob);
                    wybor_2 = "0";
                }   // if
                else if (wybor_2 =="2")
                {
                    znajdzNazwiskoZnajomego (znajomi, iloscOsob);
                    wybor_2 = "0";
                }   // else if
                else if (wybor_2 =="3")
                {
                    wybor_2 = "0";
                }   // else if

                else
                {
                    cout << "Nie ma takiej opcji";
                    Sleep (1000) ;
                    wybor_2 = "0";
                }   // else if

            }   // else if

            else if (wybor =="3")
            {
                wyswietlanieZawartosciKsiazkiAdresowej (znajomi, iloscOsob);
            }   // else if

            else if (wybor =="4")
            {
                exit (0);
            }   // else if

            else
            {
                cout << "Nie ma takiej opcji";
                Sleep (1000) ;
            }   // else if
        }   // if
    }   // while
    return 0;
}   // main

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
       };    // switch

       if (nr_linii == 6) {nr_linii = 0; j++;}

       nr_linii++ ;
    }   // while

    skorowidz.close () ;
    return j;
}   // zaladujKsiazkeAdresowa

int dodajOsobe (KsiazkaAdresowa osoba [], int ilosc)
{
    string imie, nazwisko, telefon, email, adres;
    int numer;
    system("cls");

    numer = ilosc + 1;

    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << "Podaj nazwisko znajomego";
    cin >> nazwisko;
    cout << "Podaj telefon znajomego";
    cin.sync ();
    getline(cin, telefon);
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
    fstream notatnik;
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
    }   // if

    else cout << "Nie mozna odnalezc pliku, osoba niezapisana" << endl;

    ilosc ++;
    return ilosc;
}   // dodajOsobe

void znajdzImieZnajomego (KsiazkaAdresowa Z [], int n)
{
    string f;
    cout << "Wpisz szukana fraze: " << endl;
    cin >> f;
    f = pierwszaLitera (f);
    int l = 0 ;
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
        }   // if
    }   // for

    if (l==0)
    {
        cout << "Brak znajomych o tym imieniu" << endl;
        Sleep (1000);
    }   // if

    cout << "Wcisnij enter" ;
    cin.sync ();
    getchar();
}   // znajdzImieZnajomego

void znajdzNazwiskoZnajomego (KsiazkaAdresowa Z [], int n)
{
    string f;
    cout << "Wpisz szukana fraze: " << endl;
    cin >> f;
    f = pierwszaLitera (f);
    int l = 0;
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
        }   // if
    }   // for

    if (l == 0)
    {
        cout << "Brak znajomych o tym nazwisku" << endl;
        Sleep (1000);
    }   // if

    cout << "Wcisnij enter" ;
    cin.sync ();
    getchar();
}   // znajdzNazwiskoZnajomego

string pierwszaLitera (string p)
{
    string tymczas = p;
    int dlugosc = tymczas.length () ;
    transform(tymczas.begin() , tymczas.end() , tymczas.begin() , ::toupper) ;
    char litera = tymczas[0];
    string bez = p.erase (0,1);
    string duze = litera + bez;
    return duze;
}   // pierwszaLitera

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
        }   // for

        cout << "Wcisnij enter" ;
        cin.sync ();
        getchar();
    }   // if

    else cout << "Brak znajomych w bazie" << endl;
    Sleep (1000);
}   // wyswietlaniwZawartosciKsiazkiAdresowej
