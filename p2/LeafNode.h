#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  void addToLeft(int value, int last);
  void addToRight(int value, int last);
  void addToThis(int value);
  void addValue(int value, int &last);
  void borrow(BTreeNode *sibling, int borrowVal); // new method
  int getMaximum() const;
  int getMinimum() const;
  LeafNode* insert(int value); // returns pointer to new Leaf if splits, else NULL
  LeafNode* mergeLeft();                         // new method
  LeafNode* mergeRight();                        // new method
  LeafNode* remove(int value); // NULL == no merge
  void removeVal(int value);                     // new method

  void print(Queue <BTreeNode*> &queue);
  LeafNode* split(int value, int last);

}; //LeafNode class

#endif
