#pragma once
#pragma warning( disable : 26495 )
#pragma warning( disable : 4996 )
#include <iostream>
#include <queue>
using namespace std;

class TrieStablo
{
protected:

    int m_brCvorova = 0;
    int m_brKljuceva = 0;
    

    class TrieCvor
    {
        TrieCvor* m_niz_pokazivaca[26];
        TrieCvor* m_roditelj;
        int frekvencija = 0;
        int m_brojPodstabala;
        char* rec;
        TrieCvor(const TrieCvor&) { }
        TrieCvor& operator=(const TrieCvor&) { }

    public:
        TrieCvor(TrieCvor* roditelj);
        ~TrieCvor();
        TrieCvor* roditelj() { return m_roditelj; }
        TrieCvor* pronadjiPodstablo(char deoKljuca);
        void dodajPodstablo(char deoKljuca, TrieCvor* cvor);
        void ukloniPodstablo(char deoKljuca);
        int brojPodstabala() const { return m_brojPodstabala; }
        void IncFrek() { frekvencija++; }
        void ResFrek() { frekvencija = 0; }
        int dohvatiFrek();
        TrieCvor* GetPointer(int i) { return m_niz_pokazivaca[i]; }
        void SetRec(const char* kljuc) { 
            rec = new char[strlen(kljuc) + 1];
            rec = strcpy(rec, kljuc);
        }
        const char* GetRec() { return rec; } 
    };

    TrieCvor* m_koren;
    TrieCvor* prvi = nullptr;
    TrieCvor* drugi = nullptr;
    TrieCvor* treci = nullptr;

    TrieCvor* pronadjiCvor(const char* kljuc);  
    TrieStablo(const TrieStablo&) { }
    TrieStablo& operator=(const TrieStablo&) { }

public:
    char matrix[3][10] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
                           'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '@',
                           'z', 'x', 'c', 'v', 'b', 'n', 'm', '@', '@', '@'};
    TrieCvor* GetPrvi() { return prvi; }
    TrieCvor* GetDrugi() { return drugi; }
    TrieCvor* GetTreci() { return treci; }
    int GetBrKljuceva() { return m_brKljuceva; }
    int GetBrCvorova() { return m_brCvorova; }
    TrieStablo();
    ~TrieStablo();
    bool umetni(const char* kljuc);
    bool obrisi(const char* kljuc);
    int dohvatiFrek(const char* kljuc);
    void GenerisiGreske(const char* kljuc, int i, int j, int k);
    void SveKombinacije(const char* kljuc);
    void Predikcija(const char* kljuc);
    void Azuriraj(TrieCvor* next);
};