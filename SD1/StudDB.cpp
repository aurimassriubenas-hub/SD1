#include "lib.h"
#include "Studentas.h"

int main() {
    vector <studentas> grupe;
    //skaičiavimo būdo pasirinkimas
    char pasirinkimas;
    cout << "Skaiciuoti pagal mediana? t/n ";
    cin >> pasirinkimas;

    bool mediana = (pasirinkimas == 't' || pasirinkimas == 'T');
    while (true) {
        studentas A;
        A.Skaiciuoti(mediana);
        grupe.push_back(A);
        A.clear();
        char uzkl;
        cout << "Ar ivesite dar viena studenta? t/n "; cin >> uzkl;
        if (uzkl == 'n' || uzkl == 'N') break;
    }
    std::sort(grupe.begin(), grupe.end(), vardid);

    // PAPILDYTA: lenteles antraste
    cout << std::left << std::setw(10) << "Vardas"
        << std::setw(20) << "Pavarde";

    if (mediana) {
        cout << "Galutinis (Med.)\n";
    }
    else {
        cout << "Galutinis (Vid.)\n";
    }

    cout << "---------------------------------------------\n";

    for (auto K : grupe)
        cout << K;
}