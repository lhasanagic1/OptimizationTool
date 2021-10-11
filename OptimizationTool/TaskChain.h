/*
* Klasa koja opisuje lanac zadataka. Lanac zadataka je definisan sa sljedecim parametrima:
* - zadaci koji pripadaju lancu zadataka
* - hiperperiod lanca zadataka
*/

#include<vector>
#include "Task.h"
#include "Helper.h"
#include <iostream>

#define HYPERPERIOD_OF_EMPTY_TASK_CHAIN 0


#pragma once
class TaskChain
{
private:
	std::vector<Task> tasks;
	long long int hyperperiod;


public:

	// Konstruktori 

	TaskChain();

	// Konstruktori

	// Setteri

	void setHyperperiod(long long int t_hyperperiod);

	// Setteri

	// Getteri 

	std::vector<Task> getTasks();
	long long int getHyperperiod();

	// Getteri

	// Metode

	void addTask(Task t_task);

	long long int calculateHyperperiod();

	bool isInChain(long long int taskID);

	// Funkcija koja provjerava da li je zadatak sa ID-em taskID zadnji zadatak u lancu
	bool isLastInChain(int taskID);

	// Metode

	// Operatori

	friend std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain);

	// Operatori

};

