// Node.cpp

#include "Node.h"

Node::Node(int newval){
  val = newval;
  left = NULL;
  right = NULL;
};

/*
Node::~Node(){
  left = NULL;
  right = NULL;
}
*/

Node* Node::getLeft(){
	return left;
};

Node* Node::getRight(){
	return right;
};

char Node::getVal(){
	return val;
};

void Node::setLeft(Node* node){
	left = node;
};

void Node::setRight(Node* node){
	right = node;
};
