#include "lib.h"
#include "Studentas.h"

int main() {
    vector<studentas> grupe;
    char uzkl;

    cout << "Ar duomenis nuskaityti is failo? t/n ";
    cin >> uzkl;

    if (uzkl == 'n' || uzkl == 'N') {
        while (true) {
            studentas A;
            grupe.push_back(A);
            A.clear();

            char uzkl;
            cout << "Ar ivesite dar viena studenta? t/n ";
            cin >> uzkl;

            if (uzkl == 'n' || uzkl == 'N') break;
        }
    }
    // Duomenys nuskaitomi iš failo
    else {
        try {
            std::ifstream failas("kursiokai.txt");

            if (!failas.is_open()) {
                //cout << "Nepavyko atidaryti kursiokai.txt\n";
                //return 1;
                throw std::runtime_error("Nepavyko atidaryti kursiokai.txt");
            }


            string eilute;

            // Praleidziame antraste
            std::getline(failas, eilute);

            // Skaitome studentus nuo antros eilutes
            while (std::getline(failas, eilute)) {
                std::istringstream duomenys(eilute);

                string pavarde, vardas;
                vector<int> pazymiai;
                int pazymys;

                if (!(duomenys >> pavarde >> vardas)) {
                    continue;
                }

                while (duomenys >> pazymys) {
                    pazymiai.push_back(pazymys);
                }

                // Bent vienas ND ir egzaminas
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

    cout << std::left << std::setw(15) << "Vardas"
        << std::setw(23) << "Pavarde"
        << std::left << std::setw(18) << "Galutinis (Med.) "
        << std::setw(18) << "Galutinis (Vid.)" << "\n";

    cout << "-------------------------------------------------------------------------\n";

    for (auto K : grupe)
        cout << K;
}