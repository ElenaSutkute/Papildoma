#include "mylib.h"

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

