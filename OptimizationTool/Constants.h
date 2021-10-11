#pragma once

// Konstante za zadatke

#define DEFAULT_TASK_PARAMETER -1

// Konstante za lance zadataka
#define HYPERPERIOD_OF_EMPTY_TASK_CHAIN 0

//Konstante za lance zadataka
#define HYPERPERIOD_OF_EMPTY_TASK_SET 0

//TestGenerator konstante

// Frekvencija sistemskog sata
constexpr auto CLOCK_FREQUENCY = 300000;

// Broj ciklusa sata potrebnih za citanje jednog bajta

constexpr auto NUMBER_OF_CYCLES_PER_BYTE = 10;

// Broj bajtova koji se moze procitati u jednom ciklusu sata
#define NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE 1/NUMBER_OF_CYCLES_PER_BYTE

// Postotak bajtova za citanje
#define READ_PERCENTAGE 0.9

// Postotak bajtova za pisanje
#define WRITE_PERCENTAGE 0.6

// Distribucija vjerovatnoce broja aktivacijskih uzoraka
#define activationPatterns std::vector<int> {1, 2, 3}
#define activationPatternsProbabilities std::vector<double> {0.7, 0.2, 0.1}

// Distribucija vjerovatnoce broja zadataka po aktivacijskom uzorku
#define numberOfTasksPerActivationPattern std::vector<int> {2, 3, 4, 5}
#define numberOfTasksPerActivationPatternProbabilites std::vector<double> {0.3, 0.4, 0.2, 0.1}

// Distribucija vjerovatnoce perioda zadataka
#define tasksPeriods std::vector<int> {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 1000000}
#define tasksPeriodsProbabilities std::vector<double> {0.04, 0.03, 0.03, 0.29, 0.29, 0.03, 0.22, 0.03, 0.04}

// Matrica koja predstavlja tabelu dozvoljenih komunikacija aktivacijskih uzoraka u lancima zadataka (1 dozvoljeno, 0 nije dozvoljeno)
#define isPeriodOfConsumingActivationPatternAllowed std::vector<std::vector<bool>> {{1, 0, 0, 1, 1, 0, 1, 0, 0}, {0, 1, 0, 1, 1, 0, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 1, 1, 0, 1, 1, 1}, {0, 0, 0, 1, 1, 0, 1, 1, 1}}

// Distribucija vjerovatnoce velicina read/write labela
#define labelSizes std::vector<std::vector<int>> { {1}, {2}, {4}, {5, 6, 7, 8}, {9, 10, 11, 12, 13, 14, 15, 16}, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}, {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}, {64}}
#define labelSizesProbabilities std::vector<double> {0.35, 0.49, 0.13, 0.008, 0.013, 0.005, 0.002, 0.002}

// Konstante za model


// Broj faza REW modela
#define NUMBER_OF_PHASES 3

// Ovdje specificirati broj jezgri
#define NUMBER_OF_CORES 2
