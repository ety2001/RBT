// RBnode.h

/*
 * Red-Black trees are a useful way of creating a binary search tree that 
 * balances itself (roughly).  Red-black trees have a certain set of properties:
 *
 * 1. A node is either red or black.
 * 2. The root is black.
 * All leaves (NULL) are black.
 * Both children of every red node are black.
 * Every simple path from a given node to any of its descendant leaves 
 * contains the same number of black nodes.
 */

class RBnode
{
public:
    // RB Tree Node
    int value;
    RBnode *parent;
    char color;
    RBnode *left;
    RBnode *right;

    RBnode(int val);
    ~RBnode();

    // RB Tree
    static RBnode *RBroot;

    static void leftrotate(RBnode *p);
    static void rightrotate(RBnode *p);
    static void insertfix(RBnode *t);
    static void printNode (RBnode *p, int indent);

    static void newRBTree();
    static void insert(int val);
    static void print();
};

