#include "StaticBuffer.h"
#include <stdlib.h>

unsigned char StaticBuffer::blocks[BUFFER_CAPACITY][BLOCK_SIZE];
struct BufferMetaInfo StaticBuffer::metainfo[BUFFER_CAPACITY];

StaticBuffer::StaticBuffer() {
    for (int bufferIndex = 0; bufferIndex < BUFFER_CAPACITY; bufferIndex++)
        metainfo[bufferIndex].free = true;
}

StaticBuffer::~StaticBuffer() {}


int StaticBuffer::getFreeBuffer(int blockNum) {
    if (blockNum < 0 || blockNum >= DISK_BLOCKS)
        return E_OUTOFBOUND;

    int allocatedBuffer = 0;

    while(allocatedBuffer < BUFFER_CAPACITY && !(metainfo[allocatedBuffer].free))
        allocatedBuffer++;

    metainfo[allocatedBuffer].free = false;
    metainfo[allocatedBuffer].blockNum = blockNum;

    return allocatedBuffer;
}

int StaticBuffer::getBufferNum(int blockNum) {
    if (blockNum < 0 || blockNum >= DISK_BLOCKS)
        return E_OUTOFBOUND;

    int bufferIndex = 0;
    
    while(bufferIndex < BUFFER_CAPACITY && (metainfo[bufferIndex].blockNum != blockNum))
        bufferIndex++;

    if (bufferIndex == BUFFER_CAPACITY)
        return E_BLOCKNOTINBUFFER;

    return bufferIndex;
}