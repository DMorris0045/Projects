#include "node.h"

//constructor for nodes
// initializes a question with a given node id
node::node(int id) {
    this->id = id; //sets node id
    this->next = nullptr; // initializes the next pointer to null
    this->pointVal = 0.0; // default point value
}