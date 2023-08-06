#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	/* Initialize the run copy of disk */
	Disk disk_run;
	// unsigned char buffer[BLOCK_SIZE];
	// Disk::readBlock(buffer, 7000);
	// char message[] = "hello";
	// memcpy(buffer+20, message, 6);
	// Disk::writeBlock(buffer, 7000);

	// unsigned char buffer2[BLOCK_SIZE];
	// char message2[6];
	// Disk::readBlock(buffer2, 7000);
	// memcpy(message2, buffer2+20, 6);

	// cout << message2 << endl;

	RecBuffer relCatBuffer(RELCAT_BLOCK);
	RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

	HeadInfo relCatHeader;
	HeadInfo attrCatHeader;


	relCatBuffer.getHeader(&relCatHeader);
	attrCatBuffer.getHeader(&attrCatHeader);

	for (int i = 0; i < relCatHeader.numEntries; i++) {
		Attribute relCatRecord[RELCAT_NO_ATTRS];
		relCatBuffer.getRecord(relCatRecord, i);

		printf("Relation : %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

		for (int j = 0; j < attrCatHeader.numEntries; j++) {
			Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
			attrCatBuffer.getRecord(attrCatRecord, j);
			if (!strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, relCatRecord[RELCAT_REL_NAME_INDEX].sVal)) {
				const char *attrType = (attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER) ? "NUM" : "STR";
				printf(" %s : %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
			}
		}
		cout << endl;
	}
	return 0;

	//StaticBuffer buffer;
	//OpenRelTable cache;

}
