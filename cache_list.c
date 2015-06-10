#include <stdbool.h>
#include <stdlib.h>
#include "cache_list.h"

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create(){
	struct Cache_List *cache_list= (struct Cache_List*)malloc(sizeof(struct Cache_List));//+1?

	cache_list->prev= NULL;
	cache_list->next= NULL;
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
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh) {
    if (Cache_List_Is_Empty(list)) {
        list->pheader = pbh;
        return;
    }
	struct Cache_List *cur=list;
	while (cur->next) cur = cur->next;
	struct Cache_List *element_to_add=Cache_List_Create();
	element_to_add->prev=cur;
	element_to_add->next=NULL;
	element_to_add->pheader=pbh;
	cur->next=element_to_add;
}

/*! Insertion d'un élément au début*/
void Cache_List_Prepend(struct Cache_List *list, struct Cache_Block_Header *pbh){
	struct Cache_List *element_to_add=Cache_List_Create();;
	element_to_add->prev=NULL;
	element_to_add->next=list;//ici, bug potentiel
	element_to_add->pheader=pbh;
    
    list->prev = element_to_add;
}

/*! Retrait du premier élément */
struct Cache_Block_Header *Cache_List_Remove_First(struct Cache_List *list){
    struct Cache_List *cur=list;
    struct Cache_List *second=cur->next;
    second->prev = NULL;
    //free(cur);
    return cur;
}

/*! Retrait du dernier élément */
struct Cache_Block_Header *Cache_List_Remove_Last(struct Cache_List *list){
    struct Cache_List *cur=list;
    while (cur->next) cur = cur->next;
    struct Cache_List *before_last=cur->prev;
    before_last->next=NULL;
    return cur;
}

/*! Retrait d'un élément quelconque */
struct Cache_Block_Header *Cache_List_Remove(struct Cache_List *list,
                                             struct Cache_Block_Header *pbh){
    struct Cache_List *cur=list;
    while (cur) {
        //printf("Current: %p \n", cur);
        if (cur->pheader == pbh) { 
            if (cur->prev) { // Si il a un précédent
                if(cur->next) { // Et qu'il a un suivant
                    ((cur->next)->prev) = cur->prev; // On peut le faire : CAS 4
                    ((cur->prev)->next) = cur->next; 
                } else { // Si il n'a pas de suivant (donc est le dernier de la liste) : CAS 2
                    ((cur->prev)->next) = NULL; // Le suivant de prev sera NULL
                }
                free(cur);
                return pbh;
            } else { // Si il n'a pas de précédent
                 if (cur->next) { // Si il a un suivant : CAS 1
                    ((cur->next)->prev) = NULL;
                    list = cur->next;
                    free(cur);
                    printf("LISTE : %p\n", list);
                    Cache_List_Print(list);
                    return pbh;
                } else {
                    cur->pheader = NULL; //On met son header à null
                    return pbh;
                }
            }
        }
        if (cur->next) cur = cur->next;
        else break;
    }
    // si on a pas trouvé l'élement
    return NULL;
}

/*! Remise en l'état de liste vide */
void Cache_List_Clear(struct Cache_List *list) {
    list->next = NULL; // lol
}

/*! Test de liste vide */
bool Cache_List_Is_Empty(struct Cache_List *list) {
    return (!list->next && !list->pheader);
}

/*! Transférer un élément à la fin */
void Cache_List_Move_To_End(struct Cache_List *list,
                            struct Cache_Block_Header *pbh) {
    struct Cache_List *cur=list;
    struct Cache_List *element_to_move = Cache_List_Remove(list,pbh);
    if (element_to_move) {
        while (cur->next) cur = cur->next;
        cur->next = element_to_move;
        element_to_move->prev = cur;
    }                      
}

/*! Transférer un élément  au début */
void Cache_List_Move_To_Begin(struct Cache_List *list,
                              struct Cache_Block_Header *pbh) {
    struct Cache_List *element_to_move = Cache_List_Remove(list,pbh);    
    list->prev = element_to_move;
    element_to_move->next=list;
}

/*! Afficher la cache liste entière */
void Cache_List_Print(struct Cache_List *list) {
    if (Cache_List_Is_Empty(list)) {
        printf("Elle est vide !\n");
        return;
    }
    struct Cache_List *cur=list;
    while (cur->next) {
        printf("%p\n",cur);
        cur = cur->next;
    }
    printf("%p\n",cur);
}
