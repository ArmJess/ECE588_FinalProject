#include <stdio.h>
#include "cache.h"

void main(){

    int a = 58;
    int b = 360;
    int c = 4556;

    struct DLLNode *Cache0 = NULL;
    struct DLLNode *Cache1 = NULL;
    struct DLLNode *Cache2 = NULL;
    struct DLLNode *Cache3 = NULL;

    insert(&Cache0, c, Modified);
    insert(&Cache0, c, Exclusive);
    insert(&Cache0, a, Exclusive);
    insert(&Cache0, b, Shared);
    insert(&Cache0, b, Invalid);

    length(&Cache0);
    printf("Status of b should be I (3), is it? %d\n", checkStatus(&Cache0, b));
    printCacheContent(&Cache0);
    printf("Is b in Cache0? %d, is it in Cache1? %d\n", checkMemInCache(&Cache0, b), checkMemInCache(&Cache1, b));
    delete(&Cache0, b);
    length(&Cache0);
    printCacheContent(&Cache0);
    printf("Empty? %d\n", isCacheEmpty(&Cache0));
    deleteCache(&Cache0);
    printf("Empty? %d\n", isCacheEmpty(&Cache0));
    printCacheContent(&Cache0);
  
    return;
}