#pragma once
#include <string>
#include <map>

// struct that represents a single quiz question node
struct node {
    int id;                     // unique id for the question
    std::string type;           // question type
    std::string test;           // question text
    std::string correctAns;     // the correct answer
    std::string userAns;        // the answer the user submitted
    float pointVal;             // number of points this question is worth
    bool answered = false;      // whether this question has been answered or not

    std::map<char, std::string> choices; // for multiple choice questions

    node* next; // points to the next node in the list

    //constructor
    // initializes a node with an ID and sts the default values
    node(int id); 
};