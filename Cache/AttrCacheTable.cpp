#include "AttrCacheTable.h"
#include <cstring>
#include <iostream>

using namespace std;

//-----------------stage 3----------------

AttrCacheEntry* AttrCacheTable::attrCache[MAX_OPEN];


/* returns the attrOffset-th attribute for the relation corresponding to relId
NOTE: this function expects the caller to allocate memory for `*attrCatBuf`
*/
int AttrCacheTable::getAttrCatEntry(int relId, int attrOffset, AttrCatEntry* attrCatBuf) {
  // check if 0 <= relId < MAX_OPEN and return E_OUTOFBOUND otherwise

  // check if attrCache[relId] == nullptr and return E_RELNOTOPEN if true

    if (relId < 0 || relId >= MAX_OPEN) {
    return E_OUTOFBOUND;
  }

  // if there's no entry at the rel-id
  if (attrCache[relId] == nullptr) {
    return E_RELNOTOPEN;
  }

  // traverse the linked list of attribute cache entries
  for (AttrCacheEntry* entry = attrCache[relId]; entry != nullptr; entry = entry->next) {
    if (entry->attrCatEntry.offset == attrOffset) {

      // copy entry->attrCatEntry to *attrCatBuf and return SUCCESS;

         *attrCatBuf = entry->attrCatEntry;
    }
  }

  // there is no attribute at this offset
  return E_ATTRNOTEXIST;
}

/* Converts a attribute catalog record to AttrCatEntry struct
    We get the record as Attribute[] from the BlockBuffer.getRecord() function.
    This function will convert that to a struct AttrCatEntry type.
*/
void AttrCacheTable::recordToAttrCatEntry(
  union Attribute record[ATTRCAT_NO_ATTRS],AttrCatEntry* attrCatEntry) {
  strcpy(attrCatEntry->relName, record[ATTRCAT_REL_NAME_INDEX].sVal);
  strcpy(attrCatEntry->attrName, record[ATTRCAT_ATTR_NAME_INDEX].sVal);
  // copy the rest of the fields in the record to the attrCacheEntry struct

    attrCatEntry->attrType= (int)record[ATTRCAT_ATTR_TYPE_INDEX].nVal ;
    attrCatEntry->primaryFlag = (int)record[ATTRCAT_PRIMARY_FLAG_INDEX].nVal;
    attrCatEntry->rootBlock= (int)record[ATTRCAT_ROOT_BLOCK_INDEX].nVal;
    attrCatEntry->offset =  (int)record[ATTRCAT_OFFSET_INDEX].nVal;
}
/*
//-----------stage 4 -------------

// returns the attribute with name `attrName` for the relation corresponding to relId
// NOTE: this function expects the caller to allocate memory for `*attrCatBuf`

int AttrCacheTable::getAttrCatEntry(int relId, char attrName[ATTR_SIZE], AttrCatEntry* attrCatBuf) {

  // check that relId is valid and corresponds to an open relation
  if ( relId < 0 || relId >= MAX_OPEN){
    return E_OUTOFBOUND;
  }

    if (attrCache[relId] == nullptr) {
      return E_RELNOTOPEN;   
  }

  // iterate over the entries in the attribute cache and set attrCatBuf to the entry that
  //    matches attrName
   for (AttrCacheEntry* entry = attrCache[relId]; entry != nullptr; entry = entry->next) {
    if (entry->attrCatEntry.attrName == attrName) {
        entry->attrCatEntry = *attrCatBuf;
        return SUCCESS;
    }
  }


  // no attribute with name attrName for the relation
  return E_ATTRNOTEXIST;
}
*/