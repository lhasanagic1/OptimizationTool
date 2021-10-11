#include <vector>
#include "Task.h"
#include "TaskSet.h"
#include "TaskChain.h"
#include "Constants.h"
#include <iostream>
#include <algorithm>
#include<random>
#include <ctime>

#pragma once


// Funkcija koja generise testne slucajeve
void generateTestCase(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfTasks, int numberOfChains, std::vector<double> coreUtilizations, int numberOfCommunicatingProducerConsumerInstances = -1);

// Funkcija koja provjerava ispravnost kreiranih lanaca zadataka
bool chainsValid(std::vector<TaskChain> taskChains);

// Funkcija koja provjerava da u kreiranoj ugradbenoj aplikaciji definisanoj sa taskSets i taskChains ima tacno n komunicirajucih producer-consumer parova
bool correctAmountOfCommunicatingInstances(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int n);