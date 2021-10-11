#include <ilcp/cp.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskSet.h"
#include "Helper.h"
#include "Model.h"
#include "TaskChain.h"
#include "Data.h"
#include "TestGenerator.h"


int counter = 1;



void help()
{
    for (int j = 0; j < 3; j++)
    {
        int infeasible = 0;
        std::cout << "Chain " << j << std::endl;

        for (int i = 1; i <= 1000; i++)
        {

            std::string cfilename = "C:\\Users\\Tin\\OneDrive\\Documents\\MDH\\Results\\LogFileSchedulabilityRatioVsUtilizationsChain";
            cfilename += std::to_string(j);
            cfilename += std::to_string(i);
            cfilename += ".txt";
            //std::cout << cfilename;
            std::ifstream fileInput;
            std::string line;
            int offset;
            const char* search = "Model has no solution";
            fileInput.open(cfilename.c_str());
            if (fileInput.is_open()) {
                while (!fileInput.eof()) {
                    getline(fileInput, line);
                    if ((offset = line.find(search, 0)) != std::string::npos) {
                        infeasible++;
                    }
                }
                fileInput.close();
            }
            else std::cout << "Unable to open file.";

            if (i % 100 == 0)
            {

                std::cout << std::endl << "infeasible: " << infeasible;
                infeasible = 0;
            }
        }
    }

    return;

}


// TEST 1: Kompleksnost kreiranog modela u odnosu na broj zadataka

void testConstraintsVsTasks()
{
    std::vector<int> numberOfTasks = { 10 };
    std::vector<int> numberOfChains = { 2, 3, 4 };
    std::vector<double> utilizationsForCores = { 0.5, 0.5 };
    int numberOfCommunicatingPairs = 60;
    double percentageOfConectedness = 0.7;
    int numberOfTestCases = 150;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 7;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains;
    std::vector<std::vector<double>> avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfTasks.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfTask = 0; numberOfTask < numberOfTasks.size(); numberOfTask++)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {
                std::cout << "TEST NUMBER: " << i << std::endl << std::endl;

                chains.clear();

                std::vector<TaskSet> mytaskSets;

                generateTestCase(mytaskSets, chains, numberOfTasks[numberOfTask], numberOfChains[numberOfChain], utilizationsForCores, numberOfCommunicatingPairs);

                numberOfTest++;


                int totalNumberOfConstraints = 0;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(numberOfChain).at(numberOfTask).push_back(totalNumberOfConstraints);

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfInstance = 0; numberOfInstance < numberOfTasks.size(); numberOfInstance++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += numberOfConstraintsPerNumberOfTaskInstancesPerNumberOfChains.at(numberOfChain).at(numberOfInstance).at(test);
            }

            avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }


    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfInstance = 0; numberOfInstance < numberOfTasks.size(); numberOfInstance++)
        {
            std::cout << "Number of tasks " << numberOfTasks.at(numberOfInstance) << ": ";
            std::cout << avgNumberOfConstraintsPerNumberOfTaskInstancesPerChain.at(numberOfChain).at(numberOfInstance) << std::endl;
        }

    }

    counter++;

    return;

}

// TEST 2: Kompleksnost kreiranog modela u zavisnosti od broja komunicirajucih producer-consumer parova

void testConstraintsVsCommunicatingPairs()
{
    int numberOfTasks = 80;
    std::vector<int> numberOfChains = { 3 };
    std::vector<double> utilizationsForCores = { 0.5, 0.5, 0.5, 0.5 };
    std::vector<int> numberOfCommunicatingPairs = { 100, 120, 140, 160 };
    double percentageOfConectedness = 0.6;
    int numberOfTestCases = 50;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 5;
    std::vector<TaskChain> chains;

    std::vector<std::vector<std::vector<int>>> numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains;
    std::vector<std::vector<double>> avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<std::vector<int>> numberOfConstraintsPerNumberOfTaskInstance;
        numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.push_back(numberOfConstraintsPerNumberOfTaskInstance);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        for (int j = 0; j < numberOfCommunicatingPairs.size(); j++)
        {
            std::vector<int> numberOfConstraints;
            numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(i).push_back(numberOfConstraints);
        }
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> avgNumberOfConstraintsPerNumberOfTaskInstance;

        avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.push_back(avgNumberOfConstraintsPerNumberOfTaskInstance);
    }

    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            for (int i = 0; i < numberOfTestCases; i++)
            {

                std::cout << "TEST NUMBER: " << i << std::endl << std::endl;

                chains.clear();

                std::vector<TaskSet> mytaskSets;

                generateTestCase(mytaskSets, chains, numberOfTasks, numberOfChains[numberOfChain], utilizationsForCores, numberOfCommunicatingPairs[numberOfCommunicatingPair]);

                numberOfTest++;

                int totalNumberOfConstraints = 0;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).push_back(totalNumberOfConstraints);

            }
        }
    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            double sum = 0.0;

            for (int test = 0; test < numberOfTestCases; test++)
            {
                sum += numberOfConstraintsPerNumberOfCommunicatingPairsPerNumberOfChains.at(numberOfChain).at(numberOfCommunicatingPair).at(test);
            }

            avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.at(numberOfChain).push_back(sum / numberOfTestCases);
        }
    }


    std::cout << "AVERAGE NUMBER OF CONSTRAINTS PER NUMBER: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int numberOfCommunicatingPair = 0; numberOfCommunicatingPair < numberOfCommunicatingPairs.size(); numberOfCommunicatingPair++)
        {
            std::cout << "Number of communicating producer-consumer pairs " << numberOfCommunicatingPairs.at(numberOfCommunicatingPair) << ": ";
            std::cout << avgNumberOfConstraintsPerNumberOfCommunicatingPairsPerChain.at(numberOfChain).at(numberOfCommunicatingPair) << std::endl;
        }

    }

    return;

}


