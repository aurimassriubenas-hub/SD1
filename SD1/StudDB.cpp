#include "lib.h"
#include "Studentas.h"

int main() {
    vector <studentas> grupe;
    //skaičiavimo būdo pasirinkimas

    while (true) {
        studentas A;
        grupe.push_back(A);
        A.clear();
        char uzkl;
        cout << "Ar ivesite dar viena studenta? t/n "; cin >> uzkl;
        if (uzkl == 'n' || uzkl == 'N') break;
    }
    std::sort(grupe.begin(), grupe.end(), vardid);

    // PAPILDYTA: lenteles antraste
    cout << std::left << std::setw(15) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::right << std::setw(18) << "Galutinis (Med.)"
        << std::setw(18) << "Galutinis (Vid.)" << "\n";

    cout << "-----------------------------------------------------------------------\n";

    for (auto K : grupe)
        cout << K;
}