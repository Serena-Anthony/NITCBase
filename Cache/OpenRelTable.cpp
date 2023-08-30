#include "OpenRelTable.h"
#include<stdlib.h>
#include <cstring>

//stage 3

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
  }

   /************ Setting up Relation Cache entries ************/
  // (we need to populate relation cache with entries for the relation catalog
  //  and attribute catalog.)



  /**** 1. setting up Relation Catalog relation in the Relation Cache Table****/

 RecBuffer relCatBlock(RELCAT_BLOCK);
 Attribute relCatRecord[RELCAT_NO_ATTRS];

 relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

  struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

   // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;


  /**** 2. setting up Attribute Catalog relation in the Relation Cache Table ****/

  // set up the relation cache entry for the attribute catalog similarly
  // from the record at RELCAT_SLOTNUM_FOR_ATTRCAT

  // set the value at RelCacheTable::relCache[ATTRCAT_RELID]

    RecBuffer attrCatBlock(RELCAT_BLOCK);
    Attribute attrCatRecord[RELCAT_NO_ATTRS];
    attrCatBlock.getRecord(attrCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);

  struct RelCacheEntry attrRelCacheEntry;
  RelCacheTable::recordToRelCatEntry(attrCatRecord, &attrRelCacheEntry.relCatEntry);
  attrRelCacheEntry.recId.block = RELCAT_BLOCK;
  attrRelCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

   // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = attrRelCacheEntry;




  /************ Setting up Attribute cache entries ************/
  // (we need to populate attribute cache with entries for the relation catalog
  //  and attribute catalog.)

  /**** 3. setting up Relation Catalog relation in the Attribute Cache Table ****/
  
  


// iterate through all the attributes of the relation catalog and create a linked
  // list of AttrCacheEntry (slots 0 to 5)
  // for each of the entries, set
  //    attrCacheEntry.recId.block = ATTRCAT_BLOCK;
  //    attrCacheEntry.recId.slot = i   (0 to 5)
  //    and attrCacheEntry.next appropriately
  // NOTE: allocate each entry dynamically using malloc

  // set the next field in the last entry to nullptr

RecBuffer attrCatBlock1(ATTRCAT_BLOCK);
  Attribute attrCatRecord1[ATTRCAT_NO_ATTRS];
  // head n tail
  AttrCacheEntry *head = nullptr;
  AttrCacheEntry *tail = nullptr;

  for (int i = 0; i <= 5; i++) {
    AttrCacheEntry *ptr = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    attrCatBlock1.getRecord(attrCatRecord1, i);

    AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &ptr->attrCatEntry);
    ptr->recId.block = ATTRCAT_BLOCK;
    ptr->recId.slot = i;
    ptr->next = nullptr;

    if (tail){
      tail->next = ptr;
    } else {
      head = ptr;
    }
    tail = ptr;
  }

 AttrCacheTable::attrCache[RELCAT_RELID] = head;



  /**** setting up Attribute Catalog relation in the Attribute Cache Table ****/

  // set up the attributes of the attribute cache similarly.
  // read slots 6-11 from attrCatBlock and initialise recId appropriately

  // set the value at AttrCacheTable::attrCache[ATTRCAT_RELID]


 //attrCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);
  
 AttrCacheEntry *head2 = nullptr;
  AttrCacheEntry *tail2 = nullptr;

  RecBuffer attrCatBlock2(ATTRCAT_BLOCK);
  Attribute attrCatRecord2[ATTRCAT_NO_ATTRS];

  for (int i = 6; i <= 11; i++) {
    AttrCacheEntry *ptr2 = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
      attrCatBlock2.getRecord(attrCatRecord2, i);

    AttrCacheTable::recordToAttrCatEntry(attrCatRecord2, &ptr2->attrCatEntry);
    ptr2->recId.block = ATTRCAT_BLOCK;
    ptr2->recId.slot = i;
    ptr2->next = nullptr;

    if (tail2) {
      tail2->next = ptr2;
    } else {
      head2 = ptr2;
    }
     tail2 = ptr2;
  }

AttrCacheTable::attrCache[ATTRCAT_RELID] = head2;

 

}

OpenRelTable::~OpenRelTable() {
//destructor -> free all the memory tht was allocated in const

for(int i=0; i<MAX_OPEN; i++)
{
  if(RelCacheTable::relCache[i])
  {
    free(RelCacheTable::relCache[i]);
    free(AttrCacheTable::attrCache[i]);
  }
}

/*
struct AttrCacheEntry attrCacheEntry;
  AttrCacheEntry *head = AttrCacheTable::attrCache[RELCAT_RELID];
    AttrCacheEntry *head2 = AttrCacheTable::attrCache[ATTRCAT_RELID];

AttrCacheEntry* current = head;
    while (current) {
        AttrCacheEntry* temp = current;
        current = current->next;
        free(temp);
    }

    current = head2;
    while (current) {
        AttrCacheEntry* temp = current;
        current = current->next;
        free(temp);
    }
    */
}
