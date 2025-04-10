#include <cassert>
#include <iostream>
#include "list.h"
#include "node.h"
#include "test.h"

using namespace std;

// Test1: verifies that a new list is initialized correctly
void testEmptyList() {
    list l; // creates an empty list
    assert(l.getSize() == 0); // checks if the size is zero
    assert(l.getHead() == nullptr); // checks if the head is null
    cout << "Test 1 Passed: Empty list initialized correctly.\n";
}

// Test2: verfies that a single question can be added without error
void testAddSingleQuestion() {
    list l;
    node* q = new node(1); // creates a new question node
    q->type = "tf"; // sets a question type
    q->test = "C++ is a compiled language.";
    q->correctAns = "true";
    q->pointVal = 5;
    l.addQuest(q); // adds the question to the list

    assert(l.getSize() == 1); // checks taht the size is updated
    assert(l.getHead() == q); // checks that the head points to the new node
    cout << "Test 2 Passed: Single question added successfully.\n";
}

// Test3: verfies that jumpToQuestion() correctly returns the specific question
void testJumpToQuestion() {
    list l;
    // adds 3 questions
    for (int i = 1; i <= 3; i++) {
        node* q = new node(i);
        q->type = "wr";
        q->test = "Question " + to_string(i);
        q->correctAns = "ans";
        l.addQuest(q);
    }

    node* result = l.jumpToQuestion(2); // tries to jump to question 2
    assert(result != nullptr); // checks it should exist
    assert(result->id == 2); // its id should be 2
    cout << "Test 3 Passed: jumpToQuestion works.\n";
}

// Test4: simulates deleting a question and chcks that ids are updated
void testDeleteQuestionUpdatesIDs() {
    list l;
    // adds 3 questions
    for (int i = 1; i <= 3; i++) {
        node* q = new node(i);
        q->type = "tf";
        q->test = "Q" + to_string(i);
        q->correctAns = "true";
        q->pointVal = 1;
        l.addQuest(q);
    }

    // Delete question 2 manually
    node* current = l.getHead();
    node* prev = nullptr;
    while (current && current->id != 2) {
        prev = current;
        current = current->next;
    }
    if (prev && current) prev->next = current->next; // removes from list
    delete current; // frees memory

    // Recalculate IDs
    int newID = 1;
    current = l.getHead();
    while (current) {
        current->id = newID++;
        current = current->next;
    }

    assert(l.jumpToQuestion(2)->id == 2); // what was originally ID 3
    cout << "Test 4 Passed: Delete and ID renumbering works.\n";
}

// Test5: checks if allQuestionsAnswered() correctly detectws answered status
void testAllQuestionsAnswered() {
    list l; 
    // adds two answered questions
    for (int i = 1; i <= 2; i++) {
        node* q = new node(i);
        q->answered = true; // manually set as answered
        l.addQuest(q);
    }

    assert(l.allQuestionsAnswered() == true); // should return true
    cout << "Test 5 Passed: allQuestionsAnswered detects full answer.\n";
}

// runs all the tests in this file
void runAllTests() {
    testEmptyList();
    testAddSingleQuestion();
    testJumpToQuestion();
    testDeleteQuestionUpdatesIDs();
    testAllQuestionsAnswered();
    cout << "\nAll tests passed successfully!\n";
}
