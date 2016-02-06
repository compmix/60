#ifndef BinaryTreeH
#define BinaryTreeH

#include <iomanip>
#include "BinaryHeap.h"
using namespace std;

template <typename T>

class BinaryTree
{
  T letter; 
  int value;
  BinaryTree<T> *left;
  BinaryTree<T> *right;
  

public:
  void setData(char c, T val, BinaryTree<T> *l, BinaryTree<T> *r)
  {
    letter = c;
    value = val;
    left = l;
    right = r;
  }
  
  int getCount() const
  {
    return value;
  }
  
  void printTree()
  {
    // edit to print inorder traversal of tree
    cout << letter << ":" << value << " ";
  }
 
  bool operator < (const BinaryTree &rhs) const
  {
    return value < rhs.value;
  }   

}; //BinaryTree class

#endif