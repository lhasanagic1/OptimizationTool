#include "TaskSet.h"
#include "Helper.h"
#include "iostream"

//Konstruktori

TaskSet::TaskSet(long long int t_core)
{
	setCore(t_core);

	setHyperperiod(HYPERPERIOD_OF_EMPTY_TASK_SET);
}

//Konstruktori


// Setteri

void TaskSet::setCore(long long int t_core)
{
	core = t_core;
	return;
}

void TaskSet::setHyperperiod(long long int t_hyperperiod)
{
	hyperperiod = t_hyperperiod;
}

// Setteri


// Getteri

std::vector<Task> TaskSet::getTasks() { return tasks; };

long long int TaskSet::getCore() { return core; }

long long int TaskSet::getHyperperiod() { return hyperperiod; }

std::vector<TaskInstance> TaskSet::getInstances()
{
	std::vector<TaskInstance> instances;

	for (long long int i = 0; i < tasks.size(); i++)
	{

		for (long long int j = 1; j <= this->getHyperperiod() / tasks.at(i).getPeriod(); j++)
		{
			instances.push_back(TaskInstance(tasks.at(i), (j - 1) * tasks.at(i).getPeriod(), j));
		}
	}

	return instances;
}

// Getteri


// Metode

void TaskSet::addTask(Task t_task)
{

	if (t_task.getCoreAssignedTo() != core) throw std::invalid_argument("Invalid core!");

	// Provjeri da li je zadatak vec dodan
	for (long long int i = 0; i < tasks.size(); i++)
	{

		if (tasks.at(i).getTaskId() == t_task.getTaskId()) return;
	}

	tasks.push_back(t_task);

	setHyperperiod(calculateHyperperiod()); // Kada se doda novi zadatak, ponovo izracunaj hiperperiod
}

void TaskSet::removeTask(Task t_task)
{

	for (long long int i = 0; i < tasks.size(); i++)
	{
		if (tasks.at(i).getTaskId() == t_task.getTaskId())
		{
			tasks.erase(tasks.begin() + i);
		}
	}

	setHyperperiod(calculateHyperperiod());
}

long long int TaskSet::calculateHyperperiod()
{

	if (tasks.size() == 1) return tasks.at(0).getPeriod(); // Ako je samo jedan zadatak

	std::vector<unsigned long long int> periods; // Vektor koji sadrzi sve periode zadataka u skupu zadataka, bez duplih perioda

	for (long long int i = 0; i < tasks.size(); i++)
	{
		long long int period = tasks.at(i).getPeriod();
		bool isNewPeriodValue = true;

		for (long long int j = 0; j < periods.size(); j++)
		{
			// Ukloni duple periode radi brzeg racunanja hiperperioda
			if (periods.at(j) == period) isNewPeriodValue = false;
		}

		if (isNewPeriodValue || true) periods.push_back(period);
	}
	return findLeastCommonMultiple(periods);

}

// Metode

long long int getTotalHyperperiod(std::vector<TaskSet>& taskSets)
{
	std::vector<unsigned long long int> hyperperiods;
	for (int i = 0; i < taskSets.size(); i++)
	{
		if (taskSets.at(i).getHyperperiod() != 0) hyperperiods.push_back(taskSets.at(i).getHyperperiod());
	}

	return findLeastCommonMultiple(hyperperiods);
}

bool isInSet(Task t_task, TaskSet& taskSet)
{
	if (t_task.getCoreAssignedTo() == taskSet.getCore()) return true;

	return false;
}

// Metode 