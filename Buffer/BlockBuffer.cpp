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

//constructor2 ---stage7
//Called when the block has already been initialised as a record or index block on the disk.
BlockBuffer::BlockBuffer(int blockNum) {
  // initialise this.blockNum with the argument
  // set the blockNum field of the object to input argument.
  this->blockNum = blockNum;
}

//Called if a new record block is to be allocated in the disk.
RecBuffer::RecBuffer() : BlockBuffer('R'){}
// call parent non-default constructor with 'R' denoting record block.

//constructor1 ---stage7 
// R-REC I-IND_INTERNAL L-IND_LEAF
BlockBuffer::BlockBuffer(char blockType){
    // allocate a block on the disk and a buffer in memory to hold the new block of
    // given type using getFreeBlock function and get the return error codes if any.
    int temp = getFreeBlock(blockType);

    // set the blockNum field of the object to that of the allocated block
    // number if the method returned a valid block number,
    // otherwise set the error code returned as the block number.
    if(temp <0 || temp >=DISK_BLOCKS)
    {
      cout << "error : block is not available \n";
      return;
    }
    // (The caller must check if the constructor allocatted block successfully
    // by checking the value of block number field.)
    this->blockNum = temp;
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
   int temp = loadBlockAndGetBufferPtr(&bufferPtr);
    // if loadBlockAndGetBufferPtr(&bufferPtr) != SUCCESS
        // return the value returned by the call.
    if(temp != SUCCESS)
    {
      return temp;
    }
    // cast bufferPtr to type HeadInfo*
    struct HeadInfo *bufferHeader = (struct HeadInfo *)bufferPtr;

    // copy the fields of the HeadInfo pointed to by head (except reserved) to
    // the header of the block (pointed to by bufferHeader)
    //(hint: bufferHeader->numSlots = head->numSlots )
    bufferHeader->numSlots = head->numSlots;
    bufferHeader->blockType= head->blockType;
    bufferHeader->lblock= head->lblock;
    bufferHeader->numAttrs= head->numAttrs;
    bufferHeader->numEntries= head->numEntries;
    bufferHeader->pblock= head->pblock;
    bufferHeader->rblock= head->rblock;
  
    // update dirty bit by calling StaticBuffer::setDirtyBit()
    int dirty = StaticBuffer::setDirtyBit(temp);
    // if setDirtyBit() failed, return the error code
   
     return dirty;
}

// descr: Sets the type of the block with the input block type. 
// This method sets the type in both the header of the block and 
// also in the block allocation map.
int BlockBuffer::setBlockType(int blockType){

    unsigned char *bufferPtr;
    /* get the starting address of the buffer containing the block
       using loadBlockAndGetBufferPtr(&bufferPtr). */
    int temp = loadBlockAndGetBufferPtr(&bufferPtr);
    // if loadBlockAndGetBufferPtr(&bufferPtr) != SUCCESS
        // return the value returned by the call.
   if(temp != SUCCESS)
    {
      return temp;
    }
    // store the input block type in the first 4 bytes of the buffer.
    // (hint: cast bufferPtr to int32_t* and then assign it)
    // *((int32_t *)bufferPtr) = blockType;
    *((int32_t *)bufferPtr) = blockType;
    // update the StaticBuffer::blockAllocMap entry corresponding to the
    // object's block number to `blockType`.
    StaticBuffer::blockAllocMap[this->blockNum] = blockType;
    // update dirty bit by calling StaticBuffer::setDirtyBit()
    // if setDirtyBit() failed
        // return the returned value from the call
    int dirty = StaticBuffer::setDirtyBit(this->blockNum);
    return dirty;
    // return SUCCESS
}

// descrip: Returns the block number of a free block. It sets up the header 
// of the block with the input block type and updates the block allocation 
// map with the same. A buffer is also allocated to the block. If a free block is not available,
// E_DISKFULL is returned.
int BlockBuffer::getFreeBlock(int blockType){

    // iterate through the StaticBuffer::blockAllocMap and find the block number
    // of a free block in the disk.
    int block;
    for( block =0; block< DISK_BLOCKS; block++ )
    {
      if(StaticBuffer::blockAllocMap[block] = UNUSED_BLK)
      {
        break;
      }
    }
    // if no block is free, return E_DISKFULL.
    if(block==DISK_BLOCKS)
    {
      return E_DISKFULL;
    }
    // set the object's blockNum to the block number of the free block.
    this->blockNum = block;
    // find a free buffer using StaticBuffer::getFreeBuffer() .
    int buffer = StaticBuffer::getFreeBuffer(block);
    if(buffer<0 || buffer >=BUFFER_CAPACITY)
    {
      cout << "error : buffer is full \n";
      return buffer;
    }
    // initialize the header of the block passing a struct HeadInfo with values
    // pblock: -1, lblock: -1, rblock: -1, numEntries: 0, numAttrs: 0, numSlots: 0
    // to the setHeader() function.
    struct HeadInfo header;
    header.pblock =-1;
    header.lblock =-1;
    header.rblock = -1;
    header.numAttrs=0;
    header.numEntries=0;
    header.numSlots=0;
    setHeader(&header);
    
    // update the block type of the block to the input block type using setBlockType().
    setBlockType(blockType);
    // return block number of the free block.
    return block;
}

//Sets the slotmap of the block.
int RecBuffer::setSlotMap(unsigned char *slotMap) {
    unsigned char *bufferPtr;
    /* get the starting address of the buffer containing the block using
       loadBlockAndGetBufferPtr(&bufferPtr). */
    int temp = BlockBuffer::loadBlockAndGetBufferPtr(&bufferPtr);
    // if loadBlockAndGetBufferPtr(&bufferPtr) != SUCCESS
        // return the value returned by the call.
  if(temp!= SUCCESS)
  {
    return temp;
  }

    HeadInfo header;
    BlockBuffer::getHeader(&header);
    // get the header of the block using the getHeader() function

    int numSlots = header.numSlots;/* the number of slots in the block */

    // the slotmap starts at bufferPtr + HEADER_SIZE. Copy the contents of the
    // argument `slotMap` to the buffer replacing the existing slotmap.
    // Note that size of slotmap is `numSlots`
    memcpy(bufferPtr+HEADER_SIZE , slotMap, numSlots );
    // update dirty bit using StaticBuffer::setDirtyBit
    // if setDirtyBit failed, return the value returned by the call
       int done = StaticBuffer::setDirtyBit(this->blockNum);
        // return done;    
    
    return SUCCESS;
}

int BlockBuffer::getBlockNum(){
  return this->blockNum;
    //return corresponding block number.
}