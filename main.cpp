#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>

using namespace std;

void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris);
bool ArAtsidaro(const string& failoPasirinkimas);
void rasymas(map<string, vector<int>>& sarasas, const vector<string>& urls);
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, vector<string>& urls);
string sutvarkomeZodi(const string& zodis);
bool TikrinameArUrl(const string& zodis);

int main() {

    map<string, vector<int>> sarasas;
    vector<string> urls;

    string failoPavadinimas = "egzo.txt";

    cout<<"Skaitymas vyksta is failo "<<failoPavadinimas<<endl;

    cout << "\nPalaukite kol failas bus nuskaitytas" << endl;

    if (!ArAtsidaro(failoPavadinimas)) {
        cout << "\nNurodyto failo nepavyko atidaryti." << endl;
        return 1;
    }

    failoSkaitymas(failoPavadinimas, sarasas, urls);

    cout << "\nFailas nuskaitytas. Rezultatus rasite faile rezultatai.txt" << endl;

    rasymas(sarasas, urls);

    return 0;
}

bool ArAtsidaro(const string& failoPasirinkimas) {
    ifstream in(failoPasirinkimas);
    return in.good();
}
string sutvarkomeZodi(const string& zodis) {
    regex negrazusZodisRegex("[^\\w]+");
    string grazusZodis = regex_replace(zodis, negrazusZodisRegex, "");
    transform(grazusZodis.begin(), grazusZodis.end(), grazusZodis.begin(), ::tolower);
    return grazusZodis;
}

bool TikrinameArUrl(const string& zodis) {
    regex urlRegex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    return regex_match(zodis, urlRegex);
}

void pridedameISarasa(const string& zodis, map<string, vector<int>>& sarasas, int eilutesNumeris) {
    if (zodis.empty()) {
        return;
    }

    auto it = sarasas.find(zodis);

    if (it == sarasas.end()) {
        vector<int> eiluciuNr{eilutesNumeris};
        sarasas[zodis] = eiluciuNr;
    } else {
        vector<int>& eiluciuNr = it->second;
        if (eilutesNumeris != eiluciuNr.back()) {
            eiluciuNr.push_back(eilutesNumeris);
        }
    }
}

void rasymas(map<string, vector<int>>& sarasas, const vector<string>& urls) {
    ofstream out("rezultatai.txt");

    if (!out.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    out << "URLS (" << urls.size() << ")" << endl;

    for (const auto& url : urls) {
        out << url << endl;
    }

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
void failoSkaitymas(const string& failoPasirinkimas, map<string, vector<int>>& sarasas, vector<string>& urls) {
    ifstream failas(failoPasirinkimas);
    stringstream tekstas;
    tekstas << failas.rdbuf();
    failas.close();

    string eilute;
    int eilutesNumeris = 0;

    while (getline(tekstas, eilute)) {
        eilutesNumeris++;
        string zodis;
        istringstream in(eilute);

        while (in >> zodis) {
            bool arYraSkaicius = any_of(zodis.begin(), zodis.end(), [](char c) { return isdigit(c); });

            if (TikrinameArUrl(zodis)) {
                urls.push_back(zodis);
            } else if (!arYraSkaicius) {
                zodis = sutvarkomeZodi(zodis);
                pridedameISarasa(zodis, sarasas, eilutesNumeris);
            }
        }
    }
}
