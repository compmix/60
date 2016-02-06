#include <iostream>

using namespace std;

template <class Object> 
class BinaryTree {
  public:
    BinaryTree();
    BinaryTree(BinaryTree* p, BinaryTree* l, BinaryTree* r);
    void insert(Object);
    void printTree();

    BinaryTree *parent;
    BinaryTree *left;
    BinaryTree *right;
    Object data;

};

template <class Object>
BinaryTree<Object>::BinaryTree() {
      parent = NULL;      // NULL is root
      left = NULL;
      right = NULL;
}

template <class Object>
BinaryTree<Object>::BinaryTree(BinaryTree* p, BinaryTree* l, BinaryTree* r) {
      parent = p;
      left = l;
      right = r;

      if(p->left == NULL) p->left = this;
      else if (!p->right) p->right = this;
    }

template <class Object>
void BinaryTree<Object>::insert(Object obj) {
  
}

template <class Object>
void BinaryTree<Object>::printTree() {
      cerr << "p == " << parent << endl;
      cerr << "l == " << left << endl;
      cerr << "r == " << right << endl;
}