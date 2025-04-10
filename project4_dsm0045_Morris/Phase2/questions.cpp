#include <iostream>
#include <string>
#include "questions.h"

using namespace std;

// function to create a multple choice question
bool multipleChoice(node* q) {
    string input;
    char option = 'A';

    // prompts for question
    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    //creates options A through E
    while (option < 'E') {
        cout << "Enter choice " << option << ": ";
        getline(cin, input);

        q->choices[option] = input;
        option++;
    }

    q->choices['E'] = "quit()";

    //loops if the answer entered not an acceptable type
    while (true) {
        cout << "Select correct answer: ";
        getline(cin >> ws, q->correctAns);
        if (q->test == "quit()") return false;

        // ensures valid input (a single char that exists in the choice map)
        if (q->correctAns.length() == 1 && q->choices.count(q->correctAns[0])) {
            q->correctAns = q->correctAns[0]; // stores only the letter
            break;
        }

        cout << "[Anser not recognized, please try again!]\n";
    }

    // prompts for point value
    while (true) {
        cout << "Enter point value: ";
        getline(cin >> ws, input);

        try {
            q->pointVal = stof(input); // converts string to float
            if (q->pointVal >= 0) break;
        }
        catch (...) {}

        cout << "[Not a point value, please try again!]\n";
    }

    return true;

}

// function to create a true/false question
bool trueFalse(node* q) {
    string input;

    // prompts for question text
    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    
    //correct answer to question must be true or false. Otherwise it reprompts user
    while(true) {
        cout << "Select correct answer: ";
        getline(cin >> ws, input);
        if (input == "quit()") return false;

        if (input == "true" || input == "false") {
            q->correctAns = input;
            break;
        }

        cout << "[Answer not recognized, please try again!]\n";
    }


    // prompt for point value with validation
    while (true) {
        cout << "Enter point value: ";
        getline(cin >> ws, input);
        if (input == "quit()") return false;

        try {
            q->pointVal = stof(input);
            if (q->pointVal >= 0) break;
        }
        catch (...) {}

        cout << "[Not a point value, please try again!]\n";
    }


    return true;

}

// function to create a written answer question
bool writtenAnswer(node* q) {
    string input;

    // prompt for qeustion
    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    // prompt for correct answer
    cout << "Type answer: ";
    getline(cin >> ws, q->correctAns);
    if (q->correctAns == "quit()") return false;

    // prompt for point value 
    while (true) {
        cout << "Enter point value: ";
        getline(cin >> ws, input);
        if (input == "quit()") return false;

        try {
            q->pointVal = stof(input);
            if (q->pointVal >= 0) break;
        }
        catch (...) {}

        cout << "[Not a point value, please try again!]\n";
    }

    return true;
    
}