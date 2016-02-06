#include <iostream>
#include <fstream>
#include <iomanip>
#include "BinaryTree.h"
#include "BinaryHeap.h"
#define HEAP_SIZE 1000000

using namespace std;

void printHeap(BinaryHeap<char>);

int main(int argc, char **argv) {
  BinaryHeap<char> heap(HEAP_SIZE);
  BinaryTree<char> trie;

  ifstream fileInput(argv[1]);
  if(!fileInput) return -1;   // check if file legit

  for(char c; !fileInput.eof(); ) {
    fileInput.get(c);
    heap.insert(c);
  } // while fileInput

  printHeap(heap);

  while(!heap.isEmpty()) {
    



  } // while heap !empty

  trie.insert('a');
  //trie.printTree();

  return 0;
}


void printHeap(BinaryHeap<char> heap) {
  while(!heap.isEmpty()) {
    cout << heap.findMin();
    heap.deleteMin();
  }
}