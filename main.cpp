#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

bool ArAtsidaro(const string& failoPasirinkimas);
void rasymas(const string& egzoFailoPavadinimas, const string& rezultatuFailoPavadinimas); 

int main() {
    string egzoFailoPavadinimas = "egzo.txt";
    string rezultatuFailoPavadinimas = "rezultatai.txt";
    cout << "Skaitymas vyksta is failo " << egzoFailoPavadinimas << endl;
    cout << "\nPalaukite kol failas bus nuskaitytas" << endl;

    if (!ArAtsidaro(egzoFailoPavadinimas)) {
        cout << "\nNurodyto failo nepavyko atidaryti." << endl;
        return 1;
    }

    rasymas(egzoFailoPavadinimas, rezultatuFailoPavadinimas);

    return 0; 
}

bool ArAtsidaro(const string& failoPasirinkimas) {
    ifstream in(failoPasirinkimas);
    return in.good();
}

void rasymas(const string& egzoFailoPavadinimas, const string& rezultatuFailoPavadinimas) {
    ifstream egzoFailas(egzoFailoPavadinimas);
    ofstream rezultatuFailas(rezultatuFailoPavadinimas);

    if (!egzoFailas.good()) {
        cout << "Nepavyko atidaryti egzo failo." << endl;
        return;
    }

    if (!rezultatuFailas.good()) {
        cout << "Nepavyko atidaryti rezultatu failo." << endl;
        return;
    }


    string eilute;
    while (getline(egzoFailas, eilute)) {
        rezultatuFailas << eilute << endl;
    }

    cout << "Informacija buvo sėkmingai išvesta i rezultatu faila." << endl;
}
