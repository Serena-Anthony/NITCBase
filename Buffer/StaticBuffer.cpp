#include "StaticBuffer.h"
#include<iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

// both these arrya are static members of the class hence need to be explicitly declared
unsigned char StaticBuffer::blocks[BUFFER_CAPACITY][BLOCK_SIZE];
struct BufferMetaInfo StaticBuffer::metainfo[BUFFER_CAPACITY];


StaticBuffer::StaticBuffer() {
//make everything tru(declare as free) initially
for (int bufferIndex = 0 ; bufferIndex<BUFFER_CAPACITY; bufferIndex++) {
	metainfo[bufferIndex].free = true;
}
}

/*
At this stage, we are not writing back from the buffer to the disk since we are
not modifying the buffer. So, we will define an empty destructor for now. In
subsequent stages, we will implement the write-back functionality here.
*/

StaticBuffer::~StaticBuffer(){
//empty deconstructor
  // In subsequent stages, implement the write-back functionality here
}

int StaticBuffer::getFreeBuffer(int blockNum) {
  if (blockNum < 0 || blockNum > DISK_BLOCKS) {
    return E_OUTOFBOUND;
  }
  int allocatedBuffer ;
  
  for (int bufferIndex = 0 ; bufferIndex< BUFFER_CAPACITY; bufferIndex++) 
  {
    if(metainfo[bufferIndex].free == true)
    {
      allocatedBuffer = bufferIndex;
      break;
    }
  }
  
  
  metainfo[allocatedBuffer].free = false;
  metainfo[allocatedBuffer].blockNum = blockNum;

  return allocatedBuffer;
  }

/* Get the buffer index where a particular block is stored
   or E_BLOCKNOTINBUFFER otherwise
*/
int StaticBuffer::getBufferNum(int blockNum) 
{
 if (blockNum < 0 || blockNum > DISK_BLOCKS) {
    return E_OUTOFBOUND;
  }
  
 
 for (int bufferIndex = 0 ; bufferIndex< BUFFER_CAPACITY; bufferIndex++) 
 {
	if(metainfo[bufferIndex].blockNum ==blockNum)
	{
	return bufferIndex;
	}
 }
 
 
 return E_BLOCKNOTINBUFFER;
 }
