#include "BlockAccess.h"
#include <cstring>

RecId BlockAccess::linearSearch(int relId, char attrName[ATTR_SIZE] , union Attribute attrVal, int op)
{
    RecId prevRecId;
    RelCacheTable::getSearchIndex(relId, &prevRecId);
    int block =-1, slot =-1;
    // get the previous search index of the relation relId from the relation cache
    // (use RelCacheTable::getSearchIndex() function)

    // let block and slot denote the record id of the record being currently checked

    // if the current search index record is invalid(i.e. both block and slot = -1)
    
    if(prevRecId.block==-1 && prevRecId.slot==-1)
    {   
        RelCatEntry RelCatBuf;
        RelCacheTable::getRelCatEntry(relId, &RelCatBuf);

        block = RelCatBuf.firstBlk;
        slot =0;
    }
    else
    {
        block = prevRecId.block;
        slot = prevRecId.slot+1;
    }

    /* The following code searches for the next record in the relation
       that satisfies the given condition
       We start from the record id (block, slot) and iterate over the remaining
       records of the relation
    */

   while (block != -1)
   {
    
   }

}