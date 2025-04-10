#include "access_file.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//checks if the file can be opened
bool check_file(string FILEPATH) {
    ifstream file(FILEPATH);
    
    return file.good();
}

//reads values form file and stores it in vector v
//returns false if file cannot be read
bool read_file(string FILEPATH, vector<double>& v) {
    ifstream file(FILEPATH);
    if (!file) return false; //false if file can't be opened

    string line;
    while (getline(file, line)) {
        if (!is_valid_line(line)) return false; //line contains illegal characters

        try {
            double num = stod(line); //string to double
            v.push_back(num); //add a value to vector
        } catch (...) {
            return false; //if the conversion fails
        }
    }

    //returns false if there is an error with the file
    return !file.bad();
}

//writes sorted values to a .csv output file
bool write_file(string FILEPATH, vector<double> v, double mean, double median, double mode) {
    ofstream file(FILEPATH);
    if (!file) {
        cout << "Error: Unable to write to file. Please try again.\n";
        return false;
    }

    // Write comma-separated values on one line
    file << "The orderly sorted list of " << v.size() << " values is:\n";
    for (size_t i = 0; i < v.size(); ++i) {
        file << v[i];
        if (i != v.size() - 1) file << ","; //adds commas between values
    }
    file << "\n";

    // Write mean, median, mode to file
    file << "mean," << mean << "\n";
    file << "median," << median << "\n";
    file << "mode," << mode << "\n";

    file.close();
    return true;
}

//prompts user to enter filename and reads data
//loops until valid files are read
void read_multiple_files(int file_num, int num_files, vector<double>& values) {

    //this big for loop makes sure the program doesn't exit if an invlaid filename is input
    for (; file_num <= num_files; ++file_num) {
        string filename;
        bool validFile = false;

        //if the file isn't valid, then re-prompt the user until a valid file is set
        while (!validFile) {
            cout << "Enter the filename for file " << file_num << ": ";
            cin >> filename;

            //checks if file exists
            if (!check_file(filename)) {
                cout << "File doesn't exist. Please try again.\n";
                continue; //goes back to the start of the loop if file isn't good
            }

            //tries reading the file
            if (!read_file(filename, values)) {
                cout << "Not an input file. Illegal content/structure detected.Please try again.\n";
                continue; //goes back to the start of the loop if file can't be read
            }

            //file is valid and readable
            validFile = true;
        }

        //prints all the values in the file
        cout << "The list of values in file " << filename << " is:\n";
        cout << "\n";
        for (double value : values) {
            cout << value << "\n";
        }
    }
}

//makes sure the file contains valid values
bool is_valid_line(const string& line) {
    if (line.empty()) return false;

    int dotCount = 0;
    int dashCount = 0;
    bool hasDigit = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];

        if (isdigit(c)) {
            hasDigit = true;
        } else if (c == '.') {
            dotCount++;
            if (dotCount > 1) return false; //only one dot allowed
        } else if (c == '-') {
            if (i != 0) return false; // '-' only allowed at beginning
            dashCount++;
            if (dashCount > 1) return false; //only one dash allowed
        } else {
            return false; // Any other character is illegal
        }
    }

    //makes sure at least one digit is present
    return hasDigit; 
}

