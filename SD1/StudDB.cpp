#include "lib.h"
#include "Studentas.h"
#include "Failai.h"

int main() {
    vector<studentas> grupe;
    char uzkl;
    string pavadinimas;
    bool skaitytiFaila = false;

    cout << "Ar nori generuoti faila? t/n: ";
    cin >> uzkl;

    if (uzkl == 't' || uzkl == 'T') {
        cout << "Ivesk failo pavadinima be .txt: ";
        string pavad;
        cin >> pavad;

        cout << "Kiek studentu faile? ";
        int n;

        if (!(cin >> n) || n <= 0) {
            cout << "Klaida: reikia teigiamo sveikojo skaiciaus.\n";
            return 1;
        }

        pavadinimas = pavad + std::to_string(n) + ".txt";

        try {
            GeneruotiFaila(pavadinimas, n);
            cout << "Failas sukurtas.\n";
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << "\n";
            return 1;
        }

        skaitytiFaila = true;
    }
    else {
        cout << "Ar duomenis nuskaityti is failo? t/n: ";
        cin >> uzkl;

        if (uzkl == 't' || uzkl == 'T') {
            cout << "Iveskite failo pavadinima su .txt: ";
            cin >> pavadinimas;
            skaitytiFaila = true;
        }
        else {
            while (true) {
                studentas A;
                grupe.push_back(A);
                A.clear();

                cout << "Ar ivesite dar viena studenta? t/n: ";
                cin >> uzkl;

                if (uzkl == 'n' || uzkl == 'N') break;
            }
        }
    }

    // Skaitome sugeneruota arba vartotojo pasirinkta faila
    if (skaitytiFaila) {
        try {
            std::ifstream failas(pavadinimas);

            if (!failas.is_open()) {
                throw std::runtime_error("Nepavyko atidaryti failo.");
            }

            string eilute;
            std::getline(failas, eilute); // Praleidziame antraste

            while (std::getline(failas, eilute)) {
                std::istringstream duomenys(eilute);

                string vardas, pavarde;
                vector<int> pazymiai;
                int pazymys;

                if (!(duomenys >> vardas >> pavarde)) {
                    continue;
                }

                while (duomenys >> pazymys) {
                    pazymiai.push_back(pazymys);
                }

                if (pazymiai.size() < 2) {
                    continue;
                }

                int egzaminas = pazymiai.back();
                pazymiai.pop_back();

                studentas A(vardas, pavarde, pazymiai, egzaminas);
                grupe.push_back(A);
            }
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << "\n";
            return 1;
        }
    }

   
    std::sort(grupe.begin(), grupe.end(), vardid);

    //suskirstymas į <5 (vargšiukai) ir >=5 (kietiakai)

    vector<studentas> vargsiukai;
    vector<studentas> kietiakai;

    for (const studentas& A : grupe) {
        if (A.vidurkis() < 5.0) {
            vargsiukai.push_back(A);
        }
        else {
            kietiakai.push_back(A);
        }
    }

    std::ofstream silpni("vargsiukai.txt");
    std::ofstream stiprus("kietiakai.txt");

    silpni << left << setw(15) << "Vardas"
        << setw(23) << "Pavarde"
        << setw(18) << "Galutinis (Med.)"
        << setw(18) << "Galutinis (Vid.)" << "\n";

    stiprus << left << setw(15) << "Vardas"
        << setw(23) << "Pavarde"
        << setw(18) << "Galutinis (Med.)"
        << setw(18) << "Galutinis (Vid.)" << "\n";

    for (const studentas& A : vargsiukai) {
        silpni << A;
    }

    for (const studentas& A : kietiakai) {
        stiprus << A;
    }

    //Išvedimas

    cout << std::left << std::setw(15) << "Vardas"
        << std::setw(23) << "Pavarde"
        << std::left << std::setw(18) << "Galutinis (Med.) "
        << std::setw(18) << "Galutinis (Vid.)" << "\n";

    cout << "-------------------------------------------------------------------------\n";

    for (auto K : grupe)
        cout << K;
}