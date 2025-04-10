#include <iostream>
#include "list.h"

using namespace std;

// construcctor initializes the lsit with a null head and size 0
list::list() {
    head = nullptr;
    size = 0;
}

// destructor deletes all nodes in the list
list::~list() {
    node* current = head;
    while (current != nullptr) {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// addss a new node to the end of the list
void list::addQuest(node* newNode) {
    if (!head) {
        head = newNode; // first node in the lisst
    }
    else {
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode; // appends to the end
    }
    size++;
}

// returns the number of questions in teh list
int list::getSize() const {
    return size;
}

// returns teh head pointer to the first node
node* list::getHead() const {
    return head;
}

// prints a summary of how many questions were created and the total point value
void list::printSummary() const {
    cout << "\n=== SESSION LOG ===\n";
    cout << "Total questions: " << size << "\n";
    float totalPoints = 0;
    node* temp = head;

    // accumulates total point value of all questions
    while (temp != nullptr) {
        totalPoints += temp->pointVal;
        temp = temp->next;
    }
    cout << "Total point values: " << totalPoints << "\n";
}

// runs the actual quiz and calculates the score
void list::startAssessment() {
    if (!head) {
        cout << "No questions available.\n";
        return;
    }

    node* current = head;
    int totalCorrect = 0;
    float totalEarned = 0;
    float totalPossible = 0;
    bool quitEarly = false; // value to end quiz early 

    while (current) {
        cout << "\nQuestion " << current->id << ": " << current->test << "\n";

        // handles multiple choice question
        if (current->type == "mcq") {
            for (std::map<char, std::string>::const_iterator it = current->choices.begin();
                 it != current->choices.end(); ++it) {
                cout << it->first << ". " << it->second << "\n";
            }

            while (true) {
                cout << "Your answer: ";
                getline(cin >> ws, current->userAns);

                // checks for quit input
                if (current->userAns == "E" || current-> current->userAns == "quit()") {
                    quitEarly = true;
                    break;
                }

                if (current->userAns.length() == 1) {
                    char ansChar = current->userAns[0];

                    // checks if the answer input is correct
                    if (current->choices.count(ansChar)) {
                        if (current->userAns == current->correctAns) {
                            cout << "[Your answer is correct!]\n";
                            totalEarned += current->pointVal;
                            totalCorrect++;
                        } else {
                            cout << "[Your answer is incorrect. The correct answer is " << current->correctAns << ".]\n";
                        }
                        break;
                    }
                }

                cout << "[Answer not recognized, please try again!]\n";
            }
        }
        // handles true/false
        else if (current->type == "tf") {
            while (true) {
                cout << "Your answer: ";
                getline(cin >> ws, current->userAns);

                //checks if the input is the correct answer
                if (current->userAns == "true" || current->userAns == "false") {
                    if (current->userAns == current->correctAns) {
                        cout << "[Your answer is correct!]\n";
                        totalEarned += current->pointVal;
                        totalCorrect++;
                    } else {
                        cout << "[Your answer is incorrect. The correct answer is " << current->correctAns << ".]\n";
                    }
                    break;
                }
                cout << "[Answer not recognized, please try again!]\n";
            }
            if (quitEarly) break; //quits the quiz early
        } 
        //handles write answer queustions
        else if (current->type == "wr") {
            cout << "Your answer: ";
            getline(cin >> ws, current->userAns);

            // checks if the answer input is correct
            // case sensitive
            if (current->userAns == current->correctAns) {
                cout << "[Your answer is correct!]\n";
                totalEarned += current->pointVal;
                totalCorrect++;
            } else {
                cout << "[Your answer is incorrect. The correct answer is " << current->correctAns << ".]\n";
            }
        }

        // adds question's point value to total possible
        totalPossible += current->pointVal;
        current = current->next; // move to the next question node
    }

    // formatting for end of the assessment
    cout << "\n/!\\ Assessment Complete.\n";
    cout << "=== SESSION LOG ===\n";
    cout << "Correct answers: " << totalCorrect << "/" << size << "\n";
    cout << "Final score: " << totalEarned << "/" << totalPossible << "\n";
}
