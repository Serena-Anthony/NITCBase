#include "OpenRelTable.h"
#include<stdlib.h>
#include <cstring>
#include <stdio.h>
#include <iostream>
using namespace std;
//----------stage 3-----------


/*
OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
  }

  /************ Setting up Relation Cache entries ************/
  // (we need to populate relation cache with entries for the relation catalog
  //  and attribute catalog.)

//printf("stage1/n");
  /**** setting up Relation Catalog relation in the Relation Cache Table****/
 
 /*
  RecBuffer relCatBlock(RELCAT_BLOCK);

  Attribute relCatRecord[RELCAT_NO_ATTRS];

  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);
  //cout << relCatRecord[0].sVal ;
 

  struct RelCacheEntry relCacheEntry;
 
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);

  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;







  /**** setting up Attribute Catalog relation in the Relation Cache Table ****/
  
  /*
  RecBuffer attrCatBlock(RELCAT_BLOCK);

  // set up the relation cache entry for the attribute catalog similarly
  // from the record at RELCAT_SLOTNUM_FOR_ATTRCAT
  Attribute attrCatRecord[RELCAT_NO_ATTRS];
 
  attrCatBlock.getRecord(attrCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);

  struct RelCacheEntry attrRelCacheEntry;
  //AttrCacheTable::recordToRelCatEntry(attrCatRecord, &AttrCacheEntry.relCatEntry);

  RelCacheTable::recordToRelCatEntry(attrCatRecord, &attrRelCacheEntry.relCatEntry);

  attrRelCacheEntry.recId.block = RELCAT_BLOCK;
  attrRelCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

  // set the value at RelCacheTable::relCache[ATTRCAT_RELID]

   RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = attrRelCacheEntry;



  //for loading student relation into student cache
  
    RecBuffer studentRelCatBlock(RELCAT_BLOCK);
    Attribute studentRelCatRecord[RELCAT_NO_ATTRS];
   
    studentRelCatBlock.getRecord(studentRelCatRecord, 2);

    struct RelCacheEntry studentRelCacheEntry;
 
    RelCacheTable::recordToRelCatEntry(studentRelCatRecord, &studentRelCacheEntry.relCatEntry);

    studentRelCacheEntry.recId.block = RELCAT_BLOCK;
    studentRelCacheEntry.recId.slot = 2;

    // Allocate memory on the heap for the cache entry
    RelCacheTable::relCache[2] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
    *(RelCacheTable::relCache[2]) = studentRelCacheEntry;


  /************ Setting up Attribute cache entries ************/
  // (we need to populate attribute cache with entries for the relation catalog
  //  and attribute catalog.)




  

  /**** setting up Relation Catalog relation in the Attribute Cache Table ****/
  
  /*
  RecBuffer attrCatBlock1(ATTRCAT_BLOCK);
  Attribute attrCatRecord1[ATTRCAT_NO_ATTRS];

  //attrCatBlock1.getRecord(attrCatRecord1, RELCAT_SLOTNUM_FOR_ATTRCAT);


  
  AttrCacheEntry *attrCacheHead = nullptr;
  AttrCacheEntry *attrCachePrev = nullptr;
  
  for(int i=0; i<=5; ++i){
    AttrCacheEntry *attrCacheEntry = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
    if (attrCacheEntry == nullptr) {
    break;
    }
   
    attrCatBlock1.getRecord(attrCatRecord1, i);
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord1, &attrCacheEntry->attrCatEntry);

    attrCacheEntry->recId.block = ATTRCAT_BLOCK;
    attrCacheEntry->recId.slot = i;
    attrCacheEntry->next = nullptr;

    if(attrCachePrev){
        attrCachePrev->next = attrCacheEntry;
    }
    else{
       attrCacheHead = attrCacheEntry;
    }
    attrCachePrev = attrCacheEntry;
  }

  
 AttrCacheTable::attrCache[RELCAT_RELID] = attrCacheHead;




  AttrCacheEntry *attrCacheHead2 = nullptr;
  AttrCacheEntry *attrCachePrev2 = nullptr;

  
  RecBuffer attrCatBlock2(ATTRCAT_BLOCK);
  Attribute attrCatRecord2[ATTRCAT_NO_ATTRS];\

  //attrCatBlock2.getRecord(attrCatRecord2, RELCAT_SLOTNUM_FOR_ATTRCAT);
  
  for(int i=6; i <= 11; ++i){
    AttrCacheEntry *attrCacheEntry2 = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));

    attrCatBlock2.getRecord(attrCatRecord2, i);
     
    AttrCacheTable::recordToAttrCatEntry(attrCatRecord2, &attrCacheEntry2->attrCatEntry);

    attrCacheEntry2->recId.block = ATTRCAT_BLOCK;
    attrCacheEntry2->recId.slot = i;
    attrCacheEntry2->next = nullptr;

    if(attrCachePrev2){
        attrCachePrev2->next = attrCacheEntry2;
    }
    else{
        attrCacheHead2 = attrCacheEntry2;
    }
    attrCachePrev2 = attrCacheEntry2;
  }
  AttrCacheTable::attrCache[ATTRCAT_RELID] = attrCacheHead2;


/*
  //student in attribute cache

    RecBuffer studentAttrCatBlock(ATTRCAT_BLOCK);
    Attribute studentAttrCatRecord[ATTRCAT_NO_ATTRS];

    AttrCacheEntry *studentAttrCacheHead = nullptr;
    AttrCacheEntry *studentAttrCachePrev = nullptr;

    for (int i = 12; i <= 17; ++i) {
        AttrCacheEntry *attrCacheEntry3 = (AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));
        studentAttrCatBlock.getRecord(studentAttrCatRecord, i);
        AttrCacheTable::recordToAttrCatEntry(studentAttrCatRecord, &attrCacheEntry3->attrCatEntry);
        attrCacheEntry3->recId.block = ATTRCAT_BLOCK;
        attrCacheEntry3->recId.slot = i;
        attrCacheEntry3->next = nullptr;

        if (studentAttrCachePrev) {
            studentAttrCachePrev->next = attrCacheEntry3;
        } else {
            studentAttrCacheHead = attrCacheEntry3;
        }
        studentAttrCachePrev = attrCacheEntry3;
    }

    AttrCacheTable::attrCache[2] = studentAttrCacheHead;
*/
// }


