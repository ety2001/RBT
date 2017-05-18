// RBnode.cpp
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

RBnode *RBnode::searchNode(RBnode *p, int val)
{
    if (p == RBNULL)
        return RBNULL;
    else if (p->value == val)
        return p;
    else if (val < p->value) 
	return searchNode(p->left, val);
    else
	return searchNode(p->right, val);
}

void RBnode::replaceNode(RBnode *p, RBnode *q)
{
    if (p->parent == RBNULL)
    {
        RBnode::RBroot = q;
    }
    else if (p == p->parent->left) 
    {
        p->parent->left = q;
    }
    else 
    {
        p->parent->right = q;
    }

    q->parent = p->parent;
}

void RBnode::removefix(RBnode *t)
{
    while (t != RBnode::RBroot && t->color == 'b') 
    {
        if (t == t->parent->left) 
	{
            RBnode *w = t->parent->right;
	    if (w->color == 'r')
	    {
		w->color = 'b';
		t->parent->color = 'r';
		leftrotate(t->parent);
                w = t->parent->right;
	    }

	    if (w->left->color == 'b' && w->right->color == 'b') 
	    {
		w->color = 'r';
		t = t->parent;
	    }
	    else
	    {
		if (w->right->color == 'b')
		{
	            w->left->color = 'b';
		    w->color = 'r';
		    rightrotate(w);
		    w = t->parent->right;
		}

		w->color = t->parent->color;
		t->parent->color = 'b';
		w->right->color = 'b';
		leftrotate(t->parent);
		t = RBnode::RBroot;
	    }
	}	
	else
	{
            RBnode *w = t->parent->left;
	    if (w->color == 'r')
	    {
		w->color = 'b';
		t->parent->color = 'r';
		rightrotate(t->parent);
		w = t->parent->left;
	    }

	    if (w->left->color == 'b' && w->right->color == 'b')
	    {
		w->color = 'r';
		t = t->parent;
	    }
	    else
	    {
		if (w->left->color == 'b')
		{
	            w->right->color = 'b';
		    w->color = 'r';
		    leftrotate(w);
		    w = t->parent->left;
		}

		w->color = t->parent->color;
		t->parent->color = 'b';
		w->left->color = 'b';
		rightrotate(t->parent);
		t = RBnode::RBroot;
	    }
	}
    }
    t->color = 'b';
}

/*
 * Top Level Methods
 */

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

bool RBnode::search(int val)
{
    if (searchNode(RBnode::RBroot, val) == RBNULL)
        return false;
    return true;
}

RBnode *RBnode::minimumNode(RBnode *p)
{
    while (p->left != RBNULL)
    {
        p = p->left;
    }
    return p;
}

void RBnode::remove(int val)
{
    RBnode *z = searchNode(RBnode::RBroot, val);
    if (z == RBNULL)
    {
        cout << val << " is not in the tree" << endl;
        return;
    }
 
    RBnode *y = z;
    char yc = y->color;
    RBnode *x;
 
    if (z->left == RBNULL)
    {
        x = z->right; 
	replaceNode(z, z->right);

    }
    else if (z->right == RBNULL)
    {
        x = z->left;
	replaceNode(z, z->left);
    }
    else
    {
        y = minimumNode(z->right);
	yc = y->color;
	x = y->right;
	if (y->parent == z)
	{
	    x->parent = y;
	}
	else 
	{
            replaceNode(y, y->right);
	    y->right = z->right;
	    y->right->parent = y;
	}
	replaceNode(z, y);
	y->left = z->left;
	y->left->parent = y;
	y->color = z->color;
    }

    if (yc == 'b')
    {
        removefix(x);
    }
}
