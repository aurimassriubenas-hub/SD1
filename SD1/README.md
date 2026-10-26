# Studentų pažymių skaičiavimo programa

Šią programą kuriu savarankiškam C++ darbui. Ji leidžia įvesti
studentų vardus, pavardes, namų darbų ir egzamino pažymius.
Pažymius galima įvesti ranka arba sugeneruoti atsitiktinai.
Studentų duomenis taip pat galima nuskaityti iš failo.

Programa apskaičiuoja du galutinius balus: vieną pagal namų
darbų vidurkį, kitą – pagal medianą. Abiem atvejais taikoma formulė:

```text
Galutinis balas = 0,4 × namų darbų rezultatas + 0,6 × egzaminas
```

## Versijų būsena

- `v0.1` – užbaigta ir paskelbtas „Release“.
- `v0.2` – įgyvendintas failų generavimas, studentų skirstymas
  ir atlikti `vector`, `list` bei `deque` spartos bandymai.
  Ruošiamas versijos išleidimas.

## v0.1 – pagrindinės programos kūrimas

### Pirmasis etapas

Sukūriau klasę `studentas`, kurioje saugomi vieno studento duomenys.
Realizavau konstruktorius ir trijų metodų taisyklę:
kopijavimo konstruktorių, kopijavimo priskyrimo operatorių
ir destruktorių. Taip pat pridėjau įvedimo ir išvedimo operatorius.

Namų darbų pažymiai ir studentai saugomi `std::vector`
konteineriuose. Namų darbų skaičiaus iš anksto nurodyti nereikia –
vartotojas pats nusprendžia, kada baigti įvedimą.

Pradiniame variante buvo galima pasirinkti, ar galutinį balą
skaičiuoti pagal vidurkį, ar medianą. Studentai surikiuojami
pagal vardą, o galutinis balas pateikiamas dviem skaičiais
po kablelio.

Kodą suskaidžiau į atskirus `.h` ir `.cpp` failus.

### Antrasis etapas

Pakeičiau rezultatų išvedimą: vienoje lentelėje pateikiami
abu galutiniai balai – pagal namų darbų vidurkį ir medianą.

Pridėjau galimybę pasirinkti, ar pažymius įvesti pačiam,
ar sugeneruoti atsitiktinai. Generuojami pažymiai nuo 1 iki 10.
Po kiekvieno sugeneruoto namų darbo pažymio galima pasirinkti,
ar generuoti dar vieną. Baigus namų darbus, egzamino pažymys
sugeneruojamas automatiškai.

### Trečiasis etapas

Pridėjau studentų duomenų skaitymą iš `kursiokai.txt`.
Pirmoji failo eilutė su antrašte praleidžiama, o iš kitų
eilučių nuskaitomi studentų duomenys.

Nuskaityti studentai surikiuojami pagal vardą ir pateikiami
lentelėje su abiem galutiniais balais.

Failo atidarymo klaidoms apdoroti panaudojau `try` ir `catch`.
Jei failo nepavyksta atidaryti, programa parodo klaidos pranešimą.

## v0.2 – studentų failų generavimas ir skirstymas

Sukūriau funkciją `GeneruotiFaila`, kuri sukuria pasirinkto
dydžio studentų duomenų failą. Studentų vardai ir pavardės
sudaromi pridedant eilės numerį, pavyzdžiui,
`Vardas1 Pavarde1`, `Vardas2 Pavarde2`.

Kiekvienam studentui sugeneruojama 10 namų darbų pažymių
ir vienas egzamino pažymys. Atsitiktiniams pažymiams gauti
naudoju `<random>` bibliotekos generatorių `std::mt19937`
ir `std::uniform_int_distribution<int>`.

Sugeneruotą arba pasirinktą failą programa nuskaito ir
studentus padalija į dvi grupes pagal galutinį balą,
apskaičiuotą naudojant namų darbų vidurkį:

- „Vargšiukai“ – galutinis balas < 5.
- „Kietiakai“ – galutinis balas >= 5.

Grupės įrašomos į `vargsiukai.txt` ir `kietiakai.txt`.
Kiekviename faile studentai rikiuojami pagal galutinį balą
didėjimo tvarka. Išvedami abu galutiniai balai,
tačiau skirstymui naudojamas tik balas pagal vidurkį.

## v0.2 – spartos analizė

Programą testavau „Visual Studio“, naudodamas „Release x64“
konfigūraciją ir `std::vector` konteinerį.

Sugeneravau penkis failus: 1 000, 10 000, 100 000,
1 000 000 ir 10 000 000 studentų.

Naudodamas `std::chrono::steady_clock`, atskirai matavau:

- Pradinio duomenų failo kūrimą.
- Duomenų nuskaitymą ir studentų įrašymą į vektorių.
- Studentų skirstymą į dvi grupes.
- Abiejų rezultatų failų sukūrimą, duomenų išvedimą ir uždarymą.

Studentų sąrašo išvedimą į ekraną bandymų metu užkomentavau,
kad programa nespausdintų milijonų eilučių. Ekrane palikau
veiksmų trukmes ir studentų skaičius.

### Bandymų rezultatai

Trukmės pateiktos sekundėmis. Kiekvienam failo dydžiui
atliktas vienas bandymas.

| Studentų skaičius | Failo kūrimas, s | Nuskaitymas, s | Skirstymas, s | Išvedimas į failus, s |
|------------------:|-----------------:|---------------:|--------------:|----------------------:|
| 1 000             | 0,0110493        | 0,0057812      | 0,0004072     | 0,0035062             |
| 10 000            | 0,0394027        | 0,0567575      | 0,0053199     | 0,0264481             |
| 100 000           | 0,310003         | 0,565864       | 0,0574962     | 0,201865              |
| 1 000 000         | 3,00092          | 5,50794        | 0,472118      | 1,98755               |
| 10 000 000        | 29,8997          | 56,6858        | 5,34225       | 21,145                |

### Bandymų kompiuteris

- Procesorius: Intel Core i7-8565U @ 1,80 GHz.
- Operatyvioji atmintis (RAM): 16 GB.
- Diskas: Toshiba KBG30ZMS512G, 512 GB NVMe SSD.
- Operacinė sistema: Windows, 64 bitų.
- Programos konfigūracija: Release x64.

### Rezultatų aptarimas

Didėjant studentų skaičiui, ilgėjo visų matuojamų veiksmų
trukmė. Didesniuose bandymuose, įrašų skaičių padidinus
10 kartų, trukmės taip pat didėjo maždaug 10 kartų.

Iš keturių matuojamų veiksmų didesniems failams daugiausia
laiko užtruko duomenų nuskaitymas, o mažiausiai –
studentų skirstymas į dvi grupes.

Bandant 10 milijonų studentų failą, nuskaitymas užtruko
56,6858 s, o skirstymas – 5,34225 s.
Į „vargšiukų“ grupę pateko 4 134 190 studentų,
į „kietiakų“ – 5 865 810. Jų suma yra 10 000 000.

Papildomas rikiavimas pagal vardą ir galutinį balą
į pateiktas trukmes neįtrauktas, todėl šių laikų suma
neparodo visos programos veikimo trukmės.

Kadangi kiekvienam dydžiui atliktas vienas bandymas,
pateikti rezultatai nėra kelių bandymų vidurkiai.

## Konteinerių spartos palyginimas

Palyginau `std::vector`, `std::list` ir `std::deque`.
Visiems konteineriams naudojau tuos pačius penkis `bb` failus.
Namų darbų pažymiai visais atvejais liko `std::vector<int>`.

Studentai kopijuojami į du naujus to paties tipo konteinerius.
Matuojamas nuskaitymas, skirstymas ir rezultatų išvedimas į
du failus, įskaitant jų sukūrimą ir uždarymą.
Papildomas rikiavimas į šias trukmes neįtrauktas.

Kiekvienam dydžiui ir konteineriui atliktas vienas bandymas.
Visos trukmės pateiktos sekundėmis.

### Duomenų nuskaitymas

|Studentų skaičius |    vector |      list |     deque |
|-----------------:|----------:|----------:|----------:|
|            1 000 | 0,0191384 | 0,0271421 | 0,0171263 |
|           10 000 | 0,0565368 | 0,0565414 | 0,0541053 |
|          100 000 |  0,589661 |  0,526619 |  0,532605 |
|        1 000 000 |   5,57201 |   5,38491 |   5,29365 |
|       10 000 000 |   56,3356 |   54,0342 |   57,3097 |

### Studentų skirstymas į dvi grupes

|Studentų skaičius |    vector |      list |     deque |
|-----------------:|----------:|----------:|----------:|
|            1 000 | 0,0008093 | 0,0001838 | 0,0002487 |
|           10 000 | 0,0046399 | 0,0022611 | 0,0021524 |
|          100 000 | 0,0452827 | 0,0211822 | 0,0246206 |
|        1 000 000 |  0,449008 |  0,208876 |  0,270418 |
|       10 000 000 |   5,25218 |   2,07686 |   2,73662 |

### Rezultatų išvedimas į du failus

| Studentų skaičius |    vector |      list |     deque |
|------------------:|----------:|----------:|----------:|
|            1 000  | 0,0620094 |  0,004047 | 0,0589657 |
|           10 000  | 0,0188019 | 0,0200369 | 0,0190976 |
|          100 000  |  0,179129 |  0,224802 |  0,191924 |
|        1 000 000  |   1,80388 |   2,17446 |   2,16213 |
|       10 000 000  |    39,943 |    37,347 |   35,9548 |

