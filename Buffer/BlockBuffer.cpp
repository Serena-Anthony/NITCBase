#include "BlockBuffer.h"
#include<iostream>
#include <cstdlib>
#include <cstring>
using namespace std;



//-----------stage 2 code --------------

/*
BlockBuffer::BlockBuffer(int blockNum) {
  // initialise this.blockNum with the argument
  this->blockNum = blockNum;
}

// calls the parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

// load the block header into the argument pointer
int BlockBuffer::getHeader(struct HeadInfo *head) {
  unsigned char buffer[BLOCK_SIZE];

  // read the block at this.blockNum into the buffer

	Disk::readBlock(buffer,this->blockNum); 
  
  // populate the numEntries, numAttrs and numSlots fields in *head
  
  memcpy(&head->numSlots, buffer + 24, 4);
  memcpy(&head->numEntries, buffer + 16, 4);
  memcpy(&head->numAttrs, buffer + 20, 4);
  memcpy(&head->rblock, buffer + 12, 4);
  memcpy(&head->lblock, buffer + 8, 4);

  return SUCCESS;
}

// load the record at slotNum into the argument pointer

int RecBuffer::getRecord(union Attribute *rec, int slotNum) {

  struct HeadInfo head;

  // get the header using this.getHeader() function

	getHeader(&head);
  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;

  // read the block at this.blockNum into a buffer
	unsigned char buffer[BLOCK_SIZE];
	Disk::readBlock(buffer,this->blockNum); 

  /* record at slotNum will be at offset HEADER_SIZE + slotMapSize + (recordSize * slotNum)
     - each record will have size attrCount * ATTR_SIZE
     - slotMap will be of size slotCount
     
  */

 /*
 
  int recordSize = attrCount * ATTR_SIZE;
  unsigned char *slotPointer = buffer + HEADER_SIZE +slotCount + (recordSize*slotNum);

  // load the record into the rec data structure
  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}


*/

//-------------stage 3 edit: read from buffer instead of disk directly

/*
Used to get the header of the block into the location pointed to by `head`
NOTE: this function expects the caller to allocate memory for `head`
*/


BlockBuffer::BlockBuffer(int blockNum) {
  // initialise this.blockNum with the argument
  this->blockNum = blockNum;
}

// calls the parent class constructor
RecBuffer::RecBuffer(int blockNum) : BlockBuffer::BlockBuffer(blockNum) {}

int BlockBuffer::getHeader(struct HeadInfo *head) {

  unsigned char *bufferPtr;
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;   // return any errors that might have occured in the process
  }

  // ... (the rest of the logic is as in stage 2)

   
  memcpy(&head->numSlots, bufferPtr + 24, 4);
  memcpy(&head->numEntries, bufferPtr + 16, 4);
  memcpy(&head->numAttrs, bufferPtr + 20, 4);
  memcpy(&head->rblock, bufferPtr + 12, 4);
  memcpy(&head->lblock, bufferPtr + 8, 4);

 return SUCCESS;
  
}

/*
Used to get the record at slot `slotNum` into the array `rec`
NOTE: this function expects the caller to allocate memory for `rec`
*/


int RecBuffer::getRecord(union Attribute *rec, int slotNum) {
  
  unsigned char *bufferPtr;
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;
  }
  // ... (the rest of the logic is as in stage 2
  struct HeadInfo head;
BlockBuffer::getHeader(&head);

  int attrCount = head.numAttrs;
  int slotCount = head.numSlots;

  int recordSize = attrCount * ATTR_SIZE;
  unsigned char *slotPointer = bufferPtr + HEADER_SIZE +slotCount + (recordSize*slotNum);

  // load the record into the rec data structure
  memcpy(rec, slotPointer, recordSize);

  return SUCCESS;
}


/*
Used to load a block to the buffer and get a pointer to it.
NOTE: this function expects the caller to allocate memory for the argument
*/


int BlockBuffer::loadBlockAndGetBufferPtr(unsigned char **buffPtr) {
  // check whether the block is already present in the buffer using StaticBuffer.getBufferNum()
  int bufferNum = StaticBuffer::getBufferNum(this->blockNum);

  if(bufferNum!=E_BLOCKNOTINBUFFER)
  {
    for(int bufferindex=0; bufferindex< BUFFER_CAPACITY; bufferindex++)
    {
      StaticBuffer::metainfo[bufferindex].timeStamp++;
    }

    StaticBuffer::metainfo[bufferNum].timeStamp=0;
  }

  else{
    bufferNum = StaticBuffer::getFreeBuffer(this->blockNum);

    if (bufferNum == E_OUTOFBOUND) {
      return E_OUTOFBOUND;
    }

    Disk::readBlock(StaticBuffer::blocks[bufferNum], this->blockNum);
  }

  // store the pointer to this buffer (blocks[bufferNum]) in *buffPtr
  *buffPtr = StaticBuffer::blocks[bufferNum];

  return SUCCESS;
}


