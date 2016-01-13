#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

class Row {
  StackAr<bool> ABC;
  StackAr<bool> DEF;
};

void parsePassengers(ifstream *fileInput, Queue<int> *PBoardingNumber, Queue<char> *PBoardingLetter) {
  char buf;
  while (1) {
    buf = fileInput->get();

    if(buf == '\n') break;  // end when done with the line

    int row = buf  - '0';   // first char is an row number

    buf = fileInput->get();
    if(buf < 'A') {              // if the next char is a number
      row = (10 * row) + (buf - '0');
      buf = fileInput->get();    // the next char is a letter
    }
    
    PBoardingNumber->enqueue(row);
    PBoardingLetter->enqueue(buf);

    fileInput->get();              // remove trailing space

//  cerr << row << buf << endl;
  }
}

int main(int argc, char** argv)
{
  //char filename[256];
  int clock = 0;
  Queue<int> PBoardingNumber(288);
  Queue<char> PBoardingLetter(288);

  ifstream fileInput(argv[1]);
  if (!fileInput) {
      cout << "Failed to open " << argv[1] << "." << endl;  
      return -1;
  }

//  cerr << "Opening " << argv[1] << "..." << endl;

/*
  Row row1, row2, row3, row4, row5, row6, row7, row8, row9, row10,
      row11, row12, row13, row14, row15, row16, row17, row18, row19, row20,
      row21, row22, row23, row24, row25, row26, row27, row28, row29, row30,
      row31, row32, row33, row34, row35, row36, row37, row38, row39, row40,
      row41, row42, row43, row44, row45, row46, row47, row48;
*/

// I. Parse passenger queues. //
  parsePassengers(&fileInput, &PBoardingNumber, &PBoardingLetter);

// II. Put passengers where they belong. //
  while(1){






  }





  return 0;
}