### Palyginimo aptarimas

Didesnių failų nuskaitymo trukmės buvo panašios.
10 milijonų studentų faile trumpiausiai nuskaitymas užtruko
naudojant `list` – 54,0342 s.

Skirstant studentus, `list` šiame bandyme buvo greičiausias
keturiems iš penkių dydžių. Su 10 milijonų studentų skirstymas
užtruko 2,07686 s, naudojant `deque` – 2,73662 s,
o `vector` – 5,25218 s.

Išvedimo rezultatai neparodė vieno konteinerio pranašumo
visiems failų dydžiams. Pavyzdžiui, milijono studentų
rezultatus greičiausiai išvedė `vector`, o 10 milijonų –
`deque`.

Mažiausio failo išvedimo trukmės stipriai skyrėsi.
Kadangi atlikta tik po vieną bandymą, vien iš šių matavimų
negalima nustatyti skirtumo priežasties ar teigti,
kad vienas konteineris visais atvejais yra greičiausias.

## Projekto failai

- `lib.h` – naudojamos bibliotekos ir `using` deklaracijos.
- `Studentas.h` – studento klasė ir funkcijų deklaracijos.
- `Studentas.cpp` – klasės metodų ir operatorių realizacija.
- `StudDB.cpp` – pagrindinė programos dalis su `main()` funkcija.
- `Failai.h` – failo generavimo funkcijos deklaracija.
- `Failai.cpp` – failo generavimo funkcijos realizacija.
- `kursiokai.txt` – pavyzdinis studentų duomenų failas.
- `README.md` – programos, jos naudojimo ir bandymų aprašymas.

Dideli sugeneruoti duomenų failai į repozitoriją nekeliami.
Juos galima sukurti paleidus programą.

## Kaip paleisti ir naudotis

1. Atidaryti projektą „Visual Studio“.
2. Pasirinkti „Release“ ir „x64“ konfigūraciją.
3. Paspausti `Ctrl + F5`.

### Naujo studentų failo generavimas

Į klausimą „Ar nori generuoti failą?“ atsakyti `t`.
Įvesti failo pavadinimą be `.txt` ir studentų skaičių.

Pavyzdžiui, įvedus `studentai` ir `1000`,
sukuriamas `studentai1000.txt`.

Programa automatiškai nuskaito sukurtą failą, suskirsto
studentus ir įrašo rezultatus į `vargsiukai.txt`
bei `kietiakai.txt`. Ekrane parodomos veiksmų trukmės
ir abiejų grupių studentų skaičiai.

### Esamo failo nuskaitymas

Į klausimą apie generavimą atsakyti `n`, o į klausimą
„Ar duomenis nuskaityti iš failo?“ – `t`.
Tada įvesti failo pavadinimą su `.txt`.

Dabartiniame skaitymo variante duomenų eilutės tvarka:
vardas, pavardė, namų darbų pažymiai, egzaminas.
Pirmoji eilutė skirta antraštei.

### Konteinerio pakeitimas bandymams

Dabartiniame kode naudojamas `std::vector`.
Norint išbandyti kitą konteinerį, `StudDB.cpp` faile reikia
pakeisti visų trijų studentų konteinerių – `grupe`,
`vargsiukai` ir `kietiakai` – tipą.

Naudojant `vector` arba `deque`, rikiuojama su `std::sort`.
Naudojant `list`, kviečiamas konteinerio metodas `.sort()`.

Namų darbų pažymių konteineris `std::vector<int>` nekeičiamas.
Pakeitus kodą, programą reikia iš naujo sukompiliuoti.

Palyginimui visais atvejais naudojami tie patys duomenų failai:
pasirenkama negeneruoti naujo failo ir nuskaityti jau esamą.

### Duomenų įvedimas ranka

Į abu pradinius klausimus atsakyti `n`.
Toliau įvesti studento vardą, pavardę ir pasirinkti,
ar pažymius įvesti ranka, ar generuoti atsitiktinai.

### Kur rasti failus

Failai kuriami programos darbiniame aplanke. Paleidžiant
iš „Visual Studio“ su numatytaisiais nustatymais, tai
paprastai yra projekto aplankas.

Jį galima atidaryti „Solution Explorer“ lange paspaudus
dešiniuoju pelės mygtuku ant projekto ir pasirinkus
„Open Folder in File Explorer“.

Kiekvieną kartą paleidus skirstymą, ankstesni
`vargsiukai.txt` ir `kietiakai.txt` perrašomi.