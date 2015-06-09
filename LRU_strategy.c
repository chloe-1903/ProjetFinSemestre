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

int demo1, demo2; //Pour afficher les 5 premiers blocs et le 5 premiers blocs qu'on remplace (doivent être les mêmes) 

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
	//affiche(pcache);
    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
	Cache_List_Append(((struct Cache_List *)((pcache)->pstrategy)), pbh);
	//if (demo1++<5){
		//printf("bloc invalide : %p \n ", pbh);
	//}
	return pbh;
    }

    /* Sinon on prend le bloc utilisé le moins récement*/
    pbh=Cache_List_Remove_First(((struct Cache_List *)((pcache)->pstrategy)));
	//if (demo2++<5){
		//printf("bloc valide, on remplace: %p \n ", pbh );
	//}
    Cache_List_Append(((struct Cache_List *)((pcache)->pstrategy)), pbh);
    return pbh;
}
/*
void affiche(struct Cache *pcache){
  struct Cache_List *P= (struct Cache_List *)((pcache)->pstrategy);
  while (P !=NULL)
    {
      printf("%d \t",P->pheader->ibfile);
      P = P->next;
    }
}
*/

/*!
 * RAND : Rien à faire ici.
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
	Cache_List_Move_To_End(((struct Cache_List *)((pcache)->pstrategy)), pbh);
	//printf("Lecture de %p \n", pbh);
}  

/*!
 * RAND : Rien à faire ici.
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	Cache_List_Move_To_End(((struct Cache_List *)((pcache)->pstrategy)), pbh);
	//printf("Ecriture de %p \n", pbh);
} 

char *Strategy_Name()
{
    return "LRU";
}
