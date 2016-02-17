#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "CursorList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"
using namespace std;

vector<CursorNode <int> > cursorSpace(500000);

int getChoice()
{
  int choice;
  
  cout << "\n      ADT Menu" <<endl;
  cout << "0. Quit\n"
       << "1. LinkedList\n"
       << "2. CursorList\n"
       << "3. StackAr\n"
       << "4. StackLi\n"
       << "5. QueueAr\n"
       << "6. SkipList" << endl;
  cout << "Your choice >> ";
  cin >> choice;
  
  return choice;
}

void RunList(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  List<int> linkedlist;

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int
      linkedlist.insert(value, linkedlist.zeroth()); //do the insertions. just insert to front      
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      linkedlist.remove(value); //delete that value     
    }
  } 
}

void RunCursorList(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  CursorList<int> cursorlist(cursorSpace);

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int
      cursorlist.insert(value, cursorlist.zeroth());      
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      cursorlist.remove(value); //delete that value     
    }
  } 
}

void RunStackAr(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  StackAr<int> stackAr(500000);

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int    
      stackAr.push(value);  
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      stackAr.pop();
    }
  } 
}

void RunStackLi(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  StackLi<int> stackLi;

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int    
      stackLi.push(value);  
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      stackLi.pop();
    }
  }
}

void RunQueueAr(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  Queue<int> queueAr(500000);

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int
      queueAr.enqueue(value);      
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      queueAr.dequeue();   
    }
  } 
}

void RunSkipList(char* fileName)
{
  ifstream inf(fileName);
  char command[8]; //the command is at most 7 characters long e.g., i500000
  int value;
  SkipList<int> skiplist(0,250000);

  inf.ignore(1000, '\n'); //ignore the first line of file, just contains a description of file

  while (inf >> command)
  {
    if (command[0] == 'i')
    {
      value = atoi(strtok(command, "i")); //get the value to insert. use atoi to convert to int
      skiplist.insert(value);    
    }

    else if (command[0] == 'd')
    {
      value = atoi(strtok(command, "d")); //get the value to delete
      skiplist.deleteNode(value); 
    }
  } 
}

int main(int argc, char** argv)
{
  char filename[9];
  int choice;
  CPUTimer ct;

  cout << "Filename >> ";
  cin >> filename;

  do
  {
    choice = getChoice();
    ct.reset();

    switch (choice)
    {
      case 1: RunList(filename); break;      
      case 2: RunCursorList(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;

    } // switch
  
    cout << "CPU time: " << ct.cur_CPUTime() << endl;

  } while(choice > 0);

  return 0;
}

