// Author Felix Ng
#include "DefragRunner.h"
#include "mynew.h"
#include "defragmenter.h"
#include <queue>

using namespace std;



Defragmenter::Defragmenter(DiskDrive *diskDrive) {
	DirectoryEntry *directory = diskDrive->directory;
	DiskBlock *diskBlock;
	queue<DiskBlock*> FileBlockList;


	cout << "Capacity: " << diskDrive->getCapacity() << endl
		 << "Number of Files: " << diskDrive->getNumFiles() << endl;


	diskBlock = diskDrive->readDiskBlock(directory[0].getFirstBlockID());

	for(int i = 0, j = 0, next = 0; i < diskDrive->getNumFiles(); i++) {
		diskBlock = diskDrive->readDiskBlock(directory[i].getFirstBlockID());

		cout << "File " << i << " ID: " << directory[i].getFileID()
			 << ", First Block ID: " << directory[i].getFirstBlockID()
			 << ", Size: " << directory[i].getSize() << endl;

		directory[i].setFirstBlockID(2 + j);		// starts at 2


		do {
			j++;
			FileBlockList.push(diskBlock);
			cout << diskBlock->getFileBlockNum() << " ";
			next = diskBlock->getNext();
			diskBlock = diskDrive->readDiskBlock(next);
		} while (next != 1); // for each disk block in a file

		cout << "ends at blockID: " << j << endl;

		
	} // for each file


	for(int i = 0; !FileBlockList.empty(); ) {
		diskBlock = FileBlockList.front();
		diskDrive->writeDiskBlock(diskBlock, 2 + i);
		diskBlock->setNext(2 + i++);
		delete diskBlock;
		FileBlockList.pop();
	}

}