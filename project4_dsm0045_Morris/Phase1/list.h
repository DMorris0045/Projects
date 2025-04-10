
#pragma once
#include "node.h"

class list {
    private:
        node* head;
        int size;

    public:
        list();
        ~list();

        void addQuest(node* newNode); // adds a question to the list
        void printSummary() const; // prints the summary of created questions
        void startAssessment(); // sstarts the quiz
        void printSessionSummary() const; // prints the summary of the quiz results
        int getSize() const; // gets the size of the list
        node* getHead() const; // gets the first node in the list
};

