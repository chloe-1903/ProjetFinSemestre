#include "cache_list.h"
#include "cache_list.c"
#include "low_cache.h"

int main(int argc, char const *argv[])
{
    struct Cache_List *cache_list=Cache_List_Create();
    struct Cache_Block_Header *headerTest;
    headerTest->ibfile = NULL;
    headerTest->ibcache = NULL;
    headerTest->data = NULL; 
    Cache_List_Append(cache_list, headerTest);
    struct Cache_List *tmp;
    while (cache_list->next){
        tmp=cache_list->next;
        printf("Un parcours");
        cache_list=tmp;
    }
    return 0;
}