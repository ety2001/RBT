// Main.cpp
#include <iostream>
#include <fstream>
#include "Node.h"

using namespace std;
//inserts a new value into the tree
Node* insert(int intput, Node* tree){
  if(tree == NULL){
    return new Node(intput);
  }
  // recursively add
  if(intput <= tree->getVal()){
    tree->setLeft(insert(intput, tree->getLeft()));
  }
  // recursively add
  else{
    tree->setRight(insert(intput, tree->getRight()));
  }
  return tree;
}

// add right branch to rightmost leaf of left branch
void insertRight(Node* right, Node* left){
  if(left->getRight() == NULL){
    left->setRight(right);
  }
  else{
    insertRight(right, left->getRight());
  }
}

// remove a value from the tree
Node* remove(int intput, Node* tree){
  if(tree != NULL){
    if(intput == tree->getVal()){
      // if tree is a leaf
      if(tree->getRight() == NULL && tree->getLeft() == NULL){
        return NULL;
      }
      // if tree has only a left child
      else if(tree->getRight() == NULL){
        return tree->getLeft();
      }
      // if tree has only a right child
      else if(tree->getLeft() == NULL){
        return tree->getRight();
      }
      else{
        // add right branch to rightmost leaf of left branch
        insertRight(tree->getRight(), tree->getLeft());
        return tree->getLeft();
      }
    }
    // remove value from left branch
    else if(intput < tree->getVal()){
      tree->setLeft(remove(intput, tree->getLeft()));
      return tree;
    }
    // remove value from right branch
    else {
      tree->setRight(remove(intput, tree->getRight()));
      return tree;
    }
  }
  return NULL;
}

void printTree(Node* tree, int depth){
  if(tree!=NULL){
    for (int i = 0; i < depth; i++) {
      cout<<"\t";
    }
    cout<<tree->getVal()<<endl;
    printTree(tree->getLeft(), depth+1);
    printTree(tree->getRight(), depth+1);
  }
}

int main(){
  bool run = true;
  char input [1000];
  int intput;
  Node* tree = NULL;
  while(run == true){
    cout<<"Add numbers(A)"<<endl<<"Add file(F)"<<endl<<"Remove number(R)"
    <<endl<<"Show tree(S)"<<endl<<"Quit(Q)"<<endl;
    cin>>input;
    if(input[0] == 'A'){
      cout<<"Enter your number(s) separated by spaces"<<endl;
      while(cin>>intput){
        tree = insert(intput, tree);
      }
      printTree(tree,0);
    }
    else if(input[0] == 'F'){
      cout<<"Enter the name of your file"<<endl;
      cin>>input;
      fstream myFile(input);
      while(myFile >> intput){
        tree = insert(intput, tree);
      }
      printTree(tree,0);
    }
    else if(input[0] == 'R'){
      cout<<"Enter your number"<<endl;
      cin>>intput;
      tree = remove(intput, tree);
    }
    else if(input[0] == 'S'){
      printTree(tree, 0);
    }
    else if(input[0] == 'Q'){
      run = false;
    }
    else{
      cout<<input[0]<<" is not a valid command"<<endl;
    }
  }
  return 0;
}
