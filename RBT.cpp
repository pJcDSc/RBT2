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
void RBT::addNode(int n) {
	addNode(head, n);
}

//private Addnode function (recursive)
void RBT::addNode(Node* &h, int n) {
  if (h == NULL) {
    head = new Node(n);
    return;
  }
  
} 
