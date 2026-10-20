#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::left; 
using std::right;
using std::setw;

class studentas {
    string var, pav;
    vector<int> paz;
    int exam, gal;

public:
    studentas() {
        cout << "Iveskite studento varda: "; cin >> var;
        cout << "Iveskite studento pavarde: "; cin >> pav;

        while (true) {
            int n; char uzkl;
            cout << "Iveskite studento semestro pazymi: "; cin >> n; paz.push_back(n);
            cout << "Ar ivesite dar viena pazymi? t/n"; cin >> uzkl;
            if (uzkl == 'n' || uzkl == 'N') break;
        }
        cout << "Iveskite studento egzamino pazymi: ";
        cin >> exam;

    };

    studentas(string v, string p, vector<int> pazim, int e) {
        var = v;
        pav = p;
        paz = pazim;
        exam = e;
    }

    studentas(const studentas& B) {
        var = B.var;
        pav = B.pav;
        paz = B.paz;
        exam = B.exam;
        gal = B.gal;
    }

    ~studentas() {
        clear();
    }

    void outputas() {
        cout << left << setw(10) << var
            << left << setw(20) << pav
            << right << setw(5) << exam << "\n";
    }

    void clear() {
        var.clear();
        pav.clear();
        paz.clear();
        exam = 0;
    }
};

