#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
#include<iostream>
#include<cstring>
using namespace std;

//--------------stage 2--------------------

/*
int main(int argc, char *argv[]){
	Disk disk_run;
	StaticBuffer buffer;

	//objects created for reln n attr catalog
	RecBuffer relCatBuffer(RELCAT_BLOCK);
	RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
	
	HeadInfo relCatHeader;
	HeadInfo attrCatHeader;
	
	//load headers of both into
	relCatBuffer.getHeader(&relCatHeader);
  	attrCatBuffer.getHeader(&attrCatHeader);
	
	int N= relCatHeader.numEntries;// num of relations 
	cout << N<<"\n";
	
	for(int i =0; i < N; i++){
	
	Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog
	
	 relCatBuffer.getRecord(relCatRecord, i);
	 printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);
	
	int rb = 5;
	while(rb != -1)
	{
		RecBuffer attrCatBuffer(rb);
		HeadInfo attrCatHeader;
		attrCatBuffer.getHeader(&attrCatHeader);

		 for (int j =0;j < attrCatHeader.numEntries; j++) 
		 {

		      // declare attrCatRecord and load the attribute catalog entry into it
		      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
		      attrCatBuffer.getRecord(attrCatRecord,j);
			
		 if(strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal, "STudents")==0 && strcmp(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, "Class")==0)
		 {
		 	char str[6];
		 	strncpy(str,"Batch",6);
		 	memcpy(attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,str,6);
		 }
		 	
			
			
		      if (strcmp(attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal,relCatRecord[RELCAT_REL_NAME_INDEX].sVal )==0) {
			const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
			printf("  %s: %s\n",attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
		      }
		      
		
		}
		    
		 rb = attrCatHeader.rblock; 
		 	    
	}
       
	 printf("\n");	  
		 
}
  return 0;
}




*/
//----------stage 3 : modify to fetch catalog entries from cache instead fo records

/*
int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  
  for i = 0 and i = 1 (i.e RELCAT_RELID and ATTRCAT_RELID)

      get the relation catalog entry using RelCacheTable::getRelCatEntry()
      printf("Relation: %s\n", relname);

      for j = 0 to numAttrs of the relation - 1
          get the attribute catalog entry for (rel-id i, attribute offset j)
           in attrCatEntry using AttrCacheTable::getAttrCatEntry()

          printf("  %s: %s\n", attrName, attrType);
  */

/*
for (int i = 0; i <=2; i++) {

      RelCatEntry relCatEntry;
      int getRelResult = RelCacheTable::getRelCatEntry(i, &relCatEntry);
     
	  if (getRelResult == SUCCESS) 
	  {

        printf("Relation: %s\n", relCatEntry.relName);
	  }
	  else{
		cout << "Error fetching relation catalog entry";
	  }

        for (int j = 0; j <relCatEntry.numAttrs; j++) 
		{
          AttrCatEntry attrCatEntry;
          int getAttrResult = AttrCacheTable::getAttrCatEntry(i, j, &attrCatEntry);
          if(getAttrResult == SUCCESS){
            const char* attrType = attrCatEntry.attrType== NUMBER ? "NUM" : "STR";
            printf(" %s: %s\n", attrCatEntry.attrName, attrType);
		  }
        }
      }
    
}

*/

//-----stage 4------------

int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  return FrontendInterface::handleFrontend(argc, argv);
}



























/*
int main(int argc, char *argv[]) {
  /* Initialize the Run Copy of Disk */
 // Disk disk_run;
  // StaticBuffer buffer;
  // OpenRelTable cache;
/*
  return FrontendInterface::handleFrontend(argc, argv);
}


int main(int argc, char *argv[]) {
  Disk disk_run;

 // unsigned char buffer[BLOCK_SIZE];
 //// Disk::readBlock(buffer, 0);
  //char message[] = "hello world";
 // memcpy(buffer + 20, message, 13);
  //Disk::writeBlock(buffer, 7000);

  unsigned char buffer2[BLOCK_SIZE];
  char message2[13];
  Disk::readBlock(buffer2, 0);
  memcpy(message2, buffer2, 13);
  for(auto x: message2)
  {
  int temp = int(x);
  std::cout << temp;
	}
  return 0;
}

*/
