#include <iostream>
#include "list.h"
#include <limits>

using namespace std;

//global variables to track the score
int totalCorrect = 0;
float totalEarned = 0;
float totalPossible = 0;

//constructor
list::list() {
    head = nullptr;
    size = 0;
}

//destructor
list::~list() {
    node* current = head;
    while (current != nullptr) {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

//adds a question node to the end of the list
void list::addQuest(node* newNode) {
    if (!head) {
        head = newNode;
    }
    else {
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}

// gets the size fo the list
int list::getSize() const {
    return size;
}

//returns the head
node* list::getHead() const {
    return head;
}

// returns the pointer 
node* list::jumpToQuestion(int id) {
    node* current = head;

    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// checks if all the questions have been answered
bool list::allQuestionsAnswered() const {
    node* current = head;
    while (current != nullptr) {
        if (!current->answered) return false;
        current = current->next;
    }
    return true;
}

// prints summary of the quiz
void list::printSummary() const {
    cout << "\n=== SESSION LOG ===\n";
    cout << "Total questions: " << size << "\n";
    float totalPoints = 0;
    node* temp = head;

    while (temp != nullptr) {
        totalPoints += temp->pointVal;
        temp = temp->next;
    }

    cout << "Total point values: " << totalPoints << "\n";
}

// starts the quiz
void list::startAssessment() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

    // confirms if the user wants to begin the quiz
    while (true) {
        string choice;
        cout << "/!\\ Begin assessment? [y/n]: ";
        cin >> choice;

        if (choice == "y") break;
        else if (choice == "n") return;
        else cout << "[Answer not recognized. Please try again!]\n";
    }

    if (!head) {
        cout << "No questions available.\n";
        return;
    }

    // initialize score tracker
    totalCorrect = 0;
    totalEarned = 0;
    totalPossible = 0;

    // calculates total points
    node* scan = head;
    while (scan != nullptr) {
        totalPossible += scan->pointVal;
        scan = scan->next;
    }

    // begin quiz from the first question
    node* current = head;
    quizPrompt(current);
}

// prints results of the quiz
void list::printSessionSummary() const {
    cout << "\n/!\\ Assessment Complete.\n";
    cout << "=== SESSION LOG ===\n";
    cout << "Correct answers: " << totalCorrect << "/" << size << "\n";
    cout << "Final score: " << totalEarned << "/" << totalPossible << "\n";
}

//gives the user the option to, create a question, edit one, delete one, or finish making the quiz
void list::prompt() {
    int option;
    int questNum;

    while (true) {
        cout << "Do you want to?\n";
        cout << "   1. Create new question.\n" << "   2. Edit question.\n" << "   3. Delete question.\n" << "   4. Finish.\n";
        cout << "Select an action: ";
        cin >> option;

        switch(option) {
            case 1: {
                //break out of the switch cases and move on to the question while loop in main
                return;
            }
            case 2: {
                if (!head) {
                    cout << "Nothing to edit.\n";
                    break;
                }
    
                cout << "Select a question to edit, or type 0 to quit [1-" << size << "]: ";
                cin >> questNum;
    
                if (questNum <= 0 || questNum > size) {
                    cout << "[Question does not exist]\n";
                }
    
                node* current = head; // locate the question node
                while (current && current->id != questNum) {
                    current = current->next;
                }
    
                if(!current) {
                    cout << "[Could not find question]\n";
                    break;
                }
    
                // display current value
                cout << "===============================\n";
                cout << "=== QUESTION " << current->id << " SAVED VALUES ===\n";
                cout << "1. Type: " << current->type << "\n";
                cout << "2. Question: " << current->test << "\n";
    
                if (current->type == "mcq") {
                    cout << "3. Answer choices:\n";
                    for (auto& c : current ->choices) {
                        cout << c.first << ". " << c.second << "\n";
                    }
                }
    
                cout << "4. Correct answer: " << current->correctAns << "\n";
                cout << "===============================\n";
    
                // edits the loop
                string input;
                while (true) {
                    cout << "Type a number to edit, or type quit(): ";
                    cin >> input;
                    if (input == "quit()") break;
    
                    if (input == "2") {
                        cout << "Enter a question: ";
                        cin.ignore();
                        getline(cin, current->test);
                    }
                    else if (input == "1") {
                        cout << "[Cannot edit question type]\n";
                    }
                    else if (input == "3" && current->type == "mcq") {
                        for (auto& c : current->choices) {
                            cout << "Enter choice " << c.first << ": ";
                            getline(cin >> ws, c.second);
                        }
                    }
                    else {
                        cout << "[Input not recognized. Please try again!]\n";
                    }
                }
    
                break;
            }
    
            case 3: {
                if (!head) {
                    cout << "Nothing to delete\n";
                    break;
                }
    
                cout << "Select a question to delete [1-" << size << "]: ";
                cin >> questNum;
    
                if (questNum <= 0 || questNum > size) {
                    cout << "[Question does not exist]\n";
                    break;
                }
    
                // locates and removes the nodes
                node* current = head;
                node* prev = nullptr;
    
                while (current && current->id != questNum) {
                    prev = current; 
                    current = current->next;
                }
    
                if (!current) {
                    cout << "[Question not found]\n";
                    break;
                }
    
                if (prev) {
                    prev->next = current->next;
                } 
                else {
                    head = current->next;
                }
    
                delete current;
                size--;
    
                // reassign id to remaining questions
                current = head;
                int newID = 1;
                while (current) {
                    current->id = newID++;
                    current = current->next;
                }
    
                cout << "Question " << questNum << " deleted.\n";
                break;
            
            }
            case 4: {
                printSummary();
                startAssessment();
            }
        }

    }
}

// handles answereing, revieweing, jumping between questions
bool list::quizPrompt(node*& current) {
    int option;
    
    while (true) {
        if (!current) current = head;

        cout << "\nQuestion " << current->id << ": " << current->test << "\n";

        if (current->answered) {
            cout << "You answered: " << current->userAns << "\n";

            // if already answered, offer options to edit or navigates
            while (true) {
                cout << "\nDo you want to?\n";
                cout << "   1. Edit this answer.\n";
                cout << "   2. Go to next question.\n";
                cout << "   3. Jump to question.\n";
                cout << "   4. Submit.\n";
                cout << "Select an action: ";

                int choice2;
                cin >> choice2;

                if (choice2 == 1) {
                    cout << "New answer: ";
                    getline(cin >> ws, current->userAns);
                    break;
                }
                else if (choice2 == 2) {
                    current = current->next ? current->next : head;
                    break;
                }
                else if (choice2 == 3) {
                    int id;
                    cout << "Jump to question [1-" << size << "]: ";
                    cin >> id;
                    current = jumpToQuestion(id);

                    if (!current) {
                        cout << "[Question not found. Returning to first quesiton.]\n";
                        current = head;
                    }
                    break;
                }
                else if (choice2 == 4) {
                    if (!allQuestionsAnswered()) {
                        string confirm;
                        cout << "[Warning: some questions are unanswered. Submit anyway?]: ";
                        cin >> confirm;

                        if (confirm != "y") {
                            continue;
                        }
                    }
                    
                    printSessionSummary();
                    cout << "*** Thank you for using the testing service. Goodbye! ***\n";
                    exit(0);
                }
                else {
                    cout << "[Input not recognized. Please try again!]\n";
                }
            }
            continue;
        }

        // answering the current question based on its type
        if (current->type == "mcq") {
            for (const auto& choice : current->choices) {
                cout << choice.first << ". " << choice.second << "\n";
            }

            while (true) {
                cout << "Your answer: ";
                getline(cin >> ws, current->userAns);

                if (current->userAns == 'E') {
                    printSessionSummary();
                    cout << "*** Thank you for using the testing service. Goodbye! ***\n";
                    exit(0);
                }
                
                if (current->userAns.length() == 1 && current->choices.count(current->userAns[0])) {
                    if (current->userAns == current->correctAns) {
                        totalEarned += current->pointVal;
                        totalCorrect++;
                    }
                    current->answered = true;
                    break;
                }
                cout << "[Answer not recognized, please try again!]\n";
            }
        }
        else if (current->type == "tf") {
            while(true) {
                cout << "Your answer: ";
                getline(cin >> ws, current->userAns);

                if (current->userAns == "true" || current->userAns == "false") {
                    if (current->userAns == current->correctAns) {
                        totalEarned += current->pointVal;
                        totalCorrect++;
                    }
                    current->answered = true;
                    break;
                }
                cout << "[Answer not recognized, please try again!]\n";
            }
        }
        else if (current->type == "wr") {
            cout << "Your answer: ";
            getline(cin >> ws, current->userAns);

            if (current->userAns == current->correctAns) {
                totalEarned += current->pointVal;
                totalCorrect++;
            }
            current->answered = true;
        } 
    }
}
