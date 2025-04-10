/*
=============
    Info
=============




==================
    References
==================

copilot
-how to implement a singly linked list
-how to create test casees for my code

GeeksforGeeks
-switch statements in C++

Stack Overflow
-why use cin.ignore() and cin.clear()

cppreference.com
-std::map

=======================
    How to compile
=======================


+++++++
Phase2
++++++
cd project4_dsm0045_Morris
cd Phase2

g++ -o quiz main.cpp list.cpp node.cpp questions.cpp test.cpp
./quiz

*/

#include <iostream>
#include <string>

#include "list.h"
#include "questions.h"
#include "test.h"

using namespace std;


int main() {
s    runAllTests();

    //create the quiz list object to the questions
    list questionList;
    string questType;

    cout << "*** Welcome to Danielle's Testing Service ***\n";

    //main loop to build the quiz
    while(true) {
        //calls prompt method
        questionList.prompt();

        //asks the user what kind of question they want to create
        cout << "=== QUESTION " << questionList.getSize() + 1 << " ===\n";
        cout << "Type of question [mcq/tf/wr]: ";
        cin >> questType;
        
        //if the user types quit(), then it breaks out of the loop
        if (questType == "quit()") break;
        
        //checks if the input is valid
        if (questType != "mcq" && questType != "tf" && questType != "wr") {
            cout << "[Command not recognized, please try again!]\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        //creates a new node
        node* newNode = new node(questionList.getSize() +1);
        newNode->type = questType;
        bool success = false;

        //call appropriate function
        if (questType == "mcq") {
            success = multipleChoice(newNode);
        }
        else if (questType == "tf") {
            success = trueFalse(newNode);
        }
        else if (questType == "wr") {       
            success = writtenAnswer(newNode);
        }

        if (!success) {
            delete newNode;
            continue;
        }

        //adds the valid questions to the quiz list
        questionList.addQuest(newNode);
    }
    return 0;
} 
