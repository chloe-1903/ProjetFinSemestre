/*!
 * \file FIFO_strategy.c
 *
 * \brief  Stratégie de remplacement FIFO
 * 
 */

#include <assert.h>

#include "strategy.h"
#include "low_cache.h"
#include "time.h"

struct Cache_List *cache_list;

/*!
 * FIFO : pas grand chose à faire ici. 
 *
 * En fait, nous initialisons le germe
 * (seed) du générateur aléatoire à quelque chose d'éminemment variable, pour
 * éviter d'avoir la même séquence à chque exécution...
 */
void *Strategy_Create(struct Cache *pcache) 
{
   // cache_list= Cache_List_Create();
   
    cache_list =  (struct Cache_List *)((pcache)->pstrategy);

    return cache_list;
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Close(struct Cache *pcache)
{
    Cache_List_Delete(cache_list);
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Invalidate(struct Cache *pcache)
{
    Cache_Invalidate(pcache);
    Cache_List_Clear(cache_list);
}

/*! 
 * FIFO : On prend le premier bloc invalide. S'il n'y en a plus, on prend un bloc au hasard.
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    struct Cache_Block_Header *pbh;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
	Cache_List_Append(cache_list, pbh);
	return pbh;
    }

    /* Sinon on prend le bloc le plus vieux*/
    pbh=Cache_List_Remove_First(cache_list);
    Cache_List_Append(cache_list, pbh);
    return pbh;
}


/*!
 * RAND : Rien à faire ici.
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
}  

/*!
 * RAND : Rien à faire ici.
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
} 

char *Strategy_Name()
{
    return "FIFO";
}
