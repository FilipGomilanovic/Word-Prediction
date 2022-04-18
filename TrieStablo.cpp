#pragma warning( disable :  )
#include "TrieStablo.h"



TrieStablo::TrieCvor::TrieCvor(TrieStablo::TrieCvor* roditelj) : m_roditelj(roditelj), m_brojPodstabala(0)
{
    for (int i = 0; i < 26; i++)
        m_niz_pokazivaca[i] = 0;
}

TrieStablo::TrieCvor::~TrieCvor()
{
    if (rec)  
        delete[]rec;
    for (int i = 0; i < 26; i++)
        if (m_niz_pokazivaca[i])
            delete m_niz_pokazivaca[i];
}


TrieStablo::TrieCvor* TrieStablo::TrieCvor::pronadjiPodstablo(char deoKljuca)
{ 
        return m_niz_pokazivaca[deoKljuca-97];      
}

void TrieStablo::TrieCvor::dodajPodstablo(char deoKljuca, TrieStablo::TrieCvor* cvor)
{
         if (!m_niz_pokazivaca[deoKljuca - 97])
         {
             m_niz_pokazivaca[deoKljuca - 97] = cvor;
             m_brojPodstabala++;
         }   
}

void TrieStablo::TrieCvor::ukloniPodstablo(char deoKljuca)
{
        if (m_niz_pokazivaca[deoKljuca - 97])
        {
            m_niz_pokazivaca[deoKljuca - 97] = 0;
            m_brojPodstabala--;
        }  
}

int TrieStablo::TrieCvor::dohvatiFrek()
{
    return frekvencija;
}


TrieStablo::TrieCvor* TrieStablo::pronadjiCvor(const char* kljuc)
{
    if (!m_koren)
        return 0;
    TrieCvor* tek = m_koren;
    for (unsigned int i = 0; i < strlen(kljuc) && tek; i++)
        tek = tek->pronadjiPodstablo(kljuc[i]);

    return tek;
}

TrieStablo::TrieStablo() : m_koren(0) {}

TrieStablo::~TrieStablo()
{
    if (m_koren)
        delete m_koren;
}


bool TrieStablo::umetni(const char* kljuc)
{
    if (!m_koren)
    {
        m_koren = new TrieCvor(0);
        m_brCvorova++;
    }

    TrieCvor* tek = m_koren;
    TrieCvor* sledeci = 0;

    for (unsigned int i = 0; i < strlen(kljuc); i++)
    {
        sledeci = tek->pronadjiPodstablo(kljuc[i]);
        if (!sledeci)
        {
            sledeci = new TrieCvor(tek);
            tek->dodajPodstablo(kljuc[i], sledeci);
            m_brCvorova++;
        }
        tek = sledeci;
    }

    bool rezultat = true;
    if (sledeci->dohvatiFrek() != 0)
        rezultat = false;
    else {
        m_brKljuceva++;
        sledeci->SetRec(kljuc);
    }

    sledeci->IncFrek();
    return rezultat;
}

bool TrieStablo::obrisi(const char* kljuc)
{
    if (!m_koren)
        return false;

    TrieCvor* tek = pronadjiCvor(kljuc);
    if (!tek)
        return false;

    tek->ResFrek();
    int i = strlen(kljuc) - 1;

    while (i >= 0 && tek && tek->brojPodstabala() == 0)
    {
        TrieCvor* roditelj = tek->roditelj();
        delete tek;
        m_brCvorova--;
        if (roditelj)
            roditelj->ukloniPodstablo(kljuc[i--]);
        else
            m_koren = 0;
        tek = roditelj;
    }

    m_brKljuceva--;
    return true;
}

int TrieStablo::dohvatiFrek(const char* kljuc)
{
    TrieCvor* cvor = pronadjiCvor(kljuc);
    if (cvor)
        return cvor->dohvatiFrek();
    return 0;
}

void Popuni(char matrix[3][10], char* a1, int red1, int kolona1, int* n1)
{
    if (red1 == 0) {
        if (kolona1 != 0 && kolona1 != 9) {
            *n1 = 5;
            a1[0] = matrix[red1][kolona1 - 1];
            a1[1] = matrix[red1][kolona1];
            a1[2] = matrix[red1][kolona1 + 1];
            a1[3] = matrix[red1 + 1][kolona1 - 1];
            a1[4] = matrix[red1 + 1][kolona1];
        }
        else {
            *n1 = 3;
            if (kolona1 == 0) {
                a1[0] = matrix[red1][kolona1];
                a1[1] = matrix[red1][kolona1 + 1];
                a1[2] = matrix[red1 + 1][kolona1];
            }
            else if (kolona1 == 9) {
                a1[0] = matrix[red1][kolona1];
                a1[1] = matrix[red1][kolona1 - 1];
                a1[2] = matrix[red1 + 1][kolona1 - 1];
            }
        }
    }
    else if (red1 == 1) {
        if (kolona1 != 0 && kolona1 != 8) {
            *n1 = 6;
            a1[0] = matrix[red1 - 1][kolona1];
            a1[1] = matrix[red1 - 1][kolona1 + 1];
            a1[2] = matrix[red1][kolona1 - 1];
            a1[3] = matrix[red1][kolona1];
            a1[4] = matrix[red1][kolona1 + 1];
            a1[5] = matrix[red1 + 1][kolona1 - 1];
        }
        else {
            *n1 = 4;
            if (kolona1 == 0) {
                a1[0] = matrix[red1 - 1][kolona1];
                a1[1] = matrix[red1 - 1][kolona1 + 1];
                a1[2] = matrix[red1][kolona1];
                a1[3] = matrix[red1][kolona1 + 1];
            }
            else if (kolona1 == 8) {
                a1[0] = matrix[red1 - 1][kolona1];
                a1[1] = matrix[red1 - 1][kolona1 + 1];
                a1[2] = matrix[red1][kolona1 - 1];
                a1[3] = matrix[red1][kolona1];
            }
        }
    }
    else {
        if (kolona1 != 0 && kolona1 != 6) {
            *n1 = 4;
            a1[0] = matrix[red1 - 1][kolona1 + 1];
            a1[1] = matrix[red1][kolona1 - 1];
            a1[2] = matrix[red1][kolona1];
            a1[3] = matrix[red1][kolona1 + 1];
        }
        else {
            *n1 = 3;
            if (kolona1 == 0) {
                a1[0] = matrix[red1 - 1][kolona1 + 1];
                a1[1] = matrix[red1][kolona1];
                a1[2] = matrix[red1][kolona1 + 1];
            }
            else if (kolona1 == 6) {
                a1[0] = matrix[red1 - 1][kolona1 + 1];
                a1[1] = matrix[red1][kolona1 - 1];
                a1[2] = matrix[red1][kolona1];
            }
        }
    }
}