/*
//deconstructor
OpenRelTable::~OpenRelTable() {
  // free all the memory that you allocated in the constructor
  // for(int i=0; i< MAX_OPEN; ++i){
  //   if(RelCacheTable::relCache[i]){
  //       free(RelCacheTable::relCache[i]);
  //       free(AttrCacheTable::attrCache[i]);
  //   }
  // }
}

//----------stage4 addition 1 fnc --------
/* This function will open a relation having name `relName`.
Since we are currently only working with the relation and attribute catalog, we
will just hardcode it. In subsequent stages, we will loop through all the relations
and open the appropriate one.
*/
/*
int OpenRelTable::getRelId(char relName[ATTR_SIZE]) {

  // if relname is RELCAT_RELNAME, return RELCAT_RELID
  if(strcmp(relName, RELCAT_RELNAME)==0)
      return RELCAT_RELID;
  // if relname is ATTRCAT_RELNAME, return ATTRCAT_RELID
if(strcmp(relName, ATTRCAT_RELNAME)==0)
    return ATTRCAT_RELID;

  return E_RELNOTOPEN;
}
*/
//---------------stage5--------------------------

AttrCacheEntry *createAttrList(int size) {
  AttrCacheEntry *head = nullptr, *curr = nullptr;
  head = curr = (AttrCacheEntry *)malloc(sizeof(AttrCacheEntry));
  size--;
  while (size--) {
    curr->next = (AttrCacheEntry *)malloc(sizeof(AttrCacheEntry));
    curr = curr->next;
  }
  curr->next = nullptr;

  return head;
}

OpenRelTableMetaInfo OpenRelTable::tableMetaInfo[MAX_OPEN];

