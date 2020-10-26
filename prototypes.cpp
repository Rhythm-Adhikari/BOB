#include <iostream>
#include <iomanip>
#include <vector> 
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <time.h>
#include <algorithm>
#include "prototypes.h"

using namespace std;
 
prototypes :: prototypes(char* _bands,char* _judges, char* _musicians,char* output) 
{
	writeToFile.open(output,ios::app);
//	std::ifstream bandsFile(_bands);
	bandsFile.open(_bands); 
	cout<<"Reading Bands..."<<endl;
	InitializeBands();
	judgeFile.open(_judges); 
	
	cout<<"Reading Judges..."<<endl;
	InitializeJudges();
	musicianFile.open(_musicians);
	
	cout<<"Reading Musicians..."<<endl;
	InitializeMusicians();
	outputFileName=output;
}
void prototypes :: WriteToFile()
{
 	if (writeToFile.is_open())
  	{
  		for(int i=0;i<bandReport.size();i++)
  		{
    		writeToFile.seekp (0, ios::end);
    		writeToFile <<"Name: "<<bandReport[i].Name << " Potential: "<<bandReport[i].Potential<<" Variability:"<<bandReport[i].Variability<<"\n";
		}
	//	cout<<"Successfuly written to file."<<endl;
  	}
  	else
  	{
  		cout<<"Error On File Operation While Writing Results."<<endl;
	  }
}
void prototypes :: Play()
{
	int overallBandVariability=0;
	int overallBandPotential=0;
	int toughnessofJudge=0;
	int randomScore=0;
	int randomScore1=0;
	for(int i=0;i<bandReport.size();i++)
	{
		overallBandVariability+=bandReport[i].Variability;
		overallBandPotential+=bandReport[i].Potential;
	}
	for(int i=0;i<judges.size();i++)
	{
		toughnessofJudge+=judges[i].c1;
	}
	//for mean measurement
	//overallBandPotential/=bandReport.size();
	toughnessofJudge/=judges.size();
	for(int i=0;i<bandReport.size();i++)
	{
		srand (time(NULL));
  		randomScore = rand() % 100 + 1;
		int totalScore=0;
		int passCount=0;
		int tempScore=0;
		//calculating score
		tempScore=(randomScore-overallBandPotential)/overallBandVariability;
		for(int j =0;j<judges.size();j++)
		{
			srand (time(NULL));
  			randomScore1 = rand() % 100 + 1;
  			if(judges[j].c2==0)
  			judges[j].c2=1;
			int threshold=(randomScore1-judges[i].c1)/judges[j].c2;
			if(tempScore>=threshold)
			{
				++passCount;
    			writeToFile.seekp (0, ios::end);
    			writeToFile <<"Band Name: "<<bandReport[i].Name<<" Judge Name : "<<judges[j].Name
				<<" Threshold: "<<threshold<<" Result: "<<"PASS"<<"\n";
			}
			else{
    			writeToFile.seekp (0, ios::end);
    			writeToFile <<"Band Name: "<<bandReport[i].Name<<" Judge Name : "<<judges[j].Name
				<<" Threshold: "<<threshold<<" Result: "<<"FAIL"<<"\n";
			}
		}
		float proportion=passCount/judges.size()*100;
		if(proportion<0)
		{
			cout<<"Band Name: "<<bandReport[i].Name<<" Award : "<<"No award"<<endl;
				if (writeToFile.is_open())
  				{
    				writeToFile.seekp (0, ios::end);
    				writeToFile <<"Band Name: "<<bandReport[i].Name<<" Award : "<<"No award"<<endl;
  				}
		}
		else if(proportion<20)
		{
				cout<<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Bronze award"<<endl;
				if (writeToFile.is_open())
  				{
    				writeToFile.seekp (0, ios::end);
    				writeToFile <<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Bronze award"<<endl;
  				}
		}
		else if(proportion<50)
		{
				cout<<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Silver award"<<endl;
				if (writeToFile.is_open())
  				{
    				writeToFile.seekp (0, ios::end);
    				writeToFile <<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Silver award"<<endl;
  				}
		}
		else if(proportion<80)
		{	
			cout<<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Gold award"<<endl;
				if (writeToFile.is_open())
  				{
    				writeToFile.seekp (0, ios::end);
    					writeToFile <<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Gold award"<<endl;
  				}
		}
		else if(proportion<=100)
		{
			cout<<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Platinum award"<<endl;
				if (writeToFile.is_open())
  				{
    				writeToFile.seekp (0, ios::end);
    				writeToFile <<"Band Name: "<<bandReport[i].Name<<" Award : "<<"Platinium award"<<endl;
  				}
		}
	}
 
}
void prototypes :: CalculateBandPotentialAndVariability()
{
	for (int i = 0; i < bands.size(); i++) { 
        struct BandReport tempReport;
        int potential=0;
        int variability=0;
        int temp=0;
        int temp1=0;
        int temp2=0;
        int counter=0;
        for(int j=0;j<bands[i].Code.size();j++)
        {
        	if(isdigit(bands[i].Code[j])==false)
        	{
        		for(int k =0;k<musicians.size();k++)
        		{
        			if(musicians[k].Letter==bands[i].Code[j])
        			{
        				temp=musicians[k].c2;
        				temp1=musicians[k].c3;
        				break;
					}
				}
			}
			else
			{
				temp2=(int)bands[i].Code[j]-48;
			}
			if(counter==1)
			{
				potential+=temp*temp2;
				variability+=temp1*temp2;
				counter=0;
			}
			counter++;
		}
		potential+=30;
		variability+=5;
		if(potential>100)
			potential=100;
		tempReport.Name=bands[i].Tag;
		tempReport.Potential=potential;
		tempReport.Variability=variability;
		bandReport.push_back(tempReport);
    }
}
void prototypes :: InitializeBands()
{
	string line;
	string substr1;
	if (bandsFile.is_open())
  	{
    	while ( getline (bandsFile,line))
    	{
    		struct Bands temp;
      		stringstream s_stream(line); 
	  		int i=0;
  			while(s_stream.good() && i<2) {
     		 	getline(s_stream, substr1, ':'); 
     		 	if(i==0)
     		 		temp.Tag=substr1;
     		 	if(i==1)
     		 	{
     		 		stringstream tt(substr1);
     		 		getline(tt, substr1, '.');
     		 		temp.Code=substr1;
				}
	  			i++;
    		}
    		bands.push_back(temp);
  		}
	}else
	{
		cout<<"Invalid File Supplied..."<<endl;
		exit(0);
	}
}

