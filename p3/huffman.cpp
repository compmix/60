/* File: huffman.cpp
 * Authors: Jacqueline Barcena, Felix Ng
 *  Prints out Huffman encoding with an In Order traversal
 *  Reads in any text file.
 *
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "BinaryTree.h"
#include "BinaryHeap.h"
#define HEAP_SIZE 1000000
#define CODE_LENGTH 100
using namespace std;

void printHeap(BinaryHeap<BinaryTree<char> >);

int main(int argc, char **argv) {
  BinaryHeap<BinaryTree<char> > heap(HEAP_SIZE);
  BinaryTree<char> *trie, *trie1, *trie2;
  int ascii[128] = {0};
  char c;

  ifstream fileInput(argv[1]);
  if(!fileInput) return -1;   // check if file legit

  // count all characters into array
  while(fileInput.get(c))   ascii[(int)c]++;


  // iterate through ascii array to create trie leafs
  for(int i = 0; i < 128; i++) {          //cerr << ascii[i] << " ";
    // if char exists, add to heap
    if(ascii[i] > 0) {
        trie = new BinaryTree<char>;
        trie->setData((char)i, ascii[i], NULL, NULL);
        heap.insert(*trie);
    }
  }

  // get two mins, trie them, re-add to heap
  while(!heap.isEmpty()) {
    trie1 = heap.findMin().self;
    heap.deleteMin();                 // cerr << trie1 << ": " << trie1->data << endl;
    if(heap.isEmpty()) break;         // last trie is full trie

    trie2 = heap.findMin().self;
    heap.deleteMin();                 // cerr << trie2 << ": " << trie2->data << endl;

    trie = new BinaryTree<char>;
    trie->join(trie1, trie2);
    heap.insert(*trie);
  } // while heap !empty


  int code[CODE_LENGTH] = {0};
  trie->printTree(code, 0);

  return 0;
}

