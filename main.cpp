#include<stdio.h>
#include<iostream>

#include "prototypes.h"

using namespace std;
 
int main(int argc, char *argv[])
{
	if(argc<4)
 	{
 		cout<<"Invalid Parameters ! Please See Readme.txt For More Information."<<endl;
 		exit(0);
	}
	
    prototypes t1(argv[1], argv[2], argv[3],argv[4]);
    
    //prototypes t1("Bands.txt", "Judges.txt", "Musicians.txt","output");
    
    //calculate required parameteres
    t1.CalculateBandPotentialAndVariability();
    //write basic info to file
    t1.WriteToFile();
    //play
    t1.Play();
    
	cout<<"Shutting Down."<<endl;
	return 0;
}
