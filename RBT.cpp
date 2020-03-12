/*
 * Author: Peter Jin
 * Date: 2/27/20
 * Red-Black Tree Demo Class
 * This is the class that actually does everything
 */

#include "RBT.h"
#include "Node.h"
#include <iostream>

using namespace std;

//Constructor
RBT::RBT() {
  head = NULL;
}

//public addNode function which calls private addnode function
void RBT::addNode(int in) {
  Node* n = new Node(in);
  addNode(head, n);
  fixTree(n);
}

//recursive private part of the addnode function
void RBT::addNode(Node* &h, Node* n) {
  if (head == NULL) {
    head = n;
    return;
  }
  if (n -> getValue() < h -> getValue()) { //go left
    if (h -> getLeft()) {                  //if node there recurse
      Node* t = h -> getLeft();
      addNode(t, n);
      return;
    }
    else {                                 //If no node there add
      h -> setLeft(n);
    }
  }
  else {                                   //go right
    if (h -> getRight()) {                 //if node there recurse
      Node* t = h -> getRight();
      addNode(t, n);
      return;
    }
    else {                                 //if no node there add
      h -> setRight(n);
    }
  }
  n -> setParent(h);                       //update new node parent
  if (!n -> isRed()) n -> toggleColor();   //set color to red (may be switched while fixing rbt)
}

//Fix tree (insert)
void RBT::fixTree(Node* n) {
  if (n == NULL) return;
  if (n -> getParent() == NULL) {            //n is the root (set color to black)
    if (n -> isRed()) n -> toggleColor();
  }
  else if (!n -> getParent() -> isRed()) {  //If parent is black don't bother
    //Do nothing
  }
  else if (n -> getUncle() && n -> getUncle() -> isRed()) { //Both parent and uncle are red (if parent is red, then grandparent MUST exist)
    n -> getParent() -> toggleColor();      //Set parent color to black
    n -> getUncle() -> toggleColor();       //Set uncle color to black
    if (!n -> getParent() -> getParent() -> isRed()) n -> getParent() -> getParent() -> toggleColor(); //Set grandparent color to red
    fixTree(n -> getParent() -> getParent());
  }
  else {                                    //Parent is red, Uncle is black or no uncle
    Node* p = n -> getParent();
    Node* g = p -> getParent();

    //If n is not in the outside of g's subtree, rotate to outside
    if (n == p -> getRight() && p == g -> getLeft()) { //g left subtree, p right subtree. Rotate n to outside
      p -> rotateLeft();
      n = n -> getLeft();                   //Re-set n to lower left node so cases match up
    }
    else if (n == p -> getLeft() && p == g -> getRight()) { //g right subtree, p left subtree. Rotate n to outside
      p -> rotateRight();
      n = n -> getRight();                  //Re - set n to lower right node so cases match up in part 2
    }

    p = n -> getParent();
    g = p -> getParent();                   //Update pointers in case any of them have changed after rotations
    if (n == p -> getLeft()) {              //Left subtree
      g -> rotateRight();                   //Rotate p into g's spot, g goes down
    }
    else {
      g -> rotateLeft();          
    }
    if (g == head) head = p;                //update head pointer if necessary
    p -> toggleColor();                     //Set p to black, g to red (previously established p is red, g is black)
    g -> toggleColor();
  }
}

//public display tree function
void RBT::displayTree() {
  displayTree(head, 0);
}

//private display tree function using inorder navigation
void RBT::displayTree(Node* h, int d) {
  if (!h) return;
  displayTree(h -> getLeft(), d+1);
  for (int i = 0; i < d; i++) cout << "    ";
  //cout << h -> getValue() << (h->isRed() ? "(R)" : "(B)") << endl;
  cout << (h->isRed() ? "\033[1;31m" : "\033[1;30m") << h -> getValue() << "\033[0m" << endl;
  displayTree(h -> getRight(), d+1);
}

//public delete node function
void RBT::deleteNode(int n) {
  deleteNode(head, n);
}

//private delete node function
void RBT::deleteNode(Node*& head, int n) {

}

//Destructor
RBT::~RBT() {
  deleteTree(head);
}
/*
//Just deletes the entire tree using a postorder traversal
void RBT::deleteTree(Node* n) {
  if (!n) return;
  deleteTree(n -> getLeft());
  deleteTree(n -> getRight());
  delete n;
}
*/
