#include "array_double.hpp"
#include <sstream>
#include <iostream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger*& passengers, int& arrCapacity, int& recordIdx, int& doublingCounter) {

	string line;

	AirlinePassenger tempPassenger;

	if (input.is_open()) // check that this file exists
	{
		while (getline(input, line))
		{
			stringstream ss(line);
			string word;
			int number = 0;
			if (line.size() != 0)
			{
				stringstream instring(line);
				getline(instring, tempPassenger.name, ',');
				getline(instring, tempPassenger.airline, ',');
				getline(instring, tempPassenger.location, ',');
				string ageTemp;
				getline(instring, ageTemp, ',');
				tempPassenger.age = stoi(ageTemp);
				recordIdx++;
				addPassenger(passengers, tempPassenger, arrCapacity, recordIdx, doublingCounter);

			}
		}
	}
	else
	{
		cout << "err: can not open file" << endl;
	}

    AirlinePassenger *queriedPassengers = new AirlinePassenger[2];
    int finalArrCapacity = 2;
    int finalRecordIdx = 0;
    int finalDoublingCounter = 0;

    int ageStart, ageEnd;
    stringstream strValue;
    stringstream strValue2; //keeps the first stringstream from polluting ageEnd, dunno if this is neccessary

    strValue << queryParams[4];
    strValue >> ageStart;

    strValue2 << queryParams[5];
    strValue2 >> ageEnd;

    for(int q = 0; q < arrCapacity; q++)
    {
        if(isPassengerQueried(passengers[q], queryParams[2], queryParams[3], ageStart, ageEnd))
        {
            addPassenger(queriedPassengers, passengers[q], finalArrCapacity, finalRecordIdx, finalDoublingCounter);
            finalRecordIdx++;
        }
    }
  
    printQueriedPassengers(queriedPassengers, finalRecordIdx);
}

/**
 * Checks if the passenger has their age in
 * the queried age range, and their location and
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
	if (passenger.location == queryLocation)
	{
		if (passenger.airline == queryAirline)
		{
			if (passenger.age >= startAge && passenger.age <= endAge)
			{
				return true;
			}
		}
	}
	return false;
}

/**
 * Takes in a reference to an array of structs (passengers)
 * and the current arrayCapacity. It doubles the size
 * of the array by making a new array of size the current
 * size and copying the elements of the old one.
 */
void resizeArr(AirlinePassenger*& passengers, int* arraySize) {

	AirlinePassenger* newArray = new AirlinePassenger[*arraySize * 2];

	for (int q = 0; q < *arraySize; q++) {

		newArray[q] = passengers[q];
	}
    *arraySize *= 2;
	delete[] passengers;

	passengers = newArray;
}

/**
 * Append the new record to the passengers array. Here we double the
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger*& passengers, AirlinePassenger airlinePassenger, int& arrCapacity, int& recordIdx, int& doublingCounter) {
	if (recordIdx == arrCapacity)
	{
		resizeArr(passengers, &arrCapacity);
		doublingCounter++;
	}

	passengers[recordIdx] = airlinePassenger;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger* passengers, int length) {

	for (int q = 0; q < length - 1; q++)
	{
		for (int r = 0; r < length - q - 1; r++)
		{
			if (passengers[r].age < passengers[r + 1].age)
			{
				swap(passengers[r], passengers[r + 1]);
			}
			else if (passengers[r].age == passengers[r + 1].age)
			{
				for (int s = 0; s < passengers[r].name.length() - 1; s++)
				{
					if (passengers[r].name[s] > passengers[r + 1].name[s])
					{
						swap(passengers[r], passengers[r + 1]);
					}
				}
			}
		}
	}
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger* passengers, int numOfRecords) {
	sortPassengers(passengers, numOfRecords);
	//cout << "Array doubled: 0" << endl;
	//cout << "Total number of passengers returned after the query: " << numOfRecords << endl;
	cout << "Queried Passengers" << endl;
	cout << "---------------------------------------" << endl;
	for (int i = 0; i < numOfRecords; ++i) {
		cout << passengers[i].name << " " << passengers[i].age << endl;
	}
}