void TrieStablo::GenerisiGreske(const char* kljuc, int i, int j, int k)
{
    int n1 = 0, n2 = 0, n3 = 0, red1 = -1, kolona1 = -1, red2 = -1, kolona2 = -1, red3 = -1, kolona3 = -1;
    char a1[6] = { 'X','X','X','X','X','X' };
    char a2[6] = { 'X','X','X','X','X','X' };
    char a3[6] = { 'X','X','X','X','X','X' };

    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 10; n++) {
            if (matrix[m][n] == kljuc[i]) {
                red1 = m;
                kolona1 = n;
            }
            if (j != -1 && (matrix[m][n] == kljuc[j])) {
                red2 = m;
                kolona2 = n;
            }
            if (k != -1 && (matrix[m][n] == kljuc[k])) {
                red3 = m;
                kolona3 = n;
            }
        }
    }
    Popuni(matrix, a1, red1, kolona1, &n1);
    if (j != -1)
        Popuni(matrix, a2, red2, kolona2, &n2);
    if (k != -1)
        Popuni(matrix, a3, red3, kolona3, &n3);

    char* key = new char[strlen(kljuc) + 1];
    key = strcpy(key, kljuc);

    if (j != -1 && k != -1) {
        for (int o = 0; o < n1; o++) {
            for (int p = 0; p < n2; p++) {
                for (int q = 0; q < n3; q++) {
                    key[i] = a1[o];
                    key[j] = a2[p];
                    key[k] = a3[q];
                    Predikcija(key);
                }
            }
        }
    }
    else {
        if (j != -1) {
            for (int o = 0; o < n1; o++) {
                for (int p = 0; p < n2; p++) {
                    key[i] = a1[o];
                    key[j] = a2[p];
                    Predikcija(key);
                }
            }
        }
        else {
            for (int o = 0; o < n1; o++) {
                key[i] = a1[o];
                Predikcija(key);
            }
        }
    }
}

void TrieStablo::SveKombinacije(const char* kljuc)
{
    int n = strlen(kljuc);
    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            for (int k = j + 1; k < n; k++)
                GenerisiGreske(kljuc, i, j, k);
    if (n == 2) {
        GenerisiGreske(kljuc, 0, 1, -1);
    }
    if (n == 1) {
        GenerisiGreske(kljuc, 0, -1, -1);
    }

    if (prvi != nullptr)
    cout << "1. <" << prvi->GetRec() << ">  Frekvencija: " << prvi->dohvatiFrek() << endl;
    if (drugi != nullptr)
    cout << "2. <" << drugi->GetRec() << ">  Frekvencija: " << drugi->dohvatiFrek() << endl;
    if (treci != nullptr)
    cout << "3. <" << treci->GetRec() << ">  Frekvencija: " << treci->dohvatiFrek() << endl;

    prvi = nullptr;
    drugi = nullptr;
    treci = nullptr;
}

void TrieStablo::Predikcija(const char* kljuc)
{
    TrieCvor* tekuci = pronadjiCvor(kljuc);
    TrieCvor* next;
    if (tekuci != nullptr) {
        queue<TrieCvor*> q;
        q.push(tekuci);
        while (!q.empty()) {
            next = q.front();
            q.pop();
            if (next->dohvatiFrek() != 0)
                Azuriraj(next);
            for (int i = 0; i < 26; i++) {
                if (next->GetPointer(i) != 0) {
                    q.push(next->GetPointer(i));
                }
            }
        }
    }
}

void TrieStablo::Azuriraj(TrieCvor* next)
{
    if (prvi == nullptr) {
        prvi = next;
    }
    else if (next->dohvatiFrek() > prvi->dohvatiFrek()) {
        treci = drugi;
        drugi = prvi;
        prvi = next;
    }
    else if ((drugi == nullptr) && (next->GetRec() != prvi->GetRec())) {
        drugi = next;
    }
    else if ((drugi != nullptr) && (next->dohvatiFrek() > drugi->dohvatiFrek()) && (next->GetRec() != prvi->GetRec())){
        treci = drugi;
        drugi = next;
    }
    else if ((treci == nullptr) && (next->GetRec() != prvi->GetRec()) && (next->GetRec() != drugi->GetRec())) {
        treci = next;
    }
    else if ((treci != nullptr) && (next->dohvatiFrek() > treci->dohvatiFrek()) && (next->GetRec() != prvi->GetRec()) && (next->GetRec() != drugi->GetRec())) {
        treci = next;
    }
}
