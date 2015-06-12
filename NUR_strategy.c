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

int n_acces=0; //nombre d'accès (lecture/ecriture) depuis le dernier dereferencement


void *Strategy_Create(struct Cache *pcache) 
{
}

void Strategy_Close(struct Cache *pcache)
{
}


void Strategy_Invalidate(struct Cache *pcache)
{
	deref(pcache);
}


struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    struct Cache_Block_Header *pbh;
    int num_bloc;
    int min= 4;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
	return pbh;
    }

	/*Sinon*/
    for (num_bloc = 0; num_bloc < pcache->nblocks; ++num_bloc)
    {    
	int i=0;   
    	if ((pcache->headers[num_bloc].flags & REF) > 0) i += 2;
   	if ((pcache->headers[num_bloc].flags & MODIF) > 0) i += 1;

        if (i==0)
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
 * Augmenter le nombre d'accès depuis le dernier dereferençage puis mettre R à 1 et déréférence si besoin
 */  
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{	
	n_acces++;
	deref(pcache);
	pbh->flags |= REF;
}  

/*!
 * Augmenter le nombre d'accès depuis le dernier dereferençage puis mettre R à 1 et déréférence si besoin
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	n_acces++;
	deref(pcache);
	pbh->flags |= REF;
} 

/* Déréférence (met tous les R à 0) si le nombre d'accès depuis le dernier déréférençage est superieur à nderef */
void deref(struct Cache *pcache){
	int num_bloc;
	if (n_acces >= pcache->nderef){
		n_acces=0;
		for ( num_bloc = 0;  num_bloc < pcache->nblocks;  num_bloc++) {
			pcache->headers[num_bloc].flags &= ~REF;
		}
		++pcache->instrument.n_deref;
			
	}
}

char *Strategy_Name()
{
    return "NUR";
}
