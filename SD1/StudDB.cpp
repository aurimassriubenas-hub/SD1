#include "lib.h"
#include "Studentas.h"
#include "Failai.h"
#include "Matavimai.h"

int main() {
//  vector<studentas> grupe;
//   std::list<studentas> grupe;
  std::deque<studentas> grupe;
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

        //failo generavimo laiko matavimas

        try {
            auto pradzia = std::chrono::steady_clock::now();

            GeneruotiFaila(pavadinimas, n);

            auto pabaiga = std::chrono::steady_clock::now();
            std::chrono::duration<double> trukme = pabaiga - pradzia;

            cout << "Failas sukurtas.\n";
            cout << "Failo kurimas: " << trukme.count() << " s\n";
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


    // Skaitome faila ir matuojame nuskaitymo trukme
    if (skaitytiFaila) {
        try {
            auto pradzia = std::chrono::steady_clock::now();

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

            //failo nuskaitymo laiko matavimo pabaiga
            failas.close();

            auto pabaiga = std::chrono::steady_clock::now();
            std::chrono::duration<double> trukme = pabaiga - pradzia;

            cout << "Duomenu nuskaitymas: "
                << trukme.count() << " s\n";
            cout << "Nuskaityta studentu: " << grupe.size() << "\n";
        }
        catch (const std::exception& e) {
            cout << "Klaida: " << e.what() << "\n";
            return 1;
        }
    }

      
//   grupe.sort(vardid);
    std::sort(grupe.begin(), grupe.end(), vardid);

    // Skirstome pagal galutini bala, apskaiciuota naudojant ND vidurki:
    // vargsiukai < 5, kietiakai >= 5. Matuojame skirstymo trukme.

//  vector<studentas> vargsiukai;
//  vector<studentas> kietiakai;

//   std::list<studentas> vargsiukai;
//   std::list<studentas> kietiakai;

  std::deque<studentas> vargsiukai;
  std::deque<studentas> kietiakai;

    // Atminties kiekis prieš studentų skirstymą.
    double atmintisPries = AtmintisMiB();

    auto skirstymoPradzia = std::chrono::steady_clock::now();

    for (const studentas& A : grupe) {
        if (A.vidurkis() < 5.0) {
            vargsiukai.push_back(A);
        }
        else {
            kietiakai.push_back(A);
        }
    }
    // Užfiksuojame skirstymo pabaigos laiką.
    auto skirstymoPabaiga = std::chrono::steady_clock::now();

    // Abi grupės užpildytos, o bendras grupe konteineris išlikęs.
    double atmintisPo = AtmintisMiB();

    std::chrono::duration<double> skirstymoTrukme =
        skirstymoPabaiga - skirstymoPradzia;

    cout << "Skirstymas i grupes: "
        << skirstymoTrukme.count() << " s\n";

    // Kiekviena grupe rikiuojama galutinio balo didėjimo tvarka

    std::sort(vargsiukai.begin(), vargsiukai.end(),
        [](const studentas& A, const studentas& B) {
            return A.vidurkis() < B.vidurkis();
        });

//  Vargšiukus rikiuojame pagal galutinį balą didėjimo tvarka.
/*    vargsiukai.sort(
        [](const studentas& A, const studentas& B) {
            return A.vidurkis() < B.vidurkis();
        });
*/
//  kietiakai.sort(
   std::sort(kietiakai.begin(), kietiakai.end(),
        [](const studentas& A, const studentas& B) {
            return A.vidurkis() < B.vidurkis();
        });

//  Kietiakus rikiuojame pagal galutinį balą didėjimo tvarka.
/*    kietiakai.sort(
        [](const studentas& A, const studentas& B) {
            return A.vidurkis() < B.vidurkis();
        });
*/
    //isvedimas į failus, išvedimo laiko matavimas
    auto isvedimoPradzia = std::chrono::steady_clock::now();

    std::ofstream silpni("vargsiukai.txt");
    std::ofstream stiprus("kietiakai.txt");

    if (!silpni.is_open() || !stiprus.is_open()) {
        cout << "Klaida: nepavyko sukurti rezultatu failu.\n";
        return 1;
    }

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
    } // Ciklas baigiasi cia

    // Uzdarome failus, kai visi studentai jau irasyti
    silpni.close();
    stiprus.close();

    if (!silpni || !stiprus) {
        cout << "Klaida: nepavyko irasyti rezultatu.\n";
        return 1;
    }

    // Isvedimo i failus laiko matavimo pabaiga
    auto isvedimoPabaiga = std::chrono::steady_clock::now();
    std::chrono::duration<double> isvedimoTrukme =
        isvedimoPabaiga - isvedimoPradzia;


    cout << "Isvedimas i du failus: "
        << isvedimoTrukme.count() << " s\n";

    cout << "Vargsiuku: " << vargsiukai.size() << "\n";
    cout << "Kietiaku: " << kietiakai.size() << "\n";
    
    // Parodome programos privačios atminties kiekį prieš skirstymą.
    cout << "Privati atmintis pries skirstyma: "
        << atmintisPries << " MiB\n";

    // Parodome programos privačios atminties kiekį po skirstymo.
    cout << "Privati atmintis po skirstymo: "
        << atmintisPo << " MiB\n";

    // Apskaičiuojame, kiek pasikeitė atminties naudojimas.
    cout << "Atminties pokytis: "
        << atmintisPo - atmintisPries << " MiB\n";

    /*
    
    // Spartos bandymu metu studentu saraso i ekrana neisvedame,
    // nes didelio kiekio eiluciu spausdinimas ilgina programos veikima.
    // Studentu rezultatai irasomi i vargsiukai.txt ir kietiakai.txt.

    //Išvedimas

    cout << std::left << std::setw(15) << "Vardas"
        << std::setw(23) << "Pavarde"
        << std::left << std::setw(18) << "Galutinis (Med.) "
        << std::setw(18) << "Galutinis (Vid.)" << "\n";

    cout << "-------------------------------------------------------------------------\n";

    for (auto K : grupe)
        cout << K;
    */
}