#include <stdbool.h>
#include <stdlib.h>
#include "cache_list.h"

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create() {
	struct Cache_List *cache_list = (struct Cache_List*) malloc(sizeof(struct Cache_List));//+1?
    /** On fait pointer next et prev sur lui même parce que circulaire */
	cache_list->prev = cache_list->next = cache_list;
    /** On initialise le header */
	cache_list->pheader=NULL;
	return cache_list;
}



/*! Destruction d'une liste de blocs */
void Cache_List_Delete(struct Cache_List *list) {
    struct Cache_List *bloc;
    if (!Cache_List_Is_Empty(list)) {
        for (bloc = list->next; bloc != list; bloc = bloc->next) {
            bloc->pheader    = NULL; // On met le header à NULL
            bloc->prev->next = bloc->next;  //le next du précédent devient le suivant de l'actuel
            bloc->next->prev = bloc->prev;  // le précédent du next devient le précédent de l'actuel
            free(bloc);                    //on free le bloc actuel
        }
    }
    bloc->pheader = NULL; //? je sais pas si on doit le metttre à null avant de free
    free(list);           // on free la list
}



/*! Insertion d'un élément à la fin */
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh) {
    if (Cache_List_Is_Empty(list)) {
        list->pheader = pbh;
        return;
    }
    /** On va jusqu'à la fin de la liste : tmp est le dernier élément de la liste */
    struct Cache_List *tmp = list->prev;
    
    /** Donc là tmp est le dernier bloc */
    struct Cache_List *element_to_add = Cache_List_Create();
    element_to_add->pheader = pbh;
    /** On fait la connexion de element_to_add */
    element_to_add->next = list;
    element_to_add->prev = tmp;
    /** On fait la connexion du premier element de la liste */
    list->prev = element_to_add;
    /** On fait la connexion de feu le dernier élement de la liste */
    tmp->next = element_to_add;
}






/*! Insertion d'un élément au début*/
void Cache_List_Prepend(struct Cache_List *list, struct Cache_Block_Header *pbh){
    struct Cache_List *element_to_add = Cache_List_Create(); // on crée un nouvel élément

    element_to_add->next = list->next;
    element_to_add->prev = list;
    element_to_add->pheader = list->pheader; // on met le header du nouvel élément à pbh
    
    list->pheader = pbh;

    struct Cache_List *first = list; // on récupère le second élément de la liste

    element_to_add->next     = first;      // le précédent du nouvel élément sera 
    first->prev->next = element_to_add;    // le dernier a son next sur le nouvel élément
    element_to_add->prev = first->prev;    // le précédent du nouveau est le dernier
    first->prev      = element_to_add ;     // le précédent de l'ancier premier est le nouveau
}






/*! Retrait du premier élément */
struct Cache_Block_Header *Cache_List_Remove_First(struct Cache_List *list){
    struct Cache_List *first=list;
    struct Cache_Block_Header *pbh= first->pheader;
    struct Cache_List *second= first->next;

    second->prev = first->prev;
    (first->prev)-> next = second;
    list= second;
    free(first);
    return pbh;
}

/*! Retrait du dernier élément */
struct Cache_Block_Header *Cache_List_Remove_Last(struct Cache_List *list){
    struct Cache_List *cur=list;
    while (cur->next!=list) cur = cur->next;

    struct Cache_Block_Header *pbh= cur->pheader;
    list->prev= cur;
    (cur->prev)->next=list;
    free(cur);

    return pbh;
}








/*! Retrait d'un élément quelconque */
struct Cache_Block_Header *Cache_List_Remove(struct Cache_List *list,
                                             struct Cache_Block_Header *pbh){
    struct Cache_List *cur=list;
    while (cur) {
        if (cur->pheader == pbh) {
            if (cur->prev) { // Si il a un précédent
                if (cur->next) { // Et qu'il a un suivant
                    printf("J'ai modifié un élement qui a un précédent et un suivant\n");
                    ((cur->next)->prev) = cur->prev;
                    ((cur->prev)->next) = cur->next; 
                } else { // Si il n'a pas de suivant
                    printf("J'ai modifié un élement qui a un précédent mais pas de suivant\n");
                    ((cur->prev)->next) = NULL; // Le suivant de prev sera NULL
                }
                free(cur);
                cur->pheader = NULL; //On met son header à null
                return pbh;
            } else { // Si il n'a pas de précédent
                if (cur->next) { // Si il a un suivant : CAS 1
                    printf("J'ai modifié un élement qui n'a pas de précédent mais a un suivant\n");
                    ((cur->next)->prev) = NULL;
                    
                } else {
                    printf("J'ai modifié un élement qui a ni précédent ni suivant\n");
                    list->prev = NULL;
                    list->next = NULL;
                }
                cur->pheader = NULL; //On met son header à null
                free(cur);
                /**list=cur->next;*/
                
                return pbh;
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
    return (list->next==list && list->prev==list && !list->pheader);
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
    
    if (list == NULL) { printf("Cette liste est NULL\n"); }
    
    struct Cache_List *tmp = list;
    while (tmp->next != list) {
        printf("%p , header : %p\n",tmp,tmp->pheader);
        tmp = tmp->next;
    }
    printf("%p , header : %p\n",tmp,tmp->pheader);
}
