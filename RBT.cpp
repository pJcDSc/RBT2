/*
 * Author: Peter Jin
 * Date: 2/27/20
 * Red-Black Tree Demo Class
 * This is the class that actually does everything
 * Printing tree algorithm found on techiedelight
 * Insertion for red black tree algorithms found on wikipedia
 * Deletion found on GeeksforGeeks
 */

#include "RBT.h"
#include "Node.h"
#include <iostream>
#include <cstring>

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
      rotateLeft(p);
      n = n -> getLeft();                   //Re-set n to lower left node so cases match up
    }
    else if (n == p -> getLeft() && p == g -> getRight()) { //g right subtree, p left subtree. Rotate n to outside
      rotateRight(p);
      n = n -> getRight();                  //Re - set n to lower right node so cases match up in part 2
    }

    p = n -> getParent();
    g = p -> getParent();                   //Update pointers in case any of them have changed after rotations
    if (n == p -> getLeft()) {              //Left subtree
      rotateRight(g);                   //Rotate p into g's spot, g goes down
    }
    else {
      rotateLeft(g);          
    }
    if (g == head) head = p;                //update head pointer if necessary
    p -> toggleColor();                     //Set p to black, g to red (previously established p is red, g is black)
    g -> toggleColor();
  }
}

//public display tree function
void RBT::displayTree() {
  displayTree(head, NULL, false);
}

//Helper to print branches while printing tree
void RBT::printBranches(Trunk* p) {
  if (p == NULL) return;
  printBranches(p -> prev);
  cout << p -> str;
}

//private display tree function
//algorithm found at techiedelight.com/c-program-print-binary-tree
void RBT::displayTree(Node* h, Trunk* prev, bool left) {
  if (h == NULL) return;

  char indent[5];
  strcpy(indent, "    ");
  Trunk* trunk = new Trunk(prev, indent);
  
  displayTree(h -> getLeft(), trunk, true);

  if (prev == NULL) trunk -> str = "---";
  else if (left) {
    trunk -> str = ".---";
    strcpy(indent, "   |");
  }
  else {
    trunk -> str = "`---";
    prev -> str = indent;
  }

  printBranches(trunk);
  cout << (h->isRed() ? "\033[1;31m" : "\033[1;30m") << h -> getValue() << "\033[0m" << endl;

  if (prev != NULL) {
    prev -> str = indent;
  }
  trunk -> str = "   |";

  displayTree(h -> getRight(), trunk, false);
}

//public delete node function
void RBT::deleteNode(int n) {
  deleteNode(head, n);
}

//private delete node function
void RBT::deleteNode(Node*& h, int n) {
  if (h == NULL) {
    cout << "Empty tree or node not found" << endl;
    return;
  }
  if (n < h -> getValue()) {
    Node* temp = h -> getLeft();
    deleteNode(temp, n);
    return;
  }
  if (n > h -> getValue()) {
    Node* temp = h -> getRight();
    deleteNode(temp, n);
    return;
  }

  Node* child = NULL;
  if (h -> getLeft() != NULL && h -> getRight() != NULL) { //Two children, same procedure as bst
    child = h -> getRight();
    while (child -> getLeft()) child = child -> getLeft();
    
    h -> setValue(child -> getValue());
    deleteNode(child, child -> getValue());
  }
  else if (h -> getLeft() != NULL || h -> getRight() != NULL) { //One child
    child = (h -> getRight() == NULL ? h -> getLeft() : h -> getRight()); //Child is the child of the h
    bool bothBlack = (!child -> isRed() && !h -> isRed());
    if (head == h) {                    //if head, replace h with child
      h -> setValue(child -> getValue());
      h -> setRight(NULL);
      h -> setLeft(NULL);
      delete child;
    }
    else {
      if (h == h -> getParent() -> getLeft()) {
	h -> getParent() -> setLeft(child);
      } else {
	h -> getParent() -> setRight(child);
      }
      delete h;
      child -> setParent(h -> getParent());
      if (bothBlack) { //Double black at child
	fixDBlack(child);
      } else {   //No double black, recolor suffices
        if (child -> isRed()) child -> toggleColor(); //Color u black
      }
    }
  }
  else {                  //No children (leaf)
    if (head == h) { //if h is root delete h, set root to NULL
      head = NULL;
      delete h;
    } else {
      if (!h -> isRed()) { //Double black leaf node
	fixDBlack(h);
      } else {             //No double black
	if (h -> getSibling() != NULL && !h -> getSibling() -> isRed()) h -> getSibling() -> toggleColor(); //Set sibling to red
      }
      if (h -> getParent() -> getLeft() == h) h -> getParent() -> setLeft(NULL); //Delete h from tree
      else h -> getParent() -> setRight(NULL);
      delete h;
    }
  }
}

