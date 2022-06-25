#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
// declared variables for the menu
int userInput; 
string itemName;
string fileLine;

void userMenu() {
	// menu display of user options
	cout << "____________________ User Menu ____________________" << endl;
	cout << "1: Show a list of items and their quantities purchased." << endl;
	cout << "2: Display the frequency of a specific item." << endl;
	cout << "3: Display the data as a historgram." << endl;
	cout << "4: Exit the program." << endl;
	cout << "___________________________________________________" << endl;
	cout << "Enter your choice 1-4:";
	cin >> userInput; // get user choice
	cout << endl;

	if (userInput == 1) { 
		// clear screen and change text color
		system("CLS");
		system("Color 0D");

		cout << "All items and their quantities sold today:" << endl;
		CallProcedure("AllItemCount"); // call python function to print the list of items and quantity sold of each
		cout << endl;
		return;
	}

	else if (userInput == 2) { 
		// clear screen and change text color
		system("CLS");
		system("Color 0E");

		cout << endl << endl << "Enter item name:";
		cin >> itemName; // get user input for item to search
		cout << endl << endl;
		cout << callIntFunc("UserItemCount", itemName) << " " << itemName << "s were sold today." << endl; // call python function for specific item count and display it for user
		return;
	}

	else if (userInput == 3) {
		// clear screen and change text color
		system("CLS");
		system("Color 0B");

		cout << "Histogram of items sold today:" << endl << endl; 
		CallProcedure("ItemCounterHist"); // call Python function to write data from input file to output file

		ifstream frequencyFile("frequency.dat"); // open output file to read data for histogram
		// local variables to create histogram
		string item;
		int count;

		while (getline(frequencyFile, fileLine)) { // while loop to go through each line of the file
			istringstream iss(fileLine);
			if (!(iss >> item >> count)) {
				break;
			}
			cout << item << " " << string(count, '*') << endl; // display item with a '*' for each occurence
		}
		cout << endl;
		return;
	}

	else if (userInput == 4) { // exit program option for the user if they enter 4

		cout << "Goodbye" << endl;
		exit(EXIT_SUCCESS);
	}

	else { // incase the user does not enter a valid option
		system("CLS");
		system("Color 04");

		cout << "Invalid entry." << endl;
		return;
	}
}


void main() {
	
	system("Color 07"); // set default colors

	while (1) { // infinite menu loop until user chooses exit option
		userMenu(); // call menu
	}

}