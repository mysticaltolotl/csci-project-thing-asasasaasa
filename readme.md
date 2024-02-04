# CSCI 2270 – Data Structures - Assignment 2: Array Doubling with Dynamic Memory

## Objectives

1. Read a file with an unknown size and store its contents in a dynamically allocated array
2. Store, search, and iterate through data in an array of structs
3. Use array doubling via dynamic memory to increase the size of the array

## Instructions

You are given a text file with a list of passengers traveling on various airlines. Your objective is to write a program to read the list of passengers from the text file. Because the number of passengers in the text file may not be known a priority, implement a **dynamically doubling array** to store the necessary information. 

Please read all the directions *before* writing code, as this write-up contains specific requirements for how the code should be written.

To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

 1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
 2. Run the `cmake ..` command.
 3. Run the `make` command.
 4. If there are no compilation errors, two executables will be generated within the build directory: `run_app` and `run_tests`.
 4. To run your program including your app implementation in the `main` function, execute `run_app` from the terminal by typing `./run_app <Required arguments>`.
 5. To run the tests against your code, execute `run_tests` from the terminal by typing `./run_tests`. 

## Overview

> **Warning**
> All work must be completed independently. Any use of web sites such as Chegg or CourseHero will result in Academic Consequences. We will check for assignments being published online and determine who submitted the assignment and who viewed the web site. Also, copying code from another student or anywhere for that matter will not be permitted. See the Syllabus for details.

***Problem***

***Overview*:**

You have been provided with a file: ***passengers.txt***, which contains information about each passenger's name, chosen airline, location, and age. Each line is a comma-separated list of the above-mentioned information. An example of a line is **Bob,Delta,Boulder,34.**

We want to read the data, store it in a data structure, and query from it. A query will be of the type: *Who are the people in a particular **location,** who chose a particular  **airline**, and who belong to a specific **age** group.*

Your program must take ***five*** arguments in the following order:

1.  The name of the txt file to be read and analyzed (e.g., passengers.txt)
2.  The location (e.g., Boulder)
3.  The name of the airline (e.g., Delta)
4.  The lower limit (included) of the age group (e.g., 20)
5.  The upper limit (included) of the age group (e.g., 40)

Your program will read the text from the file and store all the unique passengers encountered in a dynamically doubling array. After the necessary calculation(s), the program must print the following information:

-   The number of times array doubling was required to store all the passengers.
-   The total number of passengers returned after the query.
-   The passengers which are returned after the query is hit. Note that the passengers will have to be sorted in **descending order of the person's age**.

For example, running your program with the command:

```cpp
./run_app ../passengers.txt Boulder Delta 20 25
```

would print the passengers that chose to fly with Delta Airlines, who live in Boulder and are in the age group 20-25, in decreasing order of their age.

A sample run will look as follows:

```
Array doubled: 1
Total number of passengers returned after the query: 3
Queried Passengers
---------------------------------------
James 28
Alice 26
Bob 25
```

***Specifications*:**

1.  **Use an array of structs to store the passengers.** You will store each unique case in an **array of structs**. As the number of passengers is not known ahead of time, the array of structs must be **dynamically sized**. The struct is defined as follows (available in the .hpp file):

```cpp
struct AirlinePassenger
{
   string name;
   string airline;
   string location;
   int age;
}
```

As you read the file, store the information of a line (i.e. name, airline, location, and age) in a struct variable of the type
**AirlinePassenger** This variable will be appended to the dynamically sized array of structs. **One must note that only the passengers which satisfy the query parameters must be appended to the array.**

2.  **Use the array-doubling algorithm to increase the size of your array.** Your array will need to grow to fit the number of passengers in the file. **Start with an array size of 10**, and double the size whenever the array runs out of free space. You will need to dynamically allocate your array and copy values from the old array to the new one.

> **Note**
> Don’t use the built-in **std::vector** class. This will result in a loss of points. You’re writing code that emulates the vector container’s dynamic resizing functionality.

----------------------------------------------------------------------------------------------------------------------------------

3.  Ignore the records that do not satisfy the query parameters (i.e., location, age, airline) given through the command-line argument. If you type the location as Boulder, the airline as Delta, and the age range as 20 to 30, then do not append the records where the person is not from Boulder or did not fly with Delta, or belongs to an age less than 20 or more than 30. Note that one is **not supposed to exclude** a person with an age of exactly 20 or 30.

4.  **Output the records for a query.** Your program must print out the names and the ages of the passengers, which satisfy the query parameters in **decreasing order** of their age. If there is a tie, you can break that by using the person’s name (i.e., alphabetically). For example, if there are two records (Bob and Alice) of the same age (let’s say 25), you must print Alice’s record first.

5.  **Format your final output this way:**

```
Array doubled: <Number of times the array was doubled>
Total number of passengers returned after the query: <corresponding value>
Queried Passengers
---------------------------------------
<Name of the first person> <Corresponding age>
<Name of the second person> <Corresponding age>
…
```

For example, using the command:
```cpp
./run_app ../passengers.txt Eldora Delta 20 25
```

Output:

