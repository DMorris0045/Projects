#ifndef TEST_H
#define TEST_H

void testEmptyList();                   // verifies that a new list is initialized with size 0 and head == nullptr
void testJumpToQuestion();              // verifies that jumpToQeustion returns the correct node by ID
void testAddSingleQuestion();           // verifies that a single question can be added and accessed correctly
void testDeleteQuestionUpdatesIDs();    // verifies that after deleting a question, IDs are updated correctly
void testAllQuestionsAnswered();        // verifies that allQeustionsAnswered() detects when all the questions are amrked answered
void runAllTests();                     // runs all the tests

#endif