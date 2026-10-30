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
- `v1.0` – užbaigta ir paskelbtas „Release“. Palygintos dvi
  studentų skirstymo strategijos su `vector`, `list` ir `deque`,
  išmatuota skirstymo trukmė ir atminties naudojimas.
  Su vektoriumi išbandyti `std::partition` ir
  `std::stable_partition` algoritmai.


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
apskaičiuotą naudojant namų darbų vidurkį ir egzamino pažymį:

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

Skirstant studentus, `list` buvo greičiausias keturiems iš
penkių failų dydžių. Su 10 000 studentų šiek tiek greitesnis
buvo `deque`. Su 10 milijonų studentų `list` skirstymas
užtruko 2,07686 s, `deque` – 2,73662 s,
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

## v1.0 – antrosios strategijos spartos ir atminties bandymai

Antrojoje strategijoje kūriau tik vieną naują konteinerį –
„vargšiukų“. Į jį kopijavau studentus, kurių galutinis balas,
apskaičiuotas iš namų darbų vidurkio ir egzamino pažymio,
buvo mažesnis nei 5. Šiuos studentus pašalinau iš bendro
konteinerio `grupe`, todėl jame liko tik „kietiakai“.

Naudojant `list`, vargšiukai šalinami po vieną ciklo metu.
Naudojant `vector` ir `deque`, kietiakai surašomi į konteinerio
pradžią, o nereikalingas galas pašalinamas vienu `erase` veiksmu.
Taip išvengiama dažno likusių elementų stumdymo.

Bandymams naudojau tuos pačius penkis `bb` failus ir
„Release x64“ konfigūraciją. Namų darbų pažymiai
visais atvejais liko `std::vector<int>`.

Skirstymo trukmė apima studentų kopijavimą ir pašalinimą.
Papildomas rikiavimas pagal vardą ir galutinį balą
į šią trukmę neįtrauktas.

Privačią programos atmintį matavau prieš skirstymą ir iškart
po jo. Tai visos programos matavimai, o ne tikslus konteinerių
dydis ar didžiausias atminties naudojimas skirstymo metu.
Kiekvienam dydžiui ir konteineriui atlikau po vieną bandymą.

### std::vector rezultatai

|Studentų skaičius | Skirstymas, s |Atmintis prieš, MiB |Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0004452 |            0,84375 |        0,894531 |    0,0507812 |
|           10 000 |     0,0024759 |            2,46875 |         3,65625 |       1,1875 |
|          100 000 |     0,0311609 |            19,2109 |         26,3359 |        7,125 |
|        1 000 000 |      0,244024 |            151,766 |         202,348 |       50,582 |
|       10 000 000 |       2,65827 |            1657,91 |         2227,65 |      569,742 |

### std::list rezultatai

|Studentų skaičius | Skirstymas, s |Atmintis prieš, MiB |Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0001685 |           0,792969 |        0,800781 |    0,0078125 |
|           10 000 |     0,0010704 |            2,33594 |         2,45312 |     0,117188 |
|          100 000 |     0,0120062 |            17,6523 |         17,7383 |    0,0859375 |
|        1 000 000 |      0,118393 |            170,906 |         170,949 |    0,0429688 |
|       10 000 000 |       1,20311 |            1703,39 |         1703,44 |     0,046875 |

### std::deque rezultatai

|Studentų skaičius | Skirstymas, s |Atmintis prieš, MiB |Atmintis po, MiB | Pokytis, MiB |
|-----------------:|--------------:|-------------------:|----------------:|-------------:|
|            1 000 |     0,0002107 |           0,785156 |        0,847656 |       0,0625 |
|           10 000 |     0,0013913 |            2,33594 |         2,96484 |     0,628906 |
|          100 000 |     0,0182976 |             17,707 |         23,6133 |      5,90625 |
|        1 000 000 |      0,164553 |            163,598 |         226,762 |      63,1641 |
|       10 000 000 |       1,67449 |            1677,87 |         2296,77 |      618,906 |

Atminties pokytis apskaičiuotas programoje prieš suapvalinant
išvedamas reikšmes, todėl lentelėje atėmus suapvalintus skaičius
gali atsirasti nedidelis skirtumas.

### Abiejų strategijų skirstymo trukmių palyginimas

Visos trukmės pateiktos sekundėmis.

|Studentų skaičius |vector, 1 strategija |vector, 2 strategija |list, 1 strategija |list, 2 strategija |deque, 1 strategija |deque, 2 strategija |
|-----------------:|--------------------:|--------------------:|------------------:|------------------:|-------------------:|-------------------:|
|            1 000 |           0,0008398 |           0,0004452 |         0,0002489 |         0,0001685 |          0,0002364 |          0,0002107 |
|           10 000 |           0,0052363 |           0,0024759 |         0,0023179 |         0,0010704 |          0,0024908 |          0,0013913 |
|          100 000 |           0,0545112 |           0,0311609 |         0,0199879 |         0,0120062 |           0,023432 |          0,0182976 |
|        1 000 000 |            0,499558 |            0,244024 |          0,216933 |          0,118393 |           0,251424 |           0,164553 |
|       10 000 000 |             5,44967 |             2,65827 |           2,55257 |           1,20311 |            4,36682 |            1,67449 |

