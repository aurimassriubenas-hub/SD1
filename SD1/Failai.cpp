#include "Failai.h"

void GeneruotiFaila(string pavadinimas, int kiekis) {
    std::ofstream failas(pavadinimas);

    std::random_device rd;
    std::mt19937 generatorius(rd());
    std::uniform_int_distribution<int> pazymys(1, 10);

    failas << left
        << setw(20) << "Vardas"
        << setw(20) << "Pavarde";

    for (int j = 1; j <= 10; j++) {
        failas << setw(6) << ("ND" + std::to_string(j));
    }

    failas << setw(10) << "Egzaminas" << "\n";

    for (int i = 1; i <= kiekis; i++) {
        failas << setw(20) << ("Vardas" + std::to_string(i))
            << setw(20) << ("Pavarde" + std::to_string(i));

        for (int j = 1; j <= 10; j++) {
            failas << setw(6) << pazymys(generatorius);
        }

        failas << setw(10) << pazymys(generatorius) << "\n";
    }

    failas.close();
}