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
    self = this;
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
  
  void printTree(int *code, int index) {
    // inorder L P R
    if (left)
    {
      code[index] = 0;
      left->printTree(code, index+1);
    }
      
    if (data != '\0') // don't print internal nodes
    {
      cout << data << setw(5) << count << " ";
      for (int i = 0; i < index; i++)
        cout << code[i];
      cout << endl;
    }

    if (right)
    {
      code[index] = 1;
      right->printTree(code, index+1);
    }
    
  }
 
  bool operator < (const BinaryTree &rhs) const  {return count < rhs.count; }


}; //BinaryTree class

#endif