### Atminties po skirstymo palyginimas

Pateikta visos programos privati atmintis MiB vienetais.

|Studentų skaičius |vector, 1 strategija |vector, 2 strategija |list, 1 strategija |list, 2 strategija |deque, 1 strategija |deque, 2 strategija |
|-----------------:|--------------------:|--------------------:|------------------:|------------------:|-------------------:|-------------------:|
|            1 000 |            0,957031 |            0,894531 |          0,957031 |          0,800781 |           0,945312 |           0,847656 |
|           10 000 |             4,43359 |             3,65625 |           4,13672 |           2,45312 |            3,99219 |            2,96484 |
|          100 000 |             37,8203 |             26,3359 |           34,7891 |           17,7383 |            33,8594 |            23,6133 |
|        1 000 000 |             320,465 |             202,348 |           341,273 |           170,949 |            339,797 |            226,762 |
|       10 000 000 |              3573,6 |             2227,65 |              3406 |           1703,44 |            3336,36 |            2296,77 |

### Rezultatų aptarimas

Mano bandymuose antroji strategija su visais trimis konteineriais
skirstė studentus greičiau ir po skirstymo naudojo mažiau
privačios programos atminties nei pirmoji.

Su 10 milijonų studentų `vector` skirstymo trukmė sumažėjo
nuo 5,44967 iki 2,65827 s, `list` – nuo 2,55257 iki 1,20311 s,
o `deque` – nuo 4,36682 iki 1,67449 s.

Didžiausiame bandyme atmintis po skirstymo, palyginti su pirmąja
strategija, buvo apie 38 % mažesnė naudojant `vector`,
apie 50 % – `list` ir apie 31 % – `deque`.

Antrojoje strategijoje `list` buvo greičiausias visiems penkiems
failų dydžiams. Jo privačios atminties kiekis prieš skirstymą
ir po jo beveik nesiskyrė. Šalinant senus elementus atlaisvinta
atmintis gali būti panaudojama naujiems elementams.

Naudojant `vector`, `erase` sumažina elementų skaičių,
tačiau nesumažina rezervuotos vektoriaus talpos. Todėl mažesnis
studentų skaičius konteineryje savaime nereiškia tokio pat
programos atminties sumažėjimo.

Rezultatams įtakos turi ir konteineris, ir pasirinktas skirstymo
būdas. Kadangi atlikau po vieną bandymą, šios išvados taikomos
pateiktiems matavimams.

## v1.0 – vektoriaus skirstymas su std::partition

Išbandžiau `std::partition` algoritmą su `std::vector`.
Jis studentus, kurių galutinis balas yra ne mažesnis nei 5,
sudeda į vektoriaus pradžią, o likusius – į galą.
Galutinis balas apskaičiuojamas iš namų darbų vidurkio
ir egzamino pažymio.

Vargšiukus nukopijavau į atskirą vektorių ir pašalinau
iš bendros grupės. Joje liko tik kietiakai.

Rezultatus palyginau su antrosios strategijos ciklu,
kuriame kietiakai surašomi į vektoriaus pradžią,
o nereikalingas galas pašalinamas vienu `erase`.

Abiem variantams naudojau tuos pačius penkis `bb` failus
ir „Release x64“ konfigūraciją. Matuojama visa skirstymo
procedūra, įskaitant kopijavimą ir pašalinimą.
Papildomas rikiavimas į šias trukmes neįtrauktas.
Kiekvienam dydžiui ir variantui atlikau po vieną bandymą.

### Skirstymo trukmių palyginimas

|Studentų skaičius |Paprastas ciklas, s |std::partition variantas, s |
|-----------------:|-------------------:|---------------------------:|
|            1 000 |          0,0004452 |                  0,0002091 |
|           10 000 |          0,0024759 |                  0,0027386 |
|          100 000 |          0,0311609 |                  0,0294762 |
|        1 000 000 |           0,244024 |                   0,249987 |
|       10 000 000 |            2,65827 |                     2,7883 |

### Rezultatų aptarimas

Abu variantai studentus suskirstė į tokio pat dydžio grupes.
Tačiau `std::partition` naudojimas nepaspartino skirstymo
visais atvejais.

Su 10 milijonų studentų paprastas ciklas užtruko 2,65827 s,
o variantas su `std::partition` – 2,7883 s, arba apie 5 % ilgiau.
Su 1 000 ir 100 000 studentų greitesnis buvo
`std::partition` variantas.

