#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bf.h"
#include "hash_file.h"

#define RECORDS_NUM  200// you can change it if you want
#define BUCKETS_NUM 13  // you can change it if you want
#define FILE_NAME "data.db"
#define FILE_NAME1 "data1.db"

const char* names[] = {
  "Yannis",
  "Christofos",
  "Sofia",
  "Marianna",
  "Vagelis",
  "Maria",
  "Iosif",
  "Dionisis",
  "Konstantina",
  "Theofilos",
  "Giorgos",
  "Dimitris"
};

const char* surnames[] = {
  "Ioannidis",
  "Svingos",
  "Karvounari",
  "Rezkalla",
  "Nikolopoulos",
  "Berreta",
  "Koronis",
  "Gaitanis",
  "Oikonomou",
  "Mailis",
  "Michas",
  "Halatsis"
};

const char* cities[] = {
  "Athens",
  "San Francisco",
  "Los Angeles",
  "Amsterdam",
  "London",
  "New York",
  "Tokyo",
  "Hong Kong",
  "Munich",
  "Miami"
};

#define CALL_OR_DIE(call)     \
  {                           \
    HT_ErrorCode code = call; \
    if (code != HT_OK) {      \
      printf("Error\n");      \
      exit(code);             \
    }                         \
  }

int main(){
  int indexDesc,indexDesc1,buckets;
  int INDEXARRAY[2] = {indexDesc,indexDesc1};
  char* FILENAMEARRAY[2] = {FILE_NAME,FILE_NAME1};
  
  BF_Init(LRU);
  CALL_OR_DIE(HT_Init());
  for(int q=0;q<2;q++)
  {
    buckets=(q+1)*BUCKETS_NUM;
    CALL_OR_DIE(HT_CreateIndex(FILENAMEARRAY[q], buckets));
    CALL_OR_DIE(HT_OpenIndex(FILENAMEARRAY[q], &(INDEXARRAY[q])));
  }

  Record record;
  srand(12569874);
  int r;
  for(int j=0;j<2;j++)
  {
    int fileRecords = RECORDS_NUM*(j+1);
    for (int id = 0; id < fileRecords; ++id) {
      record.id = id;
      r = rand() % 12;
      memcpy(record.name, names[r], strlen(names[r]) + 1);
      r = rand() % 12;
      memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
      r = rand() % 10;
      memcpy(record.city, cities[r], strlen(cities[r]) + 1);

      CALL_OR_DIE(HT_InsertEntry(INDEXARRAY[j], record));
    }
  }

  for(int j=0;j<2;j++)
  {  
    printf("\n---------HASH FILE %d-------\n\n", j);
    printf("/////PRINTING.../////\n");
    
    for(int id=1;id<=100;id*=4)
    {
      printf("\nPrint Entry with id = %d\n", id); 
      CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[j], &id));
    }

    printf("\n/////DELETING.../////\n");
    for(int id=1;id<=100;id*=4)
    {
      printf("\nDelete Entry with id = %d\n" ,id);
      CALL_OR_DIE(HT_DeleteEntry(INDEXARRAY[j], id));
    }
    
    printf("\n/////RE-PRINTING.../////\n");
    for(int id=1;id<=400;id*=4)
    {
      printf("\nPrint Entry with id = %d\n", id); 
      CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[j], &id)); // must print something like : Entry doesn't exist or nothing at all
    }
  }
  
  for(int j=0;j<2;j++)
    CALL_OR_DIE(HT_CloseFile(INDEXARRAY[j]));
  
  BF_Close();
}