OpenRelTable::OpenRelTable() {

  // initialise all values in relCache and attrCache to be nullptr and all entries
  // in tableMetaInfo to be free
for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
    tableMetaInfo[i].free= true;
  }


  // load the relation and attribute catalog into the relation cache (we did this already)

  RecBuffer relCatBlock(RELCAT_BLOCK);
  Attribute relCatRecord[RELCAT_NO_ATTRS];
  RelCacheEntry *relCacheEntry = nullptr;

  for (int relId = RELCAT_RELID; relId <= ATTRCAT_RELID; relId++) {
    relCatBlock.getRecord(relCatRecord, relId);

    relCacheEntry = (RelCacheEntry *)malloc(sizeof(RelCacheEntry));
    RelCacheTable::recordToRelCatEntry(relCatRecord,
                                                 &(relCacheEntry->relCatEntry));
    relCacheEntry->recId.block = RELCAT_BLOCK;
    relCacheEntry->recId.slot = relId;

    relCacheEntry->searchIndex = {-1, -1};

    RelCacheTable::relCache[relId] = relCacheEntry;
  }

  // load the relation and attribute catalog into the attribute cache (we did this already)
  RecBuffer attrCatBlock(ATTRCAT_BLOCK);
  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  AttrCacheEntry *attrCacheEntry = nullptr, *head = nullptr;

  for (int relId = RELCAT_RELID, recordId = 0; relId <= ATTRCAT_RELID;
       relId++) {
    int numberOfAttributes =
        RelCacheTable::relCache[relId]->relCatEntry.numAttrs;
    head = createAttrList(numberOfAttributes);
    attrCacheEntry = head;

    while (numberOfAttributes--) {
      attrCatBlock.getRecord(attrCatRecord, recordId);

      AttrCacheTable::recordToAttrCatEntry(attrCatRecord,
                                           &(attrCacheEntry->attrCatEntry));
      attrCacheEntry->recId.slot = recordId++;
      attrCacheEntry->recId.block = ATTRCAT_BLOCK;

      attrCacheEntry = attrCacheEntry->next;
    }

    AttrCacheTable::attrCache[relId] = head;
  }

  /************ Setting up tableMetaInfo entries ************/

  // in the tableMetaInfo array
  //   set free = false for RELCAT_RELID and ATTRCAT_RELID
  //   set relname for RELCAT_RELID and ATTRCAT_RELID

  tableMetaInfo[RELCAT_RELID].free = false;
   strcpy(tableMetaInfo[RELCAT_RELID].relName, RELCAT_RELNAME);

   tableMetaInfo[ATTRCAT_RELID].free = false;
   strcpy(tableMetaInfo[ATTRCAT_RELID].relName, ATTRCAT_RELNAME);
}

int OpenRelTable::getFreeOpenRelTableEntry() {

  /* traverse through the tableMetaInfo array,
    find a free entry in the Open Relation Table.*/
  for(int relid=0; relid<MAX_OPEN;relid++)
  {
    if(tableMetaInfo[relid].free)
    {
      return relid;
    }
  }

  return E_CACHEFULL;
  // if found return the relation id, else return E_CACHEFULL.
}

