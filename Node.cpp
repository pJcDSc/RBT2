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
  isred = false;
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
  isred = !isred;
}

//Return whether node is red or not
bool Node::isRed() {
  return isred;
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
