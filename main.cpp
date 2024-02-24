//============================================================================
// Subject     : CS-300-R3288 DSA Analysis and Design                        
// Name        : Project.cpp                                                 
// Student     : Margarita Kiseleva                                          
// Date        : 02/23/2024 
//============================================================================

// Importing necessary libraries

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
string fileName;

// Defining a structure to hold courses and their information

struct Course {

	string courseNumber;
	string name;
	vector<string> prerequisites;

};

// Defining a function that splits a string by a chosen deliminator

vector<string> tokenize(string s, string del = " ") {

	vector<string> stringArray;
	int start = 0;
	int end = s.find(del);

	// Creating the loop that will run until the end of the document (-1) is reached

	while (end != -1) {

		stringArray.push_back(s.substr(start, end - start));
		start = end + del.size();
		end = s.find(del, start);

	}

	// Appending courses to the array and returning it when finished

	stringArray.push_back(s.substr(start, end - start));
	return stringArray;

}

// Defining a function that loads a file, stores courses in a vector, and returns it

vector<Course> LoadDataStructure() {

	// Creating an object that opens a file

	ifstream inputFile(fileName, ios::in);
	vector<Course> courses;
	string line;

	// Displaying an error message if unable to open file

	if (!inputFile) {

		cout << "\nUnable to open file " << fileName << endl;
		return courses;

	}

	// Initiating a loop that breaks when the end of a file (-1) is reached

	while (1) {

		getline(inputFile, line);

		if (line == "-1")
			break;

		Course course;

		// Accessing tokens separated by commas

		vector<string> tokenizedInformation = tokenize(line, ",");

		// Storing tokens of course number and name in the vector

		course.courseNumber = tokenizedInformation[0];
		course.name = tokenizedInformation[1];

		// Storing tokens of course prerequisites in the vector if there are any

		for (int i = 2; i < tokenizedInformation.size(); i++) {

			course.prerequisites.push_back(tokenizedInformation[i]);

		}

		// Appending the vector with courses

		courses.push_back(course);

	}

	// Closing the file upon finishing

	cout << "\nData is loaded successfully." << endl;
	inputFile.close();

	// Returning the list of courses

	return courses;

}

// Defining a function that prints number and name of a given course

void printCourse(Course course) {

	string courseNumber = course.courseNumber;
	string name = course.name;
	cout << "\n" << courseNumber << ", " << name << endl;

}

// Defining a function that prints prerequisites of a given course if there are any

void printPrereq(Course course) {

	vector<string> prerequisites = course.prerequisites;

	if (prerequisites.size() > 0) {

		cout << "\nPrerequisites: ";

		for (int i = 0; i < prerequisites.size(); i++) {

			cout << prerequisites[i] << " ";

		}

		cout << endl;

	}

	else {

		cout << "No prerequisites found for this course." << endl;

	}

}

// Defining a function that prints list of courses

void printCourseList(vector<Course> courses) {

	int n = courses.size();

	// Sorting the list of courses in alphanumerical order using bubble sort

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i - 1; j++) {

			if (courses[j].courseNumber > courses[j + 1].courseNumber) {

				swap(courses[j + 1], courses[j]);

			}

		}

	}

	// Traversing through the list of courses to print all courses

	for (int i = 0; i < n; i++) {

		printCourse(courses[i]);

	}

}

// Defining a function that will turn a string to upper case and return it

string stringToUpper(string oString) {

	for (int i = 0; i < oString.length(); i++) {

		oString[i] = toupper(oString[i]);

	}

	return oString;

}

// Defining a function that will search for a course by the entered number

void searchCourse(vector<Course> courses) {

	int n = courses.size();
	string courseNumber;
	int f = 0;
	cout << "\nEnter course number: ";
	cin >> courseNumber;

	// Convering user's input to upper case

	courseNumber = stringToUpper(courseNumber);

	// Starting a loop that will run until the course is found

	for (int i = 0; i < n; i++) {

		// Printing the course once found

		if (courses[i].courseNumber == courseNumber) {

			f = 1;
			printCourse(courses[i]);
			printPrereq(courses[i]);
			break;

		}

	}

	// Prining error message if the course is not found

	if (f == 0) {

		cout << "\nCourse with the given number is not found." << endl;

	}

}

// Defining the main function

int main(int argc, char** argv) {

	vector<Course> courses;
	
	int ch;

	// Displaying a welcome message

	cout << "Welcome to the course planner." << endl;

	// Creating a loop that will break if user enters 4

	do {

		// Printing menu

		cout << "\n"; 
		cout << "       ***Menu***" << endl;
		cout << "*************************" << endl;
		cout << "* 1.Load Data Structure *" << endl;
		cout << "* 2.Print Course List   *" << endl;
		cout << "* 3.Print Course        *" << endl;
		cout << "* 4.Exit                *" << endl;
		cout << "*************************" << endl;

		// Prompting user to enter their choice

		cout << "\nPlease enter your choice: ";
		cin >> ch;

		// Preventing the switch from entering an infinite loop if the input is not an integer

		if (cin.fail()) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}

		switch (ch) {

		case 1: {

			// Getting user's input for the name of file

			cout << "\nWhich file would you like to read?\n" << endl;
			cout << "Type in the file's name here: ";
			cin >> fileName;

			// Calling the function that loads the file

			courses = LoadDataStructure();
			break;

		}

		case 2: {

			// Making sure the file is already loaded
			
			if (!courses.empty()) {

				printCourseList(courses);
				break;

			}

			// Prompting user to load the file first if it is not yet done

			else {

				cout << "\nNo data is loaded yet. Please start with option 1." << endl;
				break;

			}

		}

		case 3: {

			// Making sure the file is already loaded

			if (!courses.empty()) {

				searchCourse(courses);
				break;
			
			}

			// Prompting user to load the file first if it is not yet done

			else {

				cout << "\nNo data is loaded yet. Please start with option 1." << endl;
				break;
			}

		}

		case 4: {

			// Exiting the program

			cout << "\nExiting the program. Thank you for using the course planner!";
			break;

		}

		default: {

			// Catching an invalid user input

			cout << "\nInvalid choice. Please enter a digit from 1 to 4." << endl;
			break;
		
		}

		}

	} while (ch != 4);

	return 0;

}
