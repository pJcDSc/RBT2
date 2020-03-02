/*
Author: Peter Jin
Date: 1/11/20
RBT demo node class
*/

#include <iostream>
#include "Node.h"

using namespace std;

//Constructor
Node::Node(int v) {
  value = v;
  right = NULL;
  left = NULL;
  parent = NULL;
  isRed = false;
}

//Get value of node
int Node::getValue() {
  return value;
}

//Set value of node
void Node::setValue(int v) {
  value = v;
}

//Get pointer to left node
Node* Node::getLeft() {
  return left;
}

//Set left node
void Node::setLeft(Node* n) {
  left = n;
}

//Get pointer to right
Node* Node::getRight() {
  return right;
}

//Set right node
void Node::setRight(Node* n) {
  right = n;
}

//Get pointer to parent
Node* Node::getParent() {
  return parent;
}

//Set parent node
void Node::setParent(Node* n) {
  parent = n;
}

//Switch the color of the node
void Node::toggleColor() {
  isRed = !isRed;
}

//Rotates this node left
/*        N             c
         / \           / \
        b  c    -->   N  e
          / \        / \ 
         d   e      b   d
*/
void rotateLeft() {
  if (right == NULL) return; //can't rotate a leaf in
  Node* rt = right; //Node that will be rotated to top (c)
  Node* p = parent; //Original parent
  
  right = right -> getLeft(); //Set this right to be right's left (d) 
  rt -> setLeft(this);        //Set this to be below rt (c - N)
  parent = rt;                //Update this parent to (c) 
  if (right != NULL) {        //if (d) is not NULL update its parent
    right -> setParent(this);
  }

  //If this is not the root node we need to update parent also
  if (p != NULL) {
    if (this == p -> getLeft()) {
      p -> setLeft(rt);
    }
    else {
      p -> setRight(rt);
    }
  }
  rt -> setParent(p);        //Update new top node's parent to be our old parent
}

//Rotate a node right
/*        N            b
         / \          / \
        b  c    -->  d   N
       / \              / \
      d   e            e   c
*/  
void rotateRight() {
  if (left == NULL) return; //can't rotate a leaf into the tree
  Node* lft = left;
  Node* p = parent;

  left = left -> getRight(); //Set this left to be lefts right (e)
  lft -> setRight(this);     //Set this below left (b - N)
  parent = lft;              //Update this parent to (b)
  if (left != NULL) {        //if (e) is not NULL update its parent
    left -> setParent(this);
  }

  //If this is not the root node we have to update parent also
  if (p != NULL) {
    if (this == p -> getLeft()) {
      p -> setLeft(lft);
    }
    else {
      p -> setRight(lft);
    }
  }
  lft -> setParent(p);
} 

//Get Sibling (return parent's other child)
Node* Node::getSibling() {
  if (parent == NULL) return NULL;
  if (this == parent -> getLeft()) return parent -> getRight();
  return parent -> getLeft();
}

//Get uncle (return parent's sibling)
Node* Node::getUncle() {
  if (parent == NULL) return NULL;
  return parent -> getSibling();
}

//Destructor
Node::~Node() {
  //Nothing to delete
}
