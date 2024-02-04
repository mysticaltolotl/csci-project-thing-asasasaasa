#ifndef READFILE_H__
#define READFILE_H__

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct AirlinePassenger 
{
	string name;
	string airline;
	string location;
	int age;
};

void parseFile(ifstream& input,string queryParams[], AirlinePassenger *&passengers, int &arrCapacity,  int &recordIdx, int &doublingCounter);
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge);
void resizeArr(AirlinePassenger *&passengers, int *arraySize);
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter);
void sortPassengers(AirlinePassenger *passengers, int length);
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords);

#endif // READFILE_H__
