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
    printCacheContent(&Cache0);
    delete(&Cache0, c);
    length(&Cache0);
    printCacheContent(&Cache0);
  
    return;
}