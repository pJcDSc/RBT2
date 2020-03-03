/*
 * Author: Peter Jin
 * Date: 2/24/20
 * Red-Black tree header
 */

#ifndef RBT_H
#define RBT_H

#include "Node.h"

class RBT {

  public:

    //Constructor
    RBT();

    //Add node
    void addNode(int);

    //Display tree
    void displayTree();

    //Destructor
    ~RBT();

  private:

    void addNode(Node*&, Node*);
    void displayTree(Node*, int);
    void fixTree(Node*);
    void deleteTree(Node*);
    Node* head;

};	

#endif
