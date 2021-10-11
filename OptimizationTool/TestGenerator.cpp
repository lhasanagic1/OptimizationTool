#include "TestGenerator.h"

bool chainsValid(std::vector<TaskChain> taskChains)
{
	int chainIndex = 0;
	int taskIndex = 0;

	for (int i = 0; i < taskChains.size(); i++)
	{
		chainIndex = i;
		for (int j = 0; j < taskChains.at(i).getTasks().size(); j++)
		{
			taskIndex = j;
			int taskId = taskChains.at(i).getTasks().at(taskIndex).getTaskId();
			std::set<int> taskPredecessors;
			std::set<int> taskSuccessors;

			for (int k = 0; k < taskChains.size(); k++)
			{
				for (int l = 0; l < taskChains.at(k).getTasks().size(); l++)
				{
					if (taskChains.at(k).getTasks().at(l).getTaskId() == taskId)
					{
						// Dodaj sve producere u skup
						for (int predecessors = 0; predecessors < l; predecessors++)
						{
							taskPredecessors.insert(taskChains.at(k).getTasks().at(predecessors).getTaskId());
						}
						// Dodaj sve consumere u skup
						for (int successors = l + 1; successors < taskChains.at(k).getTasks().size(); successors++)
						{
							taskSuccessors.insert(taskChains.at(k).getTasks().at(successors).getTaskId());
						}
					}
				}
			}

			// Ako skup producera i consumera ima zajednickih elemanata, vrati false
			if (setsIntersect(taskPredecessors, taskSuccessors))
			{
				return false;
			}
		}
	}
	return true;
}


bool correctAmountOfCommunicatingInstances(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int n)
{

	if (n < 0) return true;


	int numberOfInstances = 0;

	std::vector<std::vector<TaskInstance>> instancesOnCore;


	// Treba razmatrati zajednicki hiperperiod
	long long int hyperPeriod = getTotalHyperperiod(taskSets);

	for (int i = 0; i < taskSets.size(); i++) {

		taskSets.at(i).setHyperperiod(hyperPeriod);
	}

	for (int i = 0; i < taskSets.size(); i++)
	{
		instancesOnCore.push_back(std::vector<TaskInstance>());
		instancesOnCore.at(i) = taskSets.at(i).getInstances();
	}



	for (int chain = 0; chain < taskChains.size(); chain++)
	{

		for (int consumerIndex = 1; consumerIndex < taskChains.at(chain).getTasks().size(); consumerIndex++)
		{
			long long int consumerTaskId = taskChains.at(chain).getTasks().at(consumerIndex).getTaskId();
			long long int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerIndex).getCoreAssignedTo();

			long long int producerIndex = consumerIndex - 1;
			long long int producerTaskId = taskChains.at(chain).getTasks().at(producerIndex).getTaskId();
			long long int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerIndex).getCoreAssignedTo();

			for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnCore.at(consumerCoreAssignedTo).size(); consumerInstanceIndex++)
			{
				bool firstTime = true;
				TaskInstance currentConsumerInstance = instancesOnCore.at(consumerCoreAssignedTo).at(consumerInstanceIndex);

				if (currentConsumerInstance.getTask().getTaskId() == consumerTaskId)
				{
					for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnCore.at(producerCoreAssignedTo).size(); producerInstanceIndex++)
					{
						TaskInstance currentProducerInstance = instancesOnCore.at(producerCoreAssignedTo).at(producerInstanceIndex);


						if (currentProducerInstance.getTask().getTaskId() == producerTaskId)
						{
							if (consumerCoreAssignedTo != producerCoreAssignedTo)
							{
								if (canCommunicate(currentProducerInstance, currentConsumerInstance))
								{
									numberOfInstances++;

									if (numberOfInstances > n) {
										return false;
									}
								}

								if (currentProducerInstance.getNumberOfInstance() == 1) {

									if (intervalsOverlap(
										currentProducerInstance.getAbsoluteReleaseTime() + currentProducerInstance.getTask().getWorstCaseExecutionTime() - currentProducerInstance.getTask().getPeriod()
										, currentProducerInstance.getAbsoluteDeadline() - currentProducerInstance.getTask().getWorstCaseWrite()
										, currentConsumerInstance.getAbsoluteReleaseTime()
										, currentConsumerInstance.getAbsoluteDeadline() - currentConsumerInstance.getTask().getWorstCaseExecutionTime()

									)
										) {

										numberOfInstances++;

										if (numberOfInstances > n) {
											return false;
										}

									}
								}
							}
						}
					}

				}
			}

		}
	}

	if (numberOfInstances == n)
	{
		return true;
	}
	else
	{
		return false;
	}

}


