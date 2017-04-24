#include<iostream>
#include "RBnode.h"

using namespace std;

#define RBNULL 0

RBnode::RBnode(int val) {
    value = val;
    color = 'r';
    parent = RBNULL;
    left = RBNULL;
    right = RBNULL;
}

RBnode::~RBnode() {
    if (left != RBNULL) 
    {
        delete left;
    }

    if (right != RBNULL) 
    {
	delete right; 
    }
}

RBnode *RBnode::RBroot = RBNULL;

void RBnode::leftrotate(RBnode *x)
{
    RBnode *y = x->right;
        
    //connect x->right to b
    x->right = y->left;
    if (x->right != RBNULL)
    {
        x->right->parent = x;
    }
        
    //connect y to parent's x
    y->parent = x->parent;
    if (x->parent == RBNULL)
    {
        RBnode::RBroot = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
     
    //connect y to x
    y->left = x;
    x->parent = y;
}

void RBnode::rightrotate(RBnode *y)
{
    RBnode *x = y->left;
        
    y->left = x->right;
    if (y->left != RBNULL)
    {
        y->left->parent = y;
    }
        
    x->parent = y->parent;
    if (y->parent == RBNULL)
    {
        RBnode::RBroot = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
      
    x->right = y;
    y->parent = x;
}

void RBnode::insertfix(RBnode *x)
{
    RBnode *y;

    // continue to fix towards the tree root as long as the parent of
    // the current node x is red.
    while (x->parent != RBNULL && x->parent->color == 'r')
    {
        if (x->parent->parent != RBNULL && x->parent->parent->left == x->parent)
	{
            y = x->parent->parent->right;
            if (y->color == 'r')
	    {
                y->color = 'b';
                x->parent->color = 'b';
                x->parent->parent->color = 'r';
                x = x->parent->parent;
            }
	    else
	    {
                if (x->parent->right == x)
		{
                    x = x->parent;
                    leftrotate(x);
                }
                x->parent->color = 'b';
                x->parent->parent->color = 'r';
                rightrotate(x->parent->parent);
            }
        }
        else
	{
            if (x->parent->parent != RBNULL)
                y = x->parent->parent->left;
            else
                y = RBNULL;
            if (y != RBNULL && y->color == 'r')
	    {
                y->color = 'b';
                x->parent->color = 'b';
                x->parent->parent->color = 'r';
                x = x->parent->parent;
            }
	    else
	    {
                if (x->parent->left == x)
		{
                    x = x->parent;
                    rightrotate(x);
                }
                x->parent->color = 'b';
                x->parent->parent->color = 'r';
                leftrotate(x->parent->parent);
            }
        }
    }

    // always color the root black
    RBroot->color = 'b';
}

void RBnode::printNode (RBnode *p, int indent)
{
    // print indent
    for (int i = 0; i < indent; i++)
        cout << " ";

    // print a leaf
    if (p == RBNULL)
    {
        cout << "LEAF" << endl;
        return;
    }

    // print the value of the node
    cout << "Value: "<< p->value << " (Colour: " << p->color << ", ";
    if (p->parent != RBNULL) 
    {
        cout << "Parent: " << p->parent->value << ")" << endl;
    }
    else
    {
        cout << "Parent: NONE)" << endl;
    }

    // print two children
    printNode(p->left, indent+2);
    printNode(p->right, indent+2);
}

void RBnode::newRBTree()
{
    if (RBnode::RBroot != RBNULL)
        delete RBnode::RBroot;
    RBnode::RBroot = RBNULL;
}

void RBnode::insert(int val)
{
    RBnode *now, *x, *y;

    // create a red-clored node for the new value
    now = new RBnode (val);
        
    // insert the node the right place in the binary search tree 
    x = RBnode::RBroot;
    y = RBNULL;
    while (x != RBNULL){
        y = x;
        if (now->value < x->value)
	{
            x = x->left;
        }
        else
       	{
            x = x->right;
        }
    }
        
    if (y == RBNULL)
    {
        RBnode::RBroot = now;
    }
    else if (now->value < y->value)
    {
        y->left = now;
    }
    else
    {
        y->right = now;
    }
    now->parent = y;

    // fix the red-black tree violation
    insertfix(now);
}

void RBnode::print()
{
    if (RBnode::RBroot == RBNULL)
    {
        cout << "Empty Tree." << endl;
        return ;
    }

    printNode(RBnode::RBroot, 0);
}

