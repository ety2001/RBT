// Node.h

class Node{
  private:
    int val;
    Node* left;
    Node* right;
  public:
    Node(int);
    Node* getLeft();
    Node* getRight();
    int getVal();
    void setLeft(Node*);
    void setRight(Node*);
}
