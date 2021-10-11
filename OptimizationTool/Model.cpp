#include "Model.h"


void initializeEnviroment(void)
{
    environment = IloEnv();
}

string createIntervalVariableName(string instanceName, string phase)
{
    string intervalVariableName;

    intervalVariableName = instanceName + " " + phase;


    return intervalVariableName;
}

double createAndSolveModel(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfSolutions, int& status, int& numberOfConstraints, int timeLimit, int maximumInterCoreDelay, bool minimizeResponseTimes)
{
    int brojEndBeforeStart = 0;
    int brojNoOverlap = 0;
    int brojIloIfThen = 0;
    int brojIloStartOf = 0;
    int brojIloEndOf = 0;
    int brojInterval = 0;
    int brojExtraInstanci = 0;
    int brojRW = 0;
    int brojZ = 0;
    int brojHelper = 0;




    std::cout << "Initializing..." << std::endl << std::endl;

    // 1. Inicijaliziraj environment
    initializeEnviroment;

    // Inicijaliziraj model
    model = IloModel(environment);

    std::cout << "Setting up..." << std::endl << std::endl;

    // 2. Izracunaj hiperperiod
    long long int hyperPeriod = 0;

    // Posmatramo ukupni hiperperiod
    hyperPeriod = getTotalHyperperiod(taskSets);

    std::cout << "Hyperperiod: " << hyperPeriod << std::endl;

    for (int i = 0; i < taskSets.size(); i++) {

        taskSets.at(i).setHyperperiod(hyperPeriod);
    }

    // 3. Nadji broj jezgri
    int numberOfCores = taskSets.size();

    // 4. Inicijaliziraj numberInstancesCore vector
        // Vektor u kojem se nalazi broj instanci za svaku od jezgri
    std::vector<int> numberInstancesCore;

    for (IloInt i = 0; i < numberOfCores; i++)
    {

        numberInstancesCore.push_back(taskSets.at(i).getInstances().size());
    }


    // 5. Inicijaliziraj allPhasesOfInstances vector
        // Vektor koji sadrzi intervalske varijable za svaku fazu svih instanci
    IloIntervalVarArray allPhasesOfInstances(environment);

    // 6. Inicijaliziraj phasesOfInstancesOnCore vector
        // Matrica koja sadrzi intervalske varijable za svaku od faza svih instanci na pojedinacnim jezgrima
    std::vector<IloIntervalVarArray> phasesOfInstancesOnCore;

    for (int i = 0; i < numberOfCores; i++)
    {
        phasesOfInstancesOnCore.push_back(IloIntervalVarArray(environment, numberInstancesCore.at(i) * NUMBER_OF_PHASES));
    }


    // 7. Inicijaliziraj instancesOnCore vector
        // Matrica koja sadrzi intervalske varijable koje predstavljaju cijele instance za svaku od pojedniacnih jezgri
    std::vector<IloIntervalVarArray> instancesOnCore;

    for (int i = 0; i < numberOfCores; i++)
    {
        instancesOnCore.push_back(IloIntervalVarArray(environment));
    }

    // 8. Inicijaliziraj totalNumberOfRWPhases

    int totalNumberOfRWPhases = 0;

    for (int i = 0; i < numberOfCores; i++)
    {
        // Samo READ i WRITE faze se uzimaju u obzir
        totalNumberOfRWPhases += numberInstancesCore.at(i) * (NUMBER_OF_PHASES - 1);
    }

    // 9. Inicijaliziraj ReadAndWriteInstances vector
        // Vektor koji sadrzi intervalske varijable za read i write faze svih instanci
    IloIntervalVarArray ReadAndWriteInstaces(environment, totalNumberOfRWPhases);

    // 10. Inicijaliziraj numberOfIntervalVar i numberOfReadAndWriteIntervalVar brojace
    int numberOfIntervalVar = 0;
    int numberOfReadAndWriteIntervalVar = 0;


    // 11. Inicijaliziraj consumerProducerPairVariablesForConsumerGlobal vector
        // Vektor koji sadrzi Zi varijable prema nacinu opisanom u tezi
    IloExprArray consumerProducerPairVariablesForConsumerGlobal(environment);

    // 12. Inicijaliziraj  responseTimeDecisionVariables vector
        // Vektor koji sadrzi Ri varijable prema nacinu opisanom u tezi
    IloExprArray responseTimeDecisionVariables(environment);

    // 13. Inicijaliziraj extraWriteInstances vector
    // Vektor koji sadrzi extra write instance prema nacinu opisanom u tezi
    std::vector<IloIntervalVarArray> extraWriteInstances;
    for (IloInt i = 0; i < numberOfCores; i++)
    {
        extraWriteInstances.push_back(IloIntervalVarArray(environment));
    }

    // 14. Inicijaliziraj helper vector
    // Vektor koji sadrzi Hi varijable prema nacinu opisanom u tezi
    IloIntVarArray helper(environment);


    std::cout << "CREATING INTERVAL DECISION VARIABLES FOR TASKS..." << std::endl << std::endl;

    for (int core = 0; core < numberOfCores; core++)
    {
        for (int i = 0; i < numberInstancesCore.at(core); i++)
        {
            TaskInstance currentInstance = taskSets.at(core).getInstances().at(i);

            for (int j = 0; j < NUMBER_OF_PHASES; j++)
            {
                if (j == 0) // Kreiraj intervalsku varijablu koja predstavlja read fazu
                {

                    // Start i end tacke su detaljno opisane u tezi

                    IloIntervalVar readPhaseIntervalVar = IloIntervalVar(environment);
                    readPhaseIntervalVar.setName(createIntervalVariableName(currentInstance.getName(), "READ").c_str());

                    readPhaseIntervalVar.setPresent();

                    readPhaseIntervalVar.setStartMin(currentInstance.getAbsoluteReleaseTime());
                    readPhaseIntervalVar.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());

                    readPhaseIntervalVar.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead());
                    readPhaseIntervalVar.setEndMax(currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));

                    readPhaseIntervalVar.setLengthMin(currentInstance.getTask().getWorstCaseRead());
                    readPhaseIntervalVar.setLengthMax(currentInstance.getTask().getWorstCaseRead());

                    readPhaseIntervalVar.setSizeMin(currentInstance.getTask().getWorstCaseRead());
                    readPhaseIntervalVar.setSizeMax(currentInstance.getTask().getWorstCaseRead());

                    // Dodaj u model i odgovarajuce vektore
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = readPhaseIntervalVar;

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];

                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;

                    brojRW++;
                    brojInterval++;


                }

                else if (j == 1) // Kreiraj intervalsku varijablu koja predstavlja execute fazu
                {
                    // Start i end tacke su detaljno opisane u tezi

                    IloIntervalVar executePhaseIntervalVar = IloIntervalVar(environment);
                    executePhaseIntervalVar.setName(createIntervalVariableName(currentInstance.getName(), "EXECUTE").c_str());

                    executePhaseIntervalVar.setPresent();

                    executePhaseIntervalVar.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead());
                    executePhaseIntervalVar.setStartMax(currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));

                    executePhaseIntervalVar.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute());
                    executePhaseIntervalVar.setEndMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());

                    executePhaseIntervalVar.setLengthMin(currentInstance.getTask().getWorstCaseExecute());
                    executePhaseIntervalVar.setLengthMax(currentInstance.getTask().getWorstCaseExecute());

                    executePhaseIntervalVar.setSizeMin(currentInstance.getTask().getWorstCaseExecute());
                    executePhaseIntervalVar.setSizeMax(currentInstance.getTask().getWorstCaseExecute());

                    // Dodaj u model i odgovarajuce vektore
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = executePhaseIntervalVar;

                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfIntervalVar++;
                    brojInterval++;


                }

                else // Kreiraj intervalsku varijablu koja predstavlja write fazu
                {
                    // Start i end tacke su detaljno opisane u tezi

                    IloIntervalVar writePhaseIntervalVar = IloIntervalVar(environment);
                    writePhaseIntervalVar.setName(createIntervalVariableName(currentInstance.getName(), "WRITE").c_str());

                    writePhaseIntervalVar.setPresent();

                    writePhaseIntervalVar.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute());
                    writePhaseIntervalVar.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());

                    writePhaseIntervalVar.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime());
                    writePhaseIntervalVar.setEndMax(currentInstance.getAbsoluteDeadline());

                    writePhaseIntervalVar.setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                    writePhaseIntervalVar.setLengthMax(currentInstance.getTask().getWorstCaseWrite());

                    writePhaseIntervalVar.setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                    writePhaseIntervalVar.setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                    // Dodaj u model i odgovarajuce vektore
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = writePhaseIntervalVar;

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];

                    allPhasesOfInstances.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    model.add(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    brojRW++;
                    brojInterval++;

                    // 16. Kreiranje varijable za vremena odziva
                    if (minimizeResponseTimes)
                    {

                        IloExpr responseTimeVar = IloExpr(environment);

                        responseTimeVar.setName(createIntervalVariableName(currentInstance.getName(), "RESPONSE").c_str());

                        responseTimeVar = IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]) - currentInstance.getAbsoluteReleaseTime();


                        responseTimeDecisionVariables.add(responseTimeVar);
                    }

                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;


                }


            }

            // 17. Dodaj ogranicenja koja modeliraju REW model izvrsavanja
                // Execute faza mora poceti poslije read faze

            model.add(IloEndBeforeStart(environment, phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3], phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2]));

            brojEndBeforeStart++;

            // Write faza mora poceti poslije execute faze
            model.add(IloEndBeforeStart(environment, phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2], phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]));
            brojEndBeforeStart++;

            // 18. Kreiraj intervalsku varijablu koja predstavlja cijelu instancu
            IloIntervalVar instanceVariable(environment);

            instanceVariable.setName(createIntervalVariableName(currentInstance.getName(), "ALL").c_str());

            instanceVariable.setPresent();

            instanceVariable.setStartMin(currentInstance.getAbsoluteReleaseTime());
            instanceVariable.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());

            instanceVariable.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime());
            instanceVariable.setEndMax(currentInstance.getAbsoluteDeadline());

            instanceVariable.setLengthMin(currentInstance.getTask().getWorstCaseExecutionTime());
            instanceVariable.setLengthMax(currentInstance.getTask().getPeriod());

            instanceVariable.setSizeMin(currentInstance.getTask().getWorstCaseExecutionTime());
            instanceVariable.setSizeMax(currentInstance.getTask().getPeriod());



            // Instance mora zapoceti u isto vrijeme kada i odgovarajuca read faza
            model.add(IloStartOf(instanceVariable) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3]));
            brojIloStartOf++;


            // Instanca mora zavrsiti u isto vrijeme kada i odgovarajuca write faza
            model.add(IloEndOf(instanceVariable) == IloEndOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]));
            brojIloEndOf++;

            // Dodaj u odgovarajuca vektore
            instancesOnCore.at(core).add(instanceVariable);

            // 19. Provjeri da li je instanca u nekom lancu zadataka

            bool isInAnyChain = false;
            for (int chain = 0; chain < taskChains.size(); chain++)
            {
                if (taskChains.at(chain).isInChain(currentInstance.getTask().getTaskId()))
                {
                    isInAnyChain = true;
                    break;
                }
            }

            // Provjeri da li je instanca samo producer
            bool isAlwaysLastInChain = false;
            if (isInAnyChain) {
                isAlwaysLastInChain = true;
                for (int chain = 0; chain < taskChains.size(); chain++)
                {
                    if (!taskChains.at(chain).isLastInChain(currentInstance.getTask().getTaskId()))
                    {
                        isAlwaysLastInChain = false;
                        break;
                    }
                }

            }

            // 20. Kreiraj dodatnu write varijablu
            if (i != numberInstancesCore.at(core) - 1 && isInAnyChain && !isAlwaysLastInChain)
            {
                if (taskSets.at(core).getInstances().at(i + 1).getTask().getTaskId() != currentInstance.getTask().getTaskId())
                {
                    if (isInAnyChain && !isAlwaysLastInChain)
                    {
                        // Start i end tacke su detaljno opisane u tezi

                        IloIntervalVar extraInstance(environment);

                        extraInstance.setName(createIntervalVariableName(currentInstance.getName(), "EXTRA").c_str());

                        extraInstance.setPresent();

                        extraInstance.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute() - hyperPeriod);
                        extraInstance.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - hyperPeriod);

                        extraInstance.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - hyperPeriod);
                        extraInstance.setEndMax(0);

                        extraInstance.setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                        extraInstance.setLengthMax(currentInstance.getTask().getWorstCaseWrite());

                        extraInstance.setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                        extraInstance.setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                        // Dodaj u model i odgovarajuce vektore
                        extraWriteInstances.at(core).add(extraInstance);


                        model.add(IloStartOf(extraInstance) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]) - hyperPeriod);
                        brojIloStartOf++;
                        brojExtraInstanci++;

                    }


                }
            }
            else
            {

                if (isInAnyChain && !isAlwaysLastInChain)
                {
                    // Start i end tacke su detaljno opisane u tezi

                    IloIntervalVar extraInstance(environment);

                    extraInstance.setName(createIntervalVariableName(currentInstance.getName(), "EXTRA").c_str());

                    extraInstance.setPresent();

                    extraInstance.setStartMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute() - hyperPeriod);
                    extraInstance.setStartMax(currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - hyperPeriod);

                    extraInstance.setEndMin(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - hyperPeriod);
                    extraInstance.setEndMax(0);

                    extraInstance.setLengthMin(currentInstance.getTask().getWorstCaseWrite());
                    extraInstance.setLengthMax(currentInstance.getTask().getWorstCaseWrite());


                    extraInstance.setSizeMin(currentInstance.getTask().getWorstCaseWrite());
                    extraInstance.setSizeMax(currentInstance.getTask().getWorstCaseWrite());

                    // Dodaj u model i odgoavarjuce vektore

                    extraWriteInstances.at(core).add(extraInstance);


                    model.add(IloStartOf(extraInstance) == IloStartOf(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1]) - hyperPeriod);
                    brojIloStartOf++;
                    brojExtraInstanci++;
                }

            }

        }
        numberOfIntervalVar = 0;
    }


    // 21. Ogranicenja na ne preklapanje instanci zadataka na istom jezgru
    for (int i = 0; i < numberOfCores; i++)
    {
        ///std::cout << "NO OVERLAP: " << instancesOnCore.at(i) << std::endl;
        model.add(IloNoOverlap(environment, instancesOnCore.at(i)));
        brojNoOverlap++;
    }

    // 22. Ogranicenja na ne preklapanje read i write faza prema REW modelu izvrsavanja
    model.add(IloNoOverlap(environment, ReadAndWriteInstaces));
    brojNoOverlap++;

    // 23. Generisi Z varijable

    std::cout << "CREATING INT DEICISON VARIABLES FOR TASK CHAINS..." << std::endl << std::endl;

    for (int chain = 0; chain < taskChains.size(); chain++)
    {
        // Hiperperiod lanca
        long long int chainHyperPeriod = taskChains.at(chain).getHyperperiod();

        for (int consumerTaskIndex = 1; consumerTaskIndex < taskChains.at(chain).getTasks().size(); consumerTaskIndex++) // Loop through all of the tasks in the chain except for the first one (has no producers)
        {

            // consumer
            int consumerTaskId = taskChains.at(chain).getTasks().at(consumerTaskIndex).getTaskId();
            long long int consumerTaskPeriod = taskChains.at(chain).getTasks().at(consumerTaskIndex).getPeriod();
            int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerTaskIndex).getCoreAssignedTo();
            long long int consumerExecutionTime = taskChains.at(chain).getTasks().at(consumerTaskIndex).getWorstCaseExecutionTime();

            // producer
            int producerTaskIndex = consumerTaskIndex - 1;
            int producerTaskId = taskChains.at(chain).getTasks().at(producerTaskIndex).getTaskId();
            long long int producerTaskPeriod = taskChains.at(chain).getTasks().at(producerTaskIndex).getPeriod();
            int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerTaskIndex).getCoreAssignedTo();
            long long int producerExecutionTime = taskChains.at(chain).getTasks().at(producerTaskIndex).getWorstCaseExecutionTime();



            std::vector<TaskInstance> instancesOnProducersCore = taskSets.at(producerCoreAssignedTo).getInstances();

            std::vector<TaskInstance> instancesOnConsumersCore = taskSets.at(consumerCoreAssignedTo).getInstances();

            for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnConsumersCore.size(); consumerInstanceIndex++) // Loop through all the instances on the consumer's core
            {
                bool firstTime = true;

                // Razmatraj samo ako je instanca consumer
                TaskInstance currentInstanceOnConsumersCore = instancesOnConsumersCore.at(consumerInstanceIndex);

                if (currentInstanceOnConsumersCore.getTask().getTaskId() == consumerTaskId)
                {


                    long long int startOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod;
                    long long int endOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod + consumerTaskPeriod;

                    // Vektor koji sadrzi sve potencijalno komunicirajuce parove za odabranu consumer instancu

                    IloExprArray consumerProducerPairVariablesForConsumer(environment);

                    consumerProducerPairVariablesForConsumer.clear();

                    // Provjeri da li se data read i data write intervali preklapaju

                    for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnProducersCore.size(); producerInstanceIndex++) // Prodji kroz sve instaance na jezgri proizvodjaca
                    {

                        // Biraj samo instance producera
                        TaskInstance currentInstanceOnProducersCore = instancesOnProducersCore.at(producerInstanceIndex);
                        if (currentInstanceOnProducersCore.getTask().getTaskId() == producerTaskId)
                        {

                            if (consumerCoreAssignedTo != producerCoreAssignedTo)
                            {
                                if (intervalsOverlap(0, producerTaskPeriod - producerExecutionTime, startOfConsumer + consumerExecutionTime, endOfConsumer) && firstTime)
                                {
                                    // Komunikacija je vec dodana
                                    firstTime = false;

                                    int lastProducerInstanceIndex = producerInstanceIndex;
                                    while (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() * instancesOnProducersCore.at(lastProducerInstanceIndex).getTask().getPeriod() != taskSets.at(producerCoreAssignedTo).getHyperperiod())
                                    {
                                        lastProducerInstanceIndex++;
                                    }

                                    long long int startOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod;
                                    long long int endOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                    int indexOfProducerTaskOnCore = 0;

                                    for (int k = 0; k < taskSets.at(producerCoreAssignedTo).getTasks().size(); k++)
                                    {
                                        if (taskSets.at(producerCoreAssignedTo).getTasks().at(k).getTaskId() == producerTaskId)
                                        {
                                            indexOfProducerTaskOnCore = k;
                                        }
                                    }


                                    // Za extra instance iz prethodnog hiperperioda

                                    int indexOfExtraInstance = 0;

                                    for (int indexOfExtraWriteInstance = 0; indexOfExtraWriteInstance < extraWriteInstances.at(producerCoreAssignedTo).getSize(); indexOfExtraWriteInstance++)
                                    {

                                        // Kreiraj ime radi poredjenja
                                        string name = createIntervalVariableName(instancesOnProducersCore.at(lastProducerInstanceIndex).getName(), "EXTRA");

                                        string extraInstanceName = extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].getName();
                                        if (name.c_str() == extraInstanceName.c_str())
                                        {
                                            indexOfExtraInstance = indexOfExtraWriteInstance;
                                        }
                                    }

                                    // Kreiraj Z ogranicenja prema nacinu opisanom u tezi

                                    IloExpr zi(environment);

                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance]);
                                    brojIloStartOf++;
                                    model.add(zi);
                                    brojZ++;

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.add(zi);


                                }

                                // Kreiraj Z ogranicenja prema nacinu opisanom u tezi



                                long long int startOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod;
                                long long int endOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                if (canCommunicate(currentInstanceOnProducersCore, currentInstanceOnConsumersCore))
                                {

                                    IloExpr zi(environment);


                                    zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * producerInstanceIndex + 2]);

                                    model.add(zi);
                                    brojZ++;
                                    brojIloStartOf++;

                                    consumerProducerPairVariablesForConsumer.add(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.add(zi);

                                    long long int lowerBound = startOfConsumer - endOfProducer;
                                }

                            }


                        }

                    }

                    // 24. Kreiraj H varijable
                    // Dodatna -1 varijabla za lakse odredjivanja helpera
                    IloExpr MinusOne(environment);
                    MinusOne += -1;
                    consumerProducerPairVariablesForConsumer.add(MinusOne);



                    for (int consumerProducerPairIndex = 0; consumerProducerPairIndex < consumerProducerPairVariablesForConsumer.getSize() - 1; consumerProducerPairIndex++)
                    {

                        IloIntVar helperVar(environment, 0, 4 * hyperPeriod);


                        // Ako je slijedeca Z varijabla negativna, ovo je najmanja Zi vrijednost, postavi Hi = Zi
                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1] < 0, helperVar == consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex]));
                        brojIloIfThen++;

                        // Ako je sljedeca Z varijabla pozitivna ovo jos uvijek nije najmanja Zi vrijednost, postavi Hi = 0
                        model.add(IloIfThen(environment, consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1] >= 0, helperVar == 0));
                        brojIloIfThen++;
                        helper.add(helperVar);
                        brojHelper++;


                    }


                }

            }
        }

    }

    // 25. Kreiraj funkciju cilja
    IloExpr objectiveFunction(environment);


    objectiveFunction = IloSum(helper);


    model.add(objectiveFunction >= 0);




    // 26. Kreiraj multivarijabilnu funkciju cilja

    if (maximumInterCoreDelay != -1)
    {

        model.add(objectiveFunction <= maximumInterCoreDelay);

        IloObjective objective = IloMinimize(environment, objectiveFunction);


        model.add(objective);

    }
    else
    {
        /* Ako je potrebno minimizarti i vremena odziva
            Kreira se i dodatna funkcija cilja,
            alat prvo pronalazi rasporede sa minimalnim medjujezgrenim kasnjenjem
            a zatim od tih rasporeda bira one sa najmanjim vremenom odziva
        */

        if (minimizeResponseTimes)
        {
            IloExpr responseTimes = IloSum(responseTimeDecisionVariables);


            IloObjective responsePlusInterCore = IloMinimize(environment, IloStaticLex(environment, objectiveFunction, responseTimes));

            model.add(responsePlusInterCore);
        }
        else
        {

            IloObjective objective = IloMinimize(environment, objectiveFunction);

        }


    }


    IloCP cp(model);


    cp.setParameter(IloCP::SearchType, IloCP::IterativeDiving);


    cp.setParameter(IloCP::Presolve, IloCP::On);

    cp.setParameter(IloCP::TimeLimit, timeLimit);


    for (int i = 0; i < taskSets.size(); i++)
    {
        cp.out() << "Tasks on core " << i << ": " << std::endl;

        for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
        {
            cp.out() << taskSets.at(i).getTasks().at(j);
        }
    }

    for (int i = 0; i < taskChains.size(); i++)
    {
        cp.out() << "Chain " << i << ": " << std::endl;

        cp.out() << taskChains.at(i);

    }

    // Incijaliziraj vrijeme
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point end;

    if (cp.solve())
    {

        numberOfConstraints = cp.getInfo(IloCP::NumberOfConstraints);

        cp.end();

        return 0;

        std::cout << cp.getTime() << std::endl;

        end = std::chrono::steady_clock::now();
        if (cp.getStatus() == IloAlgorithm::Optimal)
        {
            status = 0;
        }
        else
        {
            status = 0;
        }


        cp.out() << "SOLUTION FOUND." << std::endl;

        for (IloInt core = 0; core < numberOfCores; core++)
        {
            bool first = true;

            for (IloInt i = 0; i < numberInstancesCore.at(core) * NUMBER_OF_PHASES; i++)
            {
                if (first)
                {
                    first = false;

                    //cp.out() << "************ CORE " << core << " ************" << std::endl;
                }

                //cp.out() << cp.domain(phasesOfInstancesOnCore.at(core)[i]) << std::endl;

            }

        }

        bool first = true;
        for (IloInt i = 0; i < consumerProducerPairVariablesForConsumerGlobal.getSize(); i++)
        {
            if (first)
            {
                first = false;

                //cp.out() << "************ Z_i: " << " ************" << std::endl;
            }

            //cp.out() << consumerProducerPairVariablesForConsumerGlobal[i] << ": " << cp.getValue(consumerProducerPairVariablesForConsumerGlobal[i]) << std::endl;

        }

        first = true;
        for (IloInt i = 0; i < responseTimeDecisionVariables.getSize(); i++)
        {
            if (first)
            {
                first = false;

                //cp.out() << "************ responseTimes: " << " ************" << std::endl;
            }

            //cp.out() << i << ": " << cp.getValue(responseTimeDecisionVariables[i]) << std::endl;

        }

        first = true;
        for (IloInt i = 0; i < helper.getSize(); i++)
        {
            if (first)
            {
                first = false;

                //cp.out() << "************ helper: " << " ************" << std::endl;
            }

            //cp.out() << i << ": " << cp.getValue(helper[i]) << std::endl;

        }

    }

    else
    {

        numberOfConstraints = cp.getInfo(IloCP::NumberOfConstraints);
        cp.end();
        return 0;
        end = std::chrono::steady_clock::now();
        cp.out() << "Model has no solution." << std::endl;
        status = -1;
    }


    numberOfConstraints = cp.getInfo(IloCP::NumberOfConstraints);

    cp.end();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}