Šie bandymai neparodė aiškaus `std::partition` pranašumo
prieš jau turėtą ciklą. Kadangi kiekvienam dydžiui atlikau
po vieną bandymą, nedideli trukmių skirtumai dar neįrodo,
kad vienas variantas nuolat veikia greičiau.

## v1.0 – vektoriaus skirstymas su std::stable_partition

Papildomai išbandžiau `std::stable_partition`.
Jis, kaip ir `std::partition`, kietiakus sudeda į vektoriaus
pradžią, o vargšiukus – į galą. Skirtumas tas, kad kiekvienoje
grupėje išlaikoma ankstesnė studentų tvarka.

Po padalijimo vargšiukus nukopijavau į atskirą vektorių
ir pašalinau iš `grupe`. Skirstymui naudojamas galutinis
balas iš namų darbų vidurkio ir egzamino pažymio.

Visus tris variantus bandžiau su tais pačiais penkiais `bb`
failais, naudodamas „Release x64“ konfigūraciją.
Matuojama visa skirstymo procedūra: studentų padalijimas,
vargšiukų kopijavimas ir pašalinimas iš bendro konteinerio.
Papildomas rikiavimas į šias trukmes neįtrauktas.

### Trijų skirstymo variantų palyginimas

Trukmės pateiktos sekundėmis. Kiekvienam dydžiui ir variantui
atlikau po vieną bandymą.

|Studentų skaičius |Paprastas ciklas, s | std::partition, s | std::stable_partition, s |
|-----------------:|-------------------:|------------------:|-------------------------:|
|            1 000 |          0,0004452 |         0,0002091 |                 0,000262 |
|           10 000 |          0,0024759 |         0,0027386 |                0,0029629 |
|          100 000 |          0,0311609 |         0,0294762 |                0,0345279 |
|        1 000 000 |           0,244024 |          0,249987 |                 0,304289 |
|       10 000 000 |            2,65827 |            2,7883 |                  3,31222 |

### Rezultatų aptarimas

Visi trys variantai studentus suskirstė į tokio pat dydžio
grupes. `std::stable_partition` buvo lėčiausias keturiems iš
penkių failų dydžių. Su 1 000 studentų jis veikė greičiau
už paprastą ciklą, tačiau lėčiau už `std::partition`.

Su 10 milijonų studentų paprastas ciklas užtruko 2,65827 s,
`std::partition` variantas – 2,7883 s, o
`std::stable_partition` variantas – 3,31222 s.
Pastarasis užtruko apie 25 % ilgiau už paprastą ciklą.

Privati programos atmintis po didžiausio bandymo su
`std::stable_partition` buvo 2229,21 MiB.
Atmintį matavau pasibaigus skirstymui, todėl šis skaičius
neparodo laikinos atminties maksimumo algoritmo vykdymo metu.

Išbandyti standartiniai algoritmai aiškaus paspartėjimo,
palyginti su turėtu ciklu, neparodė. Paprastas ciklas buvo
greičiausias dviejuose didžiausiuose bandymuose.
Kadangi atlikau po vieną bandymą, išvados taikomos šiems
konkretiems matavimams.


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
- `CMakeLists.txt` – programos kompiliavimo nustatymai.

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

Antrojoje strategijoje keičiami dviejų studentų konteinerių –
`grupe` ir `vargsiukai` – tipai. Konteineryje `grupe` po skirstymo
lieka tik kietiakai.

Naudojant `vector` ir `deque`, taikomas ciklas su indeksais
ir vienas `erase` konteinerio gale. Naudojant `list`,
studentai šalinami cikle su iteratoriumi.

Naudojant `vector` ir `deque`, studentai rikiuojami su
`std::sort`. Naudojant `list`, kviečiamas jo metodas `.sort()`.

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

## Kompiliavimas su CMake („Windows“)

Reikia „Visual Studio“ su C++ kūrimo įrankiais, „Windows SDK“,
CMake ir Ninja. Dabartinė atminties matavimo funkcija naudoja
„Windows“ funkcijas, todėl ši programos versija skirta „Windows“.

1. Atsisiųsti ir išskleisti projekto kodą arba klonuoti repozitoriją.
2. Atidaryti „x64 Native Tools Command Prompt for VS“.
3. Pereiti į projekto aplanką `SD1`, kuriame yra
   `CMakeLists.txt` ir `StudDB.cpp`.
4. Paruošti „Release“ kompiliavimą:

```text
cmake -S . -B build-final -G Ninja -DCMAKE_BUILD_TYPE=Release
```

5. Sukompiliuoti programą:

```text
cmake --build build-final
```

6. Paleisti programą:

```text
.\build-final\SD1.exe
```

Duomenų failai skaitomi ir rezultatai kuriami tame aplanke,
iš kurio paleidžiama programa. Kompiliavimo aplankas
`build-final` į GitHub nekeliamas.