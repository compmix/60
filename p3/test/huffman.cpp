#include <iostream>
#include <fstream>
#include "BinaryHeap.h"
#include "BinaryTree.h"

int main(int argc, char** argv)
{
  BinaryHeap<BinaryTree<char> > heap; // not sure if this is correct
  BinaryTree<char> t;
  BinaryTree<char> left, right;
  int count[256] = {0};
  char c;
  ifstream inf(argv[1]);
     
  while (inf.get(c))  // iterate through file char by char
    count[(int)c]++;  // use char's ascii value as index and keep track of count for that char
                      // i.e. a has an ascii val of 97, so count[97] holds the number of times 'a' shows up in the file
  
  //build a table of letters/occurrences. keep sorted by occurrences
  for (int i = 0; i < 256; i++)
  {
    if (count[i] != 0)
    {
      t.setData((char)i, count[i], NULL, NULL);
      t.printTree(); // just to see if each t is being set correctly
      heap.insert(t);
    }
  }

  // remove two min from the heap and merge them
  // insert this merged object back into the heap
  // do this until only one item left in heap (this is the final trie)
  /*while(1)
  {
    heap.deleteMin(left_);
    if (heap.isEmpty()) // if freq table becomes empty after one remove, break since all items have been merged into one tree
      break;
    heap.deleteMin(right_);
    // merge the two min by creating a new tree whose left points to left_ and right points to right_. (having trouble implementing this)
    heap.insert(t);
  }
 */

  return 0;
}