#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

#define SEATS 288
using namespace std;

enum AisleState { EMPTY, NEW, STOR_1, STOR_2, WAITING };
/*  Definition of states:
 *
 *  EMPTY: aisle is clear
 *  NEW: new passenger in aisle, needs to store luggage
 *  STOR_1: First of two stages to store luggage
 *  STOR_2: Second of two stages to store luggage, also sits
 *  WAITING: Passenger waiting for up to 2 other passengers to move out of their seats
 *
*/

class Passenger {
  public:
    int number;
    char letter;
    void remove() {
      number = 0;
      letter = 0;
    };

};

class Row {
  public:
    int rowID;
    StackAr<char> ABC;
    StackAr<char> DEF;
    StackAr<char> out;
    Passenger next;
    AisleState state;
    
};

void parsePassengers(ifstream *fileInput, Queue<Passenger> *PBoarding) {
  Passenger temp;
  char buf;
  int row;
  while (1) {
    buf = fileInput->get();

    if(buf == '\n' || fileInput->eof()) break;  // end when done with the line

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

void getNext(Row *curRow, Row *prevRow, Queue<Passenger> *PBoarding) {
  if(curRow->rowID == 1) {    // if row 1 empty, board next passenger in queue
      if (!PBoarding->isEmpty()) {       // if end of queue, don't get anything
        curRow->next = PBoarding->dequeue();
        curRow->state = NEW;
      }

  } else {                     // for all other rows get from the previous row
    if (prevRow->next.number > prevRow->rowID) {
      curRow->next = prevRow->next;
      curRow->state = NEW;
      prevRow->next.remove();
      prevRow->state = EMPTY;
    }
  }
}

int main(int argc, char** argv)
{
  int clock, seated;
  Queue<Passenger> PBoarding(SEATS);
  Queue<Row> RowList(48);
  Row prevRow, curRow;

  ifstream fileInput(argv[1]);
  if (!fileInput) {
      cout << "Failed to open " << argv[1] << "." << endl;  
      return -1;
  }


  // I. Initialization //
  parsePassengers(&fileInput, &PBoarding);
  clock = 0, seated = 0;

  for(int i = 48; i > 0; i--) {
    curRow.rowID = i;
    curRow.state = EMPTY;
    RowList.enqueue(curRow);
  }

  // II. Put passengers where they belong. //
  prevRow = RowList.dequeue();
  while(seated < SEATS){

    cerr << "ROW state aisle --------------------------------------seated---" << seated << " time: " << clock << endl;

    for(int i = 48; i > 0; i--) {       // iterate back to front
      curRow = prevRow;
      prevRow = RowList.dequeue();

      switch(curRow.state) {
        case EMPTY:
              getNext(&curRow, &prevRow, &PBoarding);
              break;

        case NEW:
              if(curRow.next.number == curRow.rowID)     // if passenger needs to sit here
                curRow.state = STOR_1;
              break;

        case STOR_1:
              curRow.state = STOR_2;
              break;

        case STOR_2:
              if (curRow.next.letter <= 'C'){
                if (curRow.ABC.isEmpty() || curRow.next.letter > curRow.ABC.top()){ // if row is empty or if passenger to be seated sits closer to aisle than those already seated
                  curRow.ABC.push(curRow.next.letter);                              // they can just sit down
                  seated++;
                  curRow.next.remove();
                  curRow.state = EMPTY;
                  getNext(&curRow, &prevRow, &PBoarding);

                }
                else{ // otherwise we need to start making room for them
                  curRow.out.push(curRow.ABC.topAndPop());                    
                  curRow.state = WAITING;
                }
              }
              
              // passenger is D, E, or F
              else if (curRow.next.letter >= 'D'){
                if (curRow.DEF.isEmpty() || curRow.next.letter < curRow.DEF.top()){ // if row is empty or if passenger to be seated sits closer to aisle than those already seated
                  curRow.DEF.push(curRow.next.letter);                              // they can just sit down
                  seated++;
                  curRow.next.remove();
                  curRow.state = EMPTY;
                  getNext(&curRow, &prevRow, &PBoarding);
                }
                else{ // otherwise we need to start making room for them
                  curRow.out.push(curRow.DEF.topAndPop());                    
                  curRow.state = WAITING;
                }
              }
              break;

        case WAITING:
              if (curRow.next.letter <= 'C'){
                if (curRow.ABC.isEmpty() || curRow.next.letter > curRow.ABC.top()){
                  curRow.ABC.push(curRow.next.letter);   //sit
                  curRow.next.letter = curRow.out.topAndPop();   //put whoever was in out to go next
                }
                else{                         //can't sit, take another out
                  curRow.out.push(curRow.ABC.topAndPop());
                }
              } else if (curRow.next.letter >= 'D') {
                if (curRow.DEF.isEmpty() || curRow.next.letter < curRow.DEF.top()){
                  curRow.DEF.push(curRow.next.letter);   //sit
                  curRow.next.letter = curRow.out.topAndPop();   //put whoever was in out to go next
                }
                else{                         //can't sit, take another out
                  curRow.out.push(curRow.DEF.topAndPop());
                }
              }
              
              // everyone seated one side of the aisle
              if (curRow.out.isEmpty() && (curRow.next.letter >= 'C' || curRow.next.letter <= 'D')) {
                curRow.state = STOR_2;
              }

              break;
      } //switch

      cerr << curRow.rowID << " " << curRow.state << " " << curRow.next.number << curRow.next.letter << endl;

      RowList.enqueue(curRow);
   }//for
   clock += 5;
  } //while
  cerr << "Back to front: " << clock << endl;
  
  
  // III. Delete everything. //
  PBoarding.makeEmpty();
  RowList.makeEmpty();



  

  return 0;
}

