/*
* Klasa koja opisuje jednu instancu zadataka. Instanca zadatka je definisana sa sljedecim parametrima:
* - Zadatak instance
* - absolutno vrijeme oslobadanja (trenutak u vremenu u kojem instanca postaje spremna za izvrsavanje)
* - absolutni rok za izvrsenje instance (trenutak do kojeg instanca treba zavrsiti sa egzekucijom)
* - broj instance
*/

#include "Task.h"
#include <string>

#pragma once
class TaskInstance
{
private:

	Task task;
	long long int absolute_release_time;
	long long int absolute_deadline;
	long long int number_of_instance;
	std::string name;

public:

	// Konstruktori

	TaskInstance(Task t_task, long long int t_absolute_release_time, long long int t_number_of_instance);

	// Konstruktori


	// Setteri

	void setTask(Task t_task);

	void setAbsoluteReleaseTime(long long int t_absolute_release_time);

	void setAbsoluteDeadline(long long int t_absolute_deadline);

	void setNumberOfInstance(long long int t_number_of_instance);

	void setName();

	// Setteri


	// Getteri

	Task getTask();

	long long int getAbsoluteReleaseTime();

	long long int getAbsoluteDeadline();

	long long int getNumberOfInstance();

	std::string getName() const;

	// Getteri

};



