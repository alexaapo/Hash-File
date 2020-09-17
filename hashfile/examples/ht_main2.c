#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bf.h"
#include "hash_file.h"

#define RECORDS_NUM  10// you can change it if you want
#define BUCKETS_NUM 5  // you can change it if you want
#define FILE_NAME "data.db"
#define FILE_NAME1 "data1.db"
#define FILE_NAME2 "data2.db"
#define FILE_NAME3 "data3.db"

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
  int indexDesc,indexDesc1,indexDesc2,indexDesc3,buckets;
  int INDEXARRAY[4] = {indexDesc,indexDesc1,indexDesc2,indexDesc3};
  char* FILENAMEARRAY[4] = {FILE_NAME,FILE_NAME1,FILE_NAME2,FILE_NAME3};
  
  BF_Init(LRU);    
  CALL_OR_DIE(HT_Init());
  for(int q=0;q<4;q++)
  {
    buckets=(q+1)*BUCKETS_NUM;
    CALL_OR_DIE(HT_CreateIndex(FILENAMEARRAY[q], buckets));
    CALL_OR_DIE(HT_OpenIndex(FILENAMEARRAY[q], &(INDEXARRAY[q])));
  }
  
  printf("\n");
  Record record;
  srand(12569874);
  int r;
  for(int j=0;j<4;j++)
  {
    printf("Insert Entries of Hash File %d \n", j);
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
  int id = rand() % RECORDS_NUM;
  for(int q=0;q<4;q++)
  {
    printf("\n----------Hash File %d----------\n", q);
    CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[q], NULL));
    printf("\nPrint Entry with id %d of Hash File %d\n", id, q); 
    CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[q], &id));
    printf("\nDelete Entry with id %d of Hash File %d\n" ,id, q);
    CALL_OR_DIE(HT_DeleteEntry(INDEXARRAY[q], id));
    printf("\nPrint Entry with id %d of Hash File %d\n", id, q); 
    CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[q], &id)); // must print something like : Entry doesn't exist or nothing at all
  }
  
  for(int j=0;j<4;j++)
  {
    CALL_OR_DIE(HT_CloseFile(INDEXARRAY[j]));  
  }  
  BF_Close();
}
