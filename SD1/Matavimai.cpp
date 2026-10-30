#include "lib.h"
#include "Matavimai.h"

// Neleidžiame windows.h sukurti min ir max makrokomandų,
// kurios gali trukdyti standartinėms C++ funkcijoms.
#define NOMINMAX
#include <windows.h> // Windows funkcijos, tarp jų GetCurrentProcess
#include <psapi.h> // Programos atminties naudojimo matavimas
// Nurodome Visual Studio prijungti Psapi.lib biblioteką.
#pragma comment(lib, "Psapi.lib")

// Programos privati atmintis MiB vienetais
double AtmintisMiB() {
    PROCESS_MEMORY_COUNTERS_EX duomenys{};
    duomenys.cb = sizeof(duomenys);  // Nurodome struktūros dydį baitais.
    // Bandome gauti šiuo metu veikiančios programos atminties duomenis.
    if (!GetProcessMemoryInfo(
        GetCurrentProcess(), // Gauname dabartinės programos proceso rankeną (handle).
        reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&duomenys),
        sizeof(duomenys))) { // Perduodame struktūros dydį.
        throw std::runtime_error("Nepavyko pamatuoti atminties.");  // Jei matavimas nepavyko, išmetame išimtį.
    }

    // PrivateUsage saugo privačios atminties kiekį baitais.
    // Dalijame iš 1024 * 1024, kad gautume MiB.
    return duomenys.PrivateUsage / (1024.0 * 1024.0);
}