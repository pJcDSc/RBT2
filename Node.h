/*
Author: Peter Jin
Date: 1/10/20
RBT demo node header 
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {

 public:

  //Constructor
  Node(int);

  //Get value of node
  int getValue();
  
  //Set value of node
  void setValue(int);

  //Get pointer to left node
  Node* getLeft();

  //Set left node
  void setLeft(Node*);

  //Get pointer to right
  Node* getRight();

  //Set right node
  void setRight(Node*);
  
  //Get parent
  Node* getParent();
  
  //Set parent
  void setParent(Node*);

  //Get uncle
  Node* getUncle();

  //Get Sibling
  Node* getSibling();
  
  //Toggle color
  void toggleColor();

  //Called on node that goes down
  /*       N             c
          / \           / \
         b  c    -->   N  e
           / \        / \ 
          d   e      b   d
  */
  void rotateLeft();

  bool isRed();

  //Same as rleft but reverse (still called on Node that goes down)
  void rotateRight();
  
  //Destructor
  ~Node();

private:

  Node* left = NULL;
  Node* right = NULL;
  Node* parent = NULL;
  int value;
  bool isred; 

};

#endif
