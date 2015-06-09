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

int n_acces=0; //nombre d'accès depuis le dernier dereferencement

/*!
 * FIFO : pas grand chose à faire ici. 
 *
 * En fait, nous initialisons le germe
 * (seed) du générateur aléatoire à quelque chose d'éminemment variable, pour
 * éviter d'avoir la même séquence à chque exécution...
 */
void *Strategy_Create(struct Cache *pcache) 
{
    return Cache_List_Create();
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Close(struct Cache *pcache)
{
    Cache_List_Delete(((struct Cache_List *)((pcache)->pstrategy)));
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Invalidate(struct Cache *pcache)
{
    Cache_List_Clear(((struct Cache_List *)((pcache)->pstrategy)));
}

/*! 
 * FIFO : On prend le premier bloc invalide. S'il n'y en a plus, on prend un bloc au hasard.
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    struct Cache_Block_Header *pbh;
    struct Cache_Block_Header p;
    int i, num_bloc;
    int min=4;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
	//mettre V à 1?
	return pbh;
    }

    for (num_bloc = 0;  num_bloc < pcache->nblocks;  num_bloc++) {
	if ( (i=2*pcache->headers[num_bloc].flags & REF+ pcache->headers[num_bloc].flags & MODIF) < min){
		min=i;
		p=pcache->headers[num_bloc];
	}
    }
    return pbh;		
}

/*!
 * RAND : Rien à faire ici.
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
    printf("Incrémentation\n");
	n_acces++;
    printf("Deref\n");
	deref(pcache);
    printf("Opérateur chelou\n");
	pbh->flags |= REF;
    printf("Fini read");
}  

/*!
 * RAND : Rien à faire ici.
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	n_acces++;
	deref(pcache);
	//mettre M à 1?
	pbh->flags |= REF;
} 

void deref(struct Cache *pcache){
    printf("Début deref\n");
	int num_bloc;
	if (n_acces >= pcache->nderef){
        printf("Dans la condition deref\n");
		n_acces=0;
		for ( num_bloc = 0;  num_bloc < pcache->nblocks;  num_bloc++) 
            printf("Parcours bloc %p", pcache->headers[num_bloc]);
			pcache->headers[num_bloc].flags &= ~REF;
			
	}
	//incrémenter n_deref??
}
char *Strategy_Name()
{
    return "NUR";
}
