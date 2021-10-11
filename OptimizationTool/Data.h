#include "TaskSet.h"
#include "TaskChain.h"
#include <vector>

#pragma once

// TEMPLATE:

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka:
	- Harmonijski ili neharmonijski:
	- Cirkularni ili semi-cirkularni:
	- Jednojezgreni ili Višejezgreni:
	- Jedan lanac ili više lanaca:
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje:
*/

std::vector<TaskSet>  TestCase1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase5(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase6_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase7(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase8(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Isti period
*/
std::vector<TaskSet>  TestCase10_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase10_5(std::vector<TaskChain>& chains);



/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Independent and Chains
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Semi Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/


std::vector<TaskSet> TestCase11_1(std::vector<TaskChain>& chains);

std::vector<TaskSet> TestCase11_2(std::vector<TaskChain>& chains);

std::vector<TaskSet> TestCase11_3(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase12_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase12_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase12_3(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Oboje
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Semi Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase13_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_3(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_4(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase13_5(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase14_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase14_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase14_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/

std::vector<TaskSet>  TestCase15_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase15_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase15_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Oboje
*/

std::vector<TaskSet>  TestCase16_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase16_2(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Oboje
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Oboje
*/

std::vector<TaskSet>  TestCase17_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase17_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase17_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase18_1(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/

std::vector<TaskSet>  TestCase19_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase19_2(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Oboje
*/
std::vector<TaskSet>  TestCase20_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase20_2(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Oboje
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/

std::vector<TaskSet>  TestCase21_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase21_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase21_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Oboje
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase22_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase22_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase22_3(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Prekomjerno uzorkovanje
*/

std::vector<TaskSet>  TestCase23_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase23_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase23_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/

std::vector<TaskSet>  TestCase24_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase24_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase24_3(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Oboje
*/

std::vector<TaskSet>  TestCase25_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase25_2(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Oboje
	- Harmonijski ili neharmonijski: Harmonijski
	- Cirkularni ili semi-cirkularni: Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Više lanaca
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Isti period
*/

std::vector<TaskSet>  TestCase26_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase26_2(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase26_3(std::vector<TaskChain>& chains);


/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Nedovoljno uzorkovanje
*/

std::vector<TaskSet>  TestCase27_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase27_2(std::vector<TaskChain>& chains);

/* Testni slucajevi sa sljedecim karakteristikama:
	- Tip zadataka: Samo lanci
	- Harmonijski ili neharmonijski: Neharmonijski
	- Cirkularni ili semi-cirkularni: Semi-Cirkularni
	- Jednojezgreni ili Višejezgreni: Višejezgreni
	- Jedan lanac ili više lanaca: Jedan lanac
	- Prekomjerno uzorkovanje ili Nedovoljno uzorkovanje: Oboje
*/

std::vector<TaskSet>  TestCase28_1(std::vector<TaskChain>& chains);

std::vector<TaskSet>  TestCase28_2(std::vector<TaskChain>& chains);



// Industrijski testni slucaj koristen za industrijski studiji slucaja

std::vector<TaskSet>  TestCaseIndustrial(std::vector<TaskChain>& chains);