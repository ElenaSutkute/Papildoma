#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

bool ArAtsidaro(const string& failoPasirinkimas);
void rasymas();
void failoSkaitymas(const string& failoPasirinkimas);

int main() {
    string failoPavadinimas = "egzo.txt";
    cout << "Skaitymas vyksta is failo " << failoPavadinimas << endl;
    cout << "\nPalaukite kol failas bus nuskaitytas" << endl;

    if (!ArAtsidaro(failoPavadinimas)) {
        cout << "\nNurodyto failo nepavyko atidaryti." << endl;
        return 1;
    }
    failoSkaitymas(failoPavadinimas);

    rasymas();

    return 0;
}

bool ArAtsidaro(const string& failoPasirinkimas) {
    ifstream in(failoPasirinkimas);
    return in.good();
}

void rasymas() {
    ofstream out("rezultatai.txt");

    if (!out.good()) {
        cout << "Failo nepavyko sukurti." << endl;
        return;
    }

    out << "URLS " << endl;

    out << left << setw(30) << "ZODIS" << setw(10) << "KIEKIS" << "EILUCIU NR." << endl;

    out.close();
}
void failoSkaitymas(const string& failoPasirinkimas) {
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

    }
}
