#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bf.h"
#include "hash_file.h"

#define RECORDS_NUM  2000// you can change it if you want
#define BUCKETS_NUM 100  // you can change it if you want
#define FILE_NAME "data.db"

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
  int indexDesc,indexDesc1,indexDesc2;
  Record record;
  srand(12569874);
  int r;
  BF_Init(LRU);
  CALL_OR_DIE(HT_Init());
  
  CALL_OR_DIE(HT_CreateIndex(FILE_NAME, BUCKETS_NUM));
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc));
  
  printf("-----HASH FILE %d-----\n", indexDesc);
  for (int id = 0; id < RECORDS_NUM; ++id) {
    record.id = id;
    r = rand() % 12;
    memcpy(record.name, names[r], strlen(names[r]) + 1);
    r = rand() % 12;
    memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
    r = rand() % 10;
    memcpy(record.city, cities[r], strlen(cities[r]) + 1);

    CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  } 
  int id = rand() % RECORDS_NUM;
  //CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));
  printf("\nPrint Entry with id = %d\n", id); 
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  printf("\nDelete Entry with id = %d\n" ,id);
  CALL_OR_DIE(HT_DeleteEntry(indexDesc, id));
  printf("\nPrint Entry with id = %d\n", id); 
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id)); // must print something like : Entry doesn't exist or nothing at all
  
  CALL_OR_DIE(HT_CloseFile(indexDesc));
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc1));
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc2));
  int INDEXARRAY[2]={indexDesc1,indexDesc2};
  for(int q=0;q<2;q++)
  {
    printf("\n-----HASH FILE %d-----\n", INDEXARRAY[q]);
    int recs = RECORDS_NUM/2;
    for (int id = 0; id < recs; ++id) 
    {
      record.id = id;
      r = rand() % 12;
      memcpy(record.name, names[r], strlen(names[r]) + 1);
      r = rand() % 12;
      memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
      r = rand() % 10;
      memcpy(record.city, cities[r], strlen(cities[r]) + 1);

      CALL_OR_DIE(HT_InsertEntry(INDEXARRAY[q], record));
    } 
    int id = rand() % RECORDS_NUM;
    //CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));
    printf("\nPrint Entry with id = %d\n", id); 
    CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[q], &id));

    printf("\nDelete Entry with id = %d\n" ,id);
    CALL_OR_DIE(HT_DeleteEntry(INDEXARRAY[q], id));
    printf("\nPrint Entry with id = %d\n", id); 
    CALL_OR_DIE(HT_PrintAllEntries(INDEXARRAY[q], &id)); // must print something like : Entry doesn't exist or nothing at all
  }
  CALL_OR_DIE(HT_CloseFile(indexDesc1));
  CALL_OR_DIE(HT_CloseFile(indexDesc2));
  BF_Close();
}
