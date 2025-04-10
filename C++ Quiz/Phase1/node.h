#pragma once
#include <string>
#include <map>

struct node {
    int id;                     // question number
    std::string type;           // queustion type
    std::string test;           // the actual question text
    std::string correctAns;     // the correct answer to the quesiton
    std::string userAns;        // the naswer the user inputs during the quiz
    float pointVal;             // points the question is worth
    bool answered = false;      // tracks if the question was answered

    std::map<char, std::string> choices; // used for multiple choice question to map options (A-E)

    node* next; // pointer to the next question in the list

    node(int id); // constructor to initialize a new quesion with an ID
};
