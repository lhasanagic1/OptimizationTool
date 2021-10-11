# Optimizacijski alat

Optimizacijski alat napisan u C++ programskom jeziku koji kreira problem matematičkog programiranja sa ograničenjima, a korištenjem IBM ILOG CP Optimizer softverske biblioteke, na osnovu ulaznih parametara koji karakterišu ugradbenu aplikaciju u realnom vremenu. Optimizacijski alat na svom izlazu daje raspored izvršavanja aplikacije za svako od jezgara koji je optimizovan u odnosu na među-jezgrena kašnjenja. Pored optimizacijskog alata, implementiran je i sintetički generator testova kako bi se evaluirala performansa alata.

# Upute za korištenje optimizacijskog alata (Visual Studio):

1. Preuzeti i otpakovati CPLEX CP Optimizer paket dostupan na web-stranici (https://www.ibm.com/analytics/cplex-cp-optimizer).
2. Preuzeti optimizacijski alat s GitHub-a
3. Otvoriti rješenje u Visual Studio-u
4. U Project->Properties->C/C++->Additional Include Directories dodati put do \IBM\ILOG\CPLEX_Studio1210\concert\include, \IBM\ILOG\CPLEX_Studio1210\cpoptimizer\include i \IBM\ILOG\CPLEX_Studio1210\cplex\include 
5. U Project->Properties->C/C++->Preproccessor dodati pretprocesorsku definiciju: IL_STD
6. U Project->Properties->Linker->General->Additional Library Dependencies dodati put do:  IBM\ILOG\CPLEX_Studio1210\cpoptimizer\lib\x64_windows_msvc14\stat_mda, IBM\ILOG\CPLEX_Studio1210\concert\lib\x64_windows_msvc14\stat_mda and IBM\ILOG\CPLEX_Studio1210\cplex\lib\x64_windows_msvc14\stat_mda
7. U Project->Properties->Linker->->Input->Additional Dependencies dodati:  cplex12100.lib, ilocplex.lib, concert.lib and cp.lib








