#include <iostream>
#include <fstream>
#include <iomanip>
#include "BinaryTree.h"
#include "BinaryHeap.h"
#define HEAP_SIZE 1000000
using namespace std;

void printHeap(BinaryHeap<BinaryTree<char> >);

int main(int argc, char **argv) {
  BinaryHeap<BinaryTree<char> > heap(HEAP_SIZE);
  BinaryTree<char> *trie, *trie1, *trie2;
  char c;

  int ascii[256] = {0};

  ifstream fileInput(argv[1]);
  if(!fileInput) return -1;   // check if file legit

  // count all characters into array
  while(fileInput.get(c))   ascii[(int)c]++;


  // iterate through ascii array to create trie leafs
  for(int i = 0; i < 256; i++) {          //cerr << ascii[i] << " ";
    // if char exists, add to heap
    if(ascii[i] > 0) {
        trie = new BinaryTree<char>;
        trie->setData((char)i, ascii[i], NULL, NULL);
        heap.insert(*trie);
    }
  }

  printHeap(heap);

  // get two mins, trie them, re-add to heap
  while(!heap.isEmpty()) {
    trie1 = heap.findMin().self;
    heap.deleteMin();
    cout << trie1 << "; " << trie1->data << endl;
    if(heap.isEmpty()) break; // last trie is full trie

    trie2 = heap.findMin().self;
    heap.deleteMin();
    cout << trie2 << ": " << trie2->data << endl;

    trie = new BinaryTree<char>;
    trie->join(trie1, trie2);
    heap.insert(*trie);

  } // while heap !empty

  int code[50];
  trie->printTree(code, 0);

  return 0;
}


void printHeap(BinaryHeap<BinaryTree<char> > heap) {
  while(!heap.isEmpty()) {
    cerr << heap.findMin().data;
    heap.deleteMin();
  }
  cout << endl;
}
