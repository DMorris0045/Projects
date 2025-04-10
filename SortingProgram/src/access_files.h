#ifndef _ACCESS_FILE_H_
#define _ACCESS_FILE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/*
function name: check_file
arguements:
    FILEPATH: a string of file path
return value: a bool that indicates if file in FILEPATH is accessable or not
*/
bool check_file(string FILEPATH);

/*
function name: read_file
arguements:
    FILEPATH: a string of file path
    v: a reference to a vector of double
purpose: read file in FILEPATH then parse the file and save its content into vector v
return value: a bool that indicates if the contents in FILEPATH is legal or not
*/
bool read_file(string FILEPATH, vector<double>& v);

/*
function name: write_file
arguements:
    FILEPATH: a string of file path
    v: a sorted vector of double
    mean: a double that is the calculated mean of v
    median: a double that is the calculated median of v
    mode: a double that is the calculated mode of v
purpose: write v, mean, median and mode to file in FILEPATH
return value: a bool that indicates the write process is successful or not
*/
bool write_file(string FILEPATH, vector<double> v, double mean, double median, double mode);

/*
function name: num_files
arguements:
    nums: how many files there are to read
return value:
*/
void num_files (int file_num, int num_files, vector<double>& values);

/*
function name: is_valid_line
arguement: 
    line: a line of text in the text file
purpose: to check if the line contains valid inputs
return value: a bool indicating if the input is valid
*/
bool is_valid_line(const std::string& line);

#endif

