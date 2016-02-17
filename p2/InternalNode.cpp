#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()


void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()



int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::remove(int value)
{  // to be written by students
  
  int pos; // will be where value needs to be deleted
  
  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);
  BTreeNode *ptr = children[pos]->remove(value);
   
  if (!ptr)
    return NULL;
  
  delete ptr; // delete the ptr returned, it is the child that merged into another
  
  for (int i = pos; i < count - 1; i++)
  {
    keys[i] = keys[i+1];
    children[i] = children[i+1];
  }
  count--;   
  
  
  if (!leftSibling && !rightSibling && count == 1)// root and only 1 child
    return children[0];                           // return only child to make it the root
 
  if (parent)
    parent->resetMinimum(this);
    
  if (count < (internalSize + 1) / 2)
  {
    if (leftSibling)
    {
      if (leftSibling->getCount() > (internalSize + 1) / 2)
      {
        borrowFromLeft();
        return NULL;
      }
      else
        return mergeLeft();
    }
    else if (rightSibling)
    {
      if (rightSibling->getCount() > (internalSize + 1) / 2)
      {
        borrowFromRight();//borrow from right
        return NULL;
      }
      else
        return mergeRight();
    }
  }

  return NULL; // filler for stub
} // InternalNode::remove(int value)


void InternalNode::borrowFromRight()
{
  //cout << "borrow from right";

  insert(((InternalNode*)rightSibling)->children[0]);

  // since borrowed from right sibling, need to shift it's keys and children toward 0, then decrement its count
  for (int i = 0; i < ((InternalNode*)rightSibling)->count - 1; i++)
  {
    ((InternalNode*)rightSibling)->keys[i] = ((InternalNode*)rightSibling)->keys[i+1];
    ((InternalNode*)rightSibling)->children[i] = ((InternalNode*)rightSibling)->children[i+1];
  }
  ((InternalNode*)rightSibling)->count--;
   
  if(((InternalNode*)rightSibling)->parent)
    ((InternalNode*)rightSibling)->parent->resetMinimum((InternalNode*)rightSibling);
      
}

void InternalNode::borrowFromLeft()
{
  insert(((InternalNode*)leftSibling)->children[count]);
  ((InternalNode*)leftSibling)->count--;
}

void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


BTreeNode* InternalNode::mergeRight()
{
  //children[count-1]->setRightSibling(((InternalNode*)rightSibling)->children[0]);
  //(((InternalNode*)rightSibling)->children[0])->setLeftSibling(children[count-1]);
  
  for (int i = 0; i < count; i++)
    ((InternalNode*)rightSibling)->insert(children[i]);

  ((InternalNode*)rightSibling)->setLeftSibling(leftSibling);  

  return this;     
}


BTreeNode* InternalNode::mergeLeft()
{
  
  for (int i = 0; i < count; i++)
    ((InternalNode*)leftSibling)->insert(children[i]);

  ((InternalNode*)leftSibling)->setRightSibling(rightSibling);  

  return this;     
}


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()