void generateTestCase(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfTasks, int numberOfChains, std::vector<double> coreUtilizations, int numberOfCommunicatingProducerConsumerInstances)
{

	std::vector<Task> tasks;

	std::cout << "Generating a test case with " << numberOfTasks << " tasks," << numberOfCommunicatingProducerConsumerInstances << "communicating pairs and " << numberOfChains << " chains, with the following core utilizations: ";

	for (int core = 0; core < coreUtilizations.size(); core++)
	{
		std::cout << "Core " << core << " " << coreUtilizations.at(core) << "% ";
	}

	std::cout << std::endl;

	int communicatingPairsCounter = 1;

	long long int task_id = 0;

	do
	{
		// Reset taskId brojac
		task_id = 1;


		int numberOfTasksInChains;

		// Vektor koji cuva broj zadataka po aktivacijskom uzorku za svaki od lanaca
		std::vector<std::vector<int>> numberOfTasksPerActivationPatternPerChain;

		// Vektor koji cuva periode aktivacijskih uzoraka za svaki lanac
		std::vector<std::vector<int>> periodsOfTasksPerActivationPatternPerChain;

		// Vektor koji cuva periode svih zadataka (nezavisni + zadaci u lancima)
		std::vector<long long int> periodsOfTasks;

		do
		{

			// Reset taskId counter
			task_id = 1;

			taskSets.clear();
			numberOfTasksPerActivationPatternPerChain.clear();
			periodsOfTasksPerActivationPatternPerChain.clear();
			periodsOfTasks.clear();

			for (int chain = 0; chain < numberOfChains; chain++)
			{

				// Odaberi aktivacijski uzorak
				int indexOfActivationPattern = roulleteWheelSelecetion(activationPatternsProbabilities);

				std::vector<int> numbersOfTasksForCurrentChain;
				numberOfTasksPerActivationPatternPerChain.push_back(numbersOfTasksForCurrentChain);

				std::vector<int> periodsOfTasksForCurrentChain;
				periodsOfTasksPerActivationPatternPerChain.push_back(periodsOfTasksForCurrentChain);

				// Za svaki od aktivacijskih uzoraka generisi random broj zadataka koristeci distribucije vjerovatnoce
				for (int activationPattern = 0; activationPattern < activationPatterns[indexOfActivationPattern]; activationPattern++)
				{

					numberOfTasksPerActivationPatternPerChain.at(chain).push_back(numberOfTasksPerActivationPattern.at(roulleteWheelSelecetion(numberOfTasksPerActivationPatternProbabilites)));

					// Prvi aktivacijski uzorak moze biti bilo koji
					// Svi ostali moraju postovati matricu dozvoljenih komunikacija

					if (activationPatterns[indexOfActivationPattern] == 1 || activationPattern == 0)
					{
						periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
					}

					else
					{
						// Period producera
						int periodOfProducingActivationPattern = periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern - 1);

						// Nadji index perioda producera
						int indexOfPeriodOfProducingActivationPattern = findIndex(tasksPeriods, periodOfProducingActivationPattern);

						int periodOfConsumingActivationPatternPeriod;

						int indexOfPeriodOfConsumingActivationPattern;

						// Generisi periode za consumera dok se ne dobije dozvoljena vrijednost
						do
						{
							// Reset taskId brojac
							task_id = 1;

							periodOfConsumingActivationPatternPeriod = tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities));

							indexOfPeriodOfConsumingActivationPattern = findIndex(tasksPeriods, periodOfConsumingActivationPatternPeriod);

						} while (isPeriodOfConsumingActivationPatternAllowed[indexOfPeriodOfProducingActivationPattern][indexOfPeriodOfConsumingActivationPattern] == false);

						periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(indexOfPeriodOfConsumingActivationPattern));
					}
				}
			}

			for (int chain = 0; chain < numberOfChains; chain++)
			{
				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					for (int task = 0; task < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); task++)
					{
						periodsOfTasks.push_back(periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern));
					}
				}
			}

			numberOfTasksInChains = 0;

			// Izracunaj ukupni broj zadataka u lancima
			for (int chain = 0; chain < numberOfChains; chain++)
			{
				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					numberOfTasksInChains += numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern);
				}
			}

		} while (numberOfTasksInChains > numberOfTasks); // Broj zadataka u lancima mora biti manji od ukupnog broja zadataka


		// Broj nezavisnih zadataka
		int numberOfIndependentTasks = numberOfTasks - numberOfTasksInChains;


		// Generisi periode za nezavisne zadatke

		for (int independentTask = 0; independentTask < numberOfIndependentTasks; independentTask++)
		{
			periodsOfTasks.push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
		}


		std::vector<int> allTasksIDs;

		for (int taskID = 0; taskID < numberOfTasks; taskID++)
		{
			allTasksIDs.push_back(taskID + 1);
		}

		// Promjesaj vektor ID-eva zadataka
		std::random_shuffle(allTasksIDs.begin(), allTasksIDs.end());


		// Generisi tacke razdvajanja za vektor zadataka
		std::uniform_int_distribution<> distributionForSplitUpOfTasks(1, numberOfTasks - 1);

		std::random_device rd;

		std::mt19937 gen(rd());

		std::vector<int> splitUpPoints;

		do
		{
			splitUpPoints.clear();
			for (int points = 0; points < coreUtilizations.size() - 1; points++)
			{
				splitUpPoints.push_back(distributionForSplitUpOfTasks(gen));
			}

		} while (!allDifferent(splitUpPoints));



		// Dodaj 0 i brojZadataka radi lakse manipulacije u ostatku algoritma
		splitUpPoints.push_back(0);
		splitUpPoints.push_back(numberOfTasks);

		std::sort(splitUpPoints.begin(), splitUpPoints.end());

		// Vektor koji cuva informacije o tome koji zadatak je dodijeljen kojoj jezgri
		std::vector<int> coreAssignedTo;


		for (int taskID = 0; taskID < numberOfTasks; taskID++)
		{
			int core = 0;

			for (int point = 1; point < splitUpPoints.size() - 1; point++)
			{
				if (taskID >= splitUpPoints.at(point)) core = point;
			}

			coreAssignedTo.push_back(core);
		}


		// Sortiraj IDeve zadataka i coreAssignedTo zajedno sa njim

		for (int taskID = 0; taskID < allTasksIDs.size() - 1; taskID++)
		{
			for (int taskIDHelp = 0; taskIDHelp < allTasksIDs.size() - taskID - 1; taskIDHelp++)
			{
				if (allTasksIDs[taskIDHelp] > allTasksIDs[taskIDHelp + 1])
				{
					int tempID = allTasksIDs[taskIDHelp];
					int tempCore = coreAssignedTo[taskIDHelp];

					allTasksIDs[taskIDHelp] = allTasksIDs[taskIDHelp + 1];
					coreAssignedTo[taskIDHelp] = coreAssignedTo[taskIDHelp + 1];

					allTasksIDs[taskIDHelp + 1] = tempID;
					coreAssignedTo[taskIDHelp + 1] = tempCore;

				}
			}
		}


		// Generisi utilizacije za svaki zadatak svake od jezgri i stavi ih u u odgovarajuci vektor

		std::vector<std::vector<std::vector<double>>> utilizationsForCores;

		for (int core = 0; core < coreUtilizations.size(); core++)
		{
			utilizationsForCores.push_back(generateTaskUtilization(double(splitUpPoints.at(core + 1) - splitUpPoints.at(core)), coreUtilizations.at(core)));
		}

		std::vector<double> utilizationsOfTasks(numberOfTasks, 0.0);

		std::vector<int> utilizationCounters(coreUtilizations.size(), 0);


		for (int task = 0; task < numberOfTasks; task++)
		{

			utilizationsOfTasks.at(task) = utilizationsForCores.at(coreAssignedTo.at(task)).at(0).at(utilizationCounters.at(coreAssignedTo.at(task)));

			utilizationCounters.at(coreAssignedTo.at(task))++;

		}


		// Izracunaj WCET za svaki od zadataka prema formuli WCET = T * U;

		std::vector<long long int> worstCaseExecutionTime;


		for (int task = 0; task < numberOfTasks; task++)
		{
			// Pretvori u pikosekunde
			worstCaseExecutionTime.push_back(((double)periodsOfTasks.at(task)) * (utilizationsOfTasks.at(task)));
		}


		std::vector<long long int> worstCaseRead;

		for (int task = 0; task < numberOfTasks; task++)
		{
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseRead.push_back(labelSizes.at(generatedIndex).at(whichLabel));
		}


		std::vector<long long int> worstCaseWrite;

		for (int task = 0; task < numberOfTasks; task++)
		{
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseWrite.push_back(labelSizes.at(generatedIndex).at(whichLabel));

		}


		std::vector<long long int> worstCaseExecute;

		for (int task = 0; task < numberOfTasks; task++)
		{
			if (worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task) < 0)
			{
				worstCaseExecute.push_back(0);
			}
			else
			{
				worstCaseExecute.push_back(worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task));
			}

		}


		// Kreiraj skupove zadataka

		for (int core = 0; core < coreUtilizations.size(); core++)
		{
			taskSets.push_back(TaskSet(core));
		}

		// Kreiraj zadatke i popuni skupove zadataka

		tasks.clear();

		for (int task = 0; task < numberOfTasks; task++)
		{
			Task newTask(task_id, worstCaseRead[task], worstCaseExecute[task], worstCaseWrite[task], periodsOfTasks[task], coreAssignedTo.at(task));

			task_id++;

			tasks.push_back(newTask);

			taskSets.at(coreAssignedTo.at(task)).addTask(newTask);

		}


		// Popravi jezgre zadataka

		tasks.clear();

		for (int i = 0; i < taskSets.size(); i++)
		{
			for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
			{
				tasks.push_back(taskSets.at(i).getTasks().at(j));


			}
		}


		int testCounter = 1;
		// Popuni lance zadataka
		do {

			taskChains.clear();

			for (int chain = 0; chain < numberOfChains; chain++)
			{
				TaskChain newChain;

				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					for (int taskNumber = 0; taskNumber < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); taskNumber++)
					{
						int randomTaskID = 0;

						do
						{


							std::uniform_int_distribution<> distribution(0, numberOfTasks - 1);

							randomTaskID = distribution(gen);


						} while (tasks.at(randomTaskID).getPeriod() != (long long int) periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern) || newChain.isInChain(tasks.at(randomTaskID).getTaskId()));

						newChain.addTask(tasks.at(randomTaskID));
					}
				}

				taskChains.push_back(newChain);
			}
			testCounter++;
		} while (false); // Provjeri da li su kreirani lanci zadataka semi-cirkularni


	} while (!correctAmountOfCommunicatingInstances(taskSets, taskChains, numberOfCommunicatingProducerConsumerInstances) || !chainsValid(taskChains)); // Provjeri da li je broj instanci i broj potencijalno komunicirajucih instanci korektan

}