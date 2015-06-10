#include "cache_list.h"
#include "cache_list.c"
#include "low_cache.h"
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    struct Cache_List *cache_list=Cache_List_Create();
    bool testEmpty = Cache_List_Is_Empty(cache_list);
    printf("%p\n", cache_list);
    printf(testEmpty ? "Liste vide\n" : "Liste non vide\n");
    struct Cache_Block_Header *headerTest;
    headerTest->ibfile = NULL;
    headerTest->ibcache = NULL;
    headerTest->data = NULL; 
    Cache_List_Append(cache_list, headerTest);
    testEmpty = Cache_List_Is_Empty(cache_list);
    printf("%p\n", cache_list);
    printf(testEmpty ? "Liste vide\n" : "Liste non vide\n");
    Cache_List_Append(cache_list, headerTest);
    printf("%p\n", (cache_list->next));    
    struct Cache_List *tmp;
    while (cache_list->next){
        tmp=cache_list->next;
        printf("Un parcours\n");
        cache_list=tmp;
    }
    return 0;
}