int OpenRelTable::getRelId(char relName[ATTR_SIZE]) {

  /* traverse through the tableMetaInfo array,
    find the entry in the Open Relation Table corresponding to relName.*/
  
  for(int relid =0; relid<MAX_OPEN; relid++)
  {
    if(strcmp(tableMetaInfo[relid].relName,relName)==0 && tableMetaInfo[relid].free==false)
    {
      return relid;
    }
  }
  // if found return the relation id, else indicate that the relation do not
  // have an entry in the Open Relation Table.
  return E_RELNOTOPEN;
}
// desp : Creates an entry for the input relation in the Open Relation Table and returns the corresponding relation id.
int OpenRelTable::openRel(char relName[ATTR_SIZE]) {

  //if(/* the relation `relName` already has an entry in the Open Relation Table */){
    // (checked using OpenRelTable::getRelId())
    int relidcheck = getRelId(relName);
if(relidcheck>=0)
       return relidcheck;
    // return that relation id;
   
  /* find a free slot in the Open Relation Table
     using OpenRelTable::getFreeOpenRelTableEntry(). */
  int relid= OpenRelTable::getFreeOpenRelTableEntry();

  if(relid==E_CACHEFULL){
    return E_CACHEFULL;
  }
  // let relId be used to store the free slot.
  

  /****** Setting up Relation Cache entry for the relation ******/

  /* search for the entry with relation name, relName, in the Relation Catalog using
      BlockAccess::linearSearch().
      Care should be taken to reset the searchIndex of the relation RELCAT_RELID
      before calling linearSearch().*/
Attribute attrVal;
strcpy(attrVal.sVal, relName);
  

char relation_name[strlen(RELCAT_ATTR_RELNAME) + 1]; // +1 for the null terminator
strcpy(relation_name, RELCAT_ATTR_RELNAME);
RelCacheTable::resetSearchIndex(RELCAT_RELID);
  // relcatRecId stores the rec-id of the relation `relName` in the Relation Catalog.
  RecId relcatRecId= BlockAccess::linearSearch(RELCAT_RELID,relation_name ,attrVal,EQ);

 
  if (relcatRecId.block==-1 && relcatRecId.slot==-1) {
    // (the relation is not found in the Relation Catalog.)
    return E_RELNOTEXIST;
  }
  RecBuffer relationBuffer(relcatRecId.block);
  Attribute relationRecord[RELCAT_NO_ATTRS];
  RelCacheEntry *relCacheBuffer = nullptr;


  /* read the record entry corresponding to relcatRecId and create a relCacheEntry
      on it using RecBuffer::getRecord() and RelCacheTable::recordToRelCatEntry().
      update the recId field of this Relation Cache entry to relcatRecId.
      use the Relation Cache entry to set the relId-th entry of the RelCacheTable.
    NOTE: make sure to allocate memory for the RelCacheEntry using malloc()
  */
  relationBuffer.getRecord(relationRecord, relcatRecId.slot);
  relCacheBuffer = (RelCacheEntry *)malloc(sizeof(RelCacheEntry));
  RelCacheTable::recordToRelCatEntry(relationRecord,
                                     &(relCacheBuffer->relCatEntry));
 
   // update the recId field of this Relation Cache entry to relcatRecId.
  relCacheBuffer->recId.block = relcatRecId.block;
  relCacheBuffer->recId.slot = relcatRecId.slot;
   // use the Relation Cache entry to set the relId-th entry of the
  // RelCacheTable.

  RelCacheTable::relCache[relid] = relCacheBuffer;
  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  /****** Setting up Attribute Cache entry for the relation ******/

  // let listHead be used to hold the head of the linked list of attrCache entries.

  AttrCacheEntry *attrCacheEntry = nullptr, *listhead = nullptr;
  /*iterate over all the entries in the Attribute Catalog corresponding to each
  attribute of the relation relName by multiple calls of BlockAccess::linearSearch()
  care should be taken to reset the searchIndex of the relation, ATTRCAT_RELID,
  corresponding to Attribute Catalog before the first call to linearSearch().*/
    int numberOfAttributes = RelCacheTable::relCache[relid]->relCatEntry.numAttrs;
  listhead = createAttrList(numberOfAttributes);
  attrCacheEntry = listhead;
  RelCacheTable::resetSearchIndex(ATTRCAT_RELID);
  // while (numberOfAttributes--)
  for (int attr = 0; attr < numberOfAttributes; attr++) 
  {
      /* let attrcatRecId store a valid record id an entry of the relation, relName,
      in the Attribute Catalog.*/
char relation_name[strlen(RELCAT_ATTR_RELNAME) + 1]; // +1 for the null terminator
strcpy(relation_name, RELCAT_ATTR_RELNAME);
      RecId attrcatRecId=BlockAccess::linearSearch(ATTRCAT_RELID,relation_name , attrVal, EQ);
    RecBuffer attrCatBlock(attrcatRecId.block);
    attrCatBlock.getRecord(attrCatRecord, attrcatRecId.slot);

    AttrCacheTable::recordToAttrCatEntry(attrCatRecord,
                                         &(attrCacheEntry->attrCatEntry));

    attrCacheEntry->recId.block = attrcatRecId.block;
    attrCacheEntry->recId.slot = attrcatRecId.slot;

    attrCacheEntry = attrCacheEntry->next;
      /* read the record entry corresponding to attrcatRecId and create an
      Attribute Cache entry on it using RecBuffer::getRecord() and
      AttrCacheTable::recordToAttrCatEntry().
      update the recId field of this Attribute Cache entry to attrcatRecId.
      add the Attribute Cache entry to the linked list of listHead .*/
      // NOTE: make sure to allocate memory for the AttrCacheEntry using malloc()
  }

  // set the relIdth entry of the AttrCacheTable to listHead.
  AttrCacheTable::attrCache[relid] = listhead;
  tableMetaInfo[relid].free = false;
  strcpy(tableMetaInfo[relid].relName, relName);
  /****** Setting up metadata in the Open Relation Table for the relation******/

  // update the relIdth entry of the tableMetaInfo with free as false and
  // relName as the input.

  return relid;
 }

