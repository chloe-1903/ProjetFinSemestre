#include <stdbool.h>
#include "cache_list.h"

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create(){
	struct Cache_List *cache_list= (struct Cache_List*)malloc(sizeof(struct Cache_List));//+1?
	cache_list->prev=cache_list->next= cache_list;
	cache_list->pheader=NULL;
	return cache_list; 
}

/*! Destruction d'une liste de blocs */
void Cache_List_Delete(struct Cache_List *list){
	struct Cache_List *cur=list;
	struct Cache_List *tmp;
	while (cur->next){
		tmp=cur->next;
		free(cur);
		cur=tmp;
	}
	free(cur);
}

/*! Insertion d'un élément à la fin */
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh){
	struct Cache_List *cur=list;
	struct Cache_List *tmp;
	while (cur=cur->next);
	struct Cache_List *element_to_add=Cache_List_Create();
	element_to_add->prev=cur;
	element_to_add->next=NULL;
	element_to_add->header=pbh;
	cur->next=element_to_add;
}

/*! Insertion d'un élément au début*/
void Cache_List_Prepend(struct Cache_List *list, struct Cache_Block_Header *pbh){
	struct Cache_List *element_to_add;
	element_to_add->prev=NULL;
	element_to_add->next=list;//ici, bug potentiel
	element_to_add->header=pbh;
}

/*! Retrait du premier élément */
struct Cache_Block_Header *Cache_List_Remove_First(struct Cache_List *list){

}

/*! Retrait du dernier élément */
struct Cache_Block_Header *Cache_List_Remove_Last(struct Cache_List *list){

}

/*! Retrait d'un élément quelconque */
struct Cache_Block_Header *Cache_List_Remove(struct Cache_List *list,
                                             struct Cache_Block_Header *pbh){

}

/*! Remise en l'état de liste vide */
void Cache_List_Clear(struct Cache_List *list){

}

/*! Test de liste vide */
bool Cache_List_Is_Empty(struct Cache_List *list){

}

/*! Transférer un élément à la fin */
void Cache_List_Move_To_End(struct Cache_List *list,
                            struct Cache_Block_Header *pbh){

}

/*! Transférer un élément  au début */
void Cache_List_Move_To_Begin(struct Cache_List *list,
                              struct Cache_Block_Header *pbh){

}
