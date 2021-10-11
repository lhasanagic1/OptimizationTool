/* Klasa koja opsije jedan zadatak. Zadatak je predstavljen sa sljedecim parametrima:
* - WCR
* - WCE
* - WCW
* NOTE: prva tri parametra reprezentiraju zadatak u formi REW modela opisanog u tezi
* - period
* - rok za izvršenje
* - jezgra kojoj je zadatak dodijeljen
*
* Nekoliko 'instanci' svakog zadatka se moze kreirati unutar ukupnog hiperperioda
* @SEE TaskInstance klasa
*/

#include <vector>
#include <iostream>
#include <string>

#pragma once
class Task
{
private:
	long long int task_id;
	long long int worst_case_read;
	long long int worst_case_execute;
	long long int worst_case_write;
	long long int period;
	long long int deadline; // Krajnji rok za izvrsenje zadatka (krajnji rok za izvrsenje = period)
	long long int core_assigned_to;
	std::vector<Task> successors;
	bool is_producer; // Da li je ovaj zadatak producer u nekom lancu zadatka
	bool is_consumer; // Da li je ovaj zadatak consumer u nekom lancu zadataka
	std::string name;

public:

	// Konstruktori

	Task();

	Task(long long int t_task_id, long long int t_worst_case_read, long long int t_worst_case_execute, long long int worst_case_write, long long int t_period, long long int t_core_assigned_to);

	// Konstruktori


	// Setteri

	void setTaskId(long long int t_task_id);

	void setWorstCaseRead(long long int t_worst_case_read);

	void setWorstCaseExecute(long long int t_worst_case_execute);

	void setWorstCaseWrite(long long int worst_case_write);

	void setPeriod(long long int t_period);

	void setDeadline(long long int t_deadline);

	void setCoreAssignedTo(long long int t_core_assigned_to);

	void setSuccessors(std::vector<Task> t_successors);

	void setName();

	// Setteri


	// Getteri

	const long long int getTaskId();

	long long int getWorstCaseRead();

	long long int getWorstCaseExecute();

	long long int getWorstCaseWrite();

	long long int getPeriod() const;

	long long int getDeadline();

	long long int getCoreAssignedTo();

	std::vector<Task> getSuccessors();

	std::string getName() const;

	// Getteri


	// Metode

	// Metoda koja vraca WCET zadatka (WCET = WCR + WCE + WCW)
	long long int getWorstCaseExecutionTime();

	void addSuccessor(Task successor);

	// Metode

	// Operatori

	friend std::ostream& operator<<(std::ostream& out, const Task& task);

	// Operatori


};

