#include "lib.h"
#include "Studentas.h"

// Numatytasis konstruktorius
studentas::studentas() {
    std::cout << "Iveskite studento varda: ";
    std::cin >> var;

    std::cout << "Iveskite studento pavarde: ";
    std::cin >> pav;

    //Atsitiktinių vertinimų generavimas pagal užklausą
    char generuoti;
    std::cout << "Ar pazymius generuoti atsitiktinai? t/n: ";
    std::cin >> generuoti;

    if (generuoti == 't' || generuoti == 'T') {
        std::random_device rd;
        std::mt19937 generatorius(rd());
        std::uniform_int_distribution<int> pazymys(1, 10); //gražina nuo 1 iki 10 

        char uzkl;

        do {
            int n = pazymys(generatorius);
            paz.push_back(n);

            std::cout << "Sugeneruotas ND pazymys: " << n << "\n";
            std::cout << "Ar generuoti dar viena pazymi? t/n: ";
            std::cin >> uzkl;

        } while (uzkl != 'n' && uzkl != 'N');

        exam = pazymys(generatorius);
        std::cout << "Sugeneruotas egzamino pazymys: " << exam << "\n";
    }
    else {

        while (true) {
            int n;
            char uzkl;

            while (true) {
                std::cout << "Iveskite studento semestro pazymi (1-10): ";
                std::cin >> n;

                if (n >= 1 && n <= 10) {
                    break;
                }

                std::cout << "Klaida! Pazymys turi buti nuo 1 iki 10.\n";
            }

            paz.push_back(n);

            std::cout << "Ar ivesite dar viena pazymi? t/n: ";
            std::cin >> uzkl;

            if (uzkl == 'n' || uzkl == 'N') {
                break;
            }
        }

        while (true) {
            std::cout << "Iveskite studento egzamino pazymi (1-10): ";
            std::cin >> exam;

            if (exam >= 1 && exam <= 10) {
                break;
            }

            std::cout << "Klaida! Pazymys turi buti nuo 1 iki 10.\n";
        }
    }
}
//Konstruktorius su parametrais
studentas::studentas(std::string v, std::string p, std::vector<int> pazim, int e) {
    var = v;
    pav = p;
    paz = pazim;
    exam = e;
}
//Kopijavimo konstruktorius
studentas::studentas(const studentas& B) {
    var = B.var;
    pav = B.pav;
    paz = B.paz;
    exam = B.exam;
    gal = B.gal;
}

//Kopijavimo priskyrimo operatorius
studentas& studentas::operator=(const studentas& A) {
    if (this != &A) {
        var = A.var;
        pav = A.pav;
        paz = A.paz;
        exam = A.exam;
        gal = A.gal;
    }
    return *this;
}

//Destruktorius
studentas::~studentas() {
    clear();
}

// Galutinis balas ir mediana
double studentas::mediana() const {
    double rezultatas = 0;
    int n = paz.size(); //nuskaičiuojame kiek saugoma pažymių vektoriuje

    if (n == 0) {
        return 0.6 * exam;
    }
    std::vector<int> kopija = paz;
    std::sort(kopija.begin(), kopija.end());//rikiavimas didėjimo tvarka

    if (n % 2 == 0) { //lyginis ar nelyginis
        rezultatas = (kopija[n / 2 - 1] + kopija[n / 2]) / 2.0;
    }
    else {
        rezultatas = kopija[n / 2];
    }
    return 0.4 * rezultatas + 0.6 * exam;
}

    double studentas::vidurkis() const {
        double rezultatas = 0;
        
        if (paz.empty()) {
            return 0.6 * exam;
        }

        for (int i = 0; i < paz.size(); i++) {
            rezultatas += paz[i];
        }

        rezultatas = rezultatas / paz.size(); //vidurkis
    

    return 0.4 * rezultatas + 0.6 * exam;
}

void studentas::clear() {
    var.clear();
    pav.clear();
    paz.clear();
    exam = 0;
    gal = 0;
}

std::string studentas::GetVar() const {
    return var;
}
const std::string& studentas::GetPav() const {
    return pav;
}

// Duomenu isvedimo operatorius
std::ostream& operator<<(std::ostream& out, const studentas& A) {
    out << std::left << std::setw(15) << A.var
        << std::setw(20) << A.pav
        << std::right << std::fixed << std::setprecision(2)
        << std::setw(18) << A.mediana()
        << std::setw(18) << A.vidurkis() << "\n";

    return out;
}

// Duomenu ivedimo operatorius
// Tvarka: vardas pavarde ...  egzaminas
std::istream& operator>>(std::istream& in, studentas& A) {
    A.clear();
    in >> A.var >> A.pav;
    int n;
    char uzkl;

    while (in >> n && n > 0 && n < 11) {
        A.paz.push_back(n);

        std::cout << "Ar pridesite dar ND? t/n: ";
        in >> uzkl;

        if (uzkl == 'n' || uzkl == 'N') {
            break;
        }
    }

    in >> A.exam;
    return in;
}

bool vardid(const studentas& A, const studentas& B) {
    return A.GetVar() < B.GetVar();
}

bool varmaz(const studentas& A, const studentas& B) {
    return A.GetVar() > B.GetVar();
}