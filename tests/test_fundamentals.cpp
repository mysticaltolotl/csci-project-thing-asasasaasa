// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/array_double.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <iomanip>

using namespace std;

class test_arrayDouble : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_arrayDouble::total_grade = 0;
double test_arrayDouble::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

bool compare_arrays(string a[], string b[], int size){
  bool pass = true;
  for(int i = 0; i<size; ++i){
    if(a[i] != b[i])
      pass = false;
  }
  return pass;
}

void compare_arrays_structs(AirlinePassenger a[], AirlinePassenger b[], int size){
  for(int i = 0; i<size; ++i){
	  ASSERT_EQ(a[i].name, b[i].name) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].age, b[i].age) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].location, b[i].location) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].airline, b[i].airline) << "Array differs at index i=" << i;
  }
  return;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void genStructArray(AirlinePassenger *&structArray, string nameArray[], int ages[], string locArray[], string airlineArray[], int l){
	for(int i = 0; i<l; i++){
		AirlinePassenger newstruct = AirlinePassenger();
		newstruct.name = nameArray[i];
		newstruct.age = ages[i];
		newstruct.location = locArray[i];
		newstruct.airline = airlineArray[i];
		structArray[i] = newstruct;
	}
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

std::string readFileInto(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////


/////////////////////////////////////////
// Test Case Variables Start Here
/////////////////////////////////////////
//Example Case
AirlinePassenger examplePassenger = {"Brock Parrish","Southwest","SanFrancisco",43};


string array_A_names_unsorted[] = {"Jane Doe", "Dorcey M", "Katrina Teressa", "Zack Snyder", "James Kimmel"};
int array_A_ages_unsorted[] = {24, 36, 54, 23, 45};
string array_A_locations_unsorted[] = {"Boulder", "Atlanta", "Aspen", "CopperMountain", "WinterPark"};
string array_A_airlines_unsorted[] = {"Southwest", "Delta", "United", "American", "Frontier"};
int testArrLength_A = 5;

string array_A_names_sorted[] = {"Katrina Teressa", "James Kimmel", "Dorcey M", "Jane Doe", "Zack Snyder"};
int array_A_ages_sorted[] = {54, 45, 36, 24, 23};
string array_A_locations_sorted[] = {"Aspen", "WinterPark", "Atlanta", "Boulder", "CopperMountain"};
string array_A_airlines_sorted[] = {"United", "Frontier", "Delta", "Southwest", "American"};
  
string array_B_names_unsorted[] = {"Jane Doe", "Dorcey M", "Katrina Teressa", "Zack Dane", "James Kimmel",  
                 "Jake Black", "Judy Duty", "Belatrix Honors", "Harry Triplets", "Adam Eve",
                "Alan Turing", "Trevor Adams", "Amy Green", "Sheldon MacBeth", "Ron Snape"};
int array_B_ages_unsorted[] = {36, 54, 23, 45, 33, 
                         12, 19, 89, 65, 71,
                         23, 87, 67, 34, 34};
string array_B_locations_unsorted[] = {"CopperMountain", "WinterPark", "Eldora", "A-Basin", "Lake Tahoe", 
                              "Aspen", "Loveland", "Vail", "Breckenridge", "Boulder", 
                             "SanFrancisco", "San Jose", "San Diego", "LA", "New York"};
string array_B_airlines_unsorted[] = {"Southwest", "Delta", "United", "American", "Frontier", 
                             "Southwest", "Delta", "United", "American", "Frontier",
                            	"Southwest", "Delta", "United", "American", "Frontier"};
int testArrLength_B = 15;

string array_B_names_sorted[] = {"Belatrix Honors", "Trevor Adams", "Adam Eve", "Amy Green", "Harry Triplets", "Dorcey M", "Zack Dane", "Jane Doe", "Ron Snape", "Sheldon MacBeth",
 "James Kimmel", "Alan Turing", "Katrina Teressa", "Judy Duty", "Jake Black"};
int array_B_ages_sorted[] = {89, 87, 71, 67, 65, 54, 45, 36, 34, 34, 33, 23, 23, 19, 12};
string array_B_locations_sorted[] = {"Vail", "San Jose", "Boulder", "San Diego", "Breckenridge", "WinterPark", "A-Basin", "CopperMountain", "New York", "LA",
 "Lake Tahoe","SanFrancisco", "Eldora", "Loveland", "Aspen"};
string array_B_airlines_sorted[] = {"United", "Delta", "Frontier", "United", "American", "Delta", "American", 
"Southwest", "Frontier", "American", "Frontier", "Southwest", "United", "Delta", "Southwest"};

//TODO: Update these prints based on the print function of latest
string array_A_print = "Queried Passengers\n---------------------------------------\nKatrina Teressa 54\nJames Kimmel 45\nDorcey M 36\nJane Doe 24\nZack Snyder 23\n";
string array_B_print = "Queried Passengers\n---------------------------------------\nBelatrix Honors 89\nTrevor Adams 87\nAdam Eve 71\nAmy Green 67\nHarry Triplets 65\nDorcey M 54\nZack Dane 45\nJane Doe 36\nRon Snape 34\nSheldon MacBeth 34\nJames Kimmel 33\nAlan Turing 23\nKatrina Teressa 23\nJudy Duty 19\nJake Black 12\n";

/////////////////////////////////////////
// Test Case Variables End Here
/////////////////////////////////////////


// Test the isPassengerQueried() function [10 POINTS]
TEST_F(test_arrayDouble, TestIsPassengerQueried){
	bool isValid;

	// test case 1: check for happy path
	isValid = isPassengerQueried(examplePassenger, "SanFrancisco", "Southwest", 40, 50);
	ASSERT_EQ(true, isValid);
	add_points_to_grade(2);
  
  	// test case 2: check for invalid location error path
  	isValid = isPassengerQueried(examplePassenger, "Denver", "Southwest", 40, 50);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 3: check for invalid airline error path
  	isValid = isPassengerQueried(examplePassenger, "SanFrancisco", "Delta", 40, 50);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 4: check for invalid startAge error path
  	isValid = isPassengerQueried(examplePassenger, "SanFrancisco", "Southwest", 45, 50);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 5: check for invalid endAge error path
	isValid = isPassengerQueried(examplePassenger, "SanFrancisco", "Southwest", 35, 42);

	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
}


// Test the resizeArr() function [14 POINTS]
TEST_F(test_arrayDouble, TestResizeArr){
	// Generate an unsorted array of structs:
	AirlinePassenger* testArr_A = new AirlinePassenger[testArrLength_A];
	// AirlinePassenger* testArr_A = new AirlinePassenger[testArrLength_A];
	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
					array_A_locations_unsorted, array_A_airlines_unsorted, testArrLength_A);
	int initialArrCapacity_A = testArrLength_A;
	//double the array
	resizeArr(testArr_A, &testArrLength_A);
	// Compare the array length:
	ASSERT_EQ(testArrLength_A, initialArrCapacity_A * 2) << "Array has incorrect length";
	add_points_to_grade(7);
	delete[] testArr_A;
	AirlinePassenger* testArr_B = new AirlinePassenger[testArrLength_B];
	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
					array_B_locations_unsorted, array_B_airlines_unsorted, testArrLength_B);
	int initialArrCapacity_B = testArrLength_B;
	//double the array
	resizeArr(testArr_B, &testArrLength_B);
	// Compare the array length:
	ASSERT_EQ(testArrLength_B, initialArrCapacity_B * 2) << "Array has incorrect length";
	add_points_to_grade(7);
	delete[] testArr_B;
	// check if resize did its job ! , check if the elements are all completely copied, and size is doubled, 1 point for 0 case. 
}


