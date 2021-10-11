/*
File sa svim helper funkcijama koje se koriste u projektu
*/

#include <vector>
#include <set>
#include "TaskInstance.h"
#include "Task.h"
#include "iostream"
#include "math.h"
#include <algorithm>
#include<random>
#include <ctime>

#pragma once

unsigned long long int findGreatestCommonDivisor(unsigned long long int a, unsigned long long int b);

unsigned long long int findGreatestCommonDivisorOfVector(std::vector<unsigned long long int> inputs);

unsigned long long int findLeastCommonMultiple(std::vector<unsigned long long int> inputs);

// Funkcija koja odabire element iz vektora na principu roullete wheel algoritma
int roulleteWheelSelecetion(std::vector<double> probabilities);

// Funkcija koja pronalazi index vrijednosti value u vektoru values, a vraca -1 ukoliko se value ne nalazi u vektoru values //
int findIndex(std::vector<int> values, int value);

// Funkcija koja provjerava da li su svi elementi u vektoru razlicite vrijednosti
bool allDifferent(std::vector<int> inputs);

// Funkcija koja replicira matricu mat
std::vector<std::vector<double> > repmat(std::vector<std::vector<double> > mat, int rows, int columns);

// Funkcija koja vraca n uniformno rasporedjenih brojava cija je suma jednaka u prema algoritmu opisanom u tezi
std::vector<std::vector<double>> generateTaskUtilization(double n, double u);

// Funkcija koja provjerava da li se dva skupa presjecaju
bool setsIntersect(std::set<int> a, std::set<int> b);

// Funkcija koja vraca true ako se intervali [a1, a2] i [b1, b2] presjecaju
bool intervalsOverlap(long long int a1, long long int a2, long long int b1, long long int b2);

// Funkcija koja vraca true ako producer i consumer mogu komunicirati
bool canCommunicate(TaskInstance& producer, TaskInstance& consumer);


