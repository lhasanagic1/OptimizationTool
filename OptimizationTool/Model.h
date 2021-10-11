#include <ilcp/cp.h>
#include <string>
#include <cstring>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskSet.h"
#include "Helper.h"
#include "TaskChain.h"
#include "Constants.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>


#pragma once

using namespace std;

// Globalna CPLEX environment varijabla
static IloEnv environment;

// Globalna CPLEX model varijabla
static IloModel model;

// Funkcija za inicijalizaciju environmenta
void initializeEnviroment(void);

// Funkcija koja kreira imena intervalskih varijabli u modelu
string createIntervalVariableName(string instanceName, string phase);

// Funkcija koja kreira CPLEX model na osnovu ulaznih parametara
double createAndSolveModel(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfSolutions, int& status, int& numberOfConstraints, int timeLimit = 60, int maximumInterCoreDelay = -1, bool minimizeResponseTimes = false);





