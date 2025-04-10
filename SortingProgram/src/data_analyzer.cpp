/*

----------------------------
Name: Danielle Morris
Id: 904339996
Foldername: Project3_Morris_dsm0045
-----------------------------

---------------
   COMPILE
-------------
linux commands

--Start the program--
cd Project3_Morris_dsm0045
make
./bin/main



--access files---
note: the files had to be converted from dos to unix using dos2unix
        if the regular test files are not compiling then using 
        dos2unix *.txt inside the subfolder being tested should fix it



---regular_test file---

test/regular_test/big_num_test/big1.txt

test/regular_test/basic_tests/basic1.txt

test/regular_test/n_test/n1.txt

test/regular_test/pos_test/pos1.txt

test/regular_test/small_num_test/small1.txt



--corrupt_test---

test/corrupt_test/whitespace/white1.txt

test/corrupt_test/letter/letter1.txt

test/corrupt_test/special_char/char1.txt

test/corrupt_test/mixed/mix1.txt

test/corrupt_test/empty/empty1.txt



--writing to file--

the filename must end with .csv or the program will not accept it


References:
    geeksforgeeks:
        -how to implement quick sort
        -how to read files in c++
        -how to read from a file in C++

    Github copilot:
        -how to determine if a directory is valid
        -how to set precision to 4 decimal places
        -how to implement merge sort into this project
        -how to simplify my check_file function
        -due to time constraints most of process_vector, data_analyzer, and access_file were made with copilot
*/

#include "access_file.h"
#include "process_vector.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cmath> // Include this header for std::isnan
#include <iomanip> // Include this header for std::fixed and std::setprecision

using namespace std;

int main(){
    int numFiles = 0;
    vector<double> values;

    //formatting
    cout << "*** Welcome to Danielle's Data Analyzer ***\n";

    //if the user inputs an incorrect value then, re prompt user to input a valid number
    while (true) {
        cout << "Enter the number of files to read: ";
        cin >> numFiles;

        if (cin.fail() || numFiles < 1) {
            cout << "Number of files must be a positive number. Please try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            break;
        }
    }

    //calls read_multiple_files function 
    read_multiple_files(1, numFiles, values);

    //sorts the values
    sort_vector_ascending(values);

    //calls the mean, median, mode funcitons and stores their values
    double mean = find_mean(values);
    double median = find_median(values);
    double mode = find_mode(values);

    //outputs all the values in a list
    cout << "*** Summarized Statistics ***\n";
    cout << "The orderly sorted list of " << values.size() << " values is: \n";
    for (double value : values) {
        cout << value << " ";
    }

    cout << fixed << setprecision(4); // Set fixed-point notation and precision to 4 decimal places

    //if the file being processed is empty, then mean, median, mode is set to null
    if (std::isnan(mean) || std::isnan(median) || std::isnan(mode)) {
        cout << "\nMean: null\nMedian: null\nMode: null\n";
    } else {
        cout << "\nMean: " << mean << "\nMedian: " << median << "\nMode: " << mode << endl;
    }

    string outputFilename;
    bool fileWritten = false;

    while (!fileWritten) {
        cout << "Enter the output filename to save: ";
        cin >> outputFilename;

        // Check if filename ends with .csv
        if (outputFilename.length() < 5 || outputFilename.substr(outputFilename.length() - 4) != ".csv") {
            cout << "Error: Filename must end with '.csv'. Please try again.\n";
            continue;
        }

        // writes things to file. 
        if (write_file(outputFilename, values, mean, median, mode)) {
            cout << "*** File " << outputFilename << " has been written to disk ***\n";
            fileWritten = true;
        } else {
            cout << "Failed to write to file. Please try again.\n";
        }
    }


    cout << "*** Goodbye. ***\n";

    return 0;
}
