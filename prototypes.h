#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>


#ifndef prototypes_H
#define prototypes_H

struct BandReport {
  std::string Name;
  int Potential;
  int Variability;
};


struct Musicians {
  char Letter;
  std::string Name;
  int c1,c2,c3;
};

struct Judges {
  std::string Name;
  int c1,c2;
};

struct Bands {
 std::string Tag;
 std::string Code;
};

class prototypes
{
     private :
     	 std::ifstream bandsFile;
     	 std::ifstream judgeFile;
     	 std::ifstream musicianFile;
     	 
     	 std::ofstream writeToFile;
     	 
     	 std::vector<struct Bands> bands;
     	 std::vector<struct Judges> judges;
     	 std::vector<struct Musicians> musicians;
     	 
     	 std::vector<struct BandReport> bandReport;
     	 
     	 char* outputFileName;
     	 
     	 void InitializeBands();
     	 void InitializeJudges();
     	 void InitializeMusicians();
     public :
     	prototypes(char* _bands,char* _judges, char* _musicians,char* output);
     	void CalculateBandPotentialAndVariability();
     	void WriteToFile();
		void Play();
};
 
#endif
