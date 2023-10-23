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
  // add next lines in stage6//
  metainfo[bufferIndex].dirty = false;
  metainfo[bufferIndex].timeStamp = -1;
  metainfo[bufferIndex].blockNum = -1;
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

  // -----stage6 writeback on system exit-----
  for (int bufferIndex = 0 ; bufferIndex<BUFFER_CAPACITY; bufferIndex++){
    if(metainfo[bufferIndex].free == false && metainfo[bufferIndex].dirty == true)
    {
      Disk::writeBlock(blocks[bufferIndex], metainfo[bufferIndex].blockNum);
    }
  }
}



/*
    This function never fails - a buffer is always assigned to the block.
    The timeStamp is reset to 0 each time the buffer block is accessed and incremented when other buffer blocks are accessed. Thus the buffer block with the largest timeStamp is the one that is least recently used.
    The function allots a free buffer block, fills its metaInfo with relevant information, and updates the timeStamp.
    This function will only allocate a buffer and will not load the disk block into the buffer. That task is expected to be handled by the caller.
    This function does not check whether the argument blockNum is already present in the buffer. The caller is expected to validate that before this function is called.
*/
int StaticBuffer::getFreeBuffer(int blockNum) {
  if (blockNum < 0 || blockNum > DISK_BLOCKS) {
    return E_OUTOFBOUND;
  }
  int allocatedBuffer =-1;
  
  int largesttime=0;
  int maxindex=0;
  
  for (int bufferIndex = 0 ; bufferIndex< BUFFER_CAPACITY; bufferIndex++) 
  {
    if(metainfo[bufferIndex].timeStamp > largesttime)
    {
      largesttime =metainfo[bufferIndex].timeStamp;
      maxindex = bufferIndex;
    }

    if(metainfo[bufferIndex].free)
    {
      allocatedBuffer=bufferIndex;
      break;
    }
  }

  if(metainfo[maxindex].dirty==true && allocatedBuffer==-1)
  {
    Disk::writeBlock(blocks[maxindex], metainfo[maxindex].blockNum);
    allocatedBuffer= maxindex;
  }
  
  
  metainfo[allocatedBuffer].free = false;
  metainfo[allocatedBuffer].dirty = false;
  metainfo[allocatedBuffer].blockNum = blockNum;
  metainfo[allocatedBuffer].timeStamp= 0;

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
	if(metainfo[bufferIndex].blockNum == blockNum)
	{
	return bufferIndex;
	}
 }
 
 
 return E_BLOCKNOTINBUFFER;
 }

//description : Sets the dirty bit of the buffer corresponding to the block.
int StaticBuffer::setDirtyBit(int blockNum){
    // find the buffer index corresponding to the block using getBufferNum().
    int bufferindex = getBufferNum(blockNum);

    // if block is not present in the buffer (bufferNum = E_BLOCKNOTINBUFFER)
    //     return E_BLOCKNOTINBUFFER
    if(bufferindex == E_BLOCKNOTINBUFFER)
    {
      return E_BLOCKNOTINBUFFER;
    }

    // if blockNum is out of bound (bufferNum = E_OUTOFBOUND)
    //     return E_OUTOFBOUND
    if(bufferindex == E_OUTOFBOUND)
    {
      return E_OUTOFBOUND;
    }
    else{
      metainfo[bufferindex].dirty = true;
    }
    // else
    //     (the bufferNum is valid)
    //     set the dirty bit of that buffer to true in metainfo
    
     return SUCCESS;
}
