# Hash-File
The purpose of this project is to understand the internal operation of Base Systems
Data regarding the management at block level (block) but also regarding the management at
records level. Also, through this project it will be obvious whether the existence of database indexes in records can improve
the performance of a Database Management System (DSB). 

More specifically, in the context of the project I implement a set of functions
that manage files that created based on static hash (Hash Table).

The functions are related to record management and administration of database
indexes. Their implementation will be above the level of block management, which
is already given as a library. The managment of hash files is done through the functions with the prefix HT_.

Some of the fuctions that I implement:

- HΤ_ErrorCode HT_Init()

- HT_ErrorCode HT_CreateIndex(const char *fileName, int buckets)

- HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc)

- HT_ErrorCode HT_CloseFile(int indexDesc)

- HΤ_ErrorCode HΤ_InsertEntry (int indexDesc, Record record)

- HT_ErrorCode HT_PrintAllEntries(int indexDesc, int *id)

- HT_ErrorCode HT_DeleteEntry(int indexDesc, int id)

## Execution:
I create 5 files of diferrent input for running the programm:

1) **bash script.sh**
2) **bash script1.sh**
3) **bash script2.sh**
4) **bash script3.sh**
5) **bash script4.sh**

**With execution of code we can observe that all entries have been inserted and printed normally (in seperated buckets and blocks), then find an entry with specific id, delete it and finally re-find it (which is going to throw error).**
