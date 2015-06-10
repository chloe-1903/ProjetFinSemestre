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
    printf("%p\n", cache_list);
    Cache_List_Append(cache_list, headerTest);
    printf("%p\n", cache_list->next);
    Cache_List_Append(cache_list, headerTest);
    printf("%p\n", (cache_list->next)->next);    
    struct Cache_List *tmp;
    while (cache_list->next){
        tmp=cache_list->next;
        printf("Un parcours\n");
        cache_list=tmp;
    }
    return 0;
}