//Function to fix double black node
void RBT::fixDBlack(Node* n) {
  if (head == n) //Root
    return;

  Node* sibling = n -> getSibling();
  Node* parent = n -> getParent();

  if (sibling == NULL) {
    //Push double black up (no sibling)
    fixDBlack(parent);
  }
  else {
    if (sibling -> isRed()) { //sibling is red
      if (!parent -> isRed()) parent -> toggleColor(); //set parent to red
      sibling -> toggleColor(); //set sibling to black
      if (sibling == parent -> getLeft()) { //Sibling on left
	rotateRight(parent);
      } else {
	rotateLeft(parent);
      }
      fixDBlack(n); //recurse
    }
    else { //sibling is black
      if (sibling -> getLeft() && sibling -> getLeft() -> isRed() ||
	  sibling -> getRight() && sibling -> getRight() -> isRed()) { //If sibling has red children
	if (sibling -> getLeft() && sibling -> getLeft() -> isRed()) { //if left is red
	  if (sibling -> getParent() -> getLeft() == sibling) { //sibling to left of parent
	    if (sibling -> getLeft() -> isRed() != sibling -> isRed()) sibling -> getLeft() -> toggleColor(); //Set sibling left to sibling color
	    if (sibling -> isRed() != sibling -> getParent() -> isRed()) sibling -> toggleColor(); //Set sibling to parent color
	    rotateRight(parent);
	  } else { //sibling to right of parent
	    if (sibling -> getLeft() -> isRed() != sibling -> getParent() -> isRed()) sibling -> getLeft() -> toggleColor(); //Set sibling left to parent color
	    rotateRight(sibling);
	    rotateLeft(parent);
	  }
	} else { //sibling right is red
	  if (sibling -> getParent() -> getLeft() == sibling) { //sibling on left
	    if (sibling -> getRight() -> isRed() != sibling -> getParent() -> isRed()) sibling -> getRight() -> toggleColor(); //Set sibling right to parent color
	    rotateLeft(sibling);
	    rotateRight(parent);
	  } else { //sibling on right
	    if (sibling -> getRight() -> isRed() != sibling -> isRed()) sibling -> getRight() -> toggleColor(); //Set sibling right to sibling color
	    if (sibling -> isRed() != sibling -> getParent() -> isRed()) sibling -> toggleColor(); //set sibling color to parent color
	    rotateLeft(parent);
	  }
	}
        if (parent -> isRed()) parent -> toggleColor(); //Set parent color to black
      } else { //sibling has two black children
	if (!sibling -> isRed()) sibling -> toggleColor(); //Set sibling color to red
	if (!parent -> isRed()) { //if parent is black
	  fixDBlack(parent);
	} else {
	  parent -> toggleColor(); //Set parent color to black
	}
      }
    }
  }
}

//Rotate a node right
/*        N            b
         / \          / \
        b  c    -->  d   N
       / \              / \
      d   e            e   c
*/
void RBT::rotateRight(Node* h) {
  Node* newp = h -> getLeft();
  Node* p = h -> getParent();
  
  if (h == head) head = newp;//Check root update

  h -> setLeft(newp -> getRight()); //set N left to (e)
  newp -> setRight(h);  //Set (b) right to N
  h -> setParent(newp); //Set N parent to (b)
  if (h -> getLeft() != NULL) { //Update (e) parent to N
    h -> getLeft() -> setParent(h);
  }

  if (p != NULL) { //Update parent
    if (h == p -> getLeft()) p -> setLeft(newp);
    else p -> setRight(newp);
  }
  newp -> setParent(p);
}

//Rotates this node left
/*         N             c
          / \           / \
          b  c    -->   N  e
            / \        / \ 
           d   e      b   d
*/
void RBT::rotateLeft(Node* h) {
  Node* newp = h -> getRight();
  Node* p = h -> getParent();

  if (h == head) head = newp; //Check root update

  h -> setRight(newp -> getLeft()); //Set N right to (d)
  newp -> setLeft(h); //Set (c) left to N
  h -> setParent(newp); //Set (c) to N parent
  if (h -> getRight() != NULL) { //Update parent for (d)
    h -> getRight() -> setParent(h);
  }

  if (p != NULL) { //Update parent
    if (h == p -> getLeft()) p -> setLeft(newp);
    else p -> setRight(newp);
  }
  newp -> setParent(p);
}

//function to replace one node with another (replace cur with chi in the tree (chi )
void RBT::replace(Node* cur, Node* chi) {
  if (cur -> getParent() == NULL) head = chi;
  chi -> setParent(cur -> getParent());
  if (cur -> getParent() != NULL) {
    if (cur == cur -> getParent() -> getLeft()) cur -> getParent() -> setLeft(chi);
    else cur -> getParent() -> setRight(chi);
  }
}

//public search function
bool RBT::search(int n) {
  return search(head, n);
}

//private search function
bool RBT::search(Node* h, int n) {
  if (h == NULL) return false; //Node not found
  if (n == h -> getValue()) return true; //Node found
  if (n < h -> getValue()) return search(h -> getLeft(), n); //n is less than h
  if (n > h -> getValue()) return search(h -> getRight(), n); //n is greater than h
}

//Destructor
RBT::~RBT() {
  while (head) deleteNode(head, head -> getValue());
}
