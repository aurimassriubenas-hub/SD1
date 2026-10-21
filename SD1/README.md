# Studentų pažymių skaičiavimo programa

Šią programą kuriu savarankiškam C++ darbui. Ji leidžia įvesti
studentų vardus, pavardes, namų darbų ir egzamino pažymius.
Pažymius galima įvesti ranka arba sugeneruoti atsitiktinai.

Programa apskaičiuoja du galutinius balus: vieną pagal namų
darbų vidurkį, kitą – pagal medianą. Abiem atvejais taikoma formulė:

Galutinis balas = 0.4 × namų darbų rezultatas + 0.6 × egzaminas.

## Versijos būsena

v0.1 versija užbaigta.

## Atlikti darbai

### Pirmasis etapas

Sukūriau klasę `studentas`, kurioje saugomi studento duomenys.
Realizavau konstruktorius, kopijavimo konstruktorių, kopijavimo
priskyrimo operatorių ir destruktorių pagal trijų metodų taisyklę.
Taip pat pridėjau įvedimo ir išvedimo operatorius.

Namų darbų pažymiai ir studentai saugomi `std::vector`
konteineriuose. Pažymių skaičiaus iš anksto nurodyti nereikia –
vartotojas pats nusprendžia, kada baigti juos įvesti.

Pradiniame variante buvo galima pasirinkti, ar galutinį balą
skaičiuoti pagal vidurkį, ar medianą. Studentai surikiuojami
pagal vardą, o rezultatai pateikiami lentelėje dviem skaičiais
po kablelio.

Kodą suskaidžiau į atskirus `.h` ir `.cpp` failus.

### Antrasis etapas

Pakeičiau rezultatų išvedimą: dabar vienoje lentelėje rodomi
abu galutiniai balai – pagal namų darbų vidurkį ir medianą.

Pridėjau galimybę pasirinkti, ar pažymius įvesti pačiam,
ar sugeneruoti atsitiktinai. Programa generuoja pažymius
nuo 1 iki 10. Po kiekvieno sugeneruoto namų darbo pažymio
galima pasirinkti, ar generuoti dar vieną. Baigus namų darbus,
egzamino pažymys sugeneruojamas automatiškai.
Pridėjau duomenų skaitymą iš 'kursiokai.txt'. 
Nuskaitytus studentus surikiuoju ir pateikiu abu galutinius balus.
Apdorotju failo atidarymo klaidas naudojant `try` ir `catch`.


## Projekto failai

- `lib.h` – naudojamos bibliotekos ir `using` deklaracijos.
- `Studentas.h` – klasės ir funkcijų deklaracijos.
- `Studentas.cpp` – klasės metodai ir operatoriai.
- `studDB.cpp` – pagrindinė programos dalis su `main()` funkcija.
- 'kursiokai.txt' - duomenų skaitymo failas.
- 'README.md' - darbo aprašymo failas.

## Kaip paleisti ir naudotis

1. Atidaryti projektą „Visual Studio“.
2. Paspausti `Ctrl + F5`.
3. Pasirinkti ar nuskaityti duomenis iš failo 'kursiokai.txt'
4. Suvedant duomenis ranka, įvesti studento vardą ir pavardę.
5. Pasirinkti, ar pažymius generuoti atsitiktinai:
   `t/T` – generuoti, `n/N` – įvesti ranka.
6. Įvesti arba generuoti namų darbų pažymius.
   Į klausimą apie kitą pažymį atsakius `n/N`,
   namų darbų įvedimas arba generavimas baigiamas.
7. Įvesti egzamino pažymį. Pasirinkus generavimą,
   jis sugeneruojamas automatiškai.
8. Pasirinkti, ar įvesti dar vieną studentą.
   Atsakius `n/N`, pateikiama surikiuota lentelė
   su abiem galutiniais balais.