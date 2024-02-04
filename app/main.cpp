#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;


int main(int argc, char* argv[])
{

    int arrCapacity = 10;
    int recordIdx;
    int doublingCounter;

    string *args = new string[5];
    AirlinePassenger *passengers = new AirlinePassenger[arrCapacity];

    for (int q = 0; q < 5; ++q)
    {
        args[q] = argv[q];
    }

    ifstream input;

    parseFile(input, args[], *passengers, arrCapacity, recordIdx, doublingCounter);


    //TODO
    return 0;
}