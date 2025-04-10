#pragma once
#include "node.h"

// class rep a singly linked list of quiz questions
class list {
    private:
        node* head; // sets pointer to point to the first node in the list
        int size;  // gets the total number of questions in the list

    public:
    // constructor and destructor
        list(); // initializes an empty list
        ~list(); // frees memory for all nodes in the list

        void addQuest(node* newNode);       // adds a new question node to the end of the list
        void printSummary() const;          // displays a basic cummary before assessment
        void startAssessment();             // starts the quiz 
        void prompt();                      // displays create/edit/delete prompts to the user
        bool quizPrompt(node*& current);    // handles quiz navigation and answering logic
        node* jumpToQuestion(int id);       // finds the questions node by id and jumps to it
        void printSessionSummary() const;   // displays the results at the end of the quiz
        int getSize() const;                // returns the number of questiosn in the list
        node* getHead() const;              // returns the pointer that points to the first quesiton
        bool allQuestionsAnswered() const;  // checks if all the questiosn have been answered
};