```
Array doubled: 1
Total number of passengers returned after the query: 15
Queried Passengers
---------------------------------------
Danetta Mueller 24
Yury Ferguson 24
Jamira Pierce 23
Lexie Blackburn 23
Carlis Benton 22
Latiya Williamson 22
Brad Dixon 21
Joi Parker 21
Shamar Stafford 21
Anjela Norman 20
Dartanian Starr 20
Jenne Ryan 20
Julissa McIntyre 20
Magic Archer 20
Terrian Brock 20
```

6.  **You must include the following functions (they will be tested in INGInious):**

a.  **../app/main function**

i.  If the correct number of command-line is not passed, print the below statement as-is and exit the program

```cpp
cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Airline> <Query_Start_Age> <Query_End_Age>" << endl;
```

ii.  Open the input file (ex: ***passengers.txt***) here.

iii. Start with a dynamic **AirlinePassenger** array of size 10

iv. You need to read the command line arguments in the main function and pass them to the **parseFile** function as an array of query parameters.

v. You need to print the number of times the array has been doubled and the total number of passengers returned by the query. (See the format provided in **5**).

vi.  In the end, call the **printQueriedPassengers** function to print all the queried passengers.

<!-- -->

b.  **parseFile function**

```cpp
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter);
```

> This function parses the given **input file** line by line and takes in the **query parameters** passed from the command line. We use these parameters along with the lines read from the input and store all the passengers that satisfy the query conditions (Location, Airline and Age Range). Keep track of the number of times the **AirlinePassenger** array is doubled.

c.  **isPassengerQueried function**

```cpp
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge);
```
> This function checks whether a single case with the given **location** and **airline** belongs to the given **age range**.

> For example, let’s say you have an entry of **Bob**, aged **25**, living in **Boulder** and chose to fly with **Delta** Airlines. The command line arguments ask you to get passengers in Boulder that flew with Delta  between the **age range from 20 to 30**; then this function should return True for this entry since it should be added to the array.

d.  **resizeArr function**
```cpp
void resizeArr(AirlinePassenger *&passengers, int *arraySize);
```
> This function should reisze the given array by dynamically creating a new ***AirlinePassenger*** array of twice the existing capacity, copy the contents of the ***passengers*** to the new array. Make sure to handle memory leaks by appropriate deletions.

e.  **addPassenger function**
```cpp
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter);
```
> This function must add the entry which returned True for ***isPassengerQueried*** function to the array passengers. This function will not return anything but will add the filtered entry to the array to store it.

f.  **sortPassengers function**
```cpp
void sortPassengers(AirlinePassenger *passengers, int length);
```
> This function must sort the passengers array (which contains **length** initialized elements) in descending order of the ages of the person,  such that the person with the largest age is sorted to the beginning. ***Additionally***, if a subset of entries has the same age then they should also be sorted alphabetically by name in ascending order. The function does not return anything.

***Note:*** You should *NOT* use the built-in **sort** function provided by the **&lt;algorithm&gt;** header. However, you may write your own implementation of a sorting algorithm, such as Bubble Sort. Feel free to refer to the pseudocode for bubble sort that was given in Assignment 1.

g.  **printQueriedPassengers function**
```cpp
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords);
```
> This function first sorts the passengers array by calling the sortPassenger function. It then prints the name and age of each passenger in the (now) sorted **passengers** array. The exact output format is given below. The function does not return anything.

> The format for printing the **queried passengers** should be as follows:

```
cout << "Queried Passengers\n---------------------------------------" << endl;
cout << Name << " " << Age << endl;
```

***APPENDIX 1:*** **Reading passengers from a text file**

Use the following C++ snippet to read passengers from a file:

```cpp
#include <fstream>

ifstream inStream; // stream for reading in file
inStream.open(filename); // open the file

string case;
while ( getline(inStream, case) )
{
   // process the case by tab separated values, by using istringstream or similar constructs.
} inStream.close(); // close the file
```
### Checking code into GitHub
**Important:** one of the main advantages of using git and GitHub is that it gives you a very convenient way to back up your changes. For now, you will only need to know how to `add`, `commit`, and `push`.  (You are encouraged to learn further git commands throughout the semester.) Any time you get to a point where you want to save your code (for example, you got a function to pass a test case), do the following in the terminal:
1. Stage your changes for a commit. This means that any changes you want to save, need to be added explicitly. (Note that you have all kinds of files that are present in your repository. You only need to add the ones you have changed and want to save.) For example, let's say we want to stage the changes we made in `main.cpp`. 
    ```console
    $ git add main.cpp
    ```
2. Commit the changes to our local repository:
    ```console
    $ git commit -m 'this is my first commit'
    ```
3. Finally, push the changes from your local version of the repo to the remote repo on GitHub. 
    ```console
    $ git push
    ```
You can run the above steps as many times as you want. Each time you commit/push your changes, a new commit number will be added to your repository. If ever you need to go back to a previous commit, you can fairly easily. However, further git discussion is beyond the scope of this course. 

### Submitting your code:
Write your code and push the changes to your private repository. Log onto Canvas and go to Assignment 2. Paste your GitHub repository link and submit.
