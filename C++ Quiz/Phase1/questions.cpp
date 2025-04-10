#include <iostream>
#include <string>
#include "questions.h"

using namespace std;

bool multipleChoice(node* q) {
    string input;
    char option = 'A';

    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    // creates options A through D from user input, E is always "quit()"
    while (option <= 'D') {
        cout << "Enter choice " << option << ": ";
        getline(cin, input);
        q->choices[option] = input;
        option++;
    }
    // Force E to be "quit()"
    q->choices['E'] = "quit()";

    // loops if the answer entered is not an acceptable type
    while (true) {
        cout << "Select correct answer: ";
        getline(cin >> ws, q->correctAns);
        if (q->correctAns == "quit()") return false;

        if (q->correctAns.length() == 1 && q->choices.count(q->correctAns[0])) {
            q->correctAns = q->correctAns[0];
            break;
        }

        cout << "[Answer not recognized, please try again!]\n";
    }

    while (true) {
        cout << "Enter point value: ";
        getline(cin >> ws, input);

        try {
            q->pointVal = stof(input);
            if (q->pointVal >= 0) break;
        }
        catch (...) {}

        cout << "[Not a point value, please try again!]\n";
    }

    return true;
}

bool trueFalse(node* q) {
    string input;

    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    // correct answer to question must be true or false
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

bool writtenAnswer(node* q) {
    string input;

    cout << "Enter a question: ";
    getline(cin >> ws, q->test);
    if (q->test == "quit()") return false;

    cout << "[At any time, type 'quit()' to exit]\n";

    cout << "Type correct answer: ";
    getline(cin >> ws, q->correctAns);
    if (q->correctAns == "quit()") return false;

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