//------------------stage 4 additions

/* used to get the slotmap from a record block
NOTE: this function expects the caller to allocate memory for `*slotMap`
*/


int RecBuffer::getSlotMap(unsigned char *slotMap) {
  unsigned char *bufferPtr;

  // get the starting address of the buffer containing the block using loadBlockAndGetBufferPtr().
  int ret = loadBlockAndGetBufferPtr(&bufferPtr);
  if (ret != SUCCESS) {
    return ret;
  }

  struct HeadInfo head;
  // get the header of the block using getHeader() function
   int temp = getHeader(&head);


  int slotCount = head.numSlots;
  //number of slots in block from header ;

  // get a pointer to the beginning of the slotmap in memory by offsetting HEADER_SIZE
  unsigned char *slotMapInBuffer = bufferPtr + HEADER_SIZE;

  // copy the values from `slotMapInBuffer` to `slotMap` (size is `slotCount`)
  memcpy(slotMap, slotMapInBuffer, slotCount);
  return SUCCESS;
}

int compareAttrs(union Attribute attribute1, union Attribute attribute2 , int attrType)
{
  if(attrType == NUMBER)
  {
    if(attribute1.nVal < attribute2.nVal)
    {
      return -1;
    }
    else if (attribute1.nVal > attribute2.nVal)
    {
      return 1;
    }
    else{
      return 0;
    }
  }
  else
  {
    return strcmp(attribute1.sVal, attribute2.sVal);
  }
}


// Description : Sets the slotNumth record entry of the block with the input record contents.

int RecBuffer::setRecord(union Attribute *rec, int slotNum) {
    unsigned char *bufferPtr;
    /* get the starting address of the buffer containing the block
       using loadBlockAndGetBufferPtr(&bufferPtr). */
     int bufferNum = BlockBuffer::loadBlockAndGetBufferPtr(&bufferPtr);
    // if loadBlockAndGetBufferPtr(&bufferPtr) != SUCCESS
        // return the value returned by the call.
      if(bufferNum!=SUCCESS)
      {
        return bufferNum;
      }
    /* get the header of the block using the getHeader() function */
    HeadInfo head;
    BlockBuffer::getHeader(&head);
    // get number of attributes in the block.
    // get the number of slots in the block.
    int attrcount = head.numAttrs;
    int slotcount = head.numSlots;
    // if input slotNum is not in the permitted range return E_OUTOFBOUND.
    if(slotNum > slotcount || slotNum <0 )
    {
      return E_OUTOFBOUND;
    }
    /* offset bufferPtr to point to the beginning of the record at required
       slot. the block contains the header, the slotmap, followed by all
       the records. so, for example,
       record at slot x will be at bufferPtr + HEADER_SIZE + (x*recordSize)
       copy the record from `rec` to buffer using memcpy
       (hint: a record will be of size ATTR_SIZE * numAttrs)
    */
   int recordsize = ATTR_SIZE*attrcount;
   unsigned char *slotpointer = bufferPtr+ HEADER_SIZE + slotcount +(recordsize*slotNum); 

    // update dirty bit using setDirtyBit()
    memcpy(slotpointer, rec, recordsize);
    int ret = StaticBuffer::setDirtyBit(this->blockNum);
    if(ret!=SUCCESS)
    {
      cout<<"something went wrong with setdirty function";
    }
    /* (the above function call should not fail since the block is already
       in buffer and the blockNum is valid. If the call does fail, there
       exists some other issue in the code) */

    // return SUCCESS
    return SUCCESS;
}

//Sets the header of the block. 
//Any type of block NITCbase has the same header structure.
// Therefore, setHeader() method is kept in abstract BlockBuffer class

int BlockBuffer::setHeader(struct HeadInfo *head){

    unsigned char *bufferPtr;
    // get the starting address of the buffer containing the block using
    // loadBlockAndGetBufferPtr(&bufferPtr).

    // if loadBlockAndGetBufferPtr(&bufferPtr) != SUCCESS
        // return the value returned by the call.

    // cast bufferPtr to type HeadInfo*
    struct HeadInfo *bufferHeader = (struct HeadInfo *)bufferPtr;

    // copy the fields of the HeadInfo pointed to by head (except reserved) to
    // the header of the block (pointed to by bufferHeader)
    //(hint: bufferHeader->numSlots = head->numSlots )

    // update dirty bit by calling StaticBuffer::setDirtyBit()
    // if setDirtyBit() failed, return the error code

    // return SUCCESS;
}