// Test the addPassenger() function [20 POINTS]
TEST_F(test_arrayDouble, TestAddPassenger){
	testArrLength_A = 5;
	testArrLength_B = 15;
	
	//Test Case 1: Array is not full yet; add a new case
  	AirlinePassenger* testArr_A = new AirlinePassenger[testArrLength_A + 5];
	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
  					array_A_locations_unsorted, array_A_airlines_unsorted, testArrLength_A);
	int initialArrCapacity_A = testArrLength_A + 5;
	int recordIndex = 5;
	int doubleCounter = 0;
  
  	addPassenger(testArr_A, examplePassenger, initialArrCapacity_A, recordIndex, doubleCounter);
  	ASSERT_EQ(testArrLength_A + 5, initialArrCapacity_A) << "Array has incorrect length";
  	ASSERT_EQ(doubleCounter, 0) << "New Case hasn't been added to the array";
  	add_points_to_grade(10);


  	//Test Case 2: Array is full; add a new case
  	AirlinePassenger* testArr_B = new AirlinePassenger[testArrLength_B];
	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
  					array_B_locations_unsorted, array_B_airlines_unsorted, testArrLength_B);
	int initialArrCapacity_B = testArrLength_B;
	recordIndex = 15;

  	addPassenger(testArr_B, examplePassenger, testArrLength_B, recordIndex, doubleCounter);
	ASSERT_EQ(testArrLength_B, initialArrCapacity_B * 2) << "Array has incorrect length";
	ASSERT_EQ(doubleCounter, 1) << "New case hasn't been added to the array";
  	add_points_to_grade(10);
}


