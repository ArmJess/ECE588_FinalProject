//Prototypes for the functions below are found in the cache.h header
#include "cache.h"

struct DLLNode *Cache0 = NULL; //Cache 1
struct DLLNode *Cache1 = NULL; //Cache 2
struct DLLNode *Cache2 = NULL; //Cache 3
struct DLLNode *Cache3 = NULL; //Cache 4

//Can use this array to printf user-friendly naming
const char* statusNames[] = {"Uninit","Modified", "Exclusive", "Shared", "Invalid"};

//All function code and definitions below
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
        printf("Mem location: %d in state: %s\n", temp->memory_location, statusNames[temp->status]);
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

    if(DEBUG){printf("Number of memory locations in cache: %d\n", length);}
    return length;

}

void deleteCache(struct DLLNode **head){
    *head = NULL;
}

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
            temp_prev = temp;
            temp = temp->next;
            if(temp==NULL){
                break;
            }
            if(DEBUG){printf("new temp memory after increment: %d\n", temp->memory_location);}
            if(DEBUG){printf("increment in cache\n");}
        }
        if(temp == NULL){
            //create and insert newNode to the right of temp - aka at the end of the linkedlist
            newNode = (struct DLLNode *) malloc(sizeof(struct DLLNode));
            if(!newNode){
                printf("Cache simulation: memory allocation error with DLLNode\n");
            }
            newNode->memory_location = location_mem;
            newNode->status = cache_status;
            newNode->next = NULL;
            temp_prev->next = newNode;
            newNode->previous = temp_prev;
            if(DEBUG){printf("added node to the right in cache\n");}
        }else if(temp->memory_location == location_mem){
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
            temp_next = temp;
            temp_prev = temp->previous;
            newNode->previous = temp_prev;
            if(temp_prev == NULL){
                *head = newNode;
            }else{
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

bool checkMemInCache(struct DLLNode **head, int location_mem){
    struct DLLNode *temp = *head;
    
    if(isCacheEmpty(head)){ //case where we don't have anything in the cache
        if(DEBUG){printf("Cache is empty so Mem not in this cache\n");}
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