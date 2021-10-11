#include "TaskChain.h"

// Konstruktori 

TaskChain::TaskChain()
{
	tasks.clear();
	hyperperiod = HYPERPERIOD_OF_EMPTY_TASK_CHAIN;
}

// Konstruktori

// Setteri

void TaskChain::setHyperperiod(long long int t_hyperperiod) { hyperperiod = t_hyperperiod; }

// Setteri

// Getteri

long long int TaskChain::getHyperperiod() { return hyperperiod; }

// Getteri

// Metode

void TaskChain::addTask(Task t_task)
{
	tasks.push_back(t_task);
	setHyperperiod(calculateHyperperiod()); // Nakon sto se doda novi zadatak, ponovo izracunaj hiperperiod
}

std::vector<Task> TaskChain::getTasks() { return tasks; }

long long int TaskChain::calculateHyperperiod()
{
	if (tasks.size() == 1) return tasks.at(0).getPeriod(); // Ako je samo jedan zadatak u lancu

	std::vector<unsigned long long int> periods; // Vektor svih perioda u lancu, bez duplih perioda

	for (unsigned long long int i = 0; i < tasks.size(); i++)
	{
		long long int period = tasks.at(i).getPeriod();
		bool isNewPeriodValue = true;

		for (unsigned long long int j = 0; j < periods.size(); j++)
		{
			// Ukloni duple peridoe zbog brzeg racunanja
			if (periods.at(j) == period) isNewPeriodValue = false;
		}

		if (isNewPeriodValue || true) periods.push_back(period);
	}

	return findLeastCommonMultiple(periods);
}

bool TaskChain::isInChain(long long int taskID)
{


	for (long long int task = 0; task < this->getTasks().size(); task++)
	{
		if (this->getTasks().at(task).getTaskId() == taskID)
		{
			return true;
		}
	}

	return false;
}

bool TaskChain::isLastInChain(int taskID)
{

	return this->getTasks()[this->getTasks().size() - 1].getTaskId() == taskID;
}

// Metode

// Operatori

std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain)
{
	out << "Task Chain: " << std::endl;

	for (long long int task = 0; task < taskChain.tasks.size() - 1; task++)
	{
		out << taskChain.tasks.at(task) << "\t|" << std::endl << "\tV" << std::endl;
	}

	return out << taskChain.tasks.at(taskChain.tasks.size() - 1) << std::endl;

}

// Operatori