// Test the sortPassengers() function [10 POINTS]
TEST_F(test_arrayDouble, TestSortPassengers){
	testArrLength_A = 5;
	testArrLength_B = 15;

	// Generate an unsorted array of structs:
	AirlinePassenger* testArr_A = new AirlinePassenger[testArrLength_A];
  	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
  					array_A_locations_unsorted, array_A_airlines_unsorted, testArrLength_A);
  
	// Sort the array to test if sortArray() is working
	sortPassengers(testArr_A, testArrLength_A);
	// Generate the correctly sorted array of structs:
	AirlinePassenger* sortedArrayOfStructs_A = new AirlinePassenger[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_names_sorted, array_A_ages_sorted, 
  					array_A_locations_sorted, array_A_airlines_sorted, testArrLength_A);
	
  	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_A), sizeof(sortedArrayOfStructs_A)) << "Array has incorrect length";
	compare_arrays_structs(testArr_A, sortedArrayOfStructs_A, testArrLength_A);
	add_points_to_grade(5);
	delete[] testArr_A;
	delete[] sortedArrayOfStructs_A;

	// Generate an unsorted array of structs:
	AirlinePassenger* testArr_B = new AirlinePassenger[testArrLength_B];
  	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
  					array_B_locations_unsorted, array_B_airlines_unsorted, testArrLength_B);
	// Sort the array to test if sortArray() is working
	sortPassengers(testArr_B,testArrLength_B);		
	// Generate the correctly sorted array of structs:
	AirlinePassenger* sortedArrayOfStructs_B = new AirlinePassenger[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_names_sorted, array_B_ages_sorted, 
  					array_B_locations_sorted, array_B_airlines_sorted, testArrLength_B);
	
  	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_B), sizeof(sortedArrayOfStructs_B)) << "Array has incorrect length";
	compare_arrays_structs(testArr_B, sortedArrayOfStructs_B, testArrLength_B);
	add_points_to_grade(5);
	delete[] testArr_B;
	delete[] sortedArrayOfStructs_B;
}



// Test the printQueriedCases() function [6 POINTS]
TEST_F(test_arrayDouble, TestPrintQueriedPassengers){
	testArrLength_A = 5;
	testArrLength_B = 15;

	// Generate the correctly sorted array of structs:
	AirlinePassenger* sortedArrayOfStructs_A = new AirlinePassenger[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_names_sorted, array_A_ages_sorted, 
                	array_A_locations_sorted, array_A_airlines_sorted, testArrLength_A);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printQueriedPassengers(sortedArrayOfStructs_A, testArrLength_A);
	// Record the functions std output to a sting variable
	string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_A_print);
	add_points_to_grade(3);

	// Generate the correctly sorted array of structs:
	AirlinePassenger* sortedArrayOfStructs_B = new AirlinePassenger[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_names_sorted, array_B_ages_sorted, 
  					array_B_locations_sorted, array_B_airlines_sorted, testArrLength_B);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printQueriedPassengers(sortedArrayOfStructs_B, testArrLength_B);
	// Record the functions std output to a sting variable
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_B_print);
	add_points_to_grade(3);
}

// Test the main() function [40 POINTS]
TEST_F(test_arrayDouble, TestApp){
  
	string desired = readFileIntoString("../tests/expected_1.txt");
	string resp = exec("./run_app ../tests/passengers_1.txt Boulder Delta 20 40");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_2.txt");
	resp = exec("./run_app ../tests/passengers_2.txt Eldora Delta 20 60");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_3.txt");
	resp = exec("./run_app ../tests/passengers_3.txt Chicago Southwest 20 90");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_4.txt");
	resp = exec("./run_app ../tests/passengers_4.txt Boston American 20 90");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);
}

