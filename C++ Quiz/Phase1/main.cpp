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
Phase 1
+++++++
cd project4_dsm0045_Morris
cd Phase1
g++ -o quiz main.cpp list.cpp node.cpp questions.cpp
./quiz

*/

#include <iostream>
#include <string>

#include "list.h"
#include "questions.h"

using namespace std;


int main() {
    list questionList; // linked list to store questions
    int questNum = 1; // question counter
    string questType; // stores the types of questions 

    cout << "*** Welcome to Danielle's Testing Service ***\n";

    while(true) {
        cout << "=== QUESTION " << questNum << " ===\n";
        cout << "Type of question [mcq/tf/wr]: ";
        cin >> questType;
        if (questType == "quit()") break; // exits the code

        // checks for valid inputs
        if (questType != "mcq" && questType != "tf" && questType != "wr") {
            cout << "[Command not recognized, please try again!]\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // creates new node and assigns type
        node* newNode = new node(questNum);
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

        // if the question was not successfully created, delete and retry
        if (!success) {
            delete newNode;
            continue;
        }

        // prompts user whether they want to continue adding questions
        questionList.addQuest(newNode);
        questNum++;

        // prompts user whether they want to continue adding questions
        string cont;
        while (true) {
            cout << "Question saved. Continue? [y/n]: ";
            cin >> cont;
            if (cont != "y" && cont != "n") {
                cout << "[Command not recognized, please try again!]\n";
            }
            else {
                break;
            }
        }

        //if the user doesn't choose to continue making questions, then it prompts the user to start the assessment
        if (cont != "y") {
            //print summar of questions created
            questionList.printSummary();
            string option;

            while (true) {
                cout << "\n/!\\ Begin assessment? [y/n]: ";
                cin >> option;

                if (option != "y" && option != "n") {
                    cout << "\n[Command not recognized, please try again!]\n";
                }
                else {
                    break;
                }
            }

            // starts the assesssment
            if (option == "y") {
                cin.ignore(); // clears leftover newline before getline
                questionList.startAssessment();
            }

            break; // exit main loop
        }
    }


    cout << "*** Thank you for using the testing service. Goodbye! ***\n";
    return 0;
}
