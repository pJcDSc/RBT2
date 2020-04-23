/*
 * Author: Peter Jin
 * Date: 2/24/20
 * Red-Black tree header
 */

#ifndef RBT_H
#define RBT_H

#include "Node.h"

//Structure used for printing of treee
struct Trunk {
  Trunk* prev;
  char* str;

  Trunk (Trunk* prev, char* str) {
    this -> prev = prev;
    this -> str = str;
  }
};

class RBT {
  
 public:
  
  //Constructor
  RBT();
  
  //Add node
  void addNode(int);
  
  //Delete node
  void deleteNode(int);
  
  //Display tree
  void displayTree();

  //Search for node
  bool search(int);
  
  //Destructor
  ~RBT();

 private:

  void addNode(Node*&, Node*);
  void displayTree(Node*, Trunk*, bool);
  void printBranches(Trunk*);
  void fixTree(Node*);
  void deleteNode(Node*&, int);
  bool search(Node*, int);
  void deleteTree(Node*);
  void fixDBlack(Node*);
  void replace(Node*, Node*);
  void rotateRight(Node*);
  void rotateLeft(Node*);
  Node* head;

};	

#endif
