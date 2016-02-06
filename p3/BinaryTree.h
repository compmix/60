#ifndef BinaryTreeH
#define BinaryTreeH

#include <iomanip>
#include "BinaryHeap.h"
using namespace std;

template <typename Object>
class BinaryTree
{
public: 
  Object data; 
  int count;
  BinaryTree<Object> *self;
  BinaryTree<Object> *left;
  BinaryTree<Object> *right;

  void join(BinaryTree<Object> *l, BinaryTree<Object> *r) {
    data = '\0';
    count = l->count + r->count;
    left = l;
    right = r;
  }

  void setData(Object ob, int i, BinaryTree<Object> *l, BinaryTree<Object> *r) {
    self = this;
    data = ob;
    count = i;
    left = l;
    right = r;
  }
  
  int getCount() const    {return count;}
  
  void printTree() {
    // inorder L P R
    left->printTree();
    cout << data << " ";
    right->printTree();
  }
 
  bool operator < (const BinaryTree &rhs) const  {return count < rhs.count; }


}; //BinaryTree class

#endif