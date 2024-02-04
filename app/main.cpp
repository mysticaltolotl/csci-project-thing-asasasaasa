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
    int recordIdx = 0;
    int doublingCounter = 0;

    string *args = new string[5];
    AirlinePassenger *passengers = new AirlinePassenger[arrCapacity];

    for (int q = 0; q < 5; ++q)
    {
        args[q] = argv[q];
    }

    ifstream input;

    input.open(argv[1]);

    parseFile(input, args, passengers, arrCapacity, recordIdx, doublingCounter);

    return 0;
}