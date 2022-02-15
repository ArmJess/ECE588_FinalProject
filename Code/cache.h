/*This H file will be used to declare and define all structures and functions needed for the cache simulator in our ECE588 Final Project*/
/*Each cache will be represented by a doubly linked list, each node will represent a memory location placed in that cache
The node will have the following information: memory location and MESI/MSI status*/
/*This cache simulation doesn't account for cache architecture and therefore not accurate regarding true cache latency*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 0

//enumeration definition for our MESI/MSI status
typedef enum {Modified = 0, Exclusive = 1, Shared = 2, Invalid = 3} status_t;

//declare the structure for a node in our doubly linked list, each node will represent a memory location which is in the specified cache
struct DLLNode{
    int memory_location;
    status_t status;
    struct DLLNode *next;
    struct DLLNode *previous;
};

bool isCacheEmpty(struct DLLNode **head){
    if(DEBUG){printf("Empty? %d\n", *head == NULL);}
    return *head == NULL;
}

void printCacheContent(struct DLLNode **head){
    
    struct DLLNode *temp = *head;
    if(isCacheEmpty(head)){
        printf("Cache is empty.\n");
    }
    while(temp!=NULL){
        printf("Mem location: %d in state: %d\n", temp->memory_location, temp->status);
        if(DEBUG){printf("temp mem location: %d\n", temp->memory_location);}
        temp = temp->next;
    }
    return;
}

int length(struct DLLNode **head){

    int length = 0;
    struct DLLNode *temp = *head;

    for(temp; temp != NULL; temp = temp->next){
        length++;
    }

    printf("Number of memory locations in cache: %d\n", length);
    return length;

}

void deleteCache(struct DLLNode **head){
    *head = NULL;
}

//Insert memory location into cache
void insert(struct DLLNode **head, int location_mem, status_t cache_status){

    struct DLLNode *temp = *head;
    struct DLLNode *temp_prev;
    struct DLLNode *temp_next;
    struct DLLNode *newNode;

    if(temp == NULL){
        //create and insert newNode as the first node
        newNode = (struct DLLNode *) malloc(sizeof(struct DLLNode));
        if(!newNode){
            printf("Cache simulation: memory allocation error with DLLNode\n");
        }
        newNode->memory_location = location_mem;
        newNode->status = cache_status;
        newNode->previous = NULL;
        newNode->next = NULL;
        *head  = newNode;
        if(DEBUG){printf("created first node in cache\n");}
    }
    else{
        //If there is already a cache instantiated and with nodes
        while(temp->memory_location < location_mem){
            //move us to where this memory location should be in this cache and keep the ordering as lowest mem location to highest as we progress through the linked list
            if(DEBUG){printf("temp memory: %d\n", temp->memory_location);}
            temp = temp->next;
            if(DEBUG){printf("new temp memory after increment: %d\n", temp->memory_location);}
            if(DEBUG){printf("increment in cache\n");}
        }
        if(temp->memory_location == location_mem){
            //this memory location has already been cached in this cache, just change the status
            temp->status = cache_status;
            if(DEBUG){printf("updated mem already in cache\n");}
            return;
        }else{
            //create and insert newNode to the left of temp
            newNode = (struct DLLNode *) malloc(sizeof(struct DLLNode));
            if(!newNode){
                printf("Cache simulation: memory allocation error with DLLNode\n");
            }
            newNode->memory_location = location_mem;
            newNode->status = cache_status;
            *temp_next = *temp;
            temp_prev = temp->previous;
            if(temp_prev == NULL){
                newNode->previous = temp_prev;
                *head = newNode;
            }else{
                newNode->previous = temp_prev;
                temp_prev->next = newNode;
            }
            newNode->next = temp_next;
            temp_next->previous = newNode;
            if(DEBUG){printf("added node to the left in cache\n");}

        }
        return;
    }

}

void delete(struct DLLNode **head, int location_mem){

    struct DLLNode *temp = *head;
    struct DLLNode *temp_prev;
    struct DLLNode *temp_next;

    if(isCacheEmpty(head)){ //case where we don't have anything in the cache
        printf("Nothing to delete as cache is empty\n");
        return;
    }

    int len = length(head);

    for(int i=0; i<len; i++){
        if(DEBUG){printf("getting into the for loop with temp mem value: %d and ideal deletion memory: %d\n", temp->memory_location, location_mem);}
        if(temp->memory_location == location_mem){
            //this memory location has already been cached in this cache and can be deleted
            if(DEBUG){printf("before temp manipulation and temp mem value: %d\n", temp->memory_location);}
            temp_next = temp->next;
            temp_prev = temp->previous;
            if(temp_next == NULL & temp_prev == NULL){ //case where we only have one node in the linked list
                *head = NULL;
            }else if(temp_next == NULL){ //case where our deletion is at the end of the list
                temp_prev->next = NULL;
            }else if(temp_prev == NULL){ //case where our deletion is at the beginning of the list
                *head = temp_next;
                temp_next->previous = NULL;
            }else{ //case where the node is in the middle somewhere
                temp_prev->next = temp_next;
                temp_next->previous = temp_prev;
            }
            if(DEBUG){printf("attempted to delete\n");}
        }else{
            //this memory location has not been cached in this cache
            if(DEBUG){printf("got into the else of deletion");}
            temp_prev = temp;
            temp = temp->next;
            if(DEBUG){printf("not yet made it to the right node yet for deletion\n");}
        }
    }
}

//Use this function to check the status of a certain memory location in a certain cache
status_t checkStatus(struct DLLNode **head, int location_mem){
    struct DLLNode *temp = *head;
    
    if(isCacheEmpty(head)){ //case where we don't have anything in the cache
        printf("Cache is empty so no status can be checked\n");
    }else{

        int len = length(head);

        for(int i=0; i <len; i++){
            if(temp->memory_location == location_mem){
                return temp->status;
            }else{
                temp = temp->next;
            }
        }
    }
}

//Use this function if you want to check if a certain memory location is in a certain cache
bool checkMemInCache(struct DLLNode **head, int location_mem){
    struct DLLNode *temp = *head;
    
    if(isCacheEmpty(head)){ //case where we don't have anything in the cache
        printf("Cache is empty so Mem not in this cache\n");
    }else{
        int len = length(head);

        for(int i=0; i <len; i++){
            if(temp->memory_location == location_mem){
                return 1;
            }else{
                temp = temp->next;
            }
        }
    }
    return 0;
}


