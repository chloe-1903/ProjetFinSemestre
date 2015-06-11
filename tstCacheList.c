#include "cache_list.h"
#include "cache_list.c"
#include "low_cache.h"
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    struct Cache_List *cache_list = Cache_List_Create();

    struct Cache_Block_Header *headerTest = (struct Cache_Block_Header*)malloc(sizeof(struct Cache_Block_Header));
    headerTest->ibfile = NULL;
    headerTest->ibcache = NULL;
    headerTest->data = NULL; 
    struct Cache_Block_Header *headerTest2 = (struct Cache_Block_Header*)malloc(sizeof(struct Cache_Block_Header));
    headerTest->ibfile = NULL;
    headerTest->ibcache = NULL;
    headerTest->data = NULL; 
    

    Cache_List_Prepend(cache_list, headerTest);
    Cache_List_Prepend(cache_list, headerTest2);
    Cache_List_Append(cache_list, headerTest2);
    printf("Liste: \n");
    Cache_List_Print(cache_list);
    

    printf("C'est parti pour REMOVE de  %p \n", headerTest);
    Cache_List_Remove(cache_list, headerTest);
    Cache_List_Print(cache_list);

   //printf("C'est parti pour un troisième REMOVE LAST\n");

    //Cache_List_Remove_Last(cache_list);
    //Cache_List_Print(cache_list);
    //printf("C'est parti pour un quatrième REMOVE LAST\n");

    //Cache_List_Remove_Last(cache_list);
    //Cache_List_Print(cache_list);
    //printf("C'est parti pour un cinquième REMOVE LAST\n");

    //Cache_List_Remove_Last(cache_list);
    //Cache_List_Print(cache_list);
    
    
    //~ Cache_List_Append(cache_list, headerTest);
    //~ Cache_List_Print(cache_list);
    //~ struct Cache_Block_Header *headerTest2 = (struct Cache_Block_Header*)malloc(sizeof(struct Cache_Block_Header));
    //~ headerTest2->ibfile = NULL;
    //~ headerTest2->ibcache = NULL;
    //~ headerTest2->data = NULL; 
    //~ Cache_List_Append(cache_list, headerTest2);
    //~ printf("Après le dernier ajout :\n");
    //~ Cache_List_Print(cache_list);
    
    //~ printf("\n\n PREPEND\n");
    //~ Cache_List_Prepend(cache_list,headerTest2);
    //~ Cache_List_Print(cache_list);
    
    
    //~ printf("\n\n REMOVE \n");
    //~ printf("\nAprès remove 1 : \n");
    //~ Cache_List_Remove(cache_list, headerTest2);
    //~ Cache_List_Print(cache_list);
    //~ 
    //~ printf("\nAprès remove 2 : \n");
    //~ Cache_List_Remove(cache_list, headerTest);
    //~ Cache_List_Print(cache_list);
    //~ 
    //~ printf("\nAprès remove 3 : \n");
    //~ Cache_List_Remove(cache_list, headerTest);
    //~ Cache_List_Print(cache_list);
    
    //~ free(headerTest);

    return 0;
}
