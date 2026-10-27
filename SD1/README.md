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
- `v0.2` – užbaigta ir paskelbtas „Release“. Atlikti failų
  generavimo, studentų skirstymo ir trijų konteinerių spartos bandymai.
- `v1.0` – kuriama. Atlikti pirmosios strategijos spartos
  ir atminties bandymai su `vector`, `list` ir `deque`.
  Toliau palyginsiu antrąją strategiją ir išbandysiu
  vektoriaus skirstymo optimizavimą.

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

## v0.2 – konteinerių spartos palyginimas

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
visiems penkiems failų dydžiams. Su 10 milijonų studentų
skirstymas užtruko 2,07686 s, naudojant `deque` – 2,73662 s,
o `vector` – 5,25218 s.

Išvedimo rezultatai neparodė vieno konteinerio pranašumo
visiems failų dydžiams. Pavyzdžiui, milijono studentų
rezultatus greičiausiai išvedė `vector`, o 10 milijonų –
`deque`.

Mažiausio failo išvedimo trukmės stipriai skyrėsi.
Kadangi atlikta tik po vieną bandymą, vien iš šių matavimų
negalima nustatyti skirtumo priežasties ar teigti,
kad vienas konteineris visais atvejais yra greičiausias.

## v1.0 – pirmosios strategijos spartos ir atminties bandymai

Atmintį matavau funkcija `AtmintisMiB()`, kuri naudoja
„Windows“ funkciją `GetProcessMemoryInfo`. Gautą privačios
atminties kiekį baitais perskaičiavau į MiB.

Studentus skirsčiau į du naujus to paties tipo konteinerius:
„vargšiukų“ ir „kietiakų“. Pradinis studentų konteineris
liko nepakeistas, todėl kiekvieno studento duomenys buvo
saugomi du kartus.

Bandymams naudojau tuos pačius penkis duomenų failus,
„Release x64“ konfigūraciją ir tris konteinerių tipus:
`std::vector`, `std::list` ir `std::deque`.
Namų darbų pažymiai visais atvejais liko `std::vector<int>`.

Skirstymo trukmę matavau sekundėmis. Papildomas rikiavimas
pagal vardą ir galutinį balą į šią trukmę neįtrauktas.

Programos privačią atmintį matavau prieš skirstymą ir
iškart po jo. Matavimai apima visą programą, todėl tai
nėra tikslus vien konteinerių dydis ar didžiausias atminties
naudojimas skirstymo metu. Atminties pokytis – skirtumas
tarp reikšmių po skirstymo ir prieš jį.

Kiekvienam failo dydžiui ir konteineriui atlikau po vieną bandymą.
Atmintis pateikta MiB vienetais: 1 MiB = 1 048 576 baitai.

### std::vector rezultatai

|Studentų skaičius | Skirstymas, s | Atmintis prieš, MiB | Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0008398 |           0,835938 |        0,957031 |     0,121094 |
|           10 000 |     0,0052363 |            2,45312 |         4,43359 |      1,98047 |
|          100 000 |     0,0545112 |            19,2266 |         37,8203 |      18,5938 |
|        1 000 000 |      0,499558 |            151,766 |         320,465 |      168,699 |
|       10 000 000 |       5,44967 |            1657,89 |          3573,6 |      1915,71 |

### std::list rezultatai

|Studentų skaičius | Skirstymas, s | Atmintis prieš, MiB | Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0002489 |           0,792969 |        0,957031 |     0,164062 |
|           10 000 |     0,0023179 |            2,32812 |         4,13672 |      1,80859 |
|          100 000 |     0,0199879 |            17,6523 |         34,7891 |      17,1367 |
|        1 000 000 |      0,216933 |            170,902 |         341,273 |      170,371 |
|       10 000 000 |       2,55257 |             1703,4 |            3406 |       1702,6 |

### std::deque rezultatai

|Studentų skaičius | Skirstymas, s | Atmintis prieš, MiB | Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0002364 |           0,785156 |        0,945312 |     0,160156 |
|           10 000 |     0,0024908 |            2,33203 |         3,99219 |      1,66016 |
|          100 000 |      0,023432 |            17,7109 |         33,8594 |      16,1484 |
|        1 000 000 |      0,251424 |             163,59 |         339,797 |      176,207 |
|       10 000 000 |       4,36682 |            1677,88 |         3336,36 |      1658,48 |

### Konteinerių palyginimas su 10 milijonų studentų

| Konteineris   | Skirstymas, s |Atmintis prieš, MiB | Atmintis po, MiB | Pokytis, MiB |
|---------------|--------------:|-------------------:|----------------:|-------------:|
| `std::vector` |       5,44967 |            1657,89 |          3573,6 |      1915,71 |
| `std::list`   |       2,55257 |             1703,4 |            3406 |       1702,6 |
| `std::deque`  |       4,36682 |            1677,88 |         3336,36 |      1658,48 |

### Rezultatų aptarimas

Po skirstymo atminties naudojimas padidėjo su visais trimis
konteineriais, nes pradinis sąrašas išliko, o studentų
kopijos buvo įrašytos į du naujus konteinerius.

Su 10 milijonų studentų greičiausiai skirstė `list` –
2,55257 s. `deque` užtruko 4,36682 s, o `vector` – 5,44967 s.

Šiame didžiausiame bandyme mažiausia privati atmintis po
skirstymo buvo naudojant `deque` – 3336,36 MiB.
Didžiausia buvo naudojant `vector` – 3573,6 MiB.

Kadangi kiekvienu atveju atlikau po vieną bandymą,
šios išvados taikomos pateiktiems matavimams.
Antrosios strategijos ir optimizuoto vektoriaus bandymai
dar neatlikti.


## Projekto failai

- `lib.h` – naudojamos bibliotekos ir `using` deklaracijos.
- `Studentas.h` – studento klasė ir funkcijų deklaracijos.
- `Studentas.cpp` – klasės metodų ir operatorių realizacija.
- `StudDB.cpp` – pagrindinė programos dalis su `main()` funkcija.
- `Failai.h` – failo generavimo funkcijos deklaracija.
- `Failai.cpp` – failo generavimo funkcijos realizacija.
- `kursiokai.txt` – pavyzdinis studentų duomenų failas.
- `README.md` – programos, jos naudojimo ir bandymų aprašymas.
- `Matavimai.h` – atminties matavimo funkcijos deklaracija.
- `Matavimai.cpp` – atminties matavimo funkcijos realizacija,
  naudojanti „Windows“ funkcijas.

Dideli sugeneruoti duomenų failai į repozitoriją nekeliami.
Juos galima sukurti paleidus programą.

## Kaip paleisti ir naudotis

1. Atidaryti projektą „Visual Studio“.
2. Pasirinkti „Release“ ir „x64“ konfigūraciją.
3. Paspausti `Ctrl + F5`.

Atminties matavimas šiuo metu pritaikytas „Windows“ sistemai.
Ekrane taip pat parodoma programos privati atmintis prieš
studentų skirstymą, po jo ir šių reikšmių skirtumas.

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

Studentų saugojimui naudojamas konteineris pasirenkamas
`StudDB.cpp` faile. Norint išbandyti kitą konteinerį, reikia
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