void prototypes :: InitializeJudges()
{
	string line;
	string substr1;
	if (judgeFile.is_open())
  	{
    	while ( getline (judgeFile,line))
    	{
    		struct Judges temp;
      		stringstream s_stream(line); 
	  		int i=0;
  			while(s_stream.good() && i<3) {
     		 	getline(s_stream, substr1, ':'); 
     		 	if(i==0)
     		 		temp.Name=substr1;
     		 	else if(i==1)
     		 	{
     		 		stringstream ss(substr1);
   					ss >> temp.c1;
				}
				else if(i==2)
     		 	{
     		 		stringstream tt(substr1);
     		 		getline(tt, substr1, '.');
     		 		stringstream ss(substr1);
   					ss >> temp.c2;
				}
	  			i++;
    		}
    		judges.push_back(temp);
  		}
	}else
	{
		cout<<"Invalid File Supplied..."<<endl;
		exit(0);
	}
}

void prototypes :: InitializeMusicians()
{
	string line;
	string substr1;
	if (musicianFile.is_open())
  	{
    	while ( getline (musicianFile,line))
    	{
    		struct Musicians temp;
      		stringstream s_stream(line); 
	  		int i=0;
  			while(s_stream.good() && i<5) {
     		 	getline(s_stream, substr1, ':'); 
     		 	if(i==0)
     		 		temp.Letter=substr1[0];
     		 	else if(i==1)
     		 	{
     		 		temp.Name=substr1;
				}
				else if(i==2)
     		 	{
     		 		stringstream ss(substr1);
   					ss >> temp.c1;
				}
				else if(i==3)
     		 	{
     		 		stringstream ss(substr1);
   					ss >> temp.c2;
				}
				else if(i==4)
     		 	{
     		 		stringstream tt(substr1);
     		 		getline(tt, substr1, '.');
     		 		stringstream ss(substr1);
   					ss >> temp.c3;
				}
	  			i++;
    		}
    		musicians.push_back(temp);
  		}
	}else
	{
		cout<<"Invalid File Supplied..."<<endl;
		exit(0);
	}
}
 
