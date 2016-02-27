// Author Felix Ng
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"
#include "mynew.h"
#include <iostream>
#include "QuadraticProbing.h"


class Defragmenter
{
public:
	StoredBlock storedBlock;
	QuadraticHashTable<StoredBlock> *swapTable;
	DiskDrive* diskDrive;

	Defragmenter(DiskDrive *diskDrive);
	DiskBlock* findBlock(unsigned blockID);

}; // class Defragmenter
#endif
