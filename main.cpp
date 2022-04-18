#include <filesystem>
#include <time.h>
#include <string>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <cctype>

#include "TrieStablo.h"

namespace fs = std::filesystem;

int Meni() {
    int k;

    cout << "                               ~MENI~" << endl << endl;
    cout << "          1. Stvaranje praznog recnika i brisanje recnika.\n";
    cout << "          2. Stvaranje recnika na osnovu zadatog skupa datoteka.\n";
    cout << "          0. Kraj programa.\n\n";

    while (1) {
        cin >> k;
        if ((k < 0) || (k > 2)) {
            cout << "Ne postoji opcija! Pokusajte ponovo:\n";
        }
        else {
            return k;
        }
    }
}

int Meni2() {
    int k;

    cout << "                       ~MENI~" << endl << endl;
    cout << "          1. Pretrazivanje reci.\n";
    cout << "          2. Umetanje nove reci.\n";
    cout << "          3. Predikcija na osnovu unete reci.\n";
    cout << "          4. Brisanje recnika && Vracanje na pocetni meni.\n";
    cout << "          0. Kraj programa.\n\n";

    while (1) {
        cin >> k;
        if ((k < 0) || (k > 4)) {
            cout << "Ne postoji opcija! Pokusajte ponovo:\n";
        }
        else {
            return k;
        }
    }
}

bool Slovo(const char* rec) {

    for (unsigned int i = 0; i < strlen(rec); i++)
        if (rec[i] < 'A' || (rec[i] > 'Z' && rec[i] < 'a') || rec[i] > 'z')
            return false;

    if (strlen(rec) == 0)
        return false;
    else
        return true;
}

void trazi(TrieStablo& s, const char* kljuc)
{
    cout << "Trazim kljuc: " << kljuc << endl;
    int rez = s.dohvatiFrek(kljuc);
    if (rez != 0)
        cout << "<" << kljuc << ">" << " : " << rez << endl << endl;
    else
        cout << "Ne postoji kljuc: " << kljuc << endl << endl;
}

void Pretraga(TrieStablo* stablo) {
    string kljuc;
    cout << "Rec? ";
    cin >> kljuc;
    if (!Slovo(kljuc.c_str())) {
        cout << "Rec se mora sastojati samo od velikih i malih slova abecede!" << endl;
    }
    else {
        std::transform(kljuc.begin(), kljuc.end(), kljuc.begin(),
            [](unsigned char c) { return std::tolower(c); });
        trazi(*stablo, kljuc.c_str());
    }
}

void Umetanje(TrieStablo* stablo) {
    string kljuc;
    cout << "Rec? ";
    cin >> kljuc;
    if (!Slovo(kljuc.c_str())) {
        cout << "Rec se mora sastojati samo od velikih i malih slova abecede!" << endl;
    }
    else {
        std::transform(kljuc.begin(), kljuc.end(), kljuc.begin(),
            [](unsigned char c) { return std::tolower(c); });
        stablo->umetni(kljuc.c_str());
    }
}

void Predikcija(TrieStablo* stablo) {
    string word;
    int postoji;
    cout << " '0' za kraj predikcije" << endl;
    while (word != "0") {
        cout << endl << "-->  ";
        cin >> word;
        if (word != "0") {
            cout << endl;
            if (!Slovo(word.c_str())) {
                cout << "Rec se mora sastojati samo od slova abecede!" << endl;
                continue;
            }
            std::transform(word.begin(), word.end(), word.begin(),
                [](unsigned char c) { return std::tolower(c); });
            postoji = stablo->dohvatiFrek(word.c_str());
            if (postoji == 0)
                stablo->SveKombinacije(word.c_str());
            else {
                cout << "1. <" << word << ">  Frekvencija: " << postoji << endl;
            }
        }
    }
}

int main() {
    TrieStablo* stablo = nullptr;
    while(true) {
        int meni = Meni();
        switch (meni) {
            case 1: {
                TrieStablo* stablo = new TrieStablo;
                cout << "\nPrazan recnik stvoren." << endl << endl;
                int flag = 0;
                while (flag != 1) {
                    int meni2 = Meni2();
                    switch (meni2) {
                        case 1: { Pretraga(stablo); break; }
                        case 2: { Umetanje(stablo); break; }
                        case 3: { Predikcija(stablo); break; }
                        case 4: { delete stablo; flag = 1; break;}
                        case 0: { exit(1); }
                    }
                }
                break;
            }
            case 2: {
                time_t start, end;
                time(&start);
                int j = 0;
                int broj = 0;
                TrieStablo* stablo = new TrieStablo;
                cout << "Recnik se ucitava..." << endl;
                string rec;
                std::string path = "text";
                for (const auto& entry : fs::directory_iterator(path)) {

                    ifstream fajl(entry.path());
                    while (fajl >> rec) {
                        std::transform(rec.begin(), rec.end(), rec.begin(),
                            [](unsigned char c) { return std::tolower(c); });
                        if (Slovo(rec.c_str())) {
                            if (stablo->umetni(rec.c_str())) {
                                broj++;
                            }
                        }
                    }
                    j++;
                    std::cout << entry.path() << " " << std::endl;
                }
                cout << "Recnik ucitan." << endl;
                cout << "\nBroj ucitanih datoteka: " << j << endl;
                cout << "\nBroj cvorova: " << stablo->GetBrCvorova() << endl;
                cout << "Ukupno reci: " << broj << endl;
                time(&end);
                double time_taken = (double)(end - start);
                cout << "Time: " << time_taken << "s" << endl;
                cout << endl;
                
                int flag = 0;
                while (flag != 1) {
                    int meni2 = Meni2();
                    switch (meni2) {
                    case 1: { Pretraga(stablo); break; }
                    case 2: { Umetanje(stablo); break; }
                    case 3: { Predikcija(stablo); break; }
                    case 4: { delete stablo; flag = 1; break;}
                    case 0: { exit(1); }
                    }
                }
                break;
            }
            case 0: { exit(2); }
        }
    }
}