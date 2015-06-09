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
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Close(struct Cache *pcache)
{
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Invalidate(struct Cache *pcache)
{
	deref(pcache);
}

/*! 
 * FIFO : On prend le premier bloc invalide. S'il n'y en a plus, on prend un bloc au hasard.
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    struct Cache_Block_Header *pbh;
    int i, num_bloc;
    int min= 4;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
	//mettre V à 1?
	return pbh;
    }

    for (num_bloc = 0; num_bloc < pcache->nblocks; ++num_bloc)
    {       
        // Calcul de rm
        i = evaluate_RM(&pcache->headers[num_bloc]);
        if (0 == i)
            return &pcache->headers[num_bloc];
        else
        {
            if (min > i)
            {
                min = i;
                pbh = &pcache->headers[num_bloc];
            }
        }
    }
    return pbh;		
}

/*!
 * RAND : Rien à faire ici.
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
	//printf("Read %p \n", pbh);	
	n_acces++;
	deref(pcache);
	pbh->flags |= REF;
}  

/*!
 * RAND : Rien à faire ici.
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	//printf("Write %p \n", pbh);
	n_acces++;
	deref(pcache);
	//mettre M à 1?
	pbh->flags |= REF;
} 

void deref(struct Cache *pcache){
	int num_bloc;
	if (n_acces >= pcache->nderef){
       		//printf("Dans la condition deref\n");
		n_acces=0;
		//printf("Nb de blocs: %d" , pcache->nblocks);
		for ( num_bloc = 0;  num_bloc < pcache->nblocks;  num_bloc++) {
          		//printf("Parcours bloc %p", pcache->headers[num_bloc]);
			pcache->headers[num_bloc].flags &= ~REF;
		}
		++pcache->instrument.n_deref;
			
	}
	//incrémenter n_deref??
}

int evaluate_RM(struct Cache_Block_Header *bloc)
{
    int rm = 0;
    if ((bloc->flags & REF) > 0) rm += 2;
    if ((bloc->flags & MODIF) > 0) rm += 1;

    return rm;
}

char *Strategy_Name()
{
    return "NUR";
}
