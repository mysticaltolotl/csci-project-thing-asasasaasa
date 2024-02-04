#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {

    string line;

    if (input.is_open()) // check that this file exists
    {
        // TODO 2:  Read each line from the file
        //          for each line do the following
        //               extract name, extract email, exract birthday
        //               call the addAemployee function to add them in the array
        while (getline(input, line))
        {
            stringstream ss(line);
            string word;
            int number = 0;
            if(line.size() != 0)
            {
                stringstream instring(line);
                getline(instring, name, ',');
                getline(instring, emailid, ',');
                getline(instring, birthday, ',');
                addAnEmployee(array, name, birthday, emailid, length);
                length++;
            }
        }
    }
    else
    {
        cout << "err: can not open file" << endl;
    }
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
    //TODO
    return false;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {

    int *newArray = new AirlinePassenger[arraySize*2];

    for (int q = 0; q < arraySize; q++) {

        newArray[q] = passengers[q];
    }
    delete[] passengers;

    array = dbl;
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    if(recordIdx == arrCapacity)
    {
        resizeArr(passengers, arrCapacity);
        doublingCounter++;
    }

    passengers[recordIdx] = airlinePassenger;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {
    //TODO
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    //TODO
}
