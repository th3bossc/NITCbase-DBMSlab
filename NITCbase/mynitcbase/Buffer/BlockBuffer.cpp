#include "BlockBuffer.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;



BlockBuffer::BlockBuffer(int blockNum) {
    this->blockNum = blockNum;
}


RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

int BlockBuffer::getHeader(struct HeadInfo *head) {

    unsigned char* bufferPtr;
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);
    if (ret != SUCCESS)
        return ret;

    unsigned char buffer[BLOCK_SIZE];
    Disk::readBlock(buffer, this->blockNum);

    memcpy(&head->numSlots, buffer+24, 4);
    memcpy(&head->numAttrs, buffer+20, 4);
    memcpy(&head->numEntries, buffer+16, 4);
    memcpy(&head->rblock, buffer+12, 4);
    memcpy(&head->lblock, buffer+8, 4);
    return SUCCESS;
}

int RecBuffer::getRecord(union Attribute *rec, int slotNum) {

    unsigned char* bufferPtr;
    int ret = loadBlockAndGetBufferPtr(&bufferPtr);

    if (ret != SUCCESS)
        return ret;

    struct HeadInfo head;
    this->getHeader(&head);    

    int attrCount = head.numAttrs;
    int slotCount = head.numSlots;
    

    unsigned char buffer[BLOCK_SIZE];
    Disk::readBlock(buffer, this->blockNum);

    int recordSize = attrCount*ATTR_SIZE;
    int offset = HEADER_SIZE + slotCount + (recordSize*slotNum); 
    unsigned char* slotPointer = buffer + offset;
    memcpy(rec, slotPointer, recordSize);
    return SUCCESS;
}


int BlockBuffer::loadBlockAndGetBufferPtr(unsigned char **buffPtr) {
    
}