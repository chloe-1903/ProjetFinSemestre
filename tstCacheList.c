#include "cache_list.h"
#include "cache_list.c"
#include "low_cache.h"
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    struct Cache_List *cache_list=Cache_List_Create();
    bool testEmpty = Cache_List_Is_Empty(cache_list);

    Cache_List_Print(cache_list);
    printf(testEmpty ? "Liste vide\n" : "Liste non vide\n");
    struct Cache_Block_Header *headerTest = (struct Cache_Block_Header*)malloc(sizeof(struct Cache_Block_Header));
    headerTest->ibfile = NULL;
    headerTest->ibcache = NULL;
    headerTest->data = NULL; 
    Cache_List_Append(cache_list, headerTest);
    testEmpty = Cache_List_Is_Empty(cache_list);
    Cache_List_Print(cache_list);
    printf(testEmpty ? "Liste vide\n" : "Liste non vide\n");
    Cache_List_Append(cache_list, headerTest);
    Cache_List_Print(cache_list);
    struct Cache_Block_Header *headerTest2 = (struct Cache_Block_Header*)malloc(sizeof(struct Cache_Block_Header));
    headerTest2->ibfile = NULL;
    headerTest2->ibcache = NULL;
    headerTest2->data = NULL; 
    Cache_List_Append(cache_list, headerTest2);
    printf("Après le dernier ajout :\n");
    Cache_List_Print(cache_list);
    printf("\n\n REMOVE \n");
    Cache_List_Remove(cache_list, headerTest2);
    Cache_List_Print(cache_list);
    printf("Après remove 1\n");
    Cache_List_Remove(cache_list, headerTest);
    Cache_List_Print(cache_list);
    printf("Après remove 2\n");
    Cache_List_Remove(cache_list, headerTest);
    Cache_List_Print(cache_list);
    printf("Après remove 3\n");
    free(headerTest);

    return 0;
}