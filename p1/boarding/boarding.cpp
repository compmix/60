#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;



enum AisleState { EMPTY, NEW, STOR_1, STOR_2, WAITING};
/*  Definition of states:
 *
 *  EMPTY: Row is completely empty
 *  NEW: new passenger in row, needs to store luggage
 *  STOR_1: First of two stages to store luggage
 *  STOR_2: Second of two stages to store luggage
 *  WAITING_TO_MOVE: Passenger waiting for up to 2 other passengers to move out of their seats
 *
 *
*/

class Passenger {
  public:
    int number;
    char letter;
};

class Row {
  public:
    int rowID;
    StackAr<char> ABC;
    StackAr<char> DEF;
    StackAr<Passenger> out;
    Passenger next;
    AisleState state;
    
};

void parsePassengers(ifstream *fileInput, Queue<Passenger> *PBoarding) {
  Passenger temp;
  char buf;
  int row;
  while (1) {
    buf = fileInput->get();

    if(buf == '\n') break;  // end when done with the line

    row = buf  - '0';   // first char is an row number

    buf = fileInput->get();
    if(buf < 'A') {              // if the next char is a number
      row = (10 * row) + (buf - '0');
      buf = fileInput->get();    // the next char is a letter
    }
    
    temp.number = row;
    temp.letter = buf;

    PBoarding->enqueue(temp);

    fileInput->get();              // remove trailing space

    //  cerr << temp.number << temp.letter << endl;
  }
}

int main(int argc, char** argv)
{
  int clock = 0;
  Queue<Passenger> PBoarding(288);
  Queue<Row> RowList(48);

  ifstream fileInput(argv[1]);
  if (!fileInput) {
      cout << "Failed to open " << argv[1] << "." << endl;  
      return -1;
  }


// I. Initialization //
  parsePassengers(&fileInput, &PBoarding);

  Row curRow;
  for(int i = 48; i > 0; i--) {
    curRow.rowID = i;
    curRow.state = EMPTY;
    RowList.enqueue(curRow);
  }

   cerr << curRow.rowID << endl;
// II. Put passengers where they belong. //
//1. check row 48
//6:07 PMFelix2. if not empty, do stuff
//6:07 PMFelix3. use getFront() on rowList to get the information from row 47
//6:07 PMFelix3a. check if they have a next Passenger
//6:08 PMFelix3b. copy nextPassenger from row 47 to row 48
//
//


  while(1){
    Row prevRow;

    for(int i = 48; i > 0; i--) {       // iterate back to front
      curRow = RowList.dequeue();
      Row prevRow;

      switch(curRow.state) {
        case EMPTY:
              if(curRow.rowID == 1)     // if row 1 empty, board next passenger in queue
                  curRow.next = PBoarding.dequeue();
              else                      // for all other rows get from the previous row
                prevRow = RowList.getFront();
              curRow.state = NEW;
              break;
        case NEW:
              if(curRow.next.number == curRow.rowID)     // if passenger needs to sit here
                curRow.state = STOR_1;
              else                                       // else we know next time to get a new passenger
                curRow.state = EMPTY;
              break;
        case STOR_1:
              curRow.state = STOR_2;
              break;
        case STOR_2:
              curRow.state = WAITING;
              break;
        case WAITING:
              if(curRow.next.letter == ('A' | 'B' | 'C')) {    // check for existing
                if(curRow.ABC.isEmpty()) {                      // if ABC empty, just fill it
                  curRow.ABC.push(curRow.next.letter);
                } else {                                        // if ABC not empty, iterate.
                    while(!ABC.isEmpty()) {
                      if(curRow.ABC.top() < curRow.next.letter) { // if the passenger can just sit down
                        curRow.ABC.push(curRow.next.letter);
                        break;
                      }
                      
                    }
                }

              }

              break;


      } //switch


/*
          if(curRow.next.number == curRow.rowID){       // if waiting passenger belongs in this row, do stuff



            // update states
          } else {


            prevRow = RowList.getFront();
            if (prevRow.next.number != prevRow.rowID) {
            curRow.next = prevRow.next.number;
          }


          }

*/


      RowList.enqueue(curRow);
   }//for



   clock += 5;
   break;
  } //while

  return 0;
}



/*
  Row row1, row2, row3, row4, row5, row6, row7, row8, row9, row10,
      row11, row12, row13, row14, row15, row16, row17, row18, row19, row20,
      row21, row22, row23, row24, row25, row26, row27, row28, row29, row30,
      row31, row32, row33, row34, row35, row36, row37, row38, row39, row40,
      row41, row42, row43, row44, row45, row46, row47, row48;
*/
