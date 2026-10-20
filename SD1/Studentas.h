#pragma once
#include "lib.h"

class studentas {
    std::string var, pav;
    std::vector<int> paz;
    int exam = 0;
    double gal = 0.0;

public:
    studentas(); //konstruktorius defolt
    explicit studentas(bool ivesti); //konstruktorius su loginiu parametru (explicit neleidžia kompiliatoriui automatiškai paversti bool reikšmės į studentas objektą)
    studentas(std::string v, std::string p, std::vector<int> pazim, int e); //konstruktorius su parametrais
    studentas(const studentas& B); //kopijavimo konstruktorius
    studentas& operator=(const studentas& A); //Kopijavimo priskyrimo operatorius
    ~studentas(); //destruktorius

    double Galutinis(bool mediana) const;
    void Skaiciuoti(bool mediana);
    void outputas();
    void clear();
    std::string GetVar() const;
    const std::string& GetPav() const;

    friend std::ostream& operator<<(std::ostream& out,
        const studentas& A);
    friend std::istream& operator>>(std::istream& in,
        studentas& A);
};

bool vardid(const studentas& A, const studentas& B);
bool varmaz(const studentas& A, const studentas& B);