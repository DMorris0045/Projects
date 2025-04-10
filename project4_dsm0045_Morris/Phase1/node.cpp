#include "node.h"

node::node(int id) {
    this->id = id;              // question number
    this->next = nullptr;       // points to the next node in the list
    this->pointVal = 0.0;       // defualt point sccore
}

