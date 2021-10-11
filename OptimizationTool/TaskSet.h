/*
* Klasa koja opisuje skup zadataka. Skup zadataka definisan je sljedecim parametrima:
* - zadaci koji su mu dodijeljni
* - jezgra koja mu je dodijeljena
* - hiperperioda skupa zadataka
* - sve instance zadataka koje se nalaze unutar hiperperioda
*/

#include <iterator> 
#include <vector>
#include "Task.h"
#include "TaskInstance.h"

#define HYPERPERIOD_OF_EMPTY_TASK_SET 0

#pragma once
class TaskSet
{
private:
	std::vector<Task> tasks;
	long long int core;
	long long int hyperperiod;
	std::vector<TaskInstance> instances;


public:

	//Konstruktori

	TaskSet(long long int t_core);

	//Konstruktori


	// Setteri

	void setCore(long long int t_core);
	void setHyperperiod(long long int t_hyperperiod);

	// Setteri


	// Getteri
	std::vector<Task> getTasks();
	long long int getCore();
	long long int getHyperperiod();
	std::vector<TaskInstance> getInstances();

	// Getteri


	// Metode

	void addTask(Task t_task);

	void removeTask(Task t_task);

	long long int calculateHyperperiod();

	// Metode
};

long long int getTotalHyperperiod(std::vector<TaskSet>& taskSets);