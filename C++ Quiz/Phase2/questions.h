#ifndef QUESTION_H
#define QUESTION_H
#include "node.h"

bool multipleChoice(node* q);   // prompts the user to create a multiple choice question
bool trueFalse(node* q);        // prompts the user to create a true/false question
bool writtenAnswer(node* q);    // prompts the user to create a written answer question

#endif

