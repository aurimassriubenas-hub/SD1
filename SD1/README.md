## Versijos būsena
v0.1 dar kuriama. Įgyvendintas rankinis duomenų įvedimas,
galutinio balo skaičiavimas ir studentų rikiavimas.

# Studentų pažymių skaičiavimo programa

Šią programą kuriu savarankiškam C++ darbui. Ji leidžia įvesti
studentų vardus, pavardes, namų darbų ir egzamino pažymius.
Galutinis balas skaičiuojamas pagal pasirinktą namų darbų
vidurkį arba medianą:

Galutinis balas = 0.4 × namų darbų rezultatas + 0.6 × egzaminas.

## Kas jau atlikta

Sukūriau klasę `studentas`, kurioje saugomi studento duomenys.
Realizavau konstruktorius, kopijavimo priskyrimo operatorių
ir destruktorių pagal trijų metodų taisyklę. Taip pat pridėjau
įvedimo ir išvedimo operatorius.

Namų darbų pažymiai ir studentai saugomi `std::vector`
konteineriuose. Pažymių skaičiaus iš anksto nurodyti nereikia –
vartotojas pats nusprendžia, kada baigti juos įvesti.

Programoje galima pasirinkti, ar galutinį balą skaičiuoti pagal
vidurkį, ar medianą. Baigus įvedimą, studentai surikiuojami pagal
vardą, o rezultatai pateikiami lentelėje dviem skaičiais po kablelio.

Kodą suskaidžiau į atskirus `.h` ir `.cpp` failus.

## Ką dar reikia padaryti

v0.1 versija dar nebaigta. Toliau pridėsiu:

- Atsitiktinį namų darbų ir egzamino pažymių generavimą.
- Duomenų skaitymą iš `kursiokai.txt`.
- Abiejų galutinių balų išvedimą skaitant duomenis iš failo.
- Failo atidarymo klaidų apdorojimą naudojant `try` ir `catch`.

## Projekto failai

- `lib.h` – naudojamos bibliotekos ir `using` deklaracijos.
- `Studentas.h` – klasės ir funkcijų deklaracijos.
- `Studentas.cpp` – klasės metodai ir operatoriai.
- `studDB.cpp` – pagrindinė programos dalis su `main()` funkcija.

## Kaip paleisti

1. Atidaryti projektą „Visual Studio“.
2. Paspausti `Ctrl + F5`.
3. Pasirinkti skaičiavimą pagal medianą (`t/T`)
   arba vidurkį (kitas simbolis).
4. Įvesti studento duomenis ir pažymius.
5. Įvedus namų darbo pažymį, pasirinkti, ar įvesti dar vieną.
   Pasirinkus `n/N`, pereinama prie egzamino pažymio.
6. Baigus vieno studento įvedimą, galima įvesti kitą studentą.
   Pasirinkus `n/N`, pateikiama rezultatų lentelė.