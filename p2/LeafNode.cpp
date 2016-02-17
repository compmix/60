#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


LeafNode* LeafNode::remove(int value)
{   // if merge, returns ptr to child to be deleted
    // no merge, returns NULL

  removeVal(value);
  
  if (count >= (leafSize + 1) / 2) // if no underflow, just return
    return NULL;

  if (leftSibling)
  {
    if (leftSibling->getCount() > (leafSize + 1) / 2) // if leftSibling can lend
    {
      borrow(leftSibling, leftSibling->getMaximum());
      return NULL;
    }     
    else // merge with left
      return mergeLeft();

  }
  else if (rightSibling) // left sibling non-existent
  {
    if (rightSibling->getCount() > (leafSize + 1) / 2)
    {
      borrow(rightSibling, rightSibling->getMinimum());
      return NULL;
    }          
    else // merge with right
      return mergeRight();
  }

  //return NULL;  // filler for stub
  return this;
}  // LeafNode::remove()


LeafNode* LeafNode::mergeLeft() // new method
{
  for (int i = 0; i < count; i++)
    leftSibling->insert(values[i]);           // insert values of calling leafNode into left sibling
    
  leftSibling->setRightSibling(rightSibling); // set leftSibling's right sibling to right sibling of calling node
  
  if (rightSibling)
    rightSibling->setLeftSibling(leftSibling);  // set rightSibling's left sibling to left sibling of calling node
  
  return this;                                // return this child so it can be deleted (since it merged)
}


LeafNode* LeafNode::mergeRight()  // new method
{
  for (int i = 0; i < count; i++)
    rightSibling->insert(values[i]);
    
  rightSibling->setLeftSibling(leftSibling);
  
  if (leftSibling)
    leftSibling->setRightSibling(rightSibling);

  return this;
}


void LeafNode::borrow(BTreeNode *sibling, int borrowVal) // new method
{
  sibling->remove(borrowVal);
  insert(borrowVal);
  
  if (parent)
  {
    //parent->resetMinimum(this);
    parent->resetMinimum(sibling);
  } 
}


void LeafNode::removeVal(int value) // new method
{
  int index;
  bool valFound = false;
  for (index = 0; index < count; index++)
  {
    if (value == values[index])
    {
      valFound = true;
      break;
    }
  }
  
  if (valFound == true)
  {
    for (int i = index; i < count - 1; i++)
      values[i] = values[i + 1];
    
    count--;
  }
  
  if (parent)
    parent->resetMinimum(this);
} // LeafNode::removeVal()


LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

