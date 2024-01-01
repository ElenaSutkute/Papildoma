#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>


using namespace std;

void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris);
bool ArAtsidaro(const string& failoPasirinkimas);
void rasymas(map<string, vector<int>>& sarasas);

void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas);
void sutvarkomeZodi(string& zodis);

int main() {

    map<string, vector<int>> sarasas;

    string failoPavadinimas = "egzo.txt";

    cout<<"Skaitymas vyksta is failo "<<failoPavadinimas<<endl;

    cout << "\nPalaukite kol failas bus nuskaitytas" << endl;

    if (!ArAtsidaro(failoPavadinimas)) {
        cout << "\nNurodyto failo nepavyko atidaryti." << endl;
        return 1;
    }

    failoSkaitymas(failoPavadinimas, sarasas);

    cout << "\nFailas nuskaitytas. Rezultatus rasite faile rezultatai.txt" << endl;

    rasymas(sarasas);

    return 0;
}

bool ArAtsidaro(const string& failoPasirinkimas) {
    ifstream in(failoPasirinkimas);
    return in.good();
}



bool isLithuanianLetter(char c) {
    return ((c >= 0x80 && c <= 0xAF) || (c >= 0xC4 && c <= 0xCB) || (c >= 0xD0 && c <= 0xDB) || (c >= 0xDC && c <= 0xFF));
}

void sutvarkomeZodi(string& zodis) {
    zodis.erase(remove_if(zodis.begin(), zodis.end(), [](char c) {
        return !isalpha(c) && !isLithuanianLetter(c);
    }), zodis.end());
}


void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris) {
    string cleanedZodis = zodis;
    sutvarkomeZodi(cleanedZodis);

    if (cleanedZodis.empty()) {
        return;
    }

    auto it = sarasas.find(cleanedZodis);

    if (it == sarasas.end()) {
        vector<int> eiluciuNr{eilutesNumeris};
        sarasas[cleanedZodis] = eiluciuNr;
    } else {
        vector<int>& eiluciuNr = it->second;
        if (eilutesNumeris != eiluciuNr.back()) {
            eiluciuNr.push_back(eilutesNumeris);
        }
    }
}


void rasymas(map<string, vector<int>>& sarasas) {
    ofstream out("rezultatai.txt");

    if (!out.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    out << "URLS " << endl;

    out << endl;

    if (!sarasas.empty()) {
        out << left << setw(30) << "ZODIS" << setw(10) << "KIEKIS" << "EILUCIU NR." << endl;

        for (const auto& i : sarasas) {
            if (i.second.size() > 1) {
                out << left << setw(30) << i.first << setw(10) << i.second.size();

                for (int j : i.second) {
                    out << setw(4) << j;
                }

                out << endl;
            }
        }
    }

    out.close();
}
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas) {
    ifstream failas(failoPasirinkimas);
    stringstream tekstas;
    tekstas << failas.rdbuf();
    failas.close();

    string eilute;
    int eilutesNumeris = 0;

    while (getline(tekstas, eilute))
    {
        eilutesNumeris++;
        string zodis;
        istringstream in(eilute);

        while (in >> zodis)
        {
            pridedameISarasa(zodis, sarasas, eilutesNumeris);
        }
    }

}

