/*This H file will be used to declare and define all structures and functions needed for the cache simulator in our ECE588 Final Project*/
/*Each cache will be represented by a doubly linked list, each node will represent a memory location placed in that cache
The node will have the following information: memory location and MESI/MSI status*/
/*This cache simulation doesn't account for cache architecture and therefore not accurate regarding true cache latency*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

#ifndef CACHE_H
#define CACHE_H

//Instantiations and Typedefs
//enumeration definition for our MESI/MSI status
typedef enum {Modified = 0, Exclusive = 1, Shared = 2, Invalid = 3, Uninit = 4} status_t;

extern const char* statusNames[];

extern struct DLLNode *Cache0; //Cache 1
extern struct DLLNode *Cache1; //Cache 2
extern struct DLLNode *Cache2; //Cache 3
extern struct DLLNode *Cache3; //Cache 4

//users shouldn't normally need to declare a DLLNode structure -> if so, let's see what other functions we need to put in here
//declare the structure for a node in our doubly linked list, each node will represent a memory location which is in the specified cache
struct DLLNode{
    int memory_location;
    status_t status;
    struct DLLNode *next;
    struct DLLNode *previous;
};

//README AREA where all functions are initially declared with full definitions and code below

//Use this function to check if a partciular cache is empty
//example: isCacheEmpty(&Cache0)
bool isCacheEmpty(struct DLLNode **head);

//Use this function to print all the content of a cache with memory locations and status bits
//example: printCacheContent(&Cache0)
void printCacheContent(struct DLLNode **head);

//Use this function to find out how many memory locations are saved in a particular cache
//example: length(&Cache0)
int length(struct DLLNode **head);

//Use this function to delete a whole cache's contents (caution)
//example: deleteCache(&Cache0)
void deleteCache(struct DLLNode **head);

//Use this function to insert a memory location to a cache or to update a memory locations status bit in that cache
//example: insert(&Cache0, 54468, Exclusive)
void insert(struct DLLNode **head, int location_mem, status_t cache_status);

//Use this function to delete one memory location from a cache
//example: delete(&Cache1, 54468)
void delete(struct DLLNode **head, int location_mem);

//Use this function to check the status bit for a particular memory location in a particular cache
//example: checkStatus(&Cache1, 54468) -> output will be a numerical value as specified in the MESI/MSI enum above
//this output format can change, just ask
status_t checkStatus(struct DLLNode **head, int location_mem);

//Use this function to check if a certain memory location is in a certain cache
//example: checkMemInCache(&Cache0, 54468)
bool checkMemInCache(struct DLLNode **head, int location_mem);


#endif