// TEST 3: Odonos rasporedivosti u zavisnosti od utilizacije dvaju jezgara

void testSchedulabilityRatioVsUtilizations()
{
    int numberOfTasks = 30;
    std::vector<int> numberOfChains = { 3 };
    std::vector<std::vector<double>> utilizationsForCores = { {0.1, 0.1} };
    int numberOfCommunicatingPairs = 16;
    double percentageOfConectedness = 0.5;
    int numberOfTestCases = 100;
    int numberOfSolutions = 1;
    int maximumInterCoreDelay = -1;
    int status;
    int timeLimit = 300;
    std::vector<TaskChain> chains;


    std::vector<std::vector<int>> numberOfOptimizedPerUtilizationsPerChain;
    std::vector<std::vector<int>> numberOfTightenedPerUtilizationsPerChain;
    std::vector<std::vector<int>> numberOfInfeasiblePerUtilizationsPerChain;
    std::vector<std::vector<double>> schedulabilityRatioPerUtilizationsPerChain;

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfOptimizedPerUtilizations;
        numberOfOptimizedPerUtilizationsPerChain.push_back(numberOfOptimizedPerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfTightenedPerUtilizations;
        numberOfTightenedPerUtilizationsPerChain.push_back(numberOfTightenedPerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<int> numberOfInfeasiblePerUtilizations;
        numberOfInfeasiblePerUtilizationsPerChain.push_back(numberOfInfeasiblePerUtilizations);
    }

    for (int i = 0; i < numberOfChains.size(); i++)
    {
        std::vector<double> schedulabilityRatioPerChain;
        schedulabilityRatioPerUtilizationsPerChain.push_back(schedulabilityRatioPerChain);
    }


    int numberOfTest;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        numberOfTest = 1;

        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            int numberOfOptimizedSchedulesPerUtilizationPair = 0;
            int numberOfTightenedSchedulesPerUtilizationPair = 0;
            int numberOfInfeasibleSchedulesPerUtilizationPair = 0;

            for (int i = 0; i < numberOfTestCases; i++)
            {
                chains.clear();

                std::vector<TaskSet> mytaskSets;

                generateTestCase(mytaskSets, chains, numberOfTasks, numberOfChains[numberOfChain], utilizationsForCores[utilizationPair], numberOfCommunicatingPairs);


                int totalNumberOfConstraints;

                createAndSolveModel(mytaskSets, chains, numberOfSolutions, status, totalNumberOfConstraints, timeLimit, maximumInterCoreDelay);

                std::cout << std::endl << status << std::endl;

                if (status == 0)
                {
                    numberOfOptimizedSchedulesPerUtilizationPair++;
                }
                else if (status == 1)
                {
                    numberOfTightenedSchedulesPerUtilizationPair++;
                }
                else
                {
                    numberOfInfeasibleSchedulesPerUtilizationPair++;
                }

            }


            numberOfOptimizedPerUtilizationsPerChain.at(numberOfChain).push_back(numberOfOptimizedSchedulesPerUtilizationPair);
            numberOfTightenedPerUtilizationsPerChain.at(numberOfChain).push_back(numberOfTightenedSchedulesPerUtilizationPair);
            numberOfInfeasiblePerUtilizationsPerChain.at(numberOfChain).push_back(numberOfInfeasibleSchedulesPerUtilizationPair);
        }

    }


    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            schedulabilityRatioPerUtilizationsPerChain.at(numberOfChain).push_back((double)(numberOfTestCases - numberOfInfeasiblePerUtilizationsPerChain.at(numberOfChain).at(utilizationPair)) / numberOfTestCases);
        }
    }

    std::cout << "SCHEDULABILITY RATIOS: " << std::endl;

    for (int numberOfChain = 0; numberOfChain < numberOfChains.size(); numberOfChain++)
    {
        std::cout << "CHAIN: " << numberOfChain << std::endl;

        for (int utilizationPair = 0; utilizationPair < utilizationsForCores.size(); utilizationPair++)
        {
            std::cout << "Utilization Pair " << utilizationsForCores.at(utilizationPair).at(0) << " " << utilizationsForCores.at(utilizationPair).at(1) << ": ";
            std::cout << schedulabilityRatioPerUtilizationsPerChain.at(numberOfChain).at(utilizationPair) << std::endl;
        }
    }

    return;

}


void testIndustrialTestCase()
{
    int numberOfSolutions = 1;

    std::vector<TaskChain> taskChains;

    taskChains.clear();

    int maximumInterCoreDelay = -1;

    int numberOfConstraints;

    int status = 0;

    std::vector<TaskSet> taskSets = TestCase25_1(taskChains);

    createAndSolveModel(taskSets, taskChains, numberOfSolutions, status, numberOfConstraints, 60, maximumInterCoreDelay, false);

}

int main(int, const char* []) {

    try
    {
        testConstraintsVsTasks();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();

    }

    return 0;
}

