// Author Felix Ng
#include "DefragRunner.h"
#include "mynew.h"
#include "defragmenter.h"
#include "QuadraticProbing.h"

using namespace std;

Defragmenter::Defragmenter(DiskDrive *diskDrive) {
	DirectoryEntry *directory = diskDrive->directory;
	DiskBlock *diskBlock, *diskBlockB;
	QuadraticHashTable<DiskBlock*> *swapTable = new QuadraticHashTable<DiskBlock*> (diskBlock, 20000);
	

	cout << "Capacity: " << diskDrive->getCapacity() << endl
		 << "Number of Files: " << diskDrive->getNumFiles() << endl;

	for(int entry = 0, block = 2, next = 0; entry < diskDrive->getNumFiles(); entry++) {		// for each file (directory entry)

		next = directory[entry].getFirstBlockID();
		diskBlock = diskDrive->readDiskBlock(next);		// grab first one so that we have the info

		directory[entry].setFirstBlockID(entry + block);			// update directory first block ID 

		cout << "File " << entry << " ID: " << directory[entry].getFileID()
			 << ", First Block ID: " << directory[entry].getFirstBlockID()
			 << ", Size: " << directory[entry].getSize() << endl;



		do {				// for each block in a file

			// cout << "FileBlockNumber: " << diskBlock->getFileBlockNum() << endl;

			diskBlockB = diskDrive->readDiskBlock(block);			// read swap block to compare

			if(diskBlock != diskBlockB)	{			// store somewhere (hash)
				swapTable.insert(diskBlockB);
			}

			diskDrive->writeDiskBlock(diskBlockB, next);
			
			next = diskBlock->getNext();							// find next file block


			if(next != 1) diskBlock->setNext(block + 1);			// if not end of file, set next block to be next

			diskDrive->writeDiskBlock(diskBlock, block++);			// swap A and B


			delete diskBlock;
			delete diskBlockB;

			diskBlock = diskDrive->readDiskBlock(next);				// read in next file block

		} while (next != 1); // for each disk block in a file

		
	} // for each file


}