// int OpenRelTable::closeRel(int relId) {
//   if (relId==RELCAT_RELID || relId==ATTRCAT_RELID) {
//     return E_NOTPERMITTED;
//   }

//   if (0< relId || relId >= MAX_OPEN) {
//     return E_OUTOFBOUND;
//   }

//   if (tableMetaInfo[relId].free) {
//     return E_RELNOTOPEN;
//   }

//   // free the memory allocated in the relation and attribute caches which was
//   // allocated in the OpenRelTable::openRel() function
  
//   free(RelCacheTable::relCache[relId]);
//   AttrCacheEntry *head = AttrCacheTable::attrCache[relId];
//   AttrCacheEntry *next = head->next;

//   while (next) {
//     free(head);
//     head = next;
//     next = next->next;
//   }
//   free(head);
//   // update `tableMetaInfo` to set `relId` as a free slot
//   // update `relCache` and `attrCache` to set the entry at `relId` to nullptr
  
//     RelCacheTable::relCache[relId] = nullptr;
//     AttrCacheTable::attrCache[relId] = nullptr;
//     tableMetaInfo[relId].free= true;
  

//   return SUCCESS;
// }

OpenRelTable::~OpenRelTable() {

  // close all open relations (from rel-id = 2 onwards. Why?)
  for (int i = 2; i < MAX_OPEN; ++i) {
    if (!tableMetaInfo[i].free) {
      OpenRelTable::closeRel(i); // we will implement this function later
    }
  }

  // free the memory allocated for rel-id 0 and 1 in the caches
   
   /**** Closing the catalog relations in the relation cache ****/

    //releasing the relation cache entry of the attribute catalog

    if (RelCacheTable::relCache[ATTRCAT_RELID]->dirty==true) /* RelCatEntry of the ATTRCAT_RELID-th RelCacheEntry has been modified */
    {

        /* Get the Relation Catalog entry from RelCacheTable::relCache
        Then convert it to a record using RelCacheTable::relCatEntryToRecord(). */
        RelCatEntry recbuffer;
        RelCacheTable::getRelCatEntry(ATTRCAT_RELID, &recbuffer);
        
        Attribute record[RELCAT_NO_ATTRS];

        RelCacheTable::relCatEntryToRecord(&recbuffer, record);
        RecId recid = RelCacheTable::relCache[ATTRCAT_RELID]->recId;

        // declaring an object of RecBuffer class to write back to the buffer
        RecBuffer buffer(recid.block); 
          
        // Write back to the buffer using relCatBlock.setRecord() with recId.slot
        buffer.setRecord(record, recid.slot);
    }
    // free the memory dynamically allocated to this RelCacheEntry
    free(RelCacheTable::relCache[ATTRCAT_RELID]);

    //releasing the relation cache entry of the relation catalog

    if(RelCacheTable::relCache[RELCAT_RELID]->dirty==true)/* RelCatEntry of the RELCAT_RELID-th RelCacheEntry has been modified */
   {

        /* Get the Relation Catalog entry from RelCacheTable::relCache
        Then convert it to a record using RelCacheTable::relCatEntryToRecord(). */
        RelCatEntry recbuffer;
        RelCacheTable::getRelCatEntry(RELCAT_RELID, &recbuffer);
        Attribute record[ATTRCAT_NO_ATTRS];

        RelCacheTable::relCatEntryToRecord(&recbuffer, record);
        RecId recid = RelCacheTable::relCache[RELCAT_RELID]->recId;

        // declaring an object of RecBuffer class to write back to the buffer
     RecBuffer buffer(recid.block); 

        // Write back to the buffer using relCatBlock.setRecord() with recId.slot
         buffer.setRecord(record, recid.slot);
    }
    // free the memory dynamically allocated for this RelCacheEntry
     free(RelCacheTable::relCache[RELCAT_RELID]);

    // free the memory allocated for the attribute cache entries of the
    // relation catalog and the attribute catalog
    for(int i = RELCAT_RELID; i <= ATTRCAT_RELID ; i++)
    {
      AttrCacheEntry *curr = AttrCacheTable::attrCache[i],*next= NULL;
		while(curr!=nullptr){
			next=curr->next;
			if(curr->dirty==true){
				AttrCatEntry attrCatEntry=curr->attrCatEntry;
				Attribute AttrCatrecord[ATTRCAT_NO_ATTRS];
				AttrCacheTable::attrCatEntryToRecord(&attrCatEntry,AttrCatrecord);
				RecBuffer attrCatBlock(curr->recId.block);
				attrCatBlock.setRecord(AttrCatrecord,curr->recId.slot);
			}
			free(curr);
			curr=next;
		}
    }
}


// fnc to handle the write-back for reln cache 
int OpenRelTable::closeRel(int relId) {
  // confirm that rel-id fits the following conditions
  //     2 <=relId < MAX_OPEN
  //     does not correspond to a free slot
  //  (you have done this already)
    if (relId == RELCAT_RELID || relId == ATTRCAT_RELID) return E_NOTPERMITTED;

  	if (relId <0 || relId >= MAX_OPEN) return E_OUTOFBOUND;

  	if (tableMetaInfo[relId].free) return E_RELNOTOPEN;
  /****** Releasing the Relation Cache entry of the relation ******/
  /* RelCatEntry of the relId-th Relation Cache entry has been modified */
  if (RelCacheTable::relCache[relId]->dirty ==true )
  {

    /* Get the Relation Catalog entry from RelCacheTable::relCache
    Then convert it to a record using RelCacheTable::relCatEntryToRecord(). */

    Attribute record[RELCAT_NO_ATTRS];
    RelCacheTable::relCatEntryToRecord(&(RelCacheTable::relCache[relId]->relCatEntry),record);

    // declaring an object of RecBuffer class to write back to the buffer
    RecId recId = RelCacheTable::relCache[relId]->recId;
    RecBuffer relCatBlock(recId.block);

    // Write back to the buffer using relCatBlock.setRecord() with recId.slot
    relCatBlock.setRecord(record, RelCacheTable::relCache[relId]->recId.slot);
  }

  /****** Releasing the Attribute Cache entry of the relation ******/

  // free the memory allocated in the attribute caches which was
  // allocated in the OpenRelTable::openRel() function
  free(RelCacheTable::relCache[relId]);
  // (because we are not modifying the attribute cache at this stage,
  // write-back is not required. We will do it in subsequent
  // stages when it becomes needed)


  /****** Set the Open Relation Table entry of the relation as free ******/
  AttrCacheEntry *head = AttrCacheTable::attrCache[relId];
	AttrCacheEntry *next = head->next;

  while(next!=nullptr) {
		free(head);
		head = next;
		next = next->next;
	}

	free(head);	

  // update `metainfo` to set `relId` as a free slot
  tableMetaInfo[relId].free = true;
	RelCacheTable::relCache[relId] = nullptr;
	AttrCacheTable::attrCache[relId] = nullptr;
  return